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
* File Name    : r_spibsc_lld_rza2m.c
* $Rev: 759 $
* $Date:: 2018-12-07 17:14:08 +0900#$
* Device(s)    : RZ/A2M
* OS           : None
* H/W Platform : RZ/A2M Board
* Description  : RZ/A2M Sample Program - API function of SPIBSC module
* Operation    :
* Limitations  :
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_spibsc_lld_rza2m_reg.h"
#include "r_spibsc_lld_rza2m_api.h"
#include "r_spibsc_drv_sc_cfg.h"
#include "r_spibsc_adjust_timing_data.h"

#include "iobitmask.h"
#include "rza_io_regrw.h"
#include "r_typedefs.h"

/******************************************************************************
Macro definitions
******************************************************************************/
/*! PHY Adjust */
#define SPIBSC_PRV_PHYADJ_MAX (13)
#define SPIBSC_PRV_RESULT_OK (1)
#define SPIBSC_PRV_RESULT_NG (0)

/******************************************************************************
Typedef definitions
******************************************************************************/
/*! PHY Adjust */
typedef struct r_drv_spibsc_phy_adj_t
{
    uint8_t xy; /*!< SPIBSC Phy Adj2 Data */
    uint8_t zz; /*!< SPIBSC PhyCnt cksel Data */
} st_r_drv_spibsc_phy_adj_t;

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
static void r_spibsc_common_spiflash_init( const st_spibsc_config_t  *p_spibsc_config_tbl );

static void r_spibsc_manual_set_command(uint8_t cmd, uint8_t width, uint8_t output_enable);
static void r_spibsc_manual_set_optional_command(uint8_t ocmd, uint8_t width, uint8_t output_enable);
static void r_spibsc_manual_set_address(uint32_t addr, uint8_t width, uint8_t address_output_enable, uint8_t ddr_enable);
static void r_spibsc_manual_set_option_data(uint8_t opd3, uint8_t opd2, uint8_t opd1, uint8_t opd0, uint8_t width, uint8_t option_data_output_enable,uint8_t ddr_enable);
static void r_spibsc_manual_set_dummy_cycle(uint8_t dummy_cycle_num, uint8_t width, uint8_t output_enable);
static void r_spibsc_manual_set_datatransfer(uint8_t transfer_unit,uint8_t width,uint8_t write_enable, uint8_t read_enable, uint8_t ddr_enable);
static void r_spibsc_manual_start_transfer(void);


static uint8_t r_spibsc_manual_read_data0_8(void);
static uint16_t r_spibsc_manual_read_data0_16(void);
static uint32_t r_spibsc_manual_read_data0_32(void);

static uint8_t r_spibsc_manual_read_data1_8(void);
static uint16_t r_spibsc_manual_read_data1_16(void);
static uint32_t r_spibsc_manual_read_data1_32(void);


static void r_spibsc_manual_write_data0_8(uint8_t write_data);
static void r_spibsc_manual_write_data0_16(uint16_t write_data);
static void r_spibsc_manual_write_data0_32(uint32_t write_data);

static void r_spibsc_manual_write_data1_8(uint8_t write_data);
static void r_spibsc_manual_write_data1_16(uint16_t write_data);
static void r_spibsc_manual_write_data1_32(uint32_t write_data);


static void r_spibsc_xip_set_command(uint8_t cmd, uint8_t width, uint8_t output_enable);
static void r_spibsc_xip_set_optional_command(uint8_t ocmd, uint8_t width, uint8_t output_enable);
static void r_spibsc_xip_set_address(uint8_t width, uint8_t address_output_enable, uint8_t ddr_enable);
static void r_spibsc_xip_set_option_data(uint8_t opd3, uint8_t opd2, uint8_t opd1, uint8_t opd0,
                                  uint8_t width, uint8_t option_data_output_enable,uint8_t ddr_enable);
static void r_spibsc_xip_set_dummy_cycle(uint8_t dummy_cycle_num, uint8_t width, uint8_t output_enable);
static void r_spibsc_xip_set_datatransfer(uint8_t width, uint8_t ddr_enable);


static void r_spibsc_manual_assert_ssl(void);
static void r_spibsc_manual_negate_ssl(void);

static void r_spibsc_wait_tend(void);

static void r_spibsc_change_manual_mode(uint8_t sdr_ddr);
static void r_spibsc_change_xip_mode(uint8_t sdr_ddr);
static void r_spibsc_flush_read_cache(void);
static void r_spibsc_xip_stop_access(void);

static void r_spibsc_port_voltage_setting(uint8_t voltage);
static void r_spibsc_port_current_setting(uint8_t voltage);


static int_t r_spibsc_get_ok_area_center( uint8_t *p_ok_ng_result );
static e_spibsc_err_t r_spibsc_spi_cmd_issue_read( uint8_t table_no, uint32_t addr, uint8_t *p_read_buff, int32_t read_size);
static e_spibsc_err_t r_spibsc_spi_cmd_issue_write( uint8_t table_no, uint32_t addr, uint8_t *p_write_buff, int32_t write_size );
static void r_spibsc_qspi_io_set_output_level(
    uint8_t cmncr_moiio3,
    uint8_t cmncr_moiio2,
    uint8_t cmncr_moiio1,
    uint8_t cmncr_moiio0,
    uint8_t cmncr_io3fv,
    uint8_t cmncr_io2fv,
    uint8_t cmncr_io0fv
    );

/******************************************************************************
Private global variables and functions
******************************************************************************/
/*! Version Information */
static const st_drv_info_t gs_lld_info =
{
    {
        ((STDIO_SPIBSC_RZ_LLD_VERSION_MAJOR << 16) + STDIO_SPIBSC_RZ_LLD_VERSION_MINOR)
    },
    STDIO_SPIBSC_RZ_LLD_BUILD_NUM,
    STDIO_SPIBSC_RZ_LLD_DRV_NAME
};


/*! PHY Adjust */
static const st_r_drv_spibsc_phy_adj_t gs_spibsc_phy_adj[SPIBSC_PRV_PHYADJ_MAX] =
{
/*    <xy>  <zz>    */
        { 0x01, 0x3 },    /*   0 */
        { 0x11, 0x3 },    /*   1 */
        { 0x01, 0x2 },    /*   2 */
        { 0x11, 0x2 },    /*   3 */
        { 0x01, 0x1 },    /*   4 */
        { 0x00, 0x3 },    /*   5 */
        { 0x10, 0x3 },    /*   6 */
        { 0x00, 0x2 },    /*   7 */
        { 0x10, 0x2 },    /*   8 */
        { 0x00, 0x1 },    /*   9 */
        { 0x10, 0x1 },    /*  10 */
        { 0x00, 0x0 },    /*  11 */
        { 0x10, 0x0 },    /*  12 */
};
static uint8_t gs_ok_ng_result[SPIBSC_PRV_PHYADJ_MAX];


/******************************************************************************
* Function Name: spibsc_io_reg_write_8
* Description  : IO register 8-bit write
* Arguments    : volatile uint8_t * ioreg : IO register for writing
*              :                          : Use register definition name of the
*              :                          : iodefine.h
*              : uint8_t write_value      : Write value for the IO register
*              : uint8_t shift            : The number of left shifts to the
*              :                          : target bit
*              : uint8_t mask             : Mask value for the IO register
*              :                          : (Target bit : "1")
* Return Value : None
******************************************************************************/
static void spibsc_io_reg_write_8(volatile uint8_t * ioreg, uint8_t write_value, uint8_t shift, uint32_t mask)
{
    uint8_t reg_value;

    if ( IOREG_NONMASK_ACCESS != mask )

    {
        reg_value = *ioreg;                                         /* Read from register */
        reg_value = (uint8_t)((reg_value & (~mask)) | (unsigned)(write_value << shift)); /* Modify value       */
    }
    else
    {
        reg_value = write_value;
    }
    *ioreg    = reg_value;                                      /* Write to register  */
}
/*******************************************************************************
End of function spibsc_io_reg_write_8
*******************************************************************************/

/******************************************************************************
* Function Name: spibsc_io_reg_write_16
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
static void spibsc_io_reg_write_16(volatile uint16_t * ioreg, uint16_t write_value, uint16_t shift, uint32_t mask)
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
End of function spibsc_io_reg_write_16
*******************************************************************************/

/******************************************************************************
* Function Name: spibsc_io_reg_write_32
* Description  : IO register 32-bit write
* Arguments    : volatile uint32_t * ioreg : IO register for writing
*              :                           : Use register definition name of the
*              :                           : iodefine.h
*              : uint32_t write_value      : Write value for the IO register
*              : uint32_t shift            : The number of left shifts to the
*              :                           : target bit
*              : uint32_t mask             : Mask value for the IO register
*              :                           : (Target bit : "1")
* Return Value : None
******************************************************************************/
static void spibsc_io_reg_write_32(volatile uint32_t * ioreg, uint32_t write_value, uint32_t shift, uint32_t mask)
{
    uint32_t reg_value;
    if ( IOREG_NONMASK_ACCESS != mask )
    {
        reg_value = *ioreg;                                         /* Read from register */
        reg_value = (reg_value & (~mask)) | (unsigned)(write_value << shift); /* Modify value       */
    }
    else
    {
        reg_value = write_value;
    }
    *ioreg    = reg_value;                                      /* Write to register  */
}
/*******************************************************************************
End of function spibsc_io_reg_write_32
*******************************************************************************/

/******************************************************************************
* Function Name: spibsc_io_reg_read_8
* Description  : IO register 8-bit read
* Arguments    : volatile uint8_t * ioreg : IO register for reading
*              :                          : Use register definition name of the
*              :                          : iodefine.h
*              : uint8_t shift            : The number of right shifts to the
*              :                          : target bit
*              : uint8_t mask             : Mask bit for the IO register
*              :                          : (Target bit: "1")
* Return Value : uint8_t : Value of the obtained target bit
******************************************************************************/
static uint8_t spibsc_io_reg_read_8(volatile uint8_t * ioreg, uint8_t shift, uint32_t mask)
{
    uint8_t reg_value;

    reg_value = *ioreg;                         /* Read from register            */
    if ( IOREG_NONMASK_ACCESS != mask )
    {
        reg_value = (uint8_t)((reg_value & mask) >> shift);    /* Clear other bit and Bit shift */
    }

    return reg_value;
}
/*******************************************************************************
End of function spibsc_io_reg_read_8
*******************************************************************************/

/******************************************************************************
* Function Name: spibsc_io_reg_read_16
* Description  : IO register 16-bit read
* Arguments    : volatile uint16_t * ioreg : IO register for reading
*              :                           : Use register definition name of the
*              :                           : iodefine.h
*              : uint16_t shift            : The number of right shifts to the
*              :                           : target bit
*              : uint16_t mask             : Mask bit for the IO register
*              :                           : (Target bit: "1")
* Return Value : uint16_t : Value of the obtained target bit
******************************************************************************/
static uint16_t spibsc_io_reg_read_16(volatile uint16_t * ioreg, uint16_t shift, uint32_t mask)
{
    uint16_t reg_value;

    reg_value = *ioreg;                         /* Read from register            */
    if ( IOREG_NONMASK_ACCESS != mask)
    {
        reg_value = (uint16_t)((reg_value & mask) >> shift);    /* Clear other bit and Bit shift */
    }

    return reg_value;
}
/*******************************************************************************
End of function spibsc_io_reg_read_16
*******************************************************************************/

/******************************************************************************
* Function Name: spibsc_io_reg_read_32
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
static uint32_t spibsc_io_reg_read_32(volatile uint32_t * ioreg, uint32_t shift, uint32_t mask)
{
    uint32_t reg_value;

    reg_value = *ioreg;                         /* Read from register            */
    if ( IOREG_NONMASK_ACCESS != mask)
    {
        reg_value = (reg_value & mask) >> shift;    /* Clear other bit and Bit shift */
    }

    return reg_value;
}
/*******************************************************************************
End of function spibsc_io_reg_read_32
*******************************************************************************/


/******************************************************************************
* Function Name: r_spibsc_common_spiflash_init
* Description  : spibsc manual spiflash initialize
* Arguments    : none
* Return Value : none
******************************************************************************/
static void r_spibsc_common_spiflash_init( const st_spibsc_config_t  *p_spibsc_config_tbl )
{

    /* Release module standby */
    spibsc_io_reg_write_8(&CPG.STBCR8.BYTE, 0, CPG_STBCR8_MSTP83_SHIFT, CPG_STBCR8_MSTP83);

    /* ---- SCLKSEL.SPICR[1:0] = b'01 : SPIBSC Clock = P1   ---- */
    spibsc_io_reg_write_16(&CPG.SCLKSEL.WORD, 0x1, CPG_SCLKSEL_SPICR_SHIFT, CPG_SCLKSEL_SPICR);


    /* ---- CMNCR ---- */

    /* CMNCR.MOIIO3[1:0] = b'11 : QSPIn_IO3 pin status at the time of an idle:HiZ */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, 0x3, SPIBSC_CMNCR_MOIIO3_SHIFT, SPIBSC_CMNCR_MOIIO3);

    /* CMNCR.MOIIO2[1:0] = b'11 : QSPIn_IO2 pin status at the time of an idle :HiZ */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, 0x3, SPIBSC_CMNCR_MOIIO2_SHIFT, SPIBSC_CMNCR_MOIIO2);

    /* CMNCR.MOIIO1[1:0] = b'11 : QSPIn_IO1 pin status at the time of an idle :HiZ */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, 0x3, SPIBSC_CMNCR_MOIIO1_SHIFT, SPIBSC_CMNCR_MOIIO1);

    /* CMNCR.MOIIO0[1:0] = b'11 : QSPIn_IO0 pin status at the time of an idle :HiZ */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, 0x3, SPIBSC_CMNCR_MOIIO0_SHIFT, SPIBSC_CMNCR_MOIIO0);

    /* CMNCR.IO3FV[1:0] = b'11  Output value of QSPIn_IO3 pin when 1 bit / 2 bit is set :HiZ */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, 0x3, SPIBSC_CMNCR_IO3FV_SHIFT , SPIBSC_CMNCR_IO3FV);

    /* CMNCR.IO2FV[1:0] = b'11 : Output value of QSPIn_IO2 pin when 1 bit / 2 bit is set :HiZ */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, 0x3, SPIBSC_CMNCR_IO2FV_SHIFT , SPIBSC_CMNCR_IO2FV);

    /* CMNCR.IO0FV[1:0] = b'11 : Output value of QSPIn_IO0 pin when 1 bit is set :HiZ */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, 0x3, SPIBSC_CMNCR_IO0FV_SHIFT , SPIBSC_CMNCR_IO0FV);

    /* CMNCR.BSZ[1:0] = b'00 :  SPI Flash(x1) */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, p_spibsc_config_tbl->flash_num, SPIBSC_CMNCR_BSZ_SHIFT   , SPIBSC_CMNCR_BSZ);

    /* SSLDR.SPNDL = 0 */
    spibsc_io_reg_write_32(&SPIBSC.SSLDR.LONG, 0x0, SPIBSC_SSLDR_SPNDL_SHIFT, SPIBSC_SSLDR_SPNDL);

    /* SSLDR.SLNDL = 0 */
    spibsc_io_reg_write_32(&SPIBSC.SSLDR.LONG, 0x0, SPIBSC_SSLDR_SLNDL_SHIFT, SPIBSC_SSLDR_SLNDL);

    /* SSLDR.SCKDL = 0 */
    spibsc_io_reg_write_32(&SPIBSC.SSLDR.LONG, 0x0, SPIBSC_SSLDR_SCKDL_SHIFT, SPIBSC_SSLDR_SCKDL);

    /* DRCR.RBURST = 0x3 */
    spibsc_io_reg_write_32(&SPIBSC.DRCR.LONG, 0x03, SPIBSC_DRCR_RBURST_SHIFT, SPIBSC_DRCR_RBURST);

    /* DRCR.RCF = 1 */
    spibsc_io_reg_write_32(&SPIBSC.DRCR.LONG, 0x01, SPIBSC_DRCR_RCF_SHIFT   , SPIBSC_DRCR_RCF);

    /* DRCR.RBE = 1 */
    spibsc_io_reg_write_32(&SPIBSC.DRCR.LONG, 0x01, SPIBSC_DRCR_RBE_SHIFT   , SPIBSC_DRCR_RBE);

    /* DRCR.SSLE = 1 */
    spibsc_io_reg_write_32(&SPIBSC.DRCR.LONG, 0x1, SPIBSC_DRCR_SSLE_SHIFT  , SPIBSC_DRCR_SSLE);


    /* DREAR.EAV = 0 */
    spibsc_io_reg_write_32(&SPIBSC.DREAR.LONG, 0x0, SPIBSC_DREAR_EAV_SHIFT , SPIBSC_DREAR_EAV);
    /* DREAR.EAC = 0x3 */
    spibsc_io_reg_write_32(&SPIBSC.DREAR.LONG, 0x3, SPIBSC_DREAR_EAC_SHIFT , SPIBSC_DREAR_EAC);

    /* ---- DRDRENR ---- */
    spibsc_io_reg_write_32(&SPIBSC.DRDRENR.LONG, 0x0, SPIBSC_DRDRENR_HYPE_SHIFT , SPIBSC_DRDRENR_HYPE);

    /* ---- PHYCNT ---- */
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x3, SPIBSC_PHYCNT_CKSEL_SHIFT   , SPIBSC_PHYCNT_CKSEL);
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_CAL_SHIFT     , SPIBSC_PHYCNT_CAL);
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_ALT_ALIGN_SHIFT, SPIBSC_PHYCNT_ALT_ALIGN);
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_OCTA_1_0_SHIFT, SPIBSC_PHYCNT_OCTA_1_0);
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_EXDS_SHIFT    , SPIBSC_PHYCNT_EXDS);
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_OCT_SHIFT     , SPIBSC_PHYCNT_OCT);
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_HS_SHIFT      , SPIBSC_PHYCNT_HS);
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_WBUF2_SHIFT   , SPIBSC_PHYCNT_WBUF2);
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_WBUF_SHIFT    , SPIBSC_PHYCNT_WBUF);
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_PHYMEM_SHIFT  , SPIBSC_PHYCNT_PHYMEM); /* SDR SPI Flash Memory */

    /* ---- PHYOFFSET1 ---- */
    spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET1.LONG, 0x3, SPIBSC_PHYOFFSET1_DDRTMG_SHIFT, SPIBSC_PHYOFFSET1_DDRTMG); /* SDR mode */

    /* ---- PHYOFFSET2 ---- */
    spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET2.LONG, 0x4, SPIBSC_PHYOFFSET2_OCTTMG_SHIFT, SPIBSC_PHYOFFSET2_OCTTMG); /* SPI Flash */

    /* PHY Reg Access Enable */
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ2.LONG, 0xA5390000, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ1.LONG, 0x80000000, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* Set PHY Timing Adjust Reg.(for SDR) */
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ2.LONG, 0x00008080, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ1.LONG, 0x80000022, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ2.LONG, 0x00008080, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ1.LONG, 0x80000024, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* Set PHY Timing Adjust(for SDR) */
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ2.LONG, 0x00000000, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ1.LONG, 0x80000032, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

}
/*******************************************************************************
End of function r_spibsc_common_spiflash_init
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_port_voltage_setting
* Description  : voltage setting of SPIBSC pin
* Arguments    : uint8_t voltage
* Return Value : none
*******************************************************************************/
static void r_spibsc_port_voltage_setting(uint8_t voltage)
{
    uint32_t pocsel0_value = 0x1;
    uint32_t poc0_value = 0x1;

    if (SPIBSC_PORT_VOLTAGE_1_8V == voltage)
    {
        pocsel0_value = 0x0;
        poc0_value = 0x0;
    }
    else if ( SPIBSC_PORT_VOLTAGE_3_3V == voltage)
    {
        pocsel0_value = 0x1;
        poc0_value = 0x1;
    }
    else
    {
        /* 3.3V */
    }

    /* PPOC */
    spibsc_io_reg_write_32(&GPIO.PPOC.LONG, pocsel0_value, GPIO_PPOC_POCSEL0_SHIFT, GPIO_PPOC_POCSEL0);
    spibsc_io_reg_write_32(&GPIO.PPOC.LONG, poc0_value, GPIO_PPOC_POC0_SHIFT,    GPIO_PPOC_POC0);

}
/*******************************************************************************
End of function r_spibsc_port_voltage_setting
*******************************************************************************/



/*******************************************************************************
* Function Name: r_spibsc_port_current_setting
* Description  : Current setting of SPIBSC pin
* Arguments    : uint8_t voltage
* Return Value : none
*******************************************************************************/
static void r_spibsc_port_current_setting(uint8_t voltage)
{
    uint32_t reg_value = 0x1;
    
    if( SPIBSC_PORT_VOLTAGE_1_8V == voltage)
    {
        reg_value = 0x3;   /* 1.8V : 12mA */
    }
    else if( SPIBSC_PORT_VOLTAGE_3_3V == voltage)
    {
        reg_value = 0x1;   /* 3.3V : 8mA */
    }
    else
    {
        /* Do Nothing */
    }

    /* PSPIBSC */
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI0_SPCLK_DRV_SHIFT,  GPIO_PSPIBSC_QSPI0_SPCLK_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI0_IO0_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_IO0_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI0_IO1_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_IO1_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI0_IO2_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_IO2_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI0_IO3_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_IO3_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI0_SSL_DRV_SHIFT,    GPIO_PSPIBSC_QSPI0_SSL_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_RPC_RESETN_DRV_SHIFT,   GPIO_PSPIBSC_RPC_RESETN_DRV);

    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_RPC_WPN_DRV_SHIFT,      GPIO_PSPIBSC_RPC_WPN_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI1_SPCLK_DRV_SHIFT,  GPIO_PSPIBSC_QSPI1_SPCLK_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI1_IO0_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_IO0_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI1_IO1_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_IO1_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI1_IO2_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_IO2_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI1_IO3_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_IO3_DRV);
    spibsc_io_reg_write_32(&GPIO.PSPIBSC.LONG, reg_value, GPIO_PSPIBSC_QSPI1_SSL_DRV_SHIFT,    GPIO_PSPIBSC_QSPI1_SSL_DRV);

}
/*******************************************************************************
End of function r_spibsc_port_current_setting
*******************************************************************************/




/*******************************************************************************
* Function Name: r_spibsc_manual_assert_ssl
* Description  : SSL assert keep
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_assert_ssl(void)
{
    /* SMCR.SSLKP = 1 :  (QSPIn_SSL signal level is maintained from the end of transfer 
       to the start of next access)*/
    spibsc_io_reg_write_32(&SPIBSC.SMCR.LONG, 1, SPIBSC_SMCR_SSLKP_SHIFT, SPIBSC_SMCR_SSLKP);
}
/*******************************************************************************
End of function r_spibsc_manual_assert_ssl
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_negate_ssl
* Description  : SSL assert keep
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_negate_ssl(void)
{
    /* SMCR.SSLKP = 0 : QSPIn_SSL signal is negated at the end of transfer. */
    spibsc_io_reg_write_32(&SPIBSC.SMCR.LONG, 0, SPIBSC_SMCR_SSLKP_SHIFT, SPIBSC_SMCR_SSLKP);
}
/*******************************************************************************
End of function r_spibsc_manual_negate_ssl
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_set_command
* Description  : Command Setting (Manual mode)
* Arguments    : uint8_t cmd            : Command
*              : uint8_t width          : Command bus width
*              :                        :   b'00 : 1bit
*              :                        :   b'10 : 4bit
*              : uint8_t output_enable  : Command output enable
*              :                        :      0 : Command output disabled
*              :                        :      1 : Command output enabled
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_set_command(uint8_t cmd, uint8_t width, uint8_t output_enable)
{

    /* SMCMR.CMD[7:0] = cmd (SPI Command code setting) */
    spibsc_io_reg_write_32(&SPIBSC.SMCMR.LONG, cmd,          SPIBSC_SMCMR_CMD_SHIFT, SPIBSC_SMCMR_CMD);

    /* SMENR.CDB[1:0] = width (SPI Command width setting : 1bit or 4bit ) */
    spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, width & 0x03, SPIBSC_SMENR_CDB_SHIFT, SPIBSC_SMENR_CDB);

    if( SPIBSC_OUTPUT_ENABLE == output_enable)
    {
        /* SMENR.CDE = 1 (Command output enabled) */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_ENABLE, SPIBSC_SMENR_CDE_SHIFT, SPIBSC_SMENR_CDE);
    }
    else
    {
        /* SMENR.CDE = 0 (Command output disabled) */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_DISABLE, SPIBSC_SMENR_CDE_SHIFT, SPIBSC_SMENR_CDE);
    }

}
/*******************************************************************************
End of function r_spibsc_manual_set_command
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_manual_set_optional_command
* Description  : Optional Command Setting (Manual mode)
* Arguments    : uint8_t ocmd           : Optional command
*              : uint8_t width          : Optional command bus width
*              :                        :   b'00 : 1bit
*              :                        :   b'10 : 4bit
*              : uint8_t output_enable  : Command output enable
*              :                        :      0 : Optional command output disabled
*              :                        :      1 : Optional command output enabled
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_set_optional_command(uint8_t ocmd, uint8_t width, uint8_t output_enable)
{

    /* SMCMR.OCMD[7:0] = ocmd (SPI Optional Command code setting) */
    spibsc_io_reg_write_32(&SPIBSC.SMCMR.LONG, ocmd,         SPIBSC_SMCMR_OCMD_SHIFT, SPIBSC_SMCMR_OCMD);

    /* SMENR.OCDB[1:0] = ocmd (SPI Optional Command width setting : 1bit or 4bit ) */
    spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, width & 0x03, SPIBSC_SMENR_OCDB_SHIFT, SPIBSC_SMENR_OCDB);

    if( SPIBSC_OUTPUT_ENABLE == output_enable)
    {
        /* SMENR.OCDE = 1 (Optional command output enabled) */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_ENABLE, SPIBSC_SMENR_OCDE_SHIFT, SPIBSC_SMENR_OCDE);
    }
    else
    {
        /* SMENR.OCDE = 0 (Optional command output disabled) */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_DISABLE, SPIBSC_SMENR_OCDE_SHIFT, SPIBSC_SMENR_OCDE);
    }

}
/*******************************************************************************
End of function r_spibsc_manual_set_optional_command
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_manual_set_address
* Description  : Address Setting (Manual mode)
*              : uint32_t address               : Address
*              : uint8_t width                  : Address bus width
*              :                                :   b'00 : 1bit
*              :                                :   b'10 : 4bit
*              : uint8_t address_output_enable  : Address output enable
*              :                                :   b'0000 : Address output disabled
*              :                                :   b'0100 : SMADR.ADR[23:16] output enabled
*              :                                :   b'0110 : SMADR.ADR[23:8] output enabled
*              :                                :   b'0111 : SMADR.ADR[23:0] output enabled
*              :                                :   b'1111 : SMADR.ADR[31:0] output enabled
*              : uint8_t ddr_enable             : Address DDR Enable
*              :                                :   0 : SDR transfer
*              :                                :   1 : DDR transfer
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_set_address(uint32_t address, uint8_t width, uint8_t address_output_enable, uint8_t ddr_enable)
{

    /* SMADR.ADR[31:0] = address (Address setting) */
    spibsc_io_reg_write_32(&SPIBSC.SMADR.LONG, address, SPIBSC_SMADR_ADR_SHIFT, SPIBSC_SMADR_ADR);

    /* SMENR.ADB[1:0] = width (Address width setting) */
    spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, width & 0x03, SPIBSC_SMENR_ADB_SHIFT, SPIBSC_SMENR_ADB);

    if( 0xf == address_output_enable)
    {
        /* SMENR.ADE[3:0] = b'1111 : SMADR.ADR[31:0] output enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, 0xf, SPIBSC_SMENR_ADE_SHIFT, SPIBSC_SMENR_ADE);
    }
    else if( 0x7 == address_output_enable)
    {
        /* SMENR.ADE[3:0] = b'0111 : SMADR.ADR[23:0] output enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, 0x7, SPIBSC_SMENR_ADE_SHIFT, SPIBSC_SMENR_ADE);
    }
    else if( 0x6 == address_output_enable)
    {
        /* SMENR.ADE[3:0] = b'0110 : SMADR.ADR[23:8] output enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, 0x6, SPIBSC_SMENR_ADE_SHIFT, SPIBSC_SMENR_ADE);
    }
    else if( 0x4 == address_output_enable)
    {
        /* SMENR.ADE[3:0] = b'0100 : SMADR.ADR[23:16] output enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, 0x4, SPIBSC_SMENR_ADE_SHIFT, SPIBSC_SMENR_ADE);
    }
    else if( 0x0 == address_output_enable)
    {
        /* SMENR.ADE[3:0] = b'0000 : Address output disabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, 0x0, SPIBSC_SMENR_ADE_SHIFT, SPIBSC_SMENR_ADE);
    }

    if( 1 == ddr_enable)
    {
        /* SMDRENR.ADDRE = 1 : ADDRESS is DDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.SMDRENR.LONG, 1, SPIBSC_SMDRENR_ADDRE_SHIFT, SPIBSC_SMDRENR_ADDRE);
    }
    else
    {
        /* SMDRENR.ADDRE = 0 : ADDRESS is SDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.SMDRENR.LONG, 0, SPIBSC_SMDRENR_ADDRE_SHIFT, SPIBSC_SMDRENR_ADDRE);
    }

}
/*******************************************************************************
End of function r_spibsc_manual_set_address
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_manual_set_option_data
* Description  : Option Data Setting (Manual mode)
* Arguments    : uint8_t opd3           : Option Data 3
*              : uint8_t opd2           : Option Data 2
*              : uint8_t opd1           : Option Data 1
*              : uint8_t opd0           : Option Data 0
*              : uint8_t width          : Option Data bus width
*              :                        :   b'00 : 1bit
*              :                        :   b'10 : 4bit
*              : uint8_t option_data_output_enable  : Option Data output enable
*              :                        :              b'0000 : Option Data Output disabled
*              :                        :              b'1000 : OPD3 output enabled
*              :                        :              b'1100 : OPD3, OPD2 output enabled
*              :                        :              b'1110 : OPD3, OPD2, OPD1 output enabled
*              :                        :              b'1111 : OPD3, OPD2, OPD1, OPD0 output enabled
*              : uint8_t ddr_enable     : Option Data DDR Enable
*              :                        :   0 : SDR
*              :                        :   1 : DDR
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_set_option_data(uint8_t opd3, uint8_t opd2, uint8_t opd1, uint8_t opd0, 
                                     uint8_t width, uint8_t option_data_output_enable, uint8_t ddr_enable)
{

    /* SMOPR.OPD3[7:0] = opd3 */
    spibsc_io_reg_write_32(&SPIBSC.SMOPR.LONG, opd3, SPIBSC_SMOPR_OPD3_SHIFT, SPIBSC_SMOPR_OPD3);  /* 1st output data */

    /* SMOPR.OPD2[7:0] = opd2 */
    spibsc_io_reg_write_32(&SPIBSC.SMOPR.LONG, opd2, SPIBSC_SMOPR_OPD2_SHIFT, SPIBSC_SMOPR_OPD2);  /* 2nd output data */

    /* SMOPR.OPD1[7:0] = opd1 */
    spibsc_io_reg_write_32(&SPIBSC.SMOPR.LONG, opd1, SPIBSC_SMOPR_OPD1_SHIFT, SPIBSC_SMOPR_OPD1);  /* 3rd output data */

    /* SMOPR.OPD0[7:0] = opd0 */
    spibsc_io_reg_write_32(&SPIBSC.SMOPR.LONG, opd0, SPIBSC_SMOPR_OPD0_SHIFT, SPIBSC_SMOPR_OPD0);  /* 4th output data */

    /* SMENR.OPDB[1:0] = width  (SPI Option Data width setting : 1bit or 4bit ) */
    spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, width & 0x03, SPIBSC_SMENR_OPDB_SHIFT, SPIBSC_SMENR_OPDB);


    if( 0x0 == option_data_output_enable)
    {
        /* SMENR.OPDE[3:0] = b'0000 : Option Data Output disabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, 0, SPIBSC_SMENR_OPDE_SHIFT, SPIBSC_SMENR_OPDE);
    }
    else if ( SPIBSC_OUTPUT_OPD_3 == option_data_output_enable)
    {
        /* SMENR.OPDE[3:0] = b'1000 : DATA is DDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_OPD_3, SPIBSC_SMENR_OPDE_SHIFT, SPIBSC_SMENR_OPDE);
    }
    else if ( SPIBSC_OUTPUT_OPD_32 == option_data_output_enable)
    {
        /* SMENR.OPDE[3:0] = b'1100 : OPD3, OPD2 output enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_OPD_32, SPIBSC_SMENR_OPDE_SHIFT, SPIBSC_SMENR_OPDE);
    }
    else if ( SPIBSC_OUTPUT_OPD_321 == option_data_output_enable)
    {
        /* SMENR.OPDE[3:0] = b'1110 : OPD3, OPD2, OPD1 output enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_OPD_321, SPIBSC_SMENR_OPDE_SHIFT, SPIBSC_SMENR_OPDE);
    }
    else if ( SPIBSC_OUTPUT_OPD_3210 == option_data_output_enable)
    {
        /* SMENR.OPDE[3:0] = b'1111 : OPD3, OPD2, OPD1, OPD0 output enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_OPD_3210, SPIBSC_SMENR_OPDE_SHIFT, SPIBSC_SMENR_OPDE);
    }


    if ( 1 == ddr_enable)
    {
        /* SMDRENR.OPDRE = 1 : OPTION DATA is DDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.SMDRENR.LONG, 1, SPIBSC_SMDRENR_OPDRE_SHIFT, SPIBSC_SMDRENR_OPDRE);
    }
    else
    {
        /* SMDRENR.OPDRE = 1 : OPTION DATA is SDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.SMDRENR.LONG, 0, SPIBSC_SMDRENR_OPDRE_SHIFT, SPIBSC_SMDRENR_OPDRE);
    }

}
/*******************************************************************************
End of function r_spibsc_manual_set_option_data
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_set_dummy_cycle
* Description  : Dummy Cycle Setting (Manual mode)
* Arguments    : uint8_t dummy_cycle_num : Number of Dummy Cycles
*              :                         : b'00000   :  1 cycle
*              :                         : b'00001   :  2 cycle
*              :                         : b'00010   :  3 cycle
*              :                         : ...
*              :                         : b'10011   : 20 cycle
*              : uint8_t width           : Dummy Cycle bus width
*              :                         :   b'00 : 1bit
*              :                         :   b'10 : 4bit
*              : uint8_t output_enable  : Dummy Cycle output enable
*              :                        :      0 : Dummy Cycle output disabled
*              :                        :      1 : Dummy Cycle output enabled
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_set_dummy_cycle(uint8_t dummy_cycle_num, uint8_t width, uint8_t output_enable)
{
    spibsc_io_reg_write_32(&SPIBSC.SMDMCR.LONG, dummy_cycle_num, SPIBSC_SMDMCR_DMCYC_SHIFT, SPIBSC_SMDMCR_DMCYC);

    /* Since the version of UM has changed from 0.5 to 1.0 and the DMDB bit has been deleted, comment out the next line */
/*    SPIBSC_IO_RegWrite_32(&SPIBSC.SMDMCR.LONG, width,           SPIBSC_SMDMCR_DMDB_SHIFT,  SPIBSC_SMDMCR_DMDB);*/
    UNUSED_PARAM(width);

    if ( SPIBSC_OUTPUT_ENABLE == output_enable)
    {
        /* SMENR.DME = 1 : Dummy cycle output enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_ENABLE, SPIBSC_SMENR_DME_SHIFT, SPIBSC_SMENR_DME);
    }
    else
    {
        /* SMENR.DME = 0 : Dummy Cycle output disabled */
        spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, SPIBSC_OUTPUT_DISABLE, SPIBSC_SMENR_DME_SHIFT, SPIBSC_SMENR_DME);
    }

}
/*******************************************************************************
End of function r_spibsc_manual_set_dummy_cycle
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_set_datatransfer
* Description  : Option Data Setting (Manual mode)
* Arguments    : uint8_t transfer_unit  : Transfer Unit size
*              :                        :    b'0000: Not transferred
*              :                        :    b'1000: 8 bits transferred
*              :                        :    b'1100: 16 bits transferred
*              :                        :    b'1111: 32 bits transferred
*              : uint8_t width          : Data bus width
*              :                        :   b'00 : 1bit
*              :                        :   b'10 : 4bit
*              : uint8_t write_enable   : Data Write Enable
*              :                        :   0 : Data writing disabled
*              :                        :   1 : Data writing enabled
*              : uint8_t read_enable    : Data Read Enable
*              :                        :   0 : Data reading disabled
*              :                        :   1 : Data reading enabled
*              : uint8_t ddr_enable     : Data DDR Enable
*              :                        :   0 : SDR
*              :                        :   1 : DDR
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_set_datatransfer(uint8_t transfer_unit,uint8_t width,uint8_t write_enable, uint8_t read_enable, uint8_t ddr_enable)
{

    spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, transfer_unit, SPIBSC_SMENR_SPIDE_SHIFT, SPIBSC_SMENR_SPIDE);
    spibsc_io_reg_write_32(&SPIBSC.SMENR.LONG, width,         SPIBSC_SMENR_SPIDB_SHIFT, SPIBSC_SMENR_SPIDB);


    if ( 1 == write_enable)
    {
        /* SMCR.SPIWE = 1 : Data writing enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMCR.LONG, 1, SPIBSC_SMCR_SPIWE_SHIFT, SPIBSC_SMCR_SPIWE);
    }
    else
    {
        /* SMCR.SPIWE = 0 : Data writing disabled */
        spibsc_io_reg_write_32(&SPIBSC.SMCR.LONG, 0, SPIBSC_SMCR_SPIWE_SHIFT, SPIBSC_SMCR_SPIWE);
    }

    if ( 1 == read_enable)
    {
        /* SMCR.SPIRE = 1 : Data reading enabled */
        spibsc_io_reg_write_32(&SPIBSC.SMCR.LONG, 1, SPIBSC_SMCR_SPIRE_SHIFT, SPIBSC_SMCR_SPIRE);
    }
    else
    {
        /* SMCR.SPIRE = 0 : Data reading disabled */
        spibsc_io_reg_write_32(&SPIBSC.SMCR.LONG, 0, SPIBSC_SMCR_SPIRE_SHIFT, SPIBSC_SMCR_SPIRE);
    }


    if ( 1 == ddr_enable )
    {
        /* SMDRENR.SPIDRE = 1 : TRANSFER DATA is DDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.SMDRENR.LONG, 1, SPIBSC_SMDRENR_SPIDRE_SHIFT, SPIBSC_SMDRENR_SPIDRE);
    }
    else
    {
        /* SMDRENR.SPIDRE = 0 : TRANSFER DATA is SDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.SMDRENR.LONG, 0, SPIBSC_SMDRENR_SPIDRE_SHIFT, SPIBSC_SMDRENR_SPIDRE);
    }

}
/*******************************************************************************
End of function r_spibsc_manual_set_datatransfer
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_start_transfer
* Description  : Start Transfer  (Manual mode)
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_start_transfer(void)
{

    /* PHYCNT.CAL = 1 : Calibration Setting */
    spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 1, SPIBSC_PHYCNT_CAL_SHIFT, SPIBSC_PHYCNT_CAL);

    /* SMCR.SPIE = 1 : Start Transfer  */
    spibsc_io_reg_write_32(&SPIBSC.SMCR.LONG,   1, SPIBSC_SMCR_SPIE_SHIFT,  SPIBSC_SMCR_SPIE);
}
/*******************************************************************************
End of function r_spibsc_manual_start_transfer
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_wait_tend
* Description  : Wait Transfer End (Manual mode)
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void r_spibsc_wait_tend(void)
{

    uint32_t tend;
    
    do{

        /* Read CMNSR.TEND */
       tend = spibsc_io_reg_read_32(&SPIBSC.CMNSR.LONG, SPIBSC_CMNSR_TEND_SHIFT, SPIBSC_CMNSR_TEND);
       
    }while( 0 == tend );

}
/*******************************************************************************
End of function r_spibsc_wait_tend
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_read_data0_8
* Description  : Read SMRDR0 register (8bit access)
* Arguments    : none
* Return Value : read data from SMRDR0 (8bit)
*******************************************************************************/
static uint8_t r_spibsc_manual_read_data0_8(void)
{
    uint8_t data;

    /* Read SMRDR0 register (8bit access) */
    data = spibsc_io_reg_read_8(&SPIBSC.SMRDR0.BYTE.LL, SPIBSC_SMRDR0_RDATA0_SHIFT,  (uint8_t)SPIBSC_SMRDR0_RDATA0);
    return  data;
}
/*******************************************************************************
End of function r_spibsc_manual_read_data0_8
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_read_data0_16
* Description  : Read SMRDR0 register (16bit access)
* Arguments    : none
* Return Value : read data from SMRDR0 (16bit)
*******************************************************************************/
static uint16_t r_spibsc_manual_read_data0_16(void)
{
    uint16_t data;

    /* Read SMRDR0 register (16bit access) */
    data = spibsc_io_reg_read_16(&SPIBSC.SMRDR0.WORD.L, SPIBSC_SMRDR0_RDATA0_SHIFT,  (uint16_t)SPIBSC_SMRDR0_RDATA0);

    return  data;
}
/*******************************************************************************
End of function r_spibsc_manual_read_data0_16
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_read_data0_32
* Description  : Read SMRDR0 register (32bit access)
* Arguments    : none
* Return Value : read data from SMRDR0 (32bit)
*******************************************************************************/
static uint32_t r_spibsc_manual_read_data0_32(void)
{
    uint32_t data;

    /* Read SMRDR0 register (32bit access) */
    data = spibsc_io_reg_read_32(&SPIBSC.SMRDR0.LONG, SPIBSC_SMRDR0_RDATA0_SHIFT, SPIBSC_SMRDR0_RDATA0);

    return data;
}
/*******************************************************************************
End of function r_spibsc_manual_read_data0_32
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_read_data1_8
* Description  : Read SMRDR1 register (8bit access)
* Arguments    : none
* Return Value : read data from SMRDR1 (8bit)
*******************************************************************************/
static uint8_t r_spibsc_manual_read_data1_8(void)
{
    uint8_t data;

    /* Read SMRDR1 register (8bit access) */
    data = spibsc_io_reg_read_8(&SPIBSC.SMRDR1.BYTE.LL, SPIBSC_SMRDR1_RDATA1_SHIFT,  (uint8_t)SPIBSC_SMRDR1_RDATA1);

    return data;
}
/*******************************************************************************
End of function r_spibsc_manual_read_data1_8
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_manual_read_data1_16
* Description  : Read SMRDR1 register (16bit access)
* Arguments    : none
* Return Value : read data from SMRDR1 (16bit)
*******************************************************************************/
static uint16_t r_spibsc_manual_read_data1_16(void)
{
    uint16_t data;
    
    /* Read SMRDR1 register (16bit access) */
    data = spibsc_io_reg_read_16(&SPIBSC.SMRDR1.WORD.L, SPIBSC_SMRDR1_RDATA1_SHIFT, (uint16_t)SPIBSC_SMRDR1_RDATA1);
    
    return data;
}
/*******************************************************************************
End of function r_spibsc_manual_read_data1_16
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_manual_read_data1_32
* Description  : Read SMRDR1 register (32bit access)
* Arguments    : none
* Return Value : read data from SMRDR1 (32bit)
*******************************************************************************/
static uint32_t r_spibsc_manual_read_data1_32(void)
{
    uint32_t data;
    
    /* Read SMRDR1 register (32bit access) */
    data = spibsc_io_reg_read_32(&SPIBSC.SMRDR1.LONG, SPIBSC_SMRDR1_RDATA1_SHIFT,  SPIBSC_SMRDR1_RDATA1);
    
    return data;
}
/*******************************************************************************
End of function r_spibsc_manual_read_data1_32
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_write_data0_8
* Description  : Write SMRDR0 register (8bit access)
* Arguments    : Write Data to SMWDR0 (8bit)
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_write_data0_8(uint8_t write_data)
{
    /* Write SMRDR0 register (8bit access) */
    spibsc_io_reg_write_8(&SPIBSC.SMWDR0.BYTE.LL, write_data, SPIBSC_SMWDR0_WDATA0_SHIFT, (uint8_t)SPIBSC_SMWDR0_WDATA0);
}
/*******************************************************************************
End of function r_spibsc_manual_write_data0_8
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_write_data0_16
* Description  : Write SMRDR0 register (16bit access)
* Arguments    : Write Data to SMWDR0 (16bit)
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_write_data0_16(uint16_t write_data)
{
    /* Write SMRDR0 register (16bit access) */
    spibsc_io_reg_write_16(&SPIBSC.SMWDR0.WORD.L, write_data, SPIBSC_SMWDR0_WDATA0_SHIFT, (uint16_t)SPIBSC_SMWDR0_WDATA0);
}
/*******************************************************************************
End of function r_spibsc_manual_write_data0_16
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_write_data0_32
* Description  : Write SMRDR0 register (32bit access)
* Arguments    : Write Data to SMWDR0 (32bit)
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_write_data0_32(uint32_t write_data)
{
    /* Write SMRDR0 register (32bit access) */
    spibsc_io_reg_write_32(&SPIBSC.SMWDR0.LONG, write_data, SPIBSC_SMWDR0_WDATA0_SHIFT, SPIBSC_SMWDR0_WDATA0);
}
/*******************************************************************************
End of function r_spibsc_manual_write_data0_32
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_manual_write_data1_8
* Description  : Write SMRDR1 register (8bit access)
* Arguments    : Write Data to SMWDR1 (8bit)
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_write_data1_8(uint8_t write_data)
{
    /* Write SMRDR1 register (8bit access) */
    spibsc_io_reg_write_8(&SPIBSC.SMWDR1.BYTE.LL, write_data, SPIBSC_SMWDR1_WDATA1_SHIFT, (uint8_t)SPIBSC_SMWDR1_WDATA1);
}
/*******************************************************************************
End of function r_spibsc_manual_write_data1_8
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_manual_write_data1_16
* Description  : Write SMRDR1 register (16bit access)
* Arguments    : Write Data to SMWDR1 (16bit)
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_write_data1_16(uint16_t write_data)
{

    /* Write SMRDR1 register (16bit access) */
    spibsc_io_reg_write_16(&SPIBSC.SMWDR1.WORD.L, write_data, SPIBSC_SMWDR1_WDATA1_SHIFT, (uint16_t)SPIBSC_SMWDR1_WDATA1);
}
/*******************************************************************************
End of function r_spibsc_manual_write_data1_16
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_manual_write_data1_32
* Description  : Write SMRDR1 register (32bit access)
* Arguments    : Write Data to SMWDR1 (32bit)
* Return Value : none
*******************************************************************************/
static void r_spibsc_manual_write_data1_32(uint32_t write_data)
{
    /* Write SMRDR1 register (32bit access) */
    spibsc_io_reg_write_32(&SPIBSC.SMWDR1.LONG, write_data, SPIBSC_SMWDR1_WDATA1_SHIFT, SPIBSC_SMWDR1_WDATA1);
}
/*******************************************************************************
End of function r_spibsc_manual_write_data1_32
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_xip_set_command
* Description  : Command Setting (External address space read mode (XIP) )
* Arguments    : uint8_t cmd            : Command
*              : uint8_t width          : Command bus width
*              :                        :   b'00 : 1bit
*              :                        :   b'01 : 2bit
*              :                        :   b'10 : 4bit
*              : uint8_t output_enable  : Command output enable
*              :                        :      0 : Command output disabled
*              :                        :      1 : Command output enabled
* Return Value : none
*******************************************************************************/
static void r_spibsc_xip_set_command(uint8_t cmd, uint8_t width, uint8_t output_enable)
{

    /* DRCMR.CMD[7:0] = cmd */
    spibsc_io_reg_write_32(&SPIBSC.DRCMR.LONG, cmd,         SPIBSC_DRCMR_CMD_SHIFT, SPIBSC_DRCMR_CMD);

    /* DRENR.CDB[1:0] = width */
    spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, width & 0x3, SPIBSC_DRENR_CDB_SHIFT, SPIBSC_DRENR_CDB);

    if( SPIBSC_OUTPUT_ENABLE == output_enable)
    {
        /* DRENR.CDE = 1 : Command output enabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_ENABLE, SPIBSC_DRENR_CDE_SHIFT, SPIBSC_DRENR_CDE);
    }
    else
    {
        /* DRENR.CDE = 0 : Command output disabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_DISABLE, SPIBSC_DRENR_CDE_SHIFT, SPIBSC_DRENR_CDE);
    }

}
/*******************************************************************************
End of function r_spibsc_xip_set_command
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_xip_set_optional_command
* Description  : Optional Command Setting (External address space read mode (XIP) )
* Arguments    : uint8_t ocmd           : Optional command code
*              : uint8_t width          : Optional command bus width
*              :                        :   b'00 : 1bit
*              :                        :   b'10 : 4bit
*              : uint8_t output_enable  : Optional Command output enable
*              :                        :      0 : Optional command output disabled
*              :                        :      1 : Optional command output enabled
* Return Value : none
*******************************************************************************/
static void r_spibsc_xip_set_optional_command(uint8_t ocmd, uint8_t width, uint8_t output_enable)
{
    /* DRCMR.OCMD[7:0] = ocmd */
    spibsc_io_reg_write_32(&SPIBSC.DRCMR.LONG, ocmd, SPIBSC_DRCMR_OCMD_SHIFT, SPIBSC_DRCMR_OCMD);

    /* DRENR.OCDB[1:0] = width */
    spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, width & 0x3 , SPIBSC_DRENR_OCDB_SHIFT, SPIBSC_DRENR_OCDB);


    if( SPIBSC_OUTPUT_ENABLE == output_enable)
    {
        /* DRENR.OCDE = 1 : Optional command output enabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_ENABLE, SPIBSC_DRENR_OCDE_SHIFT, SPIBSC_DRENR_OCDE);
    }
    else
    {
        /* DRENR.OCDE = 0 : Optional command output disabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_DISABLE, SPIBSC_DRENR_OCDE_SHIFT, SPIBSC_DRENR_OCDE);
    }

}
/*******************************************************************************
End of function r_spibsc_xip_set_optional_command
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_xip_set_address
* Description  : Address Setting (External address space read mode (XIP) )
*              : uint8_t width                  : Address bus width
*              :                                :   b'00 : 1bit
*              :                                :   b'01 : 2bit
*              :                                :   b'10 : 4bit
*              : uint8_t address_output_enable  : Address output enable
*              :                                :   b'0000 : Address output disabled
*              :                                :   b'0111 : Address[23:0] output enabled
*              :                                :   b'1111 : Address[31:0] output enabled
*              : uint8_t ddr_enable             : Address DDR Enable
*              :                                :   0 : SDR
*              :                                :   1 : DDR
* Return Value : none
*******************************************************************************/
static void r_spibsc_xip_set_address(uint8_t width, uint8_t address_output_enable, uint8_t ddr_enable)
{

    /* DRENR.ADB[1:0] = width */
    spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, width & 0x3, SPIBSC_DRENR_ADB_SHIFT, SPIBSC_DRENR_ADB);

    if( SPIBSC_OUTPUT_ADDR_32 == address_output_enable )
    {
        /* DRENR.ADE[3:0] = b'1111 : Address[31:0] output enabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_ADDR_32, SPIBSC_DRENR_ADE_SHIFT, SPIBSC_DRENR_ADE);
    }
    else if( SPIBSC_OUTPUT_ADDR_24 == address_output_enable)
    {
        /* DRENR.ADE[3:0] = b'0111 :  Address[23:0] output enabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_ADDR_24, SPIBSC_DRENR_ADE_SHIFT, SPIBSC_DRENR_ADE);
    }
    else if( 0x0 == address_output_enable)
    {
        /* DRENR.ADE[3:0] = b'0000 : Address output disabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, 0, SPIBSC_DRENR_ADE_SHIFT, SPIBSC_DRENR_ADE);
    }

    if( 1 == ddr_enable)
    {
        /* DRDRENR.ADDRE = 1 : ADDRESS is DDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.DRDRENR.LONG, SPIBSC_DDR_TRANSFER, SPIBSC_DRDRENR_ADDRE_SHIFT, SPIBSC_DRDRENR_ADDRE);
    }
    else
    {
       /* DRDRENR.ADDRE = 0 : ADDRESS is SDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.DRDRENR.LONG, SPIBSC_SDR_TRANSFER, SPIBSC_DRDRENR_ADDRE_SHIFT, SPIBSC_DRDRENR_ADDRE);
    }

}
/*******************************************************************************
End of function r_spibsc_xip_set_address
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_xip_set_option_data
* Description  : Option Data Setting (External address space read mode (XIP) )
* Arguments    : uint8_t opd3           : Option Data 3
*              : uint8_t opd2           : Option Data 2
*              : uint8_t opd1           : Option Data 1
*              : uint8_t opd0           : Option Data 0
*              : uint8_t width          : Option Data bus width
*              :                        :   b'00 : 1bit
*              :                        :   b'10 : 4bit
*              : uint8_t option_data_output_enable  : Option Data output enable
*              :                        :              b'0000 : Option Data Output disabled
*              :                        :              b'1000 : OPD3 output enabled
*              :                        :              b'1100 : OPD3, OPD2 output enabled
*              :                        :              b'1110 : OPD3, OPD2, OPD1 output enabled
*              :                        :              b'1111 : OPD3, OPD2, OPD1, OPD0 output enabled
*              : uint8_t ddr_enable     : Option Data DDR Enable
*              :                        :   0 : SDR
*              :                        :   1 : DDR
* Return Value : none
*******************************************************************************/
static void r_spibsc_xip_set_option_data(uint8_t opd3, uint8_t opd2, uint8_t opd1, uint8_t opd0,
                                  uint8_t width, uint8_t option_data_output_enable, uint8_t ddr_enable)
{

    /* DROPR.OPD3[7:0] = opd3 */
    spibsc_io_reg_write_32(&SPIBSC.DROPR.LONG, opd3, SPIBSC_DROPR_OPD3_SHIFT, SPIBSC_DROPR_OPD3);  /* 1st output data */

    /* DROPR.OPD2[7:0] = opd2 */
    spibsc_io_reg_write_32(&SPIBSC.DROPR.LONG, opd2, SPIBSC_DROPR_OPD2_SHIFT, SPIBSC_DROPR_OPD2);  /* 2nd output data */

    /* DROPR.OPD1[7:0] = opd1 */
    spibsc_io_reg_write_32(&SPIBSC.DROPR.LONG, opd1, SPIBSC_DROPR_OPD1_SHIFT, SPIBSC_DROPR_OPD1);  /* 3rd output data */

    /* DROPR.OPD0[7:0] = opd0 */
    spibsc_io_reg_write_32(&SPIBSC.DROPR.LONG, opd0, SPIBSC_DROPR_OPD0_SHIFT, SPIBSC_DROPR_OPD0);  /* 4th output data */

    /* DRENR.OPDB[1:0] = width */
    spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, width & 0x3 , SPIBSC_DRENR_OPDB_SHIFT, SPIBSC_DRENR_OPDB);

    if( SPIBSC_OUTPUT_OPD_3210 == option_data_output_enable)
    {
        /* DRENR.OPDE[3:0] = b'1111 : OPD3, OPD2, OPD1, OPD0 output enabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_OPD_3210, SPIBSC_DRENR_OPDE_SHIFT, SPIBSC_DRENR_OPDE);
    }
    else if( SPIBSC_OUTPUT_OPD_321 == option_data_output_enable)
    {
        /* DRENR.OPDE[3:0] = b'1110 : OPD3, OPD2, OPD1 output enabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_OPD_321, SPIBSC_DRENR_OPDE_SHIFT, SPIBSC_DRENR_OPDE);
    }
    else if( SPIBSC_OUTPUT_OPD_32 == option_data_output_enable)
    {
        /* DRENR.OPDE[3:0] = b'1100 : OPD3, OPD2 output enabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_OPD_32, SPIBSC_DRENR_OPDE_SHIFT, SPIBSC_DRENR_OPDE);
    }
    else if( SPIBSC_OUTPUT_OPD_3 == option_data_output_enable)
    {
        /* DRENR.OPDE[3:0] = b'1000 : OPD3 output enabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, SPIBSC_OUTPUT_OPD_3, SPIBSC_DRENR_OPDE_SHIFT, SPIBSC_DRENR_OPDE);
    }
    else
    {
        /* DRENR.OPDE[3:0] = b'0000 : Option Data Output disabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, 0x0, SPIBSC_DRENR_OPDE_SHIFT, SPIBSC_DRENR_OPDE);
    }


    if( 1 == ddr_enable)
    {
        /* DRDRENR.OPDRE = 1 : OPTION DATA is DDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.DRDRENR.LONG, SPIBSC_DDR_TRANSFER, SPIBSC_DRDRENR_OPDRE_SHIFT, SPIBSC_DRDRENR_OPDRE);
    }
    else
    {
        /* DRDRENR.OPDRE = 0 : OPTION DATA is SDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.DRDRENR.LONG, SPIBSC_SDR_TRANSFER, SPIBSC_DRDRENR_OPDRE_SHIFT, SPIBSC_DRDRENR_OPDRE);
    }

}
/*******************************************************************************
End of function r_spibsc_xip_set_option_data
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_xip_set_dummy_cycle
* Description  : Dummy Cycle Setting (External address space read mode (XIP) )
* Arguments    : uint8_t dummy_cycle_num : Number of Dummy Cycles
*              :                         : b'00000   :  1 cycle
*              :                         : b'00001   :  2 cycle
*              :                         : b'00010   :  3 cycle
*              :                         : ...
*              :                         : b'10011   : 20 cycle
*              : uint8_t width           : Dummy Cycle bus width
*              :                         :   b'00 : 1bit
*              :                         :   b'10 : 4bit
*              : uint8_t output_enable  : Dummy Cycle output enable
*              :                        :      0 : Dummy Cycle output disabled
*              :                        :      1 : Dummy Cycle output enabled
* Return Value : none
*******************************************************************************/
static void r_spibsc_xip_set_dummy_cycle(uint8_t dummy_cycle_num, uint8_t width, uint8_t output_enable)
{
    /* Casting the pointer to a uint32_t type is valid because "unsigned long" is same 4byte unsigned integer type. */
    spibsc_io_reg_write_32(&SPIBSC.DRDMCR.LONG, dummy_cycle_num, SPIBSC_DRDMCR_DMCYC_SHIFT, SPIBSC_DRDMCR_DMCYC);

    /* Since the version of UM has changed from 0.5 to 1.0 and the DMDB bit has been deleted, comment out the next line */
/*    SPIBSC_IO_RegWrite_32(&SPIBSC.DRDMCR.LONG, width,           SPIBSC_DRDMCR_DMDB_SHIFT,  SPIBSC_DRDMCR_DMDB);*/
    UNUSED_PARAM(width);

    if( 1 == output_enable)
    {
        /* DRENR.DME = 1 : Dummy Cycle output enabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, 1, SPIBSC_DRENR_DME_SHIFT, SPIBSC_DRENR_DME);
    }
    else
    {
        /* DRENR.DME = 0 : : Dummy Cycle output disabled */
        spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, 0, SPIBSC_DRENR_DME_SHIFT, SPIBSC_DRENR_DME);
    }

}
/*******************************************************************************
End of function r_spibsc_xip_set_dummy_cycle
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_xip_set_datatransfer
* Description  : Data Transfer Setting (External address space read mode (XIP) )
* Arguments    : uint8_t width          : Data bus width
*              :                        :   b'00 : 1bit
*              :                        :   b'01 : 2bit
*              :                        :   b'10 : 4bit
*              : uint8_t ddr_enable     : Data DDR Enable
*              :                        :   0 : SDR
*              :                        :   1 : DDR
* Return Value : none
*******************************************************************************/
static void r_spibsc_xip_set_datatransfer(uint8_t width, uint8_t ddr_enable)
{

    /* Casting the pointer to a uint32_t type is valid because "unsigned long" is same 4byte unsigned integer type. */
    spibsc_io_reg_write_32(&SPIBSC.DRENR.LONG, width, SPIBSC_DRENR_DRDB_SHIFT, SPIBSC_DRENR_DRDB);

    if( 1 == ddr_enable)
    {
        /* DRDRENR.DRDRE = 1 : DATA is DDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.DRDRENR.LONG, SPIBSC_DDR_TRANSFER, SPIBSC_DRDRENR_DRDRE_SHIFT, SPIBSC_DRDRENR_DRDRE);
    }
    else
    {
        /* DRDRENR.DRDRE = 0 : DATA is SDR transfer setting */
        spibsc_io_reg_write_32(&SPIBSC.DRDRENR.LONG, SPIBSC_SDR_TRANSFER, SPIBSC_DRDRENR_DRDRE_SHIFT, SPIBSC_DRDRENR_DRDRE);
    }

}
/*******************************************************************************
End of function r_spibsc_xip_set_datatransfer
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_change_manual_mode
* Description  : Switch to Manual mode
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void r_spibsc_change_manual_mode(uint8_t sdr_ddr)
{
    /* CMNCR.MD = 1 () */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, 0x1, SPIBSC_CMNCR_MD_SHIFT, SPIBSC_CMNCR_MD);


    if (SPIBSC_DDR_TRANSFER == sdr_ddr)
    {
        /* for SPI-Flash / DDR */
        /* Casting the pointer to a uint32_t type is valid because "unsigned long" is same 4byte unsigned integer type. */
        spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x1, SPIBSC_PHYCNT_PHYMEM_SHIFT, SPIBSC_PHYCNT_PHYMEM);
        spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET1.LONG, 0x2, SPIBSC_PHYOFFSET1_DDRTMG_SHIFT, SPIBSC_PHYOFFSET1_DDRTMG);
        spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET2.LONG, 0x4, SPIBSC_PHYOFFSET2_OCTTMG_SHIFT, SPIBSC_PHYOFFSET2_OCTTMG);
    }
    else
    {
        /* for SPI-Flash / SDR */
        spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_PHYMEM_SHIFT, SPIBSC_PHYCNT_PHYMEM);
        spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET1.LONG, 0x3, SPIBSC_PHYOFFSET1_DDRTMG_SHIFT, SPIBSC_PHYOFFSET1_DDRTMG);
        spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET2.LONG, 0x4, SPIBSC_PHYOFFSET2_OCTTMG_SHIFT, SPIBSC_PHYOFFSET2_OCTTMG);
    }
}

/*******************************************************************************
End of function r_spibsc_change_manual_mode
*******************************************************************************/

static void r_spibsc_change_xip_mode(uint8_t sdr_ddr)
{
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, 0x0, SPIBSC_CMNCR_MD_SHIFT, SPIBSC_CMNCR_MD);


    if (SPIBSC_DDR_TRANSFER == sdr_ddr)
    {
        /* for SPI-Flash / DDR */
        /* Casting the pointer to a uint32_t type is valid because "unsigned long" is same 4byte unsigned integer type. */
        spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x1, SPIBSC_PHYCNT_PHYMEM_SHIFT, SPIBSC_PHYCNT_PHYMEM);
        spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET1.LONG, 0x2, SPIBSC_PHYOFFSET1_DDRTMG_SHIFT, SPIBSC_PHYOFFSET1_DDRTMG);
        spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET2.LONG, 0x4, SPIBSC_PHYOFFSET2_OCTTMG_SHIFT, SPIBSC_PHYOFFSET2_OCTTMG);
    }
    else
    {
        /* for SPI-Flash / SDR */
        spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG, 0x0, SPIBSC_PHYCNT_PHYMEM_SHIFT, SPIBSC_PHYCNT_PHYMEM);
        spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET1.LONG, 0x3, SPIBSC_PHYOFFSET1_DDRTMG_SHIFT, SPIBSC_PHYOFFSET1_DDRTMG);
        spibsc_io_reg_write_32(&SPIBSC.PHYOFFSET2.LONG, 0x4, SPIBSC_PHYOFFSET2_OCTTMG_SHIFT, SPIBSC_PHYOFFSET2_OCTTMG);
    }
}
/*******************************************************************************
End of function r_spibsc_change_xip_mode
*******************************************************************************/



/*******************************************************************************
* Function Name: r_spibsc_flush_read_cache
* Description  : Switch to Manual mode
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void r_spibsc_flush_read_cache(void)
{

    /* DRCR.RCF = 1*/
    spibsc_io_reg_write_32(&SPIBSC.DRCR.LONG, 0x1, SPIBSC_DRCR_RCF_SHIFT, SPIBSC_DRCR_RCF);

    /* dummy read */
    spibsc_io_reg_read_32(&SPIBSC.DRCR.LONG, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
}
/*******************************************************************************
End of function r_spibsc_flush_read_cache
*******************************************************************************/

/*******************************************************************************
* Function Name: r_spibsc_xip_stop_access
* Description  : 
* Arguments    : none
* Return Value : none
*******************************************************************************/
static void r_spibsc_xip_stop_access(void)
{

    /* DRCR.SSLE = 1 and  DRCR.RBE = 1  */
    if( ( 1 == spibsc_io_reg_read_32(&SPIBSC.DRCR.LONG, SPIBSC_DRCR_SSLE_SHIFT, SPIBSC_DRCR_SSLE  )) &&
        ( 1 == spibsc_io_reg_read_32(&SPIBSC.DRCR.LONG, SPIBSC_DRCR_RBE_SHIFT, SPIBSC_DRCR_RBE    )) )
    {
        /* SSLN = 1 */
        spibsc_io_reg_write_32(&SPIBSC.DRCR.LONG, 0x1, SPIBSC_DRCR_SSLN_SHIFT, SPIBSC_DRCR_SSLN);
    }

    r_spibsc_wait_tend();

}
/*******************************************************************************
End of function r_spibsc_xip_stop_access
*******************************************************************************/


/******************************************************************************
* Function Name: r_spibsc_qspi_io_set_output_level
* Description  : spibsc _qspi_io_set_output_level
* Arguments    : cmncr_moiio3 : Set the output level of QSPIn_IO3 at SSL negation
* Arguments    : cmncr_moiio2 : Set the output level of QSPIn_IO2 at SSL negation
* Arguments    : cmncr_moiio1 : Set the output level of QSPIn_IO1 at SSL negation
* Arguments    : cmncr_moiio0 : Set the output level of QSPIn_IO0 at SSL negation
* Arguments    : cmncr_io3fv  : Set the output level of QSPIn_IO3 at QSPIn_IO3 fixed value when 1 bit width
* Arguments    : cmncr_io2fv  : Set the output level of QSPIn_IO2 at QSPIn_IO2 fixed value when 1 bit width
* Arguments    : cmncr_io0fv  : Set the output level of QSPIn_IO0 at QSPIn_IO0 fixed value when 1 bit width
* output level(B'00: 0, B'01: 1, B'10: previous value, B'11: Hi-Z)
* Return Value : none
******************************************************************************/
static void r_spibsc_qspi_io_set_output_level(
    uint8_t cmncr_moiio3,
    uint8_t cmncr_moiio2,
    uint8_t cmncr_moiio1,
    uint8_t cmncr_moiio0,
    uint8_t cmncr_io3fv,
    uint8_t cmncr_io2fv,
    uint8_t cmncr_io0fv
    )
{

    /* ---- CMNCR ---- */

    /* CMNCR.MOIIO3[1:0] = cmncr_moiio3 : QSPIn_IO3 pin status at the time of an idle */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, cmncr_moiio3, SPIBSC_CMNCR_MOIIO3_SHIFT, SPIBSC_CMNCR_MOIIO3);

    /* CMNCR.MOIIO2[1:0] = cmncr_moiio2 : QSPIn_IO2 pin status at the time of an idle */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, cmncr_moiio2, SPIBSC_CMNCR_MOIIO2_SHIFT, SPIBSC_CMNCR_MOIIO2);

    /* CMNCR.MOIIO1[1:0] = cmncr_moiio1 : QSPIn_IO1 pin status at the time of an idle */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, cmncr_moiio1, SPIBSC_CMNCR_MOIIO1_SHIFT, SPIBSC_CMNCR_MOIIO1);

    /* CMNCR.MOIIO0[1:0] = cmncr_moiio0 : QSPIn_IO0 pin status at the time of an idle */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, cmncr_moiio0, SPIBSC_CMNCR_MOIIO0_SHIFT, SPIBSC_CMNCR_MOIIO0);

    /* CMNCR.IO3FV[1:0] = cmncr_io3fv  Output value of QSPIn_IO3 pin when 1 bit is set */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, cmncr_io3fv, SPIBSC_CMNCR_IO3FV_SHIFT , SPIBSC_CMNCR_IO3FV);

    /* CMNCR.IO2FV[1:0] = cmncr_io2fv : Output value of QSPIn_IO2 pin when 1 bit is set */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, cmncr_io2fv, SPIBSC_CMNCR_IO2FV_SHIFT , SPIBSC_CMNCR_IO2FV);

    /* CMNCR.IO0FV[1:0] = cmncr_io0fv : Output value of QSPIn_IO0 pin when 1 bit is set */
    spibsc_io_reg_write_32(&SPIBSC.CMNCR.LONG, cmncr_io0fv, SPIBSC_CMNCR_IO0FV_SHIFT , SPIBSC_CMNCR_IO0FV);


}
/*******************************************************************************
End of function r_spibsc_qspi_io_set_output_level
*******************************************************************************/


/*******************************************************************************
* Function Name: r_spibsc_get_ok_area_center
* Description  : Phy Adjust
* Arguments    : p_ok_ng_result : Pointer of ok_ng_result
* Return Value : index_center   : ok area center
*******************************************************************************/
static int_t r_spibsc_get_ok_area_center( uint8_t *p_ok_ng_result )
{
    int_t index;             /**< loop counter */
    int_t ok_cnt = 0;
    int_t index_start = -1;
    int_t index_center = -1;


    /* detect ok area index start*/
    for ( index = 0; index < SPIBSC_PRV_PHYADJ_MAX; index++ )
    {
        if ( SPIBSC_PRV_RESULT_OK == p_ok_ng_result[index] )
        {
            index_start = index;
            break;

        }
        else
        {
             /* Do Nothing */
        }

    }

    /* confirm exist of ok area */
    if (-1 == index_start)
    {
        /* Do Nothing */
    }
    else
    {
        /* count number of ok */
        for ( index = index_start; index < SPIBSC_PRV_PHYADJ_MAX; index++ )
        {
            if ( SPIBSC_PRV_RESULT_OK == p_ok_ng_result[index] )
            {
                ok_cnt++;
            }
            else
            {
                break;
            }

        }

        /* check ok number */
        if (3 < ok_cnt)
        {
            /* calculate ok area center index */
            index_center = (ok_cnt/2) + index_start;

        }
        else
        {
             /* Do Nothing */
        }
    }


    return index_center;
}
/******************************************************************************
 * End of function r_spibsc_get_ok_area_center
 ******************************************************************************/


/*******************************************************************************
* Function Name: R_SPIBSC_AdjustPhy
* Description  : Phy Adjust
* Arguments    : none
* Return Value : spibsc_err_t
*******************************************************************************/
e_spibsc_err_t R_SPIBSC_AdjustPhy( void )
{
    e_spibsc_err_t ret;
    int_t index;             /**< loop counter */
    int_t index_center = -1;
    uint32_t read_data;


    /* PHY Reg Access Enable */
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ2.LONG, 0xA5390000, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ1.LONG, 0x80000000, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* Set PHY Timing Adjust Reg. */
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ2.LONG, 0x00009191, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ1.LONG, 0x80000022, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ2.LONG, 0x00009191, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
    spibsc_io_reg_write_32(&SPIBSC.PHYADJ1.LONG, 0x80000024, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

    /* detect ok/ng area */
    for ( index = 0; index < SPIBSC_PRV_PHYADJ_MAX; index++ )
    {
        
        /* ==== Waiting Tend ==== */
        r_spibsc_wait_tend();

        /* PHY Timing Adjust */
        spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG,  gs_spibsc_phy_adj[index].zz, SPIBSC_PHYCNT_CKSEL_SHIFT, SPIBSC_PHYCNT_CKSEL);
        spibsc_io_reg_write_32(&SPIBSC.PHYADJ2.LONG, gs_spibsc_phy_adj[index].xy, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
        spibsc_io_reg_write_32(&SPIBSC.PHYADJ1.LONG, 0x80000032, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
        spibsc_io_reg_read_32(&SPIBSC.PHYADJ1.LONG, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);    /* dummy read */

        /* ==== Read serial flash data ==== */
        R_SPIBSC_SPICMDIssue(SFLASH_CMD_INDEX_4DTRD4B_EEH,  (0x0FFFFFFFUL & ((uint32_t)&g_spibsc_test_pattern)), 0, 0, &read_data, 4);
    	
        /* check read */
    	if ( SPIBSC_TEST_PATTERN_EXPECTED_VALUE == read_data )
        {
            gs_ok_ng_result[index] = SPIBSC_PRV_RESULT_OK;        /* OK */
        }
        else
        {
            gs_ok_ng_result[index] = SPIBSC_PRV_RESULT_NG;        /* NG */
        }
    }

    /* get ok area center */
    index_center = r_spibsc_get_ok_area_center( gs_ok_ng_result );

    if ( 0 < index_center )
    {
        /* ==== Waiting Tend ==== */
        r_spibsc_wait_tend();

        /* Set Final PHY Timing */
        spibsc_io_reg_write_32(&SPIBSC.PHYCNT.LONG,  gs_spibsc_phy_adj[index_center].zz, SPIBSC_PHYCNT_CKSEL_SHIFT, SPIBSC_PHYCNT_CKSEL);
        spibsc_io_reg_write_32(&SPIBSC.PHYADJ2.LONG, gs_spibsc_phy_adj[index_center].xy, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);
        spibsc_io_reg_write_32(&SPIBSC.PHYADJ1.LONG, 0x80000032, IOREG_NONSHIFT_ACCESS, IOREG_NONMASK_ACCESS);

        ret = SPIBSC_SUCCESS;
    }
    else
    {
        ret = SPIBSC_ERR_INVALID;
    }

    return ret;
}
/******************************************************************************
 * End of function R_SPIBSC_AdjustPhy
 ******************************************************************************/


/******************************************************************************
* Function Name: R_SPIBSC_Init
* Description  : 
* Arguments    : 
* Return Value : spibsc_err_t
******************************************************************************/
e_spibsc_err_t  R_SPIBSC_Init( const st_spibsc_config_t  *p_spibsc_config_tbl )
{
    /* POCSEL0,POC0 set voltage*/
    r_spibsc_port_voltage_setting(p_spibsc_config_tbl->flash_port_voltage);

    /* PSPIBSC set current */
    r_spibsc_port_current_setting(p_spibsc_config_tbl->flash_port_voltage);

    if (SPIBSC_FLASH_SPI == p_spibsc_config_tbl->flash_type )
    {
        r_spibsc_common_spiflash_init(p_spibsc_config_tbl);
    }


    return (SPIBSC_SUCCESS);
}
/******************************************************************************
 * End of function R_SPIBSC_Init
 ******************************************************************************/

/******************************************************************************
* Function Name: R_SPIBSC_ChangeMode
* Description  : 
* Arguments    : uint8_t mode
*              : uint8_t table_no
* Return Value : void
******************************************************************************/
void R_SPIBSC_ChangeMode(uint8_t mode, uint8_t sdr_ddr, uint8_t table_no)
{

    const st_spibsc_xip_config_t *p_xip_cmd_tbl = NULL;

    p_xip_cmd_tbl = &gs_xip_read_table[table_no];

    /* ==== Stop Access, Wait TEND=1 ==== */
    r_spibsc_xip_stop_access();

    if ( SPIBSC_MODE_MANUAL == mode)
    {
        r_spibsc_change_manual_mode(sdr_ddr);  /* 1:DDR, 0:SDR */
    }
    else
    {


        /* ==== Set QSPIn_IOn output level ==== */
        r_spibsc_qspi_io_set_output_level(
            p_xip_cmd_tbl->cmncr_moiio3,
            p_xip_cmd_tbl->cmncr_moiio2,
            p_xip_cmd_tbl->cmncr_moiio1,
            p_xip_cmd_tbl->cmncr_moiio0,
            p_xip_cmd_tbl->cmncr_io3fv,
            p_xip_cmd_tbl->cmncr_io2fv,
            p_xip_cmd_tbl->cmncr_io0fv
        );
        r_spibsc_change_xip_mode(sdr_ddr);  /* 1:DDR, 0:SDR */

        r_spibsc_xip_set_command(p_xip_cmd_tbl->cmd, p_xip_cmd_tbl->cmd_width, p_xip_cmd_tbl->cmd_output_enable);
        r_spibsc_xip_set_optional_command(p_xip_cmd_tbl->ocmd, p_xip_cmd_tbl->ocmd_width, p_xip_cmd_tbl->ocmd_output_enable);
        r_spibsc_xip_set_address(p_xip_cmd_tbl->addr_width, p_xip_cmd_tbl->addr_output_enable, p_xip_cmd_tbl->addr_ddr_enable);

        r_spibsc_xip_set_option_data( p_xip_cmd_tbl->opd3, p_xip_cmd_tbl->opd2, p_xip_cmd_tbl->opd1, p_xip_cmd_tbl->opd0,
                                      p_xip_cmd_tbl->opdata_width,  p_xip_cmd_tbl->opdata_output_enable,  p_xip_cmd_tbl->opdata_ddr_enable);

        r_spibsc_xip_set_dummy_cycle(p_xip_cmd_tbl->dummy_cycle_count, p_xip_cmd_tbl->reserve3, p_xip_cmd_tbl->dummy_cycle_enable);
        r_spibsc_xip_set_datatransfer(p_xip_cmd_tbl->data_width, p_xip_cmd_tbl->data_ddr_enable);

    }

}
/******************************************************************************
 * End of function R_SPIBSC_ChangeMode
 ******************************************************************************/


/******************************************************************************
* Function Name: R_SPIBSC_SPICMDIssue
* Description  :
* Arguments    : uint8_t  table_no
*              : uint32_t addr
*              : uint8_t  *p_write_buff
*              : int32_t  write_size
*              : uint8_t  *p_read_buff
*              : int32_t  read_size
* Return Value : e_spibsc_err_t
******************************************************************************/
e_spibsc_err_t R_SPIBSC_SPICMDIssue( uint8_t table_no, uint32_t addr, uint8_t *p_write_buff, int32_t write_size,
                                    uint8_t *p_read_buff, int32_t read_size)

{

    const st_spibsc_manual_mode_command_config_t *p_spi_cmd_tbl = NULL;

    e_spibsc_err_t ret = SPIBSC_SUCCESS;

    /* Setting pointer to table for manual mode */
    p_spi_cmd_tbl = &gs_command_table[table_no];

    /* ==== Set QSPIn_IOn output level ==== */
    r_spibsc_qspi_io_set_output_level(
        p_spi_cmd_tbl->cmncr_moiio3,
        p_spi_cmd_tbl->cmncr_moiio2,
        p_spi_cmd_tbl->cmncr_moiio1,
        p_spi_cmd_tbl->cmncr_moiio0,
        p_spi_cmd_tbl->cmncr_io3fv,
        p_spi_cmd_tbl->cmncr_io2fv,
        p_spi_cmd_tbl->cmncr_io0fv
    );

    /* ==== Command ==== */
    r_spibsc_manual_set_command(p_spi_cmd_tbl->cmd, p_spi_cmd_tbl->cmd_width, p_spi_cmd_tbl->cmd_output_enable);

    /* ==== Optional Command ==== */
    r_spibsc_manual_set_optional_command(p_spi_cmd_tbl->ocmd, p_spi_cmd_tbl->ocmd_width, p_spi_cmd_tbl->ocmd_enable);

    /* ==== Address ==== */
    r_spibsc_manual_set_address(addr, p_spi_cmd_tbl->addr_width, p_spi_cmd_tbl->addr_output_enable, p_spi_cmd_tbl->addr_sdr_ddr);

    /* ==== Option Data ==== */
    r_spibsc_manual_set_option_data( p_spi_cmd_tbl->opd3, p_spi_cmd_tbl->opd2, p_spi_cmd_tbl->opd1, p_spi_cmd_tbl->opd0,
                                     p_spi_cmd_tbl->opdata_width, p_spi_cmd_tbl->opdata_output_enable, p_spi_cmd_tbl->opdata_ddr_enable);

    /* ==== Dummy Cycle ==== */
    r_spibsc_manual_set_dummy_cycle(p_spi_cmd_tbl->dummy_cycle_count, p_spi_cmd_tbl->reserve3, p_spi_cmd_tbl->dummy_cycle_output_enable);



    /* command only */
    if ( (0 == read_size) && (0 == write_size) )
    {

        /* ==== Transfer Data ==== */
        r_spibsc_manual_set_datatransfer( 0, /* no transterf */
                                          p_spi_cmd_tbl->transfer_data_width,
                                          0, /* write disable */
                                          0, /* read  disable */
                                          p_spi_cmd_tbl->transfer_data_sdr_ddr);

        /* ====  Start Transfer ==== */
        r_spibsc_manual_start_transfer();

        /* ==== Waiting Tend ==== */
        r_spibsc_wait_tend();
    }

    /* read command */
    else if ( (0 != read_size) && (0 == write_size) )
    {
        ret = r_spibsc_spi_cmd_issue_read( table_no, addr, p_read_buff, read_size );

    }

    /* write command */
    else if( (0 != write_size) && (0 == read_size) )
    {
        r_spibsc_spi_cmd_issue_write( table_no, addr, p_write_buff, write_size );

    }

    return (ret);
}
/******************************************************************************
 * End of function R_SPIBSC_SPICMDIssue
 ******************************************************************************/


/******************************************************************************
* Function Name: r_spibsc_spi_cmd_issue_read
* Description  :
* Arguments    : uint8_t  table_no
*              : uint32_t addr
*              : uint8_t  *p_read_buff
*              : int32_t  read_size
* Return Value : e_spibsc_err_t
******************************************************************************/
static e_spibsc_err_t r_spibsc_spi_cmd_issue_read( uint8_t table_no, uint32_t addr, uint8_t *p_read_buff, int32_t read_size)

{

    const st_spibsc_manual_mode_command_config_t *p_spi_cmd_tbl = NULL;

    uint8_t transfer_unit = 0x8;  /* 8bit transfer */
    uint8_t read_size_3_flag = 0; /* read_size 3 flag */
    uint32_t addr_out_enable = 0; /* address output enable */
    int32_t n;
    int32_t read_buf_set_size;
    int32_t unit = 0;
    uint32_t reg_l = 0;
    uint8_t  *p_buf_b = NULL;
    uint8_t  *p_reg_b = NULL;

    /* Setting pointer to table for manual mode */
    p_spi_cmd_tbl = &gs_command_table[table_no];

    /* ==== Get SPIBSC_SMENR.ADE ==== */
    addr_out_enable = spibsc_io_reg_read_32(&SPIBSC.SMENR.LONG, SPIBSC_SMENR_ADE_SHIFT, SPIBSC_SMENR_ADE);

    /* Pointer setting of read buffer */
    p_buf_b = p_read_buff;
    
    /* The remaining number of bytes? */
    while ( 0 < read_size )
    {

        /* Rounding processing when the register read byte is 3. */
        if ( SPIBSC_OUTPUT_DISABLE == addr_out_enable )
        {
            /* register access */
            if ( 5 <= read_size )
            {
                return (SPIBSC_ERR_INVALID);
            }
            else if ( 3 == read_size )
            {
                read_size = 4;
                read_size_3_flag = 1;
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            /* memory access */
            /* Do Nothing */
        }
        
        /* Calculate the transfer bit width from the remaining number of read bytes. */
        if ( 4 <= read_size )
        {
            transfer_unit = SPIBSC_MANUAL_32BIT_TRANSFERRED;
            unit = 4;
            
            /* When the number of register read bytes is 3, */
            /* after setting 4 bytes of data transfer byte, */
            /* value of read_size is returned to 3.         */
            if ( 1 == read_size_3_flag )
            {
                read_size_3_flag = 0;
                read_size = 3;
            }
            else
            {
            /* Do Nothing */
            }
        }
        else
        {
            transfer_unit = SPIBSC_MANUAL_8BIT_TRANSFERRED;
            unit = 1;
        }

        /* ==== Address ==== */
        r_spibsc_manual_set_address(addr, p_spi_cmd_tbl->addr_width, p_spi_cmd_tbl->addr_output_enable, p_spi_cmd_tbl->addr_sdr_ddr);

        /* ==== Transfer Data ==== */
        r_spibsc_manual_set_datatransfer( transfer_unit,
                                          p_spi_cmd_tbl->transfer_data_width,
                                          0, /* write disable */
                                          1, /* read  enable  */
                                          p_spi_cmd_tbl->transfer_data_sdr_ddr);

        /* ====  Start Transfer ==== */
        r_spibsc_manual_start_transfer();

        /* ==== Waiting Tend ==== */
        r_spibsc_wait_tend();

        /* Calculation of read buffer setting byte count */
        if ( unit > read_size )
        {
            read_buf_set_size = read_size;
        }
        else
        {
            read_buf_set_size = unit;
        }

        /* The read register is read according to the transfer bit width and stored in the read buffer */
        switch( transfer_unit )
        {
            case SPIBSC_MANUAL_32BIT_TRANSFERRED:
            {
                reg_l = r_spibsc_manual_read_data0_32();
                p_reg_b = (uint8_t*)&reg_l;
                
                /* Divided into bytes and copied */
                for ( n = 0; n < read_buf_set_size; n++)
                {
                    *p_buf_b = *p_reg_b;
                    p_buf_b++;
                    p_reg_b++;
                }
                break;
            }
            case SPIBSC_MANUAL_8BIT_TRANSFERRED:
            {
                /* Divided into bytes and copied */
                *p_buf_b = r_spibsc_manual_read_data0_8();
                p_buf_b++;

                break;
            }
            default:
            {
                /* Do Nothing */
                break;
            }
        }

        read_size -= unit;
        addr += (uint32_t)unit;

    }

    return (SPIBSC_SUCCESS);
}
/******************************************************************************
 * End of function r_spibsc_spi_cmd_issue_read
 ******************************************************************************/


/******************************************************************************
* Function Name: r_spibsc_spi_cmd_issue_write
* Description  :
* Arguments    : uint8_t  table_no
*              : uint32_t addr
*              : uint8_t  *p_write_buff
*              : int32_t  write_size
* Return Value : e_spibsc_err_t
******************************************************************************/
static e_spibsc_err_t r_spibsc_spi_cmd_issue_write( uint8_t table_no, uint32_t addr, uint8_t *p_write_buff, int32_t write_size )

{

    const st_spibsc_manual_mode_command_config_t *p_spi_cmd_tbl = NULL;

    uint8_t transfer_unit = 0x8; /* 8bit transfer    */
    int32_t transfer_num  = 0;   /* transufer number */
    int32_t unit = 0;            /* taransfer byte   */
    uint32_t *p_buf_l = NULL;
    uint8_t  *p_buf_b = NULL;

    /* Setting pointer to table for manual mode */
    p_spi_cmd_tbl = &gs_command_table[table_no];

    /* ==== [command] - [dummy cycle]  : SSL assert keep setting */

    /* SSL assert keep */
    r_spibsc_manual_assert_ssl();

    /* Pointer setting of write buffer */
    p_buf_b = p_write_buff;

    /* The remaining number of bytes? */
    while ( 0 < write_size )
    {

        /* Calculate the transfer bit width from the remaining number of write bytes. */
        if ( 4 <= write_size )
        {
            transfer_unit = SPIBSC_MANUAL_32BIT_TRANSFERRED;
            unit = 4;
        }
        else
        {
            transfer_unit = SPIBSC_MANUAL_8BIT_TRANSFERRED;
            unit = 1;
        }

        /* Transfer is second time? */
        if( 1 == transfer_num )
        {
            /* From the second time onward, do not transfer from command to dummy cycle. */

            /* ==== Command ==== */
            r_spibsc_manual_set_command(0x00, 0, 0);

            /* ==== Optional Command ==== */
            r_spibsc_manual_set_optional_command(0x00, 0, 0);

            /* ==== Address ==== */
            r_spibsc_manual_set_address(addr, 0, 0, 0);

            /* ==== Option Data ==== */
            r_spibsc_manual_set_option_data( 0x00, 0x00, 0x00, 0x00,
                                             0,  0,  0);

            /* ==== Dummy Cycle ==== */
            r_spibsc_manual_set_dummy_cycle(0x00, 0,  0);

        }

        /* ==== Transfer Data ==== */
        r_spibsc_manual_set_datatransfer( transfer_unit,
                                          p_spi_cmd_tbl->transfer_data_width,
                                          1, /* write enable  */
                                          0, /* read  disable */
                                          p_spi_cmd_tbl->transfer_data_sdr_ddr);

        /* last transfer? */
        if ( unit >= write_size )
        {
            /* fist data - last data - 1   : SSL assert keep setting  */
            /* last data                   : SSL negate keep setting  */
            r_spibsc_manual_negate_ssl();

        }
        else
        {
            /* Do Nothing */
        }

        /* Set the write buffer data to the write register according to the transfer bit width. */
        switch( transfer_unit )
        {
            case SPIBSC_MANUAL_32BIT_TRANSFERRED:
            {
                p_buf_l = (uint32_t*)p_buf_b;
                r_spibsc_manual_write_data0_32(*p_buf_l);
                p_buf_b += unit;

                break;
            }
            case SPIBSC_MANUAL_8BIT_TRANSFERRED:
            {
                r_spibsc_manual_write_data0_8(*p_buf_b);
                p_buf_b += unit;

                break;
            }
            default:
            {
                /* Do Nothing */
                break;
            }
        }

        /* ====  Start Transfer ==== */
        r_spibsc_manual_start_transfer();

        /* ==== Waiting Tend ==== */
        r_spibsc_wait_tend();

        write_size -= unit;
        addr += (uint32_t)unit;
        transfer_num++;
    }

    return (SPIBSC_SUCCESS);
}
/******************************************************************************
 * End of function r_spibsc_spi_cmd_issue_write
 ******************************************************************************/


/*******************************************************************************
* Function Name: R_SPIBSC_FlushReadCache
* Description  : Flush Read Cache
* Arguments    : none
* Return Value : none
*******************************************************************************/
void R_SPIBSC_FlushReadCache(void)
{
    r_spibsc_flush_read_cache();
}
/*******************************************************************************
End of function R_SPIBSC_FlushReadCache
*******************************************************************************/

/*******************************************************************************
* Function Name: R_SPIBSC_XipStopAccess
* Description  : SSL negate
* Arguments    : none
* Return Value : none
*******************************************************************************/
void R_SPIBSC_XipStopAccess(void)
{
    r_spibsc_xip_stop_access();
}
/*******************************************************************************
End of function R_SPIBSC_XipStopAccess
*******************************************************************************/


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
int_t R_SPIBSC_GetVersion(st_ver_info_t *p_ver_info)
{
    p_ver_info->lld.p_szdriver_name = gs_lld_info.p_szdriver_name;
    p_ver_info->lld.version.sub.major = gs_lld_info.version.sub.major;
    p_ver_info->lld.version.sub.minor = gs_lld_info.version.sub.minor;
    p_ver_info->lld.build = gs_lld_info.build;

    return DRV_SUCCESS;
}
/******************************************************************************
 * End of function R_SPIBSC_GetVersion
 ******************************************************************************/

/* End of File */
