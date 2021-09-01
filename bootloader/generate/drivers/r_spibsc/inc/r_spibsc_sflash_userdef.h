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
* File Name : r_spibsc_sflash_userdef.h
* $Rev: 606 $
* $Date:: 2018-09-05 18:13:42 +0900#$
* Description :
******************************************************************************/
#ifndef R_SPIBSC_SFLASH_USERDEF_H_
#define R_SPIBSC_SFLASH_USERDEF_H_

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_spibsc_lld_rza2m_reg.h"


/******************************************************************************
Typedef definitions
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/


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
 * @brief      Userdef_SPIBSC_SFLASH_SetMode
 *
 *             Setting of serial flash memory registers
 *
 *
 * @param[in]  mode:     operation mode\n
 *                       SPIBSC_QE_DISABLE: single mode(bit width 1bit)\n
 *                       SPIBSC_QE_ENABLE:  quad   mode(bit width 4bit)
 * @param[in]  sdr_ddr:  transfer format\n
 *                       0: Select command setting table 0 (DDR read command)\n
 *                       1: Select command setting table 1 (SDR read command)
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_SetMode(uint8_t mode, uint8_t sdr_ddr);

/**
 * @brief      Userdef_SPIBSC_SFLASH_ReadStatus
 *
 *             Reading the serial flash memory status register
 *
 *
 * @param[out] p_status:  Value read from status register
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_ReadStatus(uint8_t *p_status);

/**
 * @brief      Userdef_SPIBSC_SFLASH_ReadConfig
 *
 *             Reading the serial flash memory configuration register
 *
 *
 * @param[out] p_config:  Value read from configuration register
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_ReadConfig(uint8_t *p_config);

/**
 * @brief      Userdef_SPIBSC_SFLASH_WriteStatus
 *
 *             Serial flash memory status register and configuration register write
 *
 *
 * @param[in]  p_status:  Set value to the status register
 * @param[in]  p_config:  Set value to the configuration register
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_WriteStatus(uint8_t *p_status, uint8_t *p_config);

/**
 * @brief      Userdef_SPIBSC_SFLASH_WriteEnable
 *
 *             Enable write to serial flash memory
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_WriteEnable(void);

/**
 * @brief      Userdef_SPIBSC_SFLASH_WaitReady
 *
 *             Wait for serial flash memory write completion
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_WaitReady(void);

/**
 * @brief      Userdef_SPIBSC_SFLASH_Read
 *
 *             Reads the specified number of bytes from the specified address into the specified read buffer
 *
 *
 * @param[in]  addr:          Read start address
 * @param[in]  p_read_buff:   Pointer of read data buffer
 * @param[in]  read_size:     Number of read bytes
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_Read(uint32_t addr, uint8_t *p_read_buff, int32_t read_size, uint8_t sdr_ddr);

/**
 * @brief      Userdef_SPIBSC_SFLASH_ReadId
 *
 *             Read manufacturer ID
 *
 *
 * @param[in]  p_id:     Manufacturer ID storage pointer
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_ReadId(uint8_t *p_id);

/**
 * @brief      Userdef_SPIBSC_SFLASH_Write
 *
 *             Writes specified byte number of designated write data buffer after specified address
 *
 *
 * @param[in]  addr:          Write start address
 * @param[in]  p_write_buff:  Pointer of write data buffer
 * @param[in]  write_size:    Number of write bytes
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_Write(uint32_t addr, uint8_t *p_write_buff, int32_t write_size);

/**
 * @brief      Userdef_SPIBSC_SFLASH_Erase
 *
 *             Erase of specified sector
 *
 *
 * @param[in]  addr:     sector address
 *
 *
 */
extern void Userdef_SPIBSC_SFLASH_Erase(uint32_t addr);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* R_SPIBSC_SFLASH_USERDEF_H_ */

/* End of File */
