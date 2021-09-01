/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name : r_spibsc_lld_rza2m_api.h
* $Rev: 761 $
* $Date:: 2018-12-10 21:52:47 +0900#$
* Description :
******************************************************************************/
#ifndef R_SPIBSC_RZA2_IF_H_
#define R_SPIBSC_RZA2_IF_H_

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_spibsc_lld_rza2m_reg.h"
#include "r_spibsc_sflash_userdef.h"
#include "driver.h"


/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/* Version Number of API */

#define STDIO_SPIBSC_RZ_LLD_DRV_NAME ("LLD EBK_RZA2M.SPIBSC")

/** Major Version Number of API */
#define STDIO_SPIBSC_RZ_LLD_VERSION_MAJOR      (1)
/** Minor Version Number of API */
#define STDIO_SPIBSC_RZ_LLD_VERSION_MINOR      (1)
/** Minor Version Number of API */
#define STDIO_SPIBSC_RZ_LLD_BUILD_NUM          (0)
/** Unique ID */
#define STDIO_SPIBSC_RZ_LLD_UID                (0)


typedef enum
{
    SPIBSC_FLASH_SPI = 0,
    SPIBSC_FLASH_OCTA,
    SPIBSC_FLASH_HYPER,

}e_spibsc_flash_type_t;

typedef enum
{
    SPIBSC_MODE_MANUAL = 0,
    SPIBSC_MODE_XIP,

}e_spibsc_mode_type_t;

typedef enum
{
    SPIBSC_PORT_VOLTAGE_3_3V = 0,
    SPIBSC_PORT_VOLTAGE_1_8V,

}e_spibsc_port_voltage_type_t;

typedef enum
{
    SPIBSC_CMNCR_BSZ_SINGLE = 0,
    SPIBSC_CMNCR_BSZ_DUAL,

}e_spibsc_flash_num_t;



typedef struct spibsc_manual_mode_command_config
{

/* --- IDENTIFIER --- */
    uint8_t command_name[20];           /* command identifier */

/* --- Command --- */
    uint8_t  cmd;                       /* Command code (8bit) */
    uint8_t  cmd_width;                 /* Command width */
    uint8_t  cmd_output_enable;         /* Command output setting */

/* --- Optional Command --- */
    uint8_t  ocmd;                      /* Optional command code (8bit) */
    uint8_t  ocmd_width;                /* Optional command width */
    uint8_t  ocmd_enable;               /* Optional command output setting */

/* --- Address --- */
    uint8_t  addr_width;                /* Address width */
    uint8_t  addr_output_enable;        /* Address output setting */
    uint8_t  addr_sdr_ddr;              /* Address SDR/DDR setting */


/* --- Option Data --- */
    uint8_t  opdata_width;              /* Option Data width */
    uint8_t  opdata_output_enable;      /* Option Data output setting */
    uint8_t  opdata_ddr_enable;         /* Option Data SDR/DDR setting */
    uint8_t  opd3;                      /* Option Data 3 (1st output) */
    uint8_t  opd2;                      /* Option Data 2 (2nd output) */
    uint8_t  opd1;                      /* Option Data 1 (3rd output) */
    uint8_t  opd0;                      /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
    uint8_t  reserve3;                  /* Reserve3(Fiexed 0) */
    uint8_t  dummy_cycle_output_enable; /* Dummy cycle output setting */
    uint8_t  dummy_cycle_count;         /* Dummy cycle Count */

/* --- Transfer Data --- */
    uint8_t  transfer_data_width;       /* Transfer Data  :  width */
    uint8_t  transfer_data_sdr_ddr;     /* Transfer Data  :  Transfer Data SDR/DDR setting */
	uint8_t  reserve1;                  /* Reserve1(Fiexed 0) */
    uint8_t  reserve2;                  /* Reserve2(Fiexed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
    uint8_t cmncr_moiio3;               /* Set the output level of QSPIn_IO3 at SSL negation */
    uint8_t cmncr_moiio2;               /* Set the output level of QSPIn_IO2 at SSL negation */
    uint8_t cmncr_moiio1;               /* Set the output level of QSPIn_IO1 at SSL negation */
    uint8_t cmncr_moiio0;               /* Set the output level of QSPIn_IO0 at SSL negation */
    uint8_t cmncr_io3fv;                /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
    uint8_t cmncr_io2fv;                /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
    uint8_t cmncr_io0fv;                /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

} st_spibsc_manual_mode_command_config_t;


typedef struct spibsc_xip_config
{

/* --- IDENTIFIER --- */
    uint8_t command_name[20];      /* command identifier */

/* --- Command --- */
    uint8_t  cmd;                  /* Command code (8bit) */
    uint8_t  cmd_width;            /* Command width */
    uint8_t  cmd_output_enable;    /* Command output setting */

/* --- Optional Command --- */
    uint8_t  ocmd;                 /* Optional command code (8bit) */
    uint8_t  ocmd_width;           /* Optional command width */
    uint8_t  ocmd_output_enable;   /* Optional command output setting */

/* --- Address --- */
    uint8_t  addr_width;           /* Address width */
    uint8_t  addr_output_enable;   /* Address output setting  */
    uint8_t  addr_ddr_enable;      /* Address SDR/DDR setting */
	uint8_t  reserve1;             /* Reserve1(Fixed 0) */
	uint8_t  reserve2;             /* Reserve2(Fixed 0) */


/* --- Option Data --- */
    uint8_t  opdata_width;         /* Option Data width */
    uint8_t  opdata_output_enable; /* Option Data output setting */
    uint8_t  opdata_ddr_enable;    /* Option Data SDR/DDR setting */
    uint8_t  opd3;                 /* Option Data 3 (1st output) */
    uint8_t  opd2;                 /* Option Data 2 (2nd output) */
    uint8_t  opd1;                 /* Option Data 1 (3rd output) */
    uint8_t  opd0;                 /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
    uint8_t  reserve3;             /* Reserve3(Fiexed 0) */
    uint8_t  dummy_cycle_enable;   /* Dummy cycle output setting */
    uint8_t  dummy_cycle_count;    /* Dummy cycle Count */

/* --- Transfer Data --- */
    uint8_t  data_width;           /* Transfer Data width */
    uint8_t  data_ddr_enable;      /* Transfer Data SDR/DDR setting */

/* --- QSPIn_IO0-3 output level Data --- */
    uint8_t cmncr_moiio3;          /* Set the output level of QSPIn_IO3 at SSL negation */
    uint8_t cmncr_moiio2;          /* Set the output level of QSPIn_IO2 at SSL negation */
    uint8_t cmncr_moiio1;          /* Set the output level of QSPIn_IO1 at SSL negation */
    uint8_t cmncr_moiio0;          /* Set the output level of QSPIn_IO0 at SSL negation */
    uint8_t cmncr_io3fv;           /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
    uint8_t cmncr_io2fv;           /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
    uint8_t cmncr_io0fv;           /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

} st_spibsc_xip_config_t;





/******************************************************************************
Variable Externs
******************************************************************************/


/******************************************************************************
Functions Prototypes
******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**
 * @brief      R_SPIBSC_Init
 *
 *             SPIBSC initial setting
 *
 *
 * @param[in]  p_spibsc_config_tbl:  Pointer to SPIBSC initial setting table
 *
 *
 * @retval     SPIBSC_SUCCESS   Successful operation.
 *
 */
extern e_spibsc_err_t R_SPIBSC_Init( const st_spibsc_config_t  *spibsc_config_tbl );
/**
 * @brief      R_SPIBSC_SPICMDIssue
 *
 *             Issuing SPI command to serial flash memory (for manual mode)
 *
 *
 * @param[in]  table_no:      table number
 * @param[in]  addr:          address
 * @param[in]  p_write_buff:  write buffer pointer
 * @param[in]  write_size:    write byte size
 * @param[out] p_read_buff:   read buffer pointer
 * @param[in]  read_size:     read byte size
 *
 * @retval     SPIBSC_SUCCESS       Successful operation.
 * @retval     SPIBSC_ERR_INVALID   On failure
 */
extern e_spibsc_err_t R_SPIBSC_SPICMDIssue( uint8_t table_no, uint32_t addr, uint8_t *p_write_buff, int32_t write_size,
                                    uint8_t *p_read_buff, int32_t read_size);
/**
 * @brief      R_SPIBSC_ChangeMode
 *
 *             SPIBSC operation mode setting
 *
 *
 * @param[in]  mode:      operation mode\n
 *                        SPIBSC_MODE_MANUAL : manual mode\n
 *                        SPIBSC_MODE_XIP    : external address space read mode
 * @param[in]  sdr_ddr:   transfer format\n
 *                        SPIBSC_DDR_TRANSFER : DDR transfer\n
 *                        SPIBSC_SDR_TRANSFER : SDR transfer
 * @param[in]  table_no:  Command setting table number for external address space read mode\n
 *                        0: Select command setting table 0 (DDR read command)\n
 *                        1: Select command setting table 1 (SDR read command)
 *
 *
 */
extern void R_SPIBSC_ChangeMode(uint8_t mode, uint8_t sdr_ddr, uint8_t table_no);
/**
 * @brief          R_SPIBSC_GetVersion
 *                 Obtains driver specific version information which is used for
 *                 reporting
 * @param[out]     p_ver_info: driver version information is populated into
 *                               this structure
 *                               @note the structure resources are created by
 *                                     the application not this function.
 * @retval         DRV_SUCCESS  Successful operation (always)
 */
extern int_t R_SPIBSC_GetVersion(st_ver_info_t *p_ver_info);
/**
 * @brief      R_SPIBSC_AdjustPhy
 *
 *             Calibration of SPIBSC data acquisition timing
 *
 *
 * @retval     SPIBSC_SUCCESS        Successful operation.
 * @retval     SPIBSC_ERR_INVALID    On failure
 */
extern e_spibsc_err_t R_SPIBSC_AdjustPhy(void);
/**
 * @brief      R_SPIBSC_FlushReadCache
 *
 *             Clear SPIBSC read cache
 *
 *
 */
extern void R_SPIBSC_FlushReadCache(void);
/**
 * @brief      R_SPIBSC_XipStopAccess
 *
 *             Stop access to serial flash memory
 *
 *
 */
extern void R_SPIBSC_XipStopAccess(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* R_SPIBSC_RZA2_IF_H_ */

/* End of File */
