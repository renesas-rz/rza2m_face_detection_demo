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
 * @headerfile     r_cpg_drv_sc_cfg.h
 * @brief          CPG Driver setting file from Smart Configurator
 * @version        1.00
 * @date           21.05.2018
 * $Rev: 544 $
 * $Date:: 2018-08-21 15:15:33 +0900#$
 *******************************************************************************/
/*******************************************************************************
 * History       : DD.MM.YYYY Version Description
 *               : dd.mm.2018 1.00    Release
 *******************************************************************************/
#ifndef R_CPG_DRV_SC_CFG_H_
#define R_CPG_DRV_SC_CFG_H_

/* This code is auto-generated. Do not edit manually */
static const float64_t s_sc_cpg_xtal_frequency_khz_config = 24000.0;

static const st_r_drv_cpg_set_main_t s_sc_cpg_main_clock_config =
    {CPG_CLOCK_SOURCE_PLL, 1056000.0};    /*!< Main clock=PLL, 1056000KHz */

static const st_r_drv_cpg_set_sub_t s_sc_cpg_sub_clock_div_config[] =
{
    {CPG_SUB_CLOCK_ICLK,  528000.0}, /*!< CPU Clock = 528000KHz*/
    {CPG_SUB_CLOCK_BCLK,  132000.0}, /*!< Internal Bus Clock = 132000KHz */
    {CPG_SUB_CLOCK_P1CLK,  66000.0}, /*!< Peripheral Clock1 = 66000KHz */
};

static const st_r_drv_cpg_set_src_t s_sc_cpg_sub_clock_src_config[] =
{
    {CPG_SUB_CLOCK_CKIO, CPG_SUB_CLOCK_BCLK_IN},       /*!< External Clock Pin derived from Internal Bus Clock */
    {CPG_SUB_CLOCK_OCTAMEM, CPG_SUB_CLOCK_GCLK_IN},    /*!< Octa Memory Clock derived from Image Processor Clock */
    {CPG_SUB_CLOCK_HYPERBUS, CPG_SUB_CLOCK_GCLK_IN},   /*!< Hyper Bus Clock derived from Image Processor Clock */
    {CPG_SUB_CLOCK_SPICLK, CPG_SUB_CLOCK_BCLK_IN},     /*!< SPI multi IO Clock derived from Image Processor Clock */
};

static const st_r_drv_cpg_ext_clk_t s_sc_cpg_ext_clk_config =
    {CPG_CKIO_INVALID_UNSTBLE_OFF_HIZ};     /*!< External Clock Unstable/Hi Impedance */
/* End of modification */




#endif /* R_CPG_DRV_SC_CFG_H_ */
/*******************************************************************************************************************//**
End  Of File
 ***********************************************************************************************************************/
