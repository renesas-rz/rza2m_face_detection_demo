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
* File Name    : r_spibsc_sflash_userdef.c
* $Rev: 606 $
* $Date:: 2018-09-05 18:13:42 +0900#$
* Device(s)    : RZ/A2M
* OS           : None
* H/W Platform : RZ/A2M Board
* Description  : RZ/A2M Sample Program - function of SPIBSC Module
* Operation    :
* Limitations  :
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_spibsc_lld_rza2m_api.h"
#include "r_spibsc_sflash_userdef.h"
#include "r_spibsc_drv_sc_cfg.h"

/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/
/*#define SPIBSC_PRV_FOR_DEBUG */

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/


/******************************************************************************
* Function Name: Userdef_SPIBSC_SFLASH_SetMode
* Description  :
* Arguments    :
* Return Value :
******************************************************************************/
void Userdef_SPIBSC_SFLASH_SetMode(uint8_t mode, uint8_t sdr_ddr)
{
    uint8_t status;
    uint8_t config;


    /* ==== Read Status Command (05H)==== */
    Userdef_SPIBSC_SFLASH_ReadStatus(&status);

    /* ==== Read Configuration Command (15H) ==== */
    Userdef_SPIBSC_SFLASH_ReadConfig(&config);

    /* ==== Write Enable Command (06H) ==== */
    Userdef_SPIBSC_SFLASH_WriteEnable();

    /* ==== Change of status register and configuration register ==== */
    status = status & 0xC0;
    if ( SPIBSC_QE_ENABLE == mode )
    {
       status = status | SPIBSC_RDSR_QE;   /* QE(Quad Enable) = 1 */
    }
    else
    {
        status = status & (uint8_t)(~SPIBSC_RDSR_QE);   /* QE(Quad Disable) = 0 */
    }


    if ( SPIBSC_DDR_TRANSFER == sdr_ddr )
    {
        /* for EEh Command (Quad I/O DTR Read/DDR)
         * Dummy cycle            : 8cycle @ 66MHz    DC[1:0]  = B'10
         * Output Driver Strength : 15 Ohms           ODS[2:0] = B'110
         */
        config = config & 0x30;
        config = config | 0x86;
    }
    else
    {
        /* for ECh Command (Quad I/O Fast Read/SDR)
         * Dummy cycle            : 4cycle @ 70MHz    DC[1:0]  = B'01
         * Output Driver Strength : 15 Ohms           ODS[2:0] = B'110
         */
        config = config & 0x30;
        config = config | 0x46;
    }
    
    /* ==== Write Status Command (01H) ==== */
    Userdef_SPIBSC_SFLASH_WriteStatus(&status, &config);

#ifdef SPIBSC_PRV_FOR_DEBUG
    /* ==== Read Status Command (05H)==== */
    Userdef_SPIBSC_SFLASH_ReadStatus(&status);

    /* ==== Read Configuration Command (15H) ==== */
    Userdef_SPIBSC_SFLASH_ReadConfig(&config);
#endif    /* SPIBSC_PRV_FOR_DEBUG */

}
/******************************************************************************
 * End of function Userdef_SPIBSC_SFLASH_SetMode
 ******************************************************************************/


/******************************************************************************
* Function Name: Userdef_SPIBSC_SFLASH_ReadStatus
* Description  :
* Arguments    :
* Return Value :
******************************************************************************/
void Userdef_SPIBSC_SFLASH_ReadStatus(uint8_t *p_status)
{
    uint8_t table_no;
    uint32_t addr = 0x00000000;
    uint8_t status;
    
    table_no = SFLASH_CMD_INDEX_RDSR_05H;
    R_SPIBSC_SPICMDIssue(table_no, addr, 0, 0, &status, 1);
    
    *p_status = status;

}
/******************************************************************************
 * End of function Userdef_SPIBSC_SFLASH_ReadStatus
 ******************************************************************************/


/******************************************************************************
* Function Name: Userdef_SPIBSC_SFLASH_ReadConfig
* Description  :
* Arguments    :
* Return Value :
******************************************************************************/
void Userdef_SPIBSC_SFLASH_ReadConfig(uint8_t *p_config)
{
    uint8_t table_no;
    uint32_t addr = 0x00000000;
    uint8_t config;
    
    table_no = SFLASH_CMD_INDEX_RDCR_15H;
    R_SPIBSC_SPICMDIssue(table_no, addr, 0, 0, &config, 1);

    *p_config = config;

}
/******************************************************************************
 * End of function Userdef_SPIBSC_SFLASH_ReadConfig
 ******************************************************************************/


/******************************************************************************
* Function Name: Userdef_SPIBSC_SFLASH_WriteStatus
* Description  :
* Arguments    :
* Return Value :
******************************************************************************/
void Userdef_SPIBSC_SFLASH_WriteStatus(uint8_t *p_status, uint8_t *p_config)
{
    uint8_t table_no;
    uint32_t addr = 0x00000000;
    uint8_t write_data[2];

    write_data[0] = *p_status;
    write_data[1] = *p_config;

    table_no = SFLASH_CMD_INDEX_WRSR_01H;
    R_SPIBSC_SPICMDIssue(table_no, addr, &write_data[0], 2, 0, 0);  /*  Write status & config */

}
/******************************************************************************
 * End of function Userdef_SPIBSC_SFLASH_WriteStatus
 ******************************************************************************/




/******************************************************************************
* Function Name: Userdef_SPIBSC_SFLASH_WriteEnable
* Description  :
* Arguments    :
* Return Value :
******************************************************************************/
void Userdef_SPIBSC_SFLASH_WriteEnable(void)
{
    uint8_t table_no;
    uint32_t addr = 0x00000000;
    uint8_t status;


    do
    {
        /* ==== Write Enable Command (06H) ==== */
        table_no = SFLASH_CMD_INDEX_WREN_06H;
        R_SPIBSC_SPICMDIssue(table_no, addr, 0, 0, 0, 0);

        /* ==== Read Status Command (05H)==== */
        Userdef_SPIBSC_SFLASH_ReadStatus(&status);
    }
    while (SPIBSC_RDSR_WEL != (SPIBSC_RDSR_WEL & status));

}
/******************************************************************************
 * End of function Userdef_SPIBSC_SFLASH_WriteEnable
 ******************************************************************************/

/******************************************************************************
* Function Name: Userdef_SPIBSC_SFLASH_WaitReady
* Description  :
* Arguments    :
* Return Value :
******************************************************************************/
void Userdef_SPIBSC_SFLASH_WaitReady(void)
{
    uint8_t status;


    do
    {
        /* ==== Read Status Command (05H)==== */
        Userdef_SPIBSC_SFLASH_ReadStatus(&status);
    }
    while (SPIBSC_RDSR_WIP == (SPIBSC_RDSR_WIP & status));

}
/******************************************************************************
 * End of function Userdef_SPIBSC_SFLASH_WaitReady
 ******************************************************************************/

/******************************************************************************
* Function Name: Userdef_SPIBSC_SFLASH_Read
* Description  : The range of the serial flash memory designated by arguments
*                is read and stored in a buffer.
* Arguments    : uint32_t addr  : read address(address of serial flash memory)
*                uint8_t *p_read_buff: Start address in a buffer
*                uint32_t read_size  : The number of data byte
*                uint8_t sdr_ddr: The number of data byte
* Return Value : none
******************************************************************************/
void Userdef_SPIBSC_SFLASH_Read(uint32_t addr, uint8_t *p_read_buff, int32_t read_size, uint8_t sdr_ddr)
{
    uint8_t table_no;


    /* Test Code for ROM Read 256 */

    if ( SPIBSC_DDR_TRANSFER == sdr_ddr )
    {

        /* Switch to manual operating mode */
        R_SPIBSC_ChangeMode(SPIBSC_MODE_MANUAL, SPIBSC_DDR_TRANSFER, 0);

        /* ==== Read ROM data form address 0x000000000 ==== */
        table_no = SFLASH_CMD_INDEX_4DTRD4B_EEH;    /* 4BIT_DDR_READ */
        R_SPIBSC_SPICMDIssue(table_no, addr, 0, 0, p_read_buff, read_size);

        /* Switch to manual operating mode */
        R_SPIBSC_ChangeMode(SPIBSC_MODE_MANUAL, SPIBSC_SDR_TRANSFER, 0);
    }
    else
    {

        /* ==== Read ROM data form address 0x000000000 ==== */
        table_no = SFLASH_CMD_INDEX_4READ4B_ECH;    /* 4BIT_SDR_READ */
        R_SPIBSC_SPICMDIssue(table_no, addr, 0, 0, p_read_buff, read_size);
    }

}
/******************************************************************************
 * End of function Spibsc_Sflash_UserdefRead
 ******************************************************************************/

/******************************************************************************
* Function Name: Spibsc_Sflash_UserdefReadId
* Description  :
* Arguments    : uint8_t *p_id   : Start address in a buffer
* Return Value : none
******************************************************************************/
void Userdef_SPIBSC_SFLASH_ReadId(uint8_t *p_id)
{
    uint8_t table_no;
    uint32_t addr = 0x00000000;


    /* ==== RDID Command (9FH)==== */
    table_no = SFLASH_CMD_INDEX_RDID_9FH;
    R_SPIBSC_SPICMDIssue(table_no, addr, 0, 0, p_id, 3);

    /* === Expected value  === */
    /* Manufacturer ID : 0xC2  */
    /* Memory type : 0x20      */
    /* Memory density : 0x1A   */

}
/******************************************************************************
 * End of function Spibsc_Sflash_UserdefReadId
 ******************************************************************************/

/******************************************************************************
* Function Name: Spibsc_Sflash_UserdefWrite
* Description  : Data of an argument is written on a serial flash memory
* Arguments    : uint32_t addr : write address(address of serial flash memory)
*                uint8_t *p_write_buf  : write data(Start address in a buffer)
*                uint32_t write_size : The number of data byte
* Return Value : none
******************************************************************************/
void Userdef_SPIBSC_SFLASH_Write(uint32_t addr, uint8_t *p_write_buff, int32_t write_size)
{
    uint8_t table_no;


    /* ==== Write Enable ==== */
    Userdef_SPIBSC_SFLASH_WriteEnable();

    /* ==== 4BIT Page Program 4B ==== */
    table_no = SFLASH_CMD_INDEX_4PP4B_3EH;
	addr = (0xFFFFFF00UL & addr);    /* 256byte Align */
    R_SPIBSC_SPICMDIssue(table_no, addr, p_write_buff, write_size, 0, 0);

    /* ==== Wait Ready ==== */
    Userdef_SPIBSC_SFLASH_WaitReady();

}
/******************************************************************************
 * End of function Userdef_SPIBSC_SFLASH_Write
 ******************************************************************************/

/******************************************************************************
* Function Name: Userdef_SPIBSC_SFLASH_Erase
* Description  : Serial flash memory is sector erase
* Arguments    : uint32_t addr  : erase address(address of serial flash memory)
* Return Value : none
******************************************************************************/
void Userdef_SPIBSC_SFLASH_Erase(uint32_t addr)
{
    uint8_t table_no;


    /* ==== Write Enable ==== */
    Userdef_SPIBSC_SFLASH_WriteEnable();

    /* ==== Sector Erase 4B  ==== */
    table_no = SFLASH_CMD_INDEX_SE4B_21H;
	addr = (0xFFFFF000UL & addr);    /* 4Kbyte Align */
    R_SPIBSC_SPICMDIssue(table_no, addr, 0, 0, 0, 0);

    /* ==== Wait Ready ==== */
    Userdef_SPIBSC_SFLASH_WaitReady();

}
/******************************************************************************
 * End of functionUserdef_SPIBSC_SFLASH_Erase
******************************************************************************/



/* End of File */
