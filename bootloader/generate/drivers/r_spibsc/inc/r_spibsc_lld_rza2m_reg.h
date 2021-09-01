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
* File Name : r_spibsc_lld_rza2m_reg.h
* $Rev: 742 $
* $Date:: 2018-11-30 12:19:50 +0900#$
* Description :
******************************************************************************/
#ifndef R_SPIBSC_REG_RZA2M_H_
#define R_SPIBSC_REG_RZA2M_H_

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "iodefine.h"
#include "r_typedefs.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define SPIBSC_1BIT_WIDTH    (0)
#define SPIBSC_4BIT_WIDTH    (2)


#define SPIBSC_OUTPUT_DISABLE       (0)
#define SPIBSC_OUTPUT_ENABLE        (1)

/* Address Output Setting Macro */
#define SPIBSC_OUTPUT_ADDR_24       (0x07)
#define SPIBSC_OUTPUT_ADDR_32       (0x0f)

/* Option Data Setting Macro */
#define SPIBSC_OUTPUT_OPD_3         (0x08)
#define SPIBSC_OUTPUT_OPD_32        (0x0c)
#define SPIBSC_OUTPUT_OPD_321       (0x0e)
#define SPIBSC_OUTPUT_OPD_3210      (0x0f)


/* Dummy Cycle Setting Macro */
#define SPIBSC_DUMMY_02CYC           (1)
#define SPIBSC_DUMMY_03CYC           (2)
#define SPIBSC_DUMMY_04CYC           (3)
#define SPIBSC_DUMMY_05CYC           (4)
#define SPIBSC_DUMMY_06CYC           (5)
#define SPIBSC_DUMMY_07CYC           (6)
#define SPIBSC_DUMMY_08CYC           (7)
#define SPIBSC_DUMMY_09CYC           (8)
#define SPIBSC_DUMMY_10CYC           (9)
#define SPIBSC_DUMMY_11CYC           (10)
#define SPIBSC_DUMMY_12CYC           (11)
#define SPIBSC_DUMMY_13CYC           (12)
#define SPIBSC_DUMMY_14CYC           (13)
#define SPIBSC_DUMMY_15CYC           (14)
#define SPIBSC_DUMMY_16CYC           (15)
#define SPIBSC_DUMMY_17CYC           (16)
#define SPIBSC_DUMMY_18CYC           (17)
#define SPIBSC_DUMMY_19CYC           (18)
#define SPIBSC_DUMMY_20CYC           (19)


/* SDR/DDR Transfer (Address, Option Data, Transfer Data) */
#define SPIBSC_DDR_TRANSFER    (1)
#define SPIBSC_SDR_TRANSFER    (0)

#define SPIBSC_NO_DATA        (0x00)
#define SPIBSC_READ_DATA      (0x01)
#define SPIBSC_WRITE_DATA     (0x02)

#define SPIBSC_MANUAL_NOT_TRANSFERRED    (0x0)
#define SPIBSC_MANUAL_8BIT_TRANSFERRED   (0x8)
#define SPIBSC_MANUAL_32BIT_TRANSFERRED  (0xF)

#define SPIBSC_QE_ENABLE    (1)
#define SPIBSC_QE_DISABLE   (0)

#define SPIBSC_RDSR_WEL (0x02)
#define SPIBSC_RDSR_WIP (0x01)
#define SPIBSC_RDSR_QE  (0x40)

#define SPIBSC_QSPI_IO_OUTPUT_0         (0x00)
#define SPIBSC_QSPI_IO_OUTPUT_1         (0x01)
#define SPIBSC_QSPI_IO_OUTPUT_PREVIOUS  (0x02)
#define SPIBSC_QSPI_IO_OUTPUT_HI_Z      (0x03)




/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum spibsc_err{
    SPIBSC_SUCCESS = 0,
    SPIBSC_ERR_INVALID=(-1),
} e_spibsc_err_t;

typedef enum
{
    SPIBSC_CONTROL_SPI_CMD = 0,

}e_spibsc_control_code_t;

typedef enum spiflash_cmd_index{
   SFLASH_CMD_INDEX_RDSR_05H = 0,
   SFLASH_CMD_INDEX_RDCR_15H,
   SFLASH_CMD_INDEX_WREN_06H,
   SFLASH_CMD_INDEX_WRSR_01H,
   SFLASH_CMD_INDEX_RDID_9FH,
   SFLASH_CMD_INDEX_4DTRD4B_EEH,
   SFLASH_CMD_INDEX_4READ4B_ECH,
   SFLASH_CMD_INDEX_4PP4B_3EH,
   SFLASH_CMD_INDEX_SE4B_21H,
} e_spiflash_cmd_index_t;

typedef enum spiflash_cmd_index_xip{
   SFLASH_CMD_INDEX_XIP_4DTRD4B_EEH = 0,
   SFLASH_CMD_INDEX_XIP_4READ4B_ECH
} e_spiflash_cmd_index_xip_t;

typedef struct spibsc_config
{
    uint8_t flash_type;
    uint8_t flash_num;
    uint8_t flash_port_voltage;
}st_spibsc_config_t;


typedef struct spibsc_operation_mode
{
    uint8_t operation_mode;
    uint8_t spi_clock_select;
    uint8_t data_alignment;
    uint8_t data_strobe_enable;
}st_spibsc_operation_mode_t;




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



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* R_SPIBSC_REG_RZA2M_H_ */

/* End of File */
