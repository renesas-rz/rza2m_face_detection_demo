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
* File Name    : hwsetup.c
* Device(s)    : RZ/A2M
* OS           : None
* H/W Platform : RZ/A2M Evaluation Board
* Description  : RZ/A2M Sample Program - FIT function of Hardware Setup
* Operation    :
* Limitations  :
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_typedefs.h"
#include "r_cpg_drv_api.h"
#include "r_spibsc_lld_rza2m_api.h"
#include "hwsetup.h"



/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/
#define SPIBSC_PRV_DDR_SETTING


/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/


/******************************************************************************
Private global variables and functions
******************************************************************************/


/******************************************************************************
* Function Name: R_SC_HardwareSetup
* Description  :
* Arguments    :
* Return Value :
******************************************************************************/
void R_SC_HardwareSetup(void)
{

#if 0 /* This code must to be run in internal RAM. */
    volatile uint16_t dummy_read_16;

    if( 1 == RZA_IO_RegRead_16(&CPG.DSFR, CPG_DSFR_IOKEEP_SHIFT,  CPG_DSFR_IOKEEP) )
    {
        RZA_IO_RegWrite_16(&CPG.DSFR, 0, CPG_DSFR_IOKEEP_SHIFT,  CPG_DSFR_IOKEEP);
        dummy_read_16 = CPG.DSFR;
    }
#endif


    /*    initialize SPIBSC,
     *    this speeds up SPIBSC in BOOT-TIME.
     */

        e_spibsc_err_t err;
        st_spibsc_config_t  spibsc_config_tbl;

        spibsc_config_tbl.flash_type = SPIBSC_FLASH_SPI;
        spibsc_config_tbl.flash_num = SPIBSC_CMNCR_BSZ_SINGLE;
        spibsc_config_tbl.flash_port_voltage = SPIBSC_PORT_VOLTAGE_3_3V;



         /* ==== SPIBSC initialize ==== */
        R_SPIBSC_Init( &spibsc_config_tbl );


        /* Switch to manual operating mode */
        R_SPIBSC_ChangeMode(SPIBSC_MODE_MANUAL, SPIBSC_SDR_TRANSFER, 0);

#ifdef SPIBSC_PRV_DDR_SETTING
        /* Set Quad mode (DDR) */
        Userdef_SPIBSC_SFLASH_SetMode(SPIBSC_QE_ENABLE, SPIBSC_DDR_TRANSFER);
#else
        /* Set Quad mode (SDR) */
        Userdef_SPIBSC_SFLASH_SetMode(SPIBSC_QE_ENABLE, SPIBSC_SDR_TRANSFER);
#endif


        /* Switch Manual to XIP */
        /* Switch to External address space read mode */
#ifdef SPIBSC_PRV_DDR_SETTING
        R_SPIBSC_ChangeMode(SPIBSC_MODE_XIP, SPIBSC_DDR_TRANSFER, SFLASH_CMD_INDEX_XIP_4DTRD4B_EEH);
#else
        R_SPIBSC_ChangeMode(SPIBSC_MODE_XIP, SPIBSC_SDR_TRANSFER, SFLASH_CMD_INDEX_XIP_4READ4B_ECH);
#endif




    /*    Initialize clock pulse generator,
     *    this speeds up instruction clocks, etc.
     */
    R_CPG_InitialiseHwIf();

#ifdef SPIBSC_PRV_DDR_SETTING
    /* SPIBSC Adjust Phy */
    if ( SPIBSC_FLASH_SPI == spibsc_config_tbl.flash_type )
    {


        /* Switch to manual operating mode */
        R_SPIBSC_ChangeMode(SPIBSC_MODE_MANUAL, SPIBSC_DDR_TRANSFER, 0);

        err = R_SPIBSC_AdjustPhy();

        /* Switch Manual to XIP */
        /* Switch to External address space read mode */
        R_SPIBSC_ChangeMode(SPIBSC_MODE_XIP, SPIBSC_DDR_TRANSFER, SFLASH_CMD_INDEX_XIP_4DTRD4B_EEH);
        if ( 0 > err )
        {
            /* Stops program from running off */
            while(1)
            {
                __asm__("nop");
            }
            
        }
    }
#endif
}
/******************************************************************************
 * End of function R_SC_HardwareSetup
 ******************************************************************************/


/* End of File */
