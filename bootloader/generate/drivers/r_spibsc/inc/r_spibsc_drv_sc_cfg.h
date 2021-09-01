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
/******************************************************************************
* File Name    : r_spibsc_drv_sc_cfg.h
* $Rev: 702 $
* $Date:: 2018-10-30 08:49:19 +0900#$
* Description  : Initialize SPIBSC function header
******************************************************************************/

#ifndef R_SPIBSC_DRV_SC_CFG_H_
#define R_SPIBSC_DRV_SC_CFG_H_

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_spibsc_lld_rza2m_api.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/


/******************************************************************************
Variable Externs
******************************************************************************/



static const st_spibsc_manual_mode_command_config_t  gs_command_table[] =
{
    {
/* --- IDENTIFIER --- */
        "READ STATUS",                     /* command identifier */

/* --- Command --- */
        0x05,                              /* Command : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Command : width */
        SPIBSC_OUTPUT_ENABLE,              /* Command : output setting */

/* --- Optional Command --- */
        0x00,                              /* Optional command : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Optional command : width */
        SPIBSC_OUTPUT_DISABLE,             /* Optional command : output setting */

/* --- Address --- */
        SPIBSC_1BIT_WIDTH,                 /* Address : width */
        SPIBSC_OUTPUT_DISABLE,             /* Address : output setting */
        SPIBSC_SDR_TRANSFER,               /* Address : SDR/DDR setting */

/* --- Option Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Option Data : width */
        SPIBSC_OUTPUT_DISABLE,             /* Option Data : output setting */
        SPIBSC_SDR_TRANSFER,               /* Option Data : SDR/DDR setting */
        0x00,                              /* Option Data 3 (1st output) */
        0x00,                              /* Option Data 2 (2nd output) */
        0x00,                              /* Option Data 1 (3rd output) */
        0x00,                              /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
        0,                                 /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_DISABLE,             /* Dummy cycle : output setting */
        0,                                 /* Dummy cycle : Count(Fixed 0) */

/* --- Transfer Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Transfer Data : width */
        SPIBSC_SDR_TRANSFER,               /* Transfer Data : SDR/DDR setting */
        0,                                 /* Reserved1(Fixed 0) */
        0,                                 /* Reserved2(Fixed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
    {

/* --- IDENTIFIER --- */
        "READ CONFIGURATION",              /* command identifier */

/* --- Command --- */
        0x15,                              /* Command : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Command : width */
        SPIBSC_OUTPUT_ENABLE,              /* Command : output setting */

/* --- Optional Command --- */
        0x00,                              /* Optional command : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Optional command : width */
        SPIBSC_OUTPUT_DISABLE,             /* Optional command : output setting */

/* --- Address --- */
        SPIBSC_1BIT_WIDTH,                 /* Address : width */
        SPIBSC_OUTPUT_DISABLE,             /* Address : output setting */
        SPIBSC_SDR_TRANSFER,               /* Address : SDR/DDR setting */

/* --- Option Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Option Data width */
        SPIBSC_OUTPUT_DISABLE,             /* Option Data output setting */
        SPIBSC_SDR_TRANSFER,               /* Option Data SDR/DDR setting */
        0x00,                              /* Option Data 3 (1st output) */
        0x00,                              /* Option Data 2 (2nd output) */
        0x00,                              /* Option Data 1 (3rd output) */
        0x00,                              /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
        0,                                 /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_DISABLE,             /* Dummy cycle : output setting */
        0,                                 /* Dummy cycle : Count(Fixed 0) */

/* --- Transfer Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Transfer Data : width */
        SPIBSC_SDR_TRANSFER,               /* Transfer Data : SDR/DDR setting */
        0,                                 /* Reserved1(Fixed 0) */
        0,                                 /* Reserved2(Fixed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
    {

/* --- IDENTIFIER --- */
        "WRITE ENABLE",                    /* command identifier */

/* --- Command --- */
        0x06,                              /* Command  : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Command  : width */
        SPIBSC_OUTPUT_ENABLE,              /* Command  : output setting */

/* --- Optional Command --- */
        0x00,                              /* Optional command : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Optional command : width */
        SPIBSC_OUTPUT_DISABLE,             /* Optional command : output setting */

/* --- Address --- */
        SPIBSC_1BIT_WIDTH,                 /* Address : width */
        SPIBSC_OUTPUT_DISABLE,             /* Address : output setting */
        SPIBSC_SDR_TRANSFER,               /* Address : SDR/DDR setting */

/* --- Option Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Option Data : width */
        SPIBSC_OUTPUT_DISABLE,             /* Option Data : output setting */
        SPIBSC_SDR_TRANSFER,               /* Option Data : SDR/DDR setting */
        0x00,                              /* Option Data 3 (1st output) */
        0x00,                              /* Option Data 2 (2nd output) */
        0x00,                              /* Option Data 1 (3rd output) */
        0x00,                              /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
        0,                                 /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_DISABLE,             /* Dummy cycle : output setting */
        0,                                 /* Dummy cycle : Count(Fixed 0) */

/* --- Transfer Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Transfer Data : width */
        SPIBSC_SDR_TRANSFER,               /* Transfer Data : SDR/DDR setting */
        0,                                 /* Reserved1(Fixed 0) */
        0,                                 /* Reserved2(Fixed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

},
{

/* --- IDENTIFIER --- */
        "WRITE STATUS",                    /* command identifier */

/* --- Command --- */
        0x01,                              /* Command : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Command : width */
        SPIBSC_OUTPUT_ENABLE,              /* Command : output setting */

/* --- Optional Command --- */
        0x00,                              /* Optional command : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Optional command : width */
        SPIBSC_OUTPUT_DISABLE,             /* Optional command : output setting */

/* --- Address --- */
        SPIBSC_1BIT_WIDTH,                 /* Address : width */
        SPIBSC_OUTPUT_DISABLE,             /* Address : output setting */
        SPIBSC_SDR_TRANSFER,               /* Address : SDR/DDR setting */

/* --- Option Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Option Data : width */
        SPIBSC_OUTPUT_DISABLE,             /* Option Data : output setting */
        SPIBSC_SDR_TRANSFER,               /* Option Data : SDR/DDR setting */
        0x00,                              /* Option Data 3 (1st output) */
        0x00,                              /* Option Data 2 (2nd output) */
        0x00,                              /* Option Data 1 (3rd output) */
        0x00,                              /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
        0,                                 /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_DISABLE,             /* Dummy cycle : output setting */
        0,                                 /* Dummy cycle : Count(Fixed 0) */

/* --- Transfer Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Transfer Data : Width */
        SPIBSC_SDR_TRANSFER,               /* Transfer Data : SDR/DDR setting */
        0,                                 /* Reserved1(Fixed 0) */
        0,                                 /* Reserved2(Fixed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_1,           /* Set the output level of QSPIn_IO2 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_1,           /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
    {

/* --- IDENTIFIER --- */
        "RDID",                            /* command identifier */

/* --- Command --- */
        0x9F,                              /* Command : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Command : width */
        SPIBSC_OUTPUT_ENABLE,              /* Command : output setting */

/* --- Optional Command --- */
        0x00,                              /* Optional command : code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Optional command : width */
        SPIBSC_OUTPUT_DISABLE,             /* Optional command : output setting */

/* --- Address --- */
        SPIBSC_1BIT_WIDTH,                 /* Address : width */
        SPIBSC_OUTPUT_DISABLE,             /* Address : output setting */
        SPIBSC_SDR_TRANSFER,               /* Address : SDR/DDR setting */

/* --- Option Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Option Data : width */
        SPIBSC_OUTPUT_DISABLE,             /* Option Data : output setting */
        SPIBSC_SDR_TRANSFER,               /* Option Data : SDR/DDR setting */
        0x00,                              /* Option Data 3 (1st output) */
        0x00,                              /* Option Data 2 (2nd output) */
        0x00,                              /* Option Data 1 (3rd output) */
        0x00,                              /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
        0,                                 /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_DISABLE,             /* Dummy cycle : output setting */
        0,                                 /* Dummy cycle : Count(Fixed 0) */

/* --- Transfer Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Transfer Data : Width */
        SPIBSC_SDR_TRANSFER,               /* Transfer Data : SDR/DDR setting */
        0,                                 /* Reserved1(Fixed 0) */
        0,                                 /* Reserved2(Fixed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
    {

        "4DTRD4B",                         /* command identifier */

        /* --- Command --- */
        0xEE,                              /* Command code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Command width */
        SPIBSC_OUTPUT_ENABLE,              /* Command output setting */

        /* --- Optional Command --- */
        0x00,                              /* Optional command code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Optional command width */
        SPIBSC_OUTPUT_DISABLE,             /* Optional command output setting */

        /* --- Address --- */
        SPIBSC_4BIT_WIDTH,                 /* Address width */
        SPIBSC_OUTPUT_ADDR_32,             /* Address output setting  */
        SPIBSC_DDR_TRANSFER,               /* Address SDR/DDR setting */

        /* --- Option Data --- */
        SPIBSC_4BIT_WIDTH,                 /* Option Data width */
        SPIBSC_OUTPUT_OPD_3,               /* Option Data output setting */
        SPIBSC_DDR_TRANSFER,               /* Option Data SDR/DDR setting */
        0x00,                              /* Option Data 3 (1st output) */
        0x00,                              /* Option Data 2 (2nd output) */
        0x00,                              /* Option Data 1 (3rd output) */
        0x00,                              /* Option Data 0 (4th output) */

        /* --- Dummy Cycle --- */
        0,                                 /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_ENABLE,              /* Dummy cycle output setting */
        SPIBSC_DUMMY_07CYC,                /* Dummy cycle Count */

        /* --- Transfer Data --- */
        SPIBSC_4BIT_WIDTH,                 /* Transfer Data width */
        SPIBSC_DDR_TRANSFER,               /* Transfer Data SDR/DDR setting */
        0,                                 /* Reserved1(Fixed 0) */
        0,                                 /* Reserved2(Fixed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
    {

        "4READ4B",                         /* command identifier */

        /* --- Command --- */
        0xEC,                              /* Command code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Command width */
        SPIBSC_OUTPUT_ENABLE,              /* Command output setting */

        /* --- Optional Command --- */
        0x00,                              /* Optional command code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Optional command width */
        SPIBSC_OUTPUT_DISABLE,             /* Optional command output setting */

        /* --- Address --- */
        SPIBSC_4BIT_WIDTH,                 /* Address width */
        SPIBSC_OUTPUT_ADDR_32,             /* Address output setting  */
        SPIBSC_SDR_TRANSFER,               /* Address SDR/DDR setting */

        /* --- Option Data --- */
        SPIBSC_4BIT_WIDTH,                 /* Option Data width */
        SPIBSC_OUTPUT_OPD_3,               /* Option Data output setting */
        SPIBSC_SDR_TRANSFER,               /* Option Data SDR/DDR setting */
        0x00,                              /* Option Data 3 (1st output) */
        0x00,                              /* Option Data 2 (2nd output) */
        0x00,                              /* Option Data 1 (3rd output) */
        0x00,                              /* Option Data 0 (4th output) */

        /* --- Dummy Cycle --- */
        0,                                 /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_ENABLE,              /* Dummy cycle output setting */
        SPIBSC_DUMMY_02CYC,                /* Dummy cycle Count */

        /* --- Transfer Data --- */
        SPIBSC_4BIT_WIDTH,                 /* Transfer Data width */
        SPIBSC_SDR_TRANSFER,               /* Transfer Data SDR/DDR setting */
        0,                                 /* Reserved1(Fixed 0) */
        0,                                 /* Reserved2(Fixed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
    {

        "4PP4B",                           /* command identifier */

        /* --- Command --- */
        0x3E,                              /* Command code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Command width */
        SPIBSC_OUTPUT_ENABLE,              /* Command output setting */

        /* --- Optional Command --- */
        0x00,                              /* Optional command code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Optional command width */
        SPIBSC_OUTPUT_DISABLE,             /* Optional command output setting */

        /* --- Address --- */
        SPIBSC_4BIT_WIDTH,                 /* Address width */
        SPIBSC_OUTPUT_ADDR_32,             /* Address output setting  */
        SPIBSC_SDR_TRANSFER,               /* Address SDR/DDR setting */

/* --- Option Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Option Data : width */
        SPIBSC_OUTPUT_DISABLE,             /* Option Data : output setting */
        SPIBSC_SDR_TRANSFER,               /* Option Data : SDR/DDR setting */
        0x00,                              /* Option Data 3 (1st output) */
        0x00,                              /* Option Data 2 (2nd output) */
        0x00,                              /* Option Data 1 (3rd output) */
        0x00,                              /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
        0,                                 /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_DISABLE,             /* Dummy cycle : output setting */
        0,                                 /* Dummy cycle : Count(Fixed 0) */

        /* --- Transfer Data --- */
        SPIBSC_4BIT_WIDTH,                 /* Transfer Data width */
        SPIBSC_SDR_TRANSFER,               /* Transfer Data SDR/DDR setting */
        0,                                 /* Reserved1(Fixed 0) */
        0,                                 /* Reserved2(Fixed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
    {

        "SE4B",                            /* command identifier */

        /* --- Command --- */
        0x21,                              /* Command code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Command width */
        SPIBSC_OUTPUT_ENABLE,              /* Command output setting */

        /* --- Optional Command --- */
        0x00,                              /* Optional command code (8bit) */
        SPIBSC_1BIT_WIDTH,                 /* Optional command width */
        SPIBSC_OUTPUT_DISABLE,             /* Optional command output setting */

        /* --- Address --- */
        SPIBSC_1BIT_WIDTH,                 /* Address width */
        SPIBSC_OUTPUT_ADDR_32,             /* Address output setting  */
        SPIBSC_SDR_TRANSFER,               /* Address SDR/DDR setting */

/* --- Option Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Option Data : width */
        SPIBSC_OUTPUT_DISABLE,             /* Option Data : output setting */
        SPIBSC_SDR_TRANSFER,               /* Option Data : SDR/DDR setting */
        0x00,                              /* Option Data 3 (1st output) */
        0x00,                              /* Option Data 2 (2nd output) */
        0x00,                              /* Option Data 1 (3rd output) */
        0x00,                              /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
        0,                                 /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_DISABLE,             /* Dummy cycle : output setting */
        0,                                 /* Dummy cycle : Count(Fixed 0) */

/* --- Transfer Data --- */
        SPIBSC_1BIT_WIDTH,                 /* Transfer Data : width */
        SPIBSC_SDR_TRANSFER,               /* Transfer Data : SDR/DDR setting */
        0,                                 /* Reserved1(Fixed 0) */
        0,                                 /* Reserved2(Fixed 0) */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
};






static const st_spibsc_xip_config_t gs_xip_read_table[] =
{
    {

        "4BIT_DDR_READ",               /* command identifier */

/* --- Command --- */
        0xEE,                          /* Command code (8bit) */
        SPIBSC_1BIT_WIDTH,             /* Command width */
        SPIBSC_OUTPUT_ENABLE,          /* Command output setting */

/* --- Optional Command --- */
        0x00,                          /* Optional command code (8bit) */
        SPIBSC_1BIT_WIDTH,             /* Optional command width */
        SPIBSC_OUTPUT_DISABLE,         /* Optional command output setting */

/* --- Address --- */
        SPIBSC_4BIT_WIDTH,             /* Address width */
        SPIBSC_OUTPUT_ADDR_32,         /* Address output setting  */
        SPIBSC_DDR_TRANSFER,           /* Address SDR/DDR setting */
        0,                             /* Reserved1(Fixed 0) */
        0,                             /* Reserved2(Fixed 0) */

/* --- Option Data --- */
        SPIBSC_4BIT_WIDTH,              /* Option Data width */
        SPIBSC_OUTPUT_OPD_3,            /* Option Data output setting */
        SPIBSC_DDR_TRANSFER,            /* Option Data SDR/DDR setting */
        0x00,                           /* Option Data 3 (1st output) */
        0x00,                           /* Option Data 2 (2nd output) */
        0x00,                           /* Option Data 1 (3rd output) */
        0x00,                           /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
        0,                              /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_ENABLE,           /* Dummy cycle output setting */
        SPIBSC_DUMMY_07CYC,             /* Dummy cycle Count */

/* --- Transfer Data --- */
        SPIBSC_4BIT_WIDTH,             /* Transfer Data width */
        SPIBSC_DDR_TRANSFER,           /* Transfer Data SDR/DDR setting */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
    {

        "4BIT_SDR_READ",                /* command identifier */

/* --- Command --- */
        0xEC,                          /* Command code (8bit) */
        SPIBSC_1BIT_WIDTH,             /* Command width */
        SPIBSC_OUTPUT_ENABLE,          /* Command output setting */

/* --- Optional Command --- */
        0x00,                          /* Optional command code (8bit) */
        SPIBSC_1BIT_WIDTH,             /* Optional command width */
        SPIBSC_OUTPUT_DISABLE,         /* Optional command output setting */

/* --- Address --- */
        SPIBSC_4BIT_WIDTH,             /* Address width */
        SPIBSC_OUTPUT_ADDR_32,         /* Address output setting  */
        SPIBSC_SDR_TRANSFER,           /* Address SDR/DDR setting */
        0,                             /* Reserved1(Fixed 0) */
        0,                             /* Reserved2(Fixed 0) */

/* --- Option Data --- */
        SPIBSC_4BIT_WIDTH,              /* Option Data width */
        SPIBSC_OUTPUT_OPD_3,            /* Option Data output setting */
        SPIBSC_SDR_TRANSFER,            /* Option Data SDR/DDR setting */
        0x00,                           /* Option Data 3 (1st output) */
        0x00,                           /* Option Data 2 (2nd output) */
        0x00,                           /* Option Data 1 (3rd output) */
        0x00,                           /* Option Data 0 (4th output) */

/* --- Dummy Cycle --- */
        0,                              /* Reserved3(Fixed 0) */
        SPIBSC_OUTPUT_ENABLE,           /* Dummy cycle output setting */
        SPIBSC_DUMMY_02CYC,             /* Dummy cycle Count */

/* --- Transfer Data --- */
        SPIBSC_4BIT_WIDTH,             /* Transfer Data width */
        SPIBSC_SDR_TRANSFER,           /* Transfer Data SDR/DDR setting */

/* --- QSPIn_IO0-3 output level Data --- */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO1 at SSL negation */ 
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at SSL negation */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width */
        SPIBSC_QSPI_IO_OUTPUT_HI_Z,        /* Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width */

    },
} ;



/******************************************************************************
Functions Prototypes
******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* R_SPIBSC_DRV_SC_CFG_H_ */

/* End of File */
