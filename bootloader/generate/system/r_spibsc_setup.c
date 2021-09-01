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
* File Name    : r_spibsc_setup.c
* $Rev: 708 $
* $Date:: 2018-10-31 11:16:00 +0900#$
* Device(s)    : RZ/A2M
* OS           : None
* H/W Platform : RZ/A2M Board
* Description  : RZ/A2M Sample Program
* Operation    :
* Limitations  :
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

#include "r_typedefs.h"
#include "iodefine.h"
#include "iobitmask.h"
#include "rza_io_regrw.h"
#include "r_spibsc_setup.h"

/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/


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
* Function Name: HW_INIT_IO_RegWrite_16
* Description  : IO register 16-bit write
* Arguments    : volatile uint16_t * ioreg : IO register for writing
*              :                           : Use register definition name of the
*              :                           : iodefine.h
*              : uint16_t write_value      : Write value for the IO register
*              : uint16_t shift            : The number of left shifts to the
*              :                           : target bit
*              : uint16_t mask             : Mask value for the IO register
*              :                           : (Target bit : "1")
* Return Value : None
******************************************************************************/
static void HW_INIT_IO_RegWrite_16(volatile uint16_t * ioreg, uint16_t write_value, uint16_t shift, uint32_t mask)
{
    uint16_t reg_value;

    if ( IOREG_NONMASK_ACCESS != mask )
    {
        reg_value = *ioreg;                                         /* Read from register */
        reg_value = (uint16_t)((reg_value & (~mask)) | (unsigned)(write_value << shift)); /* Modify value       */
    }
    else
    {
        reg_value = write_value;
    }
    *ioreg    = reg_value;                                      /* Write to register  */
}
/*******************************************************************************
End of function HW_INIT_IO_RegWrite_16
*******************************************************************************/

/******************************************************************************
* Function Name: HW_INIT_IO_RegRead_32
* Description  : IO register 32-bit read
* Arguments    : volatile uint32_t * ioreg : IO register for reading
*              :                           : Use register definition name of the
*              :                           : iodefine.h
*              : uint32_t shift            : The number of right shifts to the
*              :                           : target bit
*              : uint32_t mask             : Mask bit for the IO register
*              :                           : (Target bit: "1")
* Return Value : uint32_t : Value of the obtained target bit
******************************************************************************/
static uint32_t HW_INIT_IO_RegRead_32(volatile uint32_t * ioreg, uint32_t shift, uint32_t mask)
{
    uint32_t reg_value;

    reg_value = *ioreg;                             /* Read from register            */
    if ( IOREG_NONMASK_ACCESS != mask)
    {
        reg_value = (reg_value & mask) >> shift;    /* Clear other bit and Bit shift */
    }

    return reg_value;
}
/*******************************************************************************
End of function HW_INIT_IO_RegRead_32
*******************************************************************************/

/*******************************************************************************
* Function Name: hw_init_spibsc_wait_tend
* Description  : Wait Transfer End (Manual mode)
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void hw_init_spibsc_wait_tend(void)
{

    uint32_t tend;

    do{

        /* Read CMNSR.TEND */
       tend = HW_INIT_IO_RegRead_32(&SPIBSC.CMNSR.LONG, SPIBSC_CMNSR_TEND_SHIFT, SPIBSC_CMNSR_TEND);

    }while( 0 == tend );

}
/*******************************************************************************
End of function hw_init_spibsc_wait_tend
*******************************************************************************/

/******************************************************************************
* Function Name: r_spibsc_setup
* Description  : 
* Arguments    : none
* Return Value : none
******************************************************************************/
void r_spibsc_setup( void )
{

	/* Wait TEND = 1 */
	hw_init_spibsc_wait_tend();

    /* ---- SCLKSEL.SPICR[1:0] = b'01 : SPIBSC Clock = P1   ---- */
    HW_INIT_IO_RegWrite_16(&CPG.SCLKSEL.WORD, 0x1, CPG_SCLKSEL_SPICR_SHIFT, CPG_SCLKSEL_SPICR);

}
/*******************************************************************************
End of function r_spibsc_setup
*******************************************************************************/

/* End of File */
