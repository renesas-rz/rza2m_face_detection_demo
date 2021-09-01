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
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_bcd_main.h
**********************************************************************************************************************/

/**********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
**********************************************************************************************************************/
#include <stdbool.h>

/**********************************************************************************************************************
Typedef definitions
**********************************************************************************************************************/

/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/
#ifndef R_BCD_MAIN_H
#define R_BCD_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum
{
	IPP_BAYER_2_GRAY_TOTAL,
	IPP_BAYER_2_GRAY_DL,
	IPP_BAYER_2_GRAY_EXE,
	IPP_RESIZE_FIXED_TOTAL,
	IPP_RESIZE_FIXED_DL,
	IPP_RESIZE_FIXED_EXE,
	IPP_FACE_DETECTION,
	IPP_RESIZE2_FIXED_TOTAL,
	IPP_FACE_DETECTION2,
	IPP_FACE_DETECTION3,
	IPP_CAMERA_FRAMERATE,
	IPP_TOTAL,
	IPP_INVALID,
}R_IMG_PROCESS_PROFILING;

/**********************************************************************************************************************
Variable Externs
**********************************************************************************************************************/

/**********************************************************************************************************************
Functions Prototypes
**********************************************************************************************************************/
void sample_main(void);

void R_BCD_MainBinarization2(uint32_t in_adr, uint32_t out_adr, uint32_t width, uint32_t height);
bool R_BCD_MainReedsolomon(int8_t * codewordBytes, uint8_t numCodewords, uint8_t numECCodewords);
void R_BCD_MainSetReedsolomonTime(uint32_t time);

#ifdef __cplusplus
}
#endif

#endif  /* R_BCD_MAIN_H */

/* End of File */
