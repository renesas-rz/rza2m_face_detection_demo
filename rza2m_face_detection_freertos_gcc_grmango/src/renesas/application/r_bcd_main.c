/**********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
* THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

/**********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
**********************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#include "r_typedefs.h"
#include "iodefine.h"
#include "r_cache_lld_rza2m.h"
#include "r_bcd_ae.h"
#include "r_bcd_camera.h"
#include "r_bcd_lcd.h"
#include "draw.h"
#include "perform.h"
#include "picornt.h"
#include "r_dk2_if.h"
#include "r_drp_simple_isp_2_tiles.h"
#include "r_drp_resize_bilinear_fixed.h"
#include "r_mmu_lld_rza2m.h"

/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/
#define TILE_0          (0)
#define TILE_1          (1)
#define TILE_2          (2)
#define TILE_3          (3)
#define TILE_4          (4)
#define TILE_5          (5)

#define DRP_NOT_FINISH  (0)
#define DRP_FINISH      (1)

#define DRP_DRV_ASSERT(x) if ((x) != 0) return

#define SCREEN_MESSAGE_LINE_BUF_SIZE       (64)

/* Key status */
#define KEY_STAUS_INIT  (0x00000000U)
#define KEY_CHECK_BIT   (0x00000003U)
#define KEY_JUST_ON     (0x00000002U)
#define KEY_ON_KEEP     (0x00000000U)

/**********************************************************************************************************************
Imported global variables and functions (from other files)
**********************************************************************************************************************/
extern uint8_t g_drp_lib_isp_face_detection[];
extern uint8_t g_drp_lib_resize_bilinear_fixed[];
extern uint32_t g_camera_vsync_us;

/**********************************************************************************************************************
Private global variables and functions
*******************************************************************************/
static const char* g_version = "Version: 2.2.0";
static r_drp_simple_isp_2_tiles_t param_isp_fd[3] __attribute__ ((section("UNCACHED_BSS")));
static r_drp_resize_bilinear_fixed_t param_resize_fixed __attribute__ ((section("UNCACHED_BSS")));
static uint8_t screen_str_buf[SCREEN_MESSAGE_LINE_BUF_SIZE];
static uint8_t resize_buffer[(R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) / 4] __attribute__ ((section("Video_RAM")));
static uint8_t resize_buffer1[(R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) / 16] __attribute__ ((section("Video_RAM")));


/* use ae */
static uint8_t  look_up_table[256] __attribute__ ((section("UNCACHED_BSS")));
static uint32_t ave_result[3][3] __attribute__ ((section("UNCACHED_BSS")));

static uint8_t drp_lib_id[R_DK2_TILE_NUM] = {0};
static volatile uint8_t drp_lib_status[R_DK2_TILE_NUM] = {DRP_NOT_FINISH};
static r_bcd_ae_setting_t ae_setting;

/* key status */
static uint32_t key3_status;
static uint32_t key4_status;

/* face detection*/
#define MAXNDETECTIONS (100)

typedef struct {
	uint8_t*			pbuf;
	uint16_t		width;
	uint16_t		height;
}PYT_MEM_ST;

typedef struct
{
	int x0;
	int y0;
	int x1;
	int y1;
}R_RECT_ST;


typedef enum
{
	DM_FACE,
	DM_MASK,
	DM_FACE_MASK,
	DM_INVALID,
}R_DETECTION_MODE;

typedef struct
{
	int minsize;
	int maxsize;
	float angle;
	float scalefactor;
	float stridefactor;
	float qthreshold;
	int usepyr;
	int noclustering;
	int verbose;
}R_DETECTION_PARAM;

float rcsq[4*MAXNDETECTIONS];
float rcsq_mask[4*MAXNDETECTIONS];
PYT_MEM_ST g_pyr[2];
int facedetections;
int maskdetections;
R_DETECTION_MODE g_detection_mode = DM_FACE_MASK;
R_DETECTION_PARAM g_detection_param;

extern uint8_t g_cascade[];
extern uint8_t g_cascade_mask[];
static void cb_drp_finish(uint8_t id);

/**********************************************************************************************************************
* Function Name: cb_drp_finish
* Description  : This function is a callback function called from the
*              : DRP driver at the finish of the DRP library processing.
* Arguments    : id
*              :   The ID of the DRP library that finished processing.
* Return Value : -
**********************************************************************************************************************/
static void cb_drp_finish(uint8_t id)
{
    uint32_t tile_no;

    /* Change the operation state of the DRP library notified by the argument to finish */
    for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
    {
        if (drp_lib_id[tile_no] == id)
        {
            drp_lib_status[tile_no] = DRP_FINISH;
            break;
        }
    }

    return;
}


static void clip_rect(uint16_t x0, uint16_t y0, uint16_t w0, uint16_t h0,
					  uint16_t x1, uint16_t y1, uint16_t w1, uint16_t h1,
					  uint16_t *x2, uint16_t *y2, uint16_t *w2, uint16_t *h2)
{
	if (y1 >= y0 + h0 || y1 + h1 < y0)
	{
		*x2 = 0; *y2 = 0; *w2 = 0; *h2 = 0;
		return;
	}

	if (y1 >= y0)
	{
		*x2 = x1;
		*y2 = y1 - y0;
		*w2 = w1;
		*h2 = (y1 + h1 > y0 + h0) ? (y1 + h1 - (y0 + h0)) : h1;
	}
	else
	{
		*x2 = x1;
		*y2 = 0;
		*w2 = w1;
		*h2 = (y1 + h1 > y0 + h0) ? h0 : (y1 + h1 - y0);
	}
}

/*******************************************************************************
* Function Name: bayer2gray_drp
* Description  : This function convery bayer image to gray image by DRP
* Arguments    : in_adr - bayer image buffer address
*                out_adr - gray image buffer address
*                width - image width
*                height - image height
* Return Value : - n/a
*******************************************************************************/
static void bayer2gray_drp(uint32_t in_adr, uint32_t out_adr, uint32_t width, uint32_t height
		,uint16_t area1_offsetx, uint16_t area1_offsety, uint16_t area1_w, uint16_t area1_h
		,uint16_t area2_offsetx, uint16_t area2_offsety, uint16_t area2_w, uint16_t area2_h
		,uint16_t area3_offsetx, uint16_t area3_offsety, uint16_t area3_w, uint16_t area3_h
						)
{
	int32_t ret_val;
	uint32_t tile_no = 0;

	if (height % 6 != 0)
		return;

    /******************************/
    /* Load DRP Library           */
    /*        +-----------------+ */
    /* tile 0 |IspBayer2Gray    | */
    /*        |                 | */
    /* tile 1 |                 | */
    /*        +-----------------+ */
    /* tile 2 |IspBayer2Gray    | */
    /*        |                 | */
    /* tile 3 |                 | */
    /*        +-----------------+ */
    /* tile 4 |IspBayer2Gray    | */
    /*        |                 | */
    /* tile 5 |                 | */
    /*        +-----------------+ */
    /******************************/
	PerformSetStartTime(IPP_BAYER_2_GRAY_DL);
	ret_val = R_DK2_Load(&g_drp_lib_isp_face_detection[0],
						 R_DK2_TILE_0 | R_DK2_TILE_2 | R_DK2_TILE_4,
						 R_DK2_TILE_PATTERN_2_2_2, NULL, &cb_drp_finish, &drp_lib_id[0]);
	DRP_DRV_ASSERT(ret_val);
	ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_2] | drp_lib_id[TILE_4], 0);
	DRP_DRV_ASSERT(ret_val);
	PerformSetEndTime(IPP_BAYER_2_GRAY_DL);

	PerformSetStartTime(IPP_BAYER_2_GRAY_EXE);


	for (tile_no = 0; tile_no < 3; tile_no++)
	{
		R_MMU_VAtoPA((uint32_t)(in_adr + (width * (height / 3)*tile_no)), &(param_isp_fd[tile_no].src));
		R_MMU_VAtoPA((uint32_t)(out_adr+ (width * (height / 3)*tile_no)), &(param_isp_fd[tile_no].dst));

		/* Set Image size */
		param_isp_fd[tile_no].width = width;
		param_isp_fd[tile_no].height = height/3;
		R_MMU_VAtoPA((uint32_t)&ave_result[tile_no], &(param_isp_fd[tile_no].accumulate));

		clip_rect(0, tile_no*param_isp_fd[tile_no].height, width, param_isp_fd[tile_no].height,
				area1_offsetx, area1_offsety, area1_w, area1_h,
				(uint16_t*)&param_isp_fd[tile_no].area1_offset_x, (uint16_t*)&param_isp_fd[tile_no].area1_offset_y, (uint16_t*)&param_isp_fd[tile_no].area1_width, (uint16_t*)&param_isp_fd[tile_no].area1_height);


		clip_rect(0, tile_no*param_isp_fd[tile_no].height, width, param_isp_fd[tile_no].height,
						area2_offsetx, area2_offsety, area2_w, area2_h,
						(uint16_t*)&param_isp_fd[tile_no].area2_offset_x, (uint16_t*)&param_isp_fd[tile_no].area2_offset_y, (uint16_t*)&param_isp_fd[tile_no].area2_width, (uint16_t*)&param_isp_fd[tile_no].area2_height);

		clip_rect(0, tile_no*param_isp_fd[tile_no].height, width, param_isp_fd[tile_no].height,
						area3_offsetx, area3_offsety, area3_w, area3_h,
						(uint16_t*)&param_isp_fd[tile_no].area3_offset_x, (uint16_t*)&param_isp_fd[tile_no].area3_offset_y, (uint16_t*)&param_isp_fd[tile_no].area3_width, (uint16_t*)&param_isp_fd[tile_no].area3_height);

		/* Initialize variables to be used in termination judgment of the DRP library */
		drp_lib_status[tile_no] = DRP_NOT_FINISH;

		/*********************/
		/* Start DRP Library */
		/*********************/
		ret_val = R_DK2_Start(drp_lib_id[2*tile_no], (void *)&param_isp_fd[tile_no], sizeof(param_isp_fd[tile_no]));
		DRP_DRV_ASSERT(ret_val);
	}

    /***************************************/
    /* Wait until DRP processing is finish */
    /***************************************/
	for (tile_no = 0; tile_no < 3; tile_no++)
	{
		while (drp_lib_status[2*tile_no] == DRP_NOT_FINISH);
	}
	ave_result[0][0] = ave_result[0][0] + ave_result[1][0] + ave_result[2][0];
	ave_result[0][1] = ave_result[0][1] + ave_result[1][1] + ave_result[2][1];
	ave_result[0][2] = ave_result[0][2] + ave_result[1][2] + ave_result[2][2];

	/**********************/
	/* Unload DRP Library */
	/**********************/
	ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_2] | drp_lib_id[TILE_4], &drp_lib_id[0]);
	DRP_DRV_ASSERT(ret_val);

	PerformSetEndTime(IPP_BAYER_2_GRAY_EXE);
//    TRACE_INFO("bayer2gray_drp end\r\n");

}
/*******************************************************************************
* End of function bayer2gray_drp
*******************************************************************************/

/*******************************************************************************
* Function Name: resize_fixed_drp
* Description  : This function resize gray image by DRP
* Arguments    : in_adr - gray image buffer address
*                out_adr - gray image buffer address
*                width - input image width
*                height - input image height
*                fx - Horizontal scale factor
*                fy - Vertical scale factor
* Return Value : - n/a
*******************************************************************************/
static void resize_fixed_drp(uint32_t in_adr, uint32_t out_adr, uint32_t width, uint32_t height, uint8_t fx, uint8_t fy)
{
	int32_t ret_val;

    /******************************/
    /* Load DRP Library           */
    /*        +-----------------+ */
    /* tile 0 |Resize           | */
    /*        |                 | */
    /* tile 1 |                 | */
    /*        |                 | */
    /* tile 2 |                 | */
    /*        |                 | */
    /* tile 3 |                 | */
    /*        +-----------------+ */
    /* tile 4 |                 | */
    /*        |                 | */
    /* tile 5 |                 | */
    /*        +-----------------+ */
    /******************************/

	PerformSetStartTime(IPP_RESIZE_FIXED_DL);
    ret_val = R_DK2_Load(&g_drp_lib_resize_bilinear_fixed[0],
                         R_DK2_TILE_0,
						 R_DK2_TILE_PATTERN_4_2, NULL, &cb_drp_finish, &drp_lib_id[0]);
    DRP_DRV_ASSERT(ret_val);
    ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
    DRP_DRV_ASSERT(ret_val);
    PerformSetEndTime(IPP_RESIZE_FIXED_DL);

    PerformSetStartTime(IPP_RESIZE_FIXED_EXE);
    R_MMU_VAtoPA((uint32_t)in_adr, &(param_resize_fixed.src));
    R_MMU_VAtoPA((uint32_t)out_adr, &(param_resize_fixed.dst));
    /* Set Image size */
    param_resize_fixed.src_width = width;
    param_resize_fixed.src_height = height;
    param_resize_fixed.fx = fx;
    param_resize_fixed.fy = fy;

    /* Initialize variables to be used in termination judgment of the DRP library */
    drp_lib_status[TILE_0] = DRP_NOT_FINISH;

    /*********************/
    /* Start DRP Library */
    /*********************/
    ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_resize_fixed, sizeof(param_resize_fixed));
    DRP_DRV_ASSERT(ret_val);

    /***************************************/
    /* Wait until DRP processing is finish */
    /***************************************/
    while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);

    /* Set end time of process */
    //PerformSetEndTime(IPP_BAYER_2_GRAY);

	/**********************/
	/* Unload DRP Library */
	/**********************/
	ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[0]);
	DRP_DRV_ASSERT(ret_val);

	PerformSetEndTime(IPP_RESIZE_FIXED_EXE);
//    TRACE_INFO("bayer2gray_drp end\r\n");

}
/*******************************************************************************
* End of function resize_fixed_drp
*******************************************************************************/

static void face_detection(uint8_t *img, uint16_t w, uint16_t h)
{
	static int bInitPyr = 0;
	int i, j;
	
	facedetections = 0;
	maskdetections = 0;

	if(!bInitPyr)
	{
		bInitPyr = 1;

		g_pyr[0].pbuf = img;
		g_pyr[0].width = w;
		g_pyr[0].height = h;

		if (g_detection_param.usepyr)
		{
			g_pyr[1].pbuf = (uint8_t*)resize_buffer1;
			g_pyr[1].width = w>>1;
			g_pyr[1].height = h>>1;
		}
	}

	// perform detection with the pico library
	memset((uint8_t*)rcsq, 0, 4*MAXNDETECTIONS*sizeof(float));
	memset((uint8_t*)rcsq_mask, 0, 4*MAXNDETECTIONS*sizeof(float));

	if (g_detection_mode == DM_FACE || g_detection_mode == DM_FACE_MASK)
	{
		int nd = 0;
		//TRACE_INFO("process image from 0x%x\r\n",pixels);
		facedetections = find_objects(rcsq, MAXNDETECTIONS, g_cascade, g_detection_param.angle, g_pyr[0].pbuf, g_pyr[0].height, g_pyr[0].width, g_pyr[0].width, g_detection_param.scalefactor, g_detection_param.stridefactor, g_detection_param.minsize, g_detection_param.maxsize);
		if (g_detection_param.usepyr)
		{
			PerformSetStartTime(IPP_FACE_DETECTION2);
			nd = find_objects(&rcsq[4*facedetections], MAXNDETECTIONS-facedetections, g_cascade, g_detection_param.angle, g_pyr[1].pbuf, g_pyr[1].height, g_pyr[1].width, g_pyr[1].width, g_detection_param.scalefactor, g_detection_param.stridefactor, g_detection_param.minsize>>1, g_detection_param.maxsize>>1);
			for(j=facedetections; j<facedetections+nd; ++j)
			{
				rcsq[4*j+0] = rcsq[4*j+0] * 2;
				rcsq[4*j+1] = rcsq[4*j+1] * 2;
				rcsq[4*j+2] = rcsq[4*j+2] * 2;
			}
			facedetections += nd;
			PerformSetEndTime(IPP_FACE_DETECTION2);
		}
		if(!g_detection_param.noclustering)
			facedetections = cluster_detections(rcsq, facedetections);
	}

	if (g_detection_mode == DM_MASK || g_detection_mode == DM_FACE_MASK)
	{
		int nd = 0;
		maskdetections = find_objects(rcsq_mask, MAXNDETECTIONS, g_cascade_mask, g_detection_param.angle, g_pyr[0].pbuf, g_pyr[0].height, g_pyr[0].width, g_pyr[0].width, g_detection_param.scalefactor, g_detection_param.stridefactor, g_detection_param.minsize, g_detection_param.maxsize);
		if (g_detection_param.usepyr)
		{
			PerformSetStartTime(IPP_FACE_DETECTION3);
			nd = find_objects(&rcsq_mask[4*maskdetections], MAXNDETECTIONS-maskdetections, g_cascade_mask, g_detection_param.angle, g_pyr[1].pbuf, g_pyr[1].height, g_pyr[1].width, g_pyr[1].width, g_detection_param.scalefactor, g_detection_param.stridefactor, g_detection_param.minsize>>1, g_detection_param.maxsize>>1);
			for(j=maskdetections; j<maskdetections+nd; ++j)
			{
				rcsq_mask[4*j+0] = rcsq_mask[4*j+0] * 2;
				rcsq_mask[4*j+1] = rcsq_mask[4*j+1] * 2;
				rcsq_mask[4*j+2] = rcsq_mask[4*j+2] * 2;
			}
			maskdetections += nd;
			PerformSetEndTime(IPP_FACE_DETECTION3);
		}
		if(!g_detection_param.noclustering)
			maskdetections = cluster_detections(rcsq_mask, maskdetections);


		//If face result are overlap with mask result, keep the face detection result
		for (i=0; i<facedetections; i++)
		{
			for (j=0; j< maskdetections; j++)
			{
				if (get_overlap(rcsq[4*i+0], rcsq[4*i+1], rcsq[4*i+2], rcsq_mask[4*j+0], rcsq_mask[4*j+1], rcsq_mask[4*j+2])>0.3f)
				{
					rcsq_mask[4*j+3] = 0.0f;

//					if (rcsq[4*i+3] >= rcsq_mask[4*j+3])
//					{
//						rcsq_mask[4*j+3] = 0.0f;
//					}
//					else
//					{
//						rcsq[4*i+3] = 0.0f;
//					}
				}
			}
		}
	}
}

static void draw_rcs_as_rect(float rcsq[], uint8_t color)
{
	R_RECT_ST rect;

	//TRACE_INFO("update display region [%d]\r\n", ndetections);
	rect.x0 = (rcsq[1] >= rcsq[2]/2) ? (int)(rcsq[1] - rcsq[2]/2) : 0;
	rect.x1 = ((rcsq[1] + rcsq[2]/2) >= R_BCD_LCD_WIDTH) ? R_BCD_LCD_WIDTH - 1 : (int)(rcsq[1] + rcsq[2]/2);
	rect.y0 = (rcsq[0] >= rcsq[2]/2) ? (int)(rcsq[0] - rcsq[2]/2) : 0;
	rect.y1 = ((rcsq[0] + rcsq[2]/2) >= R_BCD_LCD_HEIGHT) ? R_BCD_LCD_HEIGHT - 1 : (int)(rcsq[0] + rcsq[2]/2);

	//source image is resized
	rect.x0 *= 2;
	rect.x1 *= 2;
	rect.y0 *= 2;
	rect.y1 *= 2;

	DrawLine(VDC_LAYER_ID_2_RD,rect.x0,rect.y0,rect.x1,rect.y0,color);
	DrawLine(VDC_LAYER_ID_2_RD,rect.x0,rect.y0,rect.x0,rect.y1,color);
	DrawLine(VDC_LAYER_ID_2_RD,rect.x0,rect.y1,rect.x1,rect.y1,color);
	DrawLine(VDC_LAYER_ID_2_RD,rect.x1,rect.y0,rect.x1,rect.y1,color);
	//Double line width
	DrawLine(VDC_LAYER_ID_2_RD,rect.x0,rect.y0+1,rect.x1,rect.y0+1,color);
	DrawLine(VDC_LAYER_ID_2_RD,rect.x0+1,rect.y0,rect.x0+1,rect.y1,color);
	DrawLine(VDC_LAYER_ID_2_RD,rect.x0,rect.y1-1,rect.x1,rect.y1-1,color);
	DrawLine(VDC_LAYER_ID_2_RD,rect.x1-1,rect.y0,rect.x1-1,rect.y1,color);
}

static void show_rect_on_graphic(void)
{

	uint8_t color = YELLOW;
	int i;
	
	for(i=0; i<facedetections; ++i)
	{
		if(rcsq[4*i+3]>=g_detection_param.qthreshold) // check the confidence threshold
		{
			// if the `verbose` flag is set, print the results to standard output
//			if(g_detection_param.verbose)
//				TRACE_INFO("%d %d %d %f\r\n", (int)rcsq[4*i+0], (int)rcsq[4*i+1], (int)rcsq[4*i+2], rcsq[4*i+3]);
			draw_rcs_as_rect(&rcsq[4*i], YELLOW);
		}
	}
	for(i=0; i<maskdetections; ++i)
	{
		if(rcsq_mask[4*i+3]>=g_detection_param.qthreshold) // check the confidence threshold
		{
			// if the `verbose` flag is set, print the results to standard output
//			if(g_detection_param.verbose)
//				TRACE_INFO("%d %d %d %f\n", (int)rcsq_mask[4*i+0], (int)rcsq_mask[4*i+1], (int)rcsq_mask[4*i+2], rcsq_mask[4*i+3]);
			draw_rcs_as_rect(&rcsq_mask[4*i], GREEN);
		}
	}
}


/*******************************************************************************
* Function Name: sample_main
* Description  : First function called after initialization is completed
* Arguments    : -
* Return Value : -
**********************************************************************************************************************/
void sample_main(void)
{
    int32_t frame_buf_id;
    int32_t ret_val;
    uint32_t us;
    uint8_t * input_bufadr;
    uint8_t * output_bufadr;
    int32_t result;
    static int32_t fail_count = 0;
    uint32_t drp_gray_time, resize_time, face_detection_time;
    uint32_t drp_gray_time_dl, resize_time_dl;
    uint32_t resize2_time, face_detection2_time, face_detection3_time;
    uint32_t total_time;
    uint8_t frame_rate;

	// set face detection default parameters
	g_detection_param.minsize = (R_BCD_CAMERA_HEIGHT / 4) / 2 ;  // 1/4 camera input height
	g_detection_param.maxsize = (2 * R_BCD_CAMERA_HEIGHT / 3) / 2;   // 2/3 camera input height
//    g_detection_param.minsize = (R_BCD_CAMERA_HEIGHT / 6) / 2 ;  // 1/6 camera input height
//    g_detection_param.maxsize = (4 * R_BCD_CAMERA_HEIGHT / 5) / 2;   // 4/5 camera input height
	g_detection_param.angle = 0.0f;
	g_detection_param.scalefactor = 1.1f;
	g_detection_param.stridefactor = 0.1f;
	g_detection_param.qthreshold = 5.0f;
	g_detection_param.usepyr = 0;			//set to 1: detect face w/ different scaling size
	g_detection_param.noclustering = 0;
	g_detection_param.verbose = 1;

    /* VDC6 L2 Cache ON */
    PRR.AXIBUSCTL6.BIT.VDC601ARCACHE = 0xF;
    PRR.AXIBUSCTL6.BIT.VDC602ARCACHE = 0xF;
    PRR.AXIBUSCTL7.BIT.VDC604ARCACHE = 0xF;

    /* DRP L2 Cache ON */
    PRR.AXIBUSCTL4.BIT.DRPARCACHE = 0xF;
    PRR.AXIBUSCTL4.BIT.DRPAWCACHE = 0xF;

    /* Initialization of VIN and MIPI driver */
    R_BCD_CameraInit();

    /* Initialization of LCD driver */
    R_BCD_LcdInit();

    /* Set SW4 readable */
    PORT5.PMR.BIT.PMR6 = 0;
    PORT5.PDR.BIT.PDR6 = 2;

    /* Capture Start */
    R_BCD_CameraClearCaptureStatus();
    R_BCD_CameraCaptureStart();

    /* Initialize of Performance counter */
    PerformInit();

    /********************************/
    /* Initialization of DRP driver */
    /********************************/
    R_DK2_Initialize();

    R_BCD_AeInit(&ae_setting);
    R_BCD_AeMakeGammaTable(&ae_setting, (double)1.2, look_up_table);
    //R_BCD_AeStop(&ae_setting);

    /* Key initialize */
    key3_status = KEY_STAUS_INIT;
    key4_status = KEY_STAUS_INIT;

    /* main loop */
    while (1)
    {

    	/* Get User Switch0 (SW2) key */
		key3_status = (key3_status << 1) | PORTD.PIDR.BIT.PIDR6;
		if ( ( key3_status & KEY_CHECK_BIT) == KEY_JUST_ON )
		{
	       	switch (g_detection_mode)
	        	{
	        	case DM_FACE:
	        		g_detection_mode = DM_MASK;
	        		break;
	        	case DM_MASK:
	        		g_detection_mode = DM_FACE_MASK;
	        		break;
	        	case DM_FACE_MASK:
	        		g_detection_mode = DM_FACE;
	        		break;
	        	default:
	        		break;
	        	}

		}

		/* Get User Switch1 (SW3) key */
		key4_status = (key4_status << 1) | PORTD.PIDR.BIT.PIDR7;
		if ( ( key4_status & KEY_CHECK_BIT) == KEY_JUST_ON )
		{

		}

        /* Wait until camera capture is complete */
        while ((frame_buf_id = R_BCD_CameraGetCaptureStatus()) == R_BCD_CAMERA_NOT_CAPTURED)
        {
            /* DO NOTHING */
        }

        PerformSetStartTime(IPP_TOTAL);

        input_bufadr  = R_BCD_CameraGetFrameAddress(frame_buf_id);
        output_bufadr = R_BCD_LcdGetVramAddress();

        PerformSetStartTime(IPP_BAYER_2_GRAY_TOTAL);
        bayer2gray_drp((uint32_t)input_bufadr,(uint32_t)output_bufadr,R_BCD_CAMERA_WIDTH,R_BCD_CAMERA_HEIGHT,
        		150,150,R_BCD_CAMERA_WIDTH-150,R_BCD_CAMERA_HEIGHT-150,
				50,50,R_BCD_CAMERA_WIDTH-50,R_BCD_CAMERA_HEIGHT-50,
				0,0,R_BCD_CAMERA_WIDTH,R_BCD_CAMERA_HEIGHT);
        PerformSetEndTime(IPP_BAYER_2_GRAY_TOTAL);

        PerformSetStartTime(IPP_RESIZE_FIXED_TOTAL);
        resize_fixed_drp((uint32_t)output_bufadr, (uint32_t)resize_buffer, R_BCD_CAMERA_WIDTH, R_BCD_CAMERA_HEIGHT, 0x20, 0x20);
        PerformSetEndTime(IPP_RESIZE_FIXED_TOTAL);

        if (g_detection_param.usepyr)
        {
            PerformSetStartTime(IPP_RESIZE2_FIXED_TOTAL);
            resize_fixed_drp((uint32_t)resize_buffer, (uint32_t)resize_buffer1, (R_BCD_CAMERA_WIDTH>>1), (R_BCD_CAMERA_HEIGHT>>1), 0x20, 0x20);
            PerformSetEndTime(IPP_RESIZE2_FIXED_TOTAL);
        }

        PerformSetStartTime(IPP_FACE_DETECTION);
		//face_detection(output_bufadr,R_BCD_CAMERA_WIDTH,R_BCD_CAMERA_HEIGHT);
        face_detection(resize_buffer,R_BCD_CAMERA_WIDTH>>1,R_BCD_CAMERA_HEIGHT>>1);
        PerformSetEndTime(IPP_FACE_DETECTION);

        //use region 2 (full screen) accumulation value
        R_BCD_AeRunAutoExpousure(&ae_setting, (uint16_t)(ave_result[0][2] / (R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT)));


        PerformSetEndTime(IPP_TOTAL);

        /* Clear the current capture state and enable the detection of the next capture completion */
        R_BCD_CameraClearCaptureStatus();

		/* update display data on the LCD screen */

        R_BCD_LcdClearGraphicsBuffer();


        //r_show_hand_rect(output_bufadr);
        show_rect_on_graphic();

        memset(screen_str_buf,0,SCREEN_MESSAGE_LINE_BUF_SIZE);
        drp_gray_time = PerformGetElapsedTime_us(IPP_BAYER_2_GRAY_TOTAL);
        drp_gray_time_dl = PerformGetElapsedTime_us(IPP_BAYER_2_GRAY_DL);
        snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "bayer to gray DRP: %d.%03dms(DL:%d.%03dms)",
        		(int)(drp_gray_time/1000), (int)(drp_gray_time - ((drp_gray_time/1000) * 1000)),
				(int)(drp_gray_time_dl/1000), (int)(drp_gray_time_dl - ((drp_gray_time_dl/1000) * 1000)));
        R_BCD_LcdWriteString(&screen_str_buf[0], 0 + 2, 0 + 2, GREEN);

        memset(screen_str_buf,0,SCREEN_MESSAGE_LINE_BUF_SIZE);
        resize_time = PerformGetElapsedTime_us(IPP_RESIZE_FIXED_TOTAL);
        resize_time_dl = PerformGetElapsedTime_us(IPP_RESIZE_FIXED_DL);
        resize2_time = g_detection_param.usepyr ? PerformGetElapsedTime_us(IPP_RESIZE2_FIXED_TOTAL) : 0;

        if (g_detection_param.usepyr)
        {
			snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "resize DRP: %d.%03dms (%d.%03dms)",
					(int)((resize_time+resize2_time)/1000), (int)((resize_time+resize2_time) - ((resize_time+resize2_time)/1000)*1000),
					(int)(resize2_time/1000),  (int)(resize2_time - (int)(resize2_time - ((resize2_time/1000)*1000))));
        }
        else
        {
        	snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "resize DRP: %d.%03dms(DL:%d.%03dms)",
					(int)((resize_time+resize2_time)/1000), (int)((resize_time+resize2_time) - ((resize_time+resize2_time)/1000)*1000),
					(int)((resize_time_dl)/1000), (int)((resize_time_dl) - ((resize_time_dl)/1000)*1000));
        }
		R_BCD_LcdWriteString(&screen_str_buf[0], 0 + 2, 30 + 2, GREEN);

        memset(screen_str_buf,0,SCREEN_MESSAGE_LINE_BUF_SIZE);
        face_detection_time = PerformGetElapsedTime_us(IPP_FACE_DETECTION);
        if (g_detection_param.usepyr)
        {
        	face_detection2_time = PerformGetElapsedTime_us(IPP_FACE_DETECTION2) + (g_detection_mode > DM_FACE) ? PerformGetElapsedTime_us(IPP_FACE_DETECTION3) : 0;
        	snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "face detection: %d.%03dms (%d.%03dms)",
        			(int)((face_detection_time)/1000), (int)(face_detection_time - (face_detection_time/1000)*1000),
					(int)((face_detection2_time)/1000), (int)(face_detection2_time - (face_detection2_time/1000)*1000));
        }
        else
        {
        	snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "face detection: %d.%03dms",
        			(int)(face_detection_time/1000),  (int)(face_detection_time - ((face_detection_time/1000)*1000)));
        }
		R_BCD_LcdWriteString(&screen_str_buf[0], 0 + 2, 60 + 2, GREEN);

		memset(screen_str_buf,0,SCREEN_MESSAGE_LINE_BUF_SIZE);
		total_time = PerformGetElapsedTime_us(IPP_TOTAL);
		frame_rate = 1000000 / total_time;
		snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "process frame rate: %d fps (%d ms)",
				frame_rate,
				(int)(total_time/1000),  (int)(total_time - (int)(total_time - ((total_time/1000)*1000))));
		R_BCD_LcdWriteString(&screen_str_buf[0], 0 + 2, 90 + 2, GREEN);

		memset(screen_str_buf,0,SCREEN_MESSAGE_LINE_BUF_SIZE);
		if (g_detection_mode == DM_FACE)
		{
			snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "mode: face");
		}
		else if (g_detection_mode == DM_MASK)
		{
			snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "mode: mask");
		}
		else
		{
			snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "mode: face+mask");
		}
		R_BCD_LcdWriteString(&screen_str_buf[0], 0 + 2, 120 + 2, GREEN);

		memset(screen_str_buf,0,SCREEN_MESSAGE_LINE_BUF_SIZE);
		frame_rate = 1000000 / g_camera_vsync_us;
		snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, "Camera frame rate: %d fps (%d ms)",
				frame_rate,
				(int)(g_camera_vsync_us/1000),  (int)(g_camera_vsync_us - (int)(g_camera_vsync_us - ((g_camera_vsync_us/1000)*1000))));
		R_BCD_LcdWriteString(&screen_str_buf[0], 0 + 2, 150 + 2, GREEN);

		memset(screen_str_buf,0,SCREEN_MESSAGE_LINE_BUF_SIZE);
		snprintf(screen_str_buf, SCREEN_MESSAGE_LINE_BUF_SIZE, g_version);
		R_BCD_LcdWriteString(&screen_str_buf[0], 0 + 2, 180 + 2, GREEN);

        /* Write the data(buf) on the cache to physical memory */
        R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (GRAPHICS2_BUFFER_STRIDE * GRAPHICS2_BUFFER_HEIGHT));

        /* Display overlay buffer written processing time */
        R_BCD_LcdSwapGraphicsBuffer();
    }

sample_finish:

    return;
}
/**********************************************************************************************************************
* End of function sample_main
**********************************************************************************************************************/

/* End of File */
