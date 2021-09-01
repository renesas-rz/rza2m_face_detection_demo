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
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/ 
/*******************************************************************************
* Rev: 3.01
* Description : IO bitmask header
*******************************************************************************/

#ifndef PL310_IOBITMASK_H
#define PL310_IOBITMASK_H


/* ==== Mask values for IO registers ==== */

#define PL310_REG0_CACHE_ID_RTLrelease                                         (0x0000003Fu)
#define PL310_REG0_CACHE_ID_RTLrelease_SHIFT                                   (0u)
#define PL310_REG0_CACHE_ID_Partnumber                                         (0x000003C0u)
#define PL310_REG0_CACHE_ID_Partnumber_SHIFT                                   (6u)
#define PL310_REG0_CACHE_ID_CACHEID                                            (0x0000FC00u)
#define PL310_REG0_CACHE_ID_CACHEID_SHIFT                                      (10u)
#define PL310_REG0_CACHE_ID_Implementer                                        (0xFF000000u)
#define PL310_REG0_CACHE_ID_Implementer_SHIFT                                  (24u)
#define PL310_REG0_CACHE_TYPE_L2cachelinelength1                               (0x00000003u)
#define PL310_REG0_CACHE_TYPE_L2cachelinelength1_SHIFT                         (0u)
#define PL310_REG0_CACHE_TYPE_L2associativity1                                 (0x00000040u)
#define PL310_REG0_CACHE_TYPE_L2associativity1_SHIFT                           (6u)
#define PL310_REG0_CACHE_TYPE_Isize                                            (0x00000F80u)
#define PL310_REG0_CACHE_TYPE_Isize_SHIFT                                      (7u)
#define PL310_REG0_CACHE_TYPE_L2cachelinelength0                               (0x00003000u)
#define PL310_REG0_CACHE_TYPE_L2cachelinelength0_SHIFT                         (12u)
#define PL310_REG0_CACHE_TYPE_L2associativity0                                 (0x00040000u)
#define PL310_REG0_CACHE_TYPE_L2associativity0_SHIFT                           (18u)
#define PL310_REG0_CACHE_TYPE_Dsize                                            (0x00F80000u)
#define PL310_REG0_CACHE_TYPE_Dsize_SHIFT                                      (19u)
#define PL310_REG0_CACHE_TYPE_H                                                (0x01000000u)
#define PL310_REG0_CACHE_TYPE_H_SHIFT                                          (24u)
#define PL310_REG0_CACHE_TYPE_ctype                                            (0x1E000000u)
#define PL310_REG0_CACHE_TYPE_ctype_SHIFT                                      (25u)
#define PL310_REG0_CACHE_TYPE_Databanking                                      (0x80000000u)
#define PL310_REG0_CACHE_TYPE_Databanking_SHIFT                                (31u)
#define PL310_REG1_CONTROL_L2Cacheenable                                       (0x00000001u)
#define PL310_REG1_CONTROL_L2Cacheenable_SHIFT                                 (0u)
#define PL310_REG1_AUX_CONTROL_FullLineofZeroEnable                            (0x00000001u)
#define PL310_REG1_AUX_CONTROL_FullLineofZeroEnable_SHIFT                      (0u)
#define PL310_REG1_AUX_CONTROL_HighPriorityforSOandDevReadsEnable              (0x00000400u)
#define PL310_REG1_AUX_CONTROL_HighPriorityforSOandDevReadsEnable_SHIFT        (10u)
#define PL310_REG1_AUX_CONTROL_StorebufferdevicelimitationEnable               (0x00000800u)
#define PL310_REG1_AUX_CONTROL_StorebufferdevicelimitationEnable_SHIFT         (11u)
#define PL310_REG1_AUX_CONTROL_Exclusivecacheconfiguration                     (0x00001000u)
#define PL310_REG1_AUX_CONTROL_Exclusivecacheconfiguration_SHIFT               (12u)
#define PL310_REG1_AUX_CONTROL_SharedAttributeInvalidateEnable                 (0x00002000u)
#define PL310_REG1_AUX_CONTROL_SharedAttributeInvalidateEnable_SHIFT           (13u)
#define PL310_REG1_AUX_CONTROL_Associativity                                   (0x00010000u)
#define PL310_REG1_AUX_CONTROL_Associativity_SHIFT                             (16u)
#define PL310_REG1_AUX_CONTROL_Waysize                                         (0x000E0000u)
#define PL310_REG1_AUX_CONTROL_Waysize_SHIFT                                   (17u)
#define PL310_REG1_AUX_CONTROL_Eventmonitorbusenable                           (0x00100000u)
#define PL310_REG1_AUX_CONTROL_Eventmonitorbusenable_SHIFT                     (20u)
#define PL310_REG1_AUX_CONTROL_Parityenable                                    (0x00200000u)
#define PL310_REG1_AUX_CONTROL_Parityenable_SHIFT                              (21u)
#define PL310_REG1_AUX_CONTROL_Sharedattributeoverrideenable                   (0x00400000u)
#define PL310_REG1_AUX_CONTROL_Sharedattributeoverrideenable_SHIFT             (22u)
#define PL310_REG1_AUX_CONTROL_Forcewriteallocate                              (0x01800000u)
#define PL310_REG1_AUX_CONTROL_Forcewriteallocate_SHIFT                        (23u)
#define PL310_REG1_AUX_CONTROL_Cachereplacementpolicy                          (0x02000000u)
#define PL310_REG1_AUX_CONTROL_Cachereplacementpolicy_SHIFT                    (25u)
#define PL310_REG1_AUX_CONTROL_Nonsecurelockdownenable                         (0x04000000u)
#define PL310_REG1_AUX_CONTROL_Nonsecurelockdownenable_SHIFT                   (26u)
#define PL310_REG1_AUX_CONTROL_Nonsecureinterruptaccesscontrol                 (0x08000000u)
#define PL310_REG1_AUX_CONTROL_Nonsecureinterruptaccesscontrol_SHIFT           (27u)
#define PL310_REG1_AUX_CONTROL_Dataprefetchenable                              (0x10000000u)
#define PL310_REG1_AUX_CONTROL_Dataprefetchenable_SHIFT                        (28u)
#define PL310_REG1_AUX_CONTROL_Instructionprefetchenable                       (0x20000000u)
#define PL310_REG1_AUX_CONTROL_Instructionprefetchenable_SHIFT                 (29u)
#define PL310_REG1_AUX_CONTROL_EarlyBRESPenable                                (0x40000000u)
#define PL310_REG1_AUX_CONTROL_EarlyBRESPenable_SHIFT                          (30u)
#define PL310_REG1_TAG_RAM_CONTROL_RAMsetuplatency                             (0x00000007u)
#define PL310_REG1_TAG_RAM_CONTROL_RAMsetuplatency_SHIFT                       (0u)
#define PL310_REG1_TAG_RAM_CONTROL_RAMreadaccesslatency                        (0x00000070u)
#define PL310_REG1_TAG_RAM_CONTROL_RAMreadaccesslatency_SHIFT                  (4u)
#define PL310_REG1_TAG_RAM_CONTROL_RAMwriteaccesslatency                       (0x00000700u)
#define PL310_REG1_TAG_RAM_CONTROL_RAMwriteaccesslatency_SHIFT                 (8u)
#define PL310_REG1_DATA_RAM_CONTROL_RAMsetuplatency                            (0x00000007u)
#define PL310_REG1_DATA_RAM_CONTROL_RAMsetuplatency_SHIFT                      (0u)
#define PL310_REG1_DATA_RAM_CONTROL_RAMreadaccesslatency                       (0x00000070u)
#define PL310_REG1_DATA_RAM_CONTROL_RAMreadaccesslatency_SHIFT                 (4u)
#define PL310_REG1_DATA_RAM_CONTROL_RAMwriteaccesslatency                      (0x00000700u)
#define PL310_REG1_DATA_RAM_CONTROL_RAMwriteaccesslatency_SHIFT                (8u)
#define PL310_REG2_EV_COUNTER_CTRL_Eventcounterenable                          (0x00000001u)
#define PL310_REG2_EV_COUNTER_CTRL_Eventcounterenable_SHIFT                    (0u)
#define PL310_REG2_EV_COUNTER_CTRL_Counterreset                                (0x00000006u)
#define PL310_REG2_EV_COUNTER_CTRL_Counterreset_SHIFT                          (1u)
#define PL310_REG2_EV_COUNTER1_CFG_Eventcounterinterruptgeneration             (0x00000003u)
#define PL310_REG2_EV_COUNTER1_CFG_Eventcounterinterruptgeneration_SHIFT       (0u)
#define PL310_REG2_EV_COUNTER1_CFG_Countereventsource                          (0x0000003Cu)
#define PL310_REG2_EV_COUNTER1_CFG_Countereventsource_SHIFT                    (2u)
#define PL310_REG2_EV_COUNTER0_CFG_Eventcounterinterruptgeneration             (0x00000003u)
#define PL310_REG2_EV_COUNTER0_CFG_Eventcounterinterruptgeneration_SHIFT       (0u)
#define PL310_REG2_EV_COUNTER0_CFG_Countereventsource                          (0x0000003Cu)
#define PL310_REG2_EV_COUNTER0_CFG_Countereventsource_SHIFT                    (2u)
#define PL310_REG2_EV_COUNTER1_Countervalue                                    (0xFFFFFFFFu)
#define PL310_REG2_EV_COUNTER1_Countervalue_SHIFT                              (0u)
#define PL310_REG2_EV_COUNTER0_Countervalue                                    (0xFFFFFFFFu)
#define PL310_REG2_EV_COUNTER0_Countervalue_SHIFT                              (0u)
#define PL310_REG2_INT_MASK_ECNTR                                              (0x00000001u)
#define PL310_REG2_INT_MASK_ECNTR_SHIFT                                        (0u)
#define PL310_REG2_INT_MASK_PARRT                                              (0x00000002u)
#define PL310_REG2_INT_MASK_PARRT_SHIFT                                        (1u)
#define PL310_REG2_INT_MASK_PARRD                                              (0x00000004u)
#define PL310_REG2_INT_MASK_PARRD_SHIFT                                        (2u)
#define PL310_REG2_INT_MASK_ERRWT                                              (0x00000008u)
#define PL310_REG2_INT_MASK_ERRWT_SHIFT                                        (3u)
#define PL310_REG2_INT_MASK_ERRWD                                              (0x00000010u)
#define PL310_REG2_INT_MASK_ERRWD_SHIFT                                        (4u)
#define PL310_REG2_INT_MASK_ERRRT                                              (0x00000020u)
#define PL310_REG2_INT_MASK_ERRRT_SHIFT                                        (5u)
#define PL310_REG2_INT_MASK_ERRRD                                              (0x00000040u)
#define PL310_REG2_INT_MASK_ERRRD_SHIFT                                        (6u)
#define PL310_REG2_INT_MASK_SLVERR                                             (0x00000080u)
#define PL310_REG2_INT_MASK_SLVERR_SHIFT                                       (7u)
#define PL310_REG2_INT_MASK_DECERR                                             (0x00000100u)
#define PL310_REG2_INT_MASK_DECERR_SHIFT                                       (8u)
#define PL310_REG2_INT_MASK_STATUS_ECNTR                                       (0x00000001u)
#define PL310_REG2_INT_MASK_STATUS_ECNTR_SHIFT                                 (0u)
#define PL310_REG2_INT_MASK_STATUS_PARRT                                       (0x00000002u)
#define PL310_REG2_INT_MASK_STATUS_PARRT_SHIFT                                 (1u)
#define PL310_REG2_INT_MASK_STATUS_PARRD                                       (0x00000004u)
#define PL310_REG2_INT_MASK_STATUS_PARRD_SHIFT                                 (2u)
#define PL310_REG2_INT_MASK_STATUS_ERRWT                                       (0x00000008u)
#define PL310_REG2_INT_MASK_STATUS_ERRWT_SHIFT                                 (3u)
#define PL310_REG2_INT_MASK_STATUS_ERRWD                                       (0x00000010u)
#define PL310_REG2_INT_MASK_STATUS_ERRWD_SHIFT                                 (4u)
#define PL310_REG2_INT_MASK_STATUS_ERRRT                                       (0x00000020u)
#define PL310_REG2_INT_MASK_STATUS_ERRRT_SHIFT                                 (5u)
#define PL310_REG2_INT_MASK_STATUS_ERRRD                                       (0x00000040u)
#define PL310_REG2_INT_MASK_STATUS_ERRRD_SHIFT                                 (6u)
#define PL310_REG2_INT_MASK_STATUS_SLVERR                                      (0x00000080u)
#define PL310_REG2_INT_MASK_STATUS_SLVERR_SHIFT                                (7u)
#define PL310_REG2_INT_MASK_STATUS_DECERR                                      (0x00000100u)
#define PL310_REG2_INT_MASK_STATUS_DECERR_SHIFT                                (8u)
#define PL310_REG2_INT_RAW_STATUS_ECNTR                                        (0x00000001u)
#define PL310_REG2_INT_RAW_STATUS_ECNTR_SHIFT                                  (0u)
#define PL310_REG2_INT_RAW_STATUS_PARRT                                        (0x00000002u)
#define PL310_REG2_INT_RAW_STATUS_PARRT_SHIFT                                  (1u)
#define PL310_REG2_INT_RAW_STATUS_PARRD                                        (0x00000004u)
#define PL310_REG2_INT_RAW_STATUS_PARRD_SHIFT                                  (2u)
#define PL310_REG2_INT_RAW_STATUS_ERRWT                                        (0x00000008u)
#define PL310_REG2_INT_RAW_STATUS_ERRWT_SHIFT                                  (3u)
#define PL310_REG2_INT_RAW_STATUS_ERRWD                                        (0x00000010u)
#define PL310_REG2_INT_RAW_STATUS_ERRWD_SHIFT                                  (4u)
#define PL310_REG2_INT_RAW_STATUS_ERRRT                                        (0x00000020u)
#define PL310_REG2_INT_RAW_STATUS_ERRRT_SHIFT                                  (5u)
#define PL310_REG2_INT_RAW_STATUS_ERRRD                                        (0x00000040u)
#define PL310_REG2_INT_RAW_STATUS_ERRRD_SHIFT                                  (6u)
#define PL310_REG2_INT_RAW_STATUS_SLVERR                                       (0x00000080u)
#define PL310_REG2_INT_RAW_STATUS_SLVERR_SHIFT                                 (7u)
#define PL310_REG2_INT_RAW_STATUS_DECERR                                       (0x00000100u)
#define PL310_REG2_INT_RAW_STATUS_DECERR_SHIFT                                 (8u)
#define PL310_REG2_INT_CLEAR_ECNTR                                             (0x00000001u)
#define PL310_REG2_INT_CLEAR_ECNTR_SHIFT                                       (0u)
#define PL310_REG2_INT_CLEAR_PARRT                                             (0x00000002u)
#define PL310_REG2_INT_CLEAR_PARRT_SHIFT                                       (1u)
#define PL310_REG2_INT_CLEAR_PARRD                                             (0x00000004u)
#define PL310_REG2_INT_CLEAR_PARRD_SHIFT                                       (2u)
#define PL310_REG2_INT_CLEAR_ERRWT                                             (0x00000008u)
#define PL310_REG2_INT_CLEAR_ERRWT_SHIFT                                       (3u)
#define PL310_REG2_INT_CLEAR_ERRWD                                             (0x00000010u)
#define PL310_REG2_INT_CLEAR_ERRWD_SHIFT                                       (4u)
#define PL310_REG2_INT_CLEAR_ERRRT                                             (0x00000020u)
#define PL310_REG2_INT_CLEAR_ERRRT_SHIFT                                       (5u)
#define PL310_REG2_INT_CLEAR_ERRRD                                             (0x00000040u)
#define PL310_REG2_INT_CLEAR_ERRRD_SHIFT                                       (6u)
#define PL310_REG2_INT_CLEAR_SLVERR                                            (0x00000080u)
#define PL310_REG2_INT_CLEAR_SLVERR_SHIFT                                      (7u)
#define PL310_REG2_INT_CLEAR_DECERR                                            (0x00000100u)
#define PL310_REG2_INT_CLEAR_DECERR_SHIFT                                      (8u)
#define PL310_REG7_CACHE_SYNC_C                                                (0x00000001u)
#define PL310_REG7_CACHE_SYNC_C_SHIFT                                          (0u)
#define PL310_REG7_INV_PA_C                                                    (0x00000001u)
#define PL310_REG7_INV_PA_C_SHIFT                                              (0u)
#define PL310_REG7_INV_PA_INDEX                                                (0x00003FE0u)
#define PL310_REG7_INV_PA_INDEX_SHIFT                                          (5u)
#define PL310_REG7_INV_PA_TAG                                                  (0xFFFFC000u)
#define PL310_REG7_INV_PA_TAG_SHIFT                                            (14u)
#define PL310_REG7_INV_WAY_Way_bits                                            (0x000000FFu)
#define PL310_REG7_INV_WAY_Way_bits_SHIFT                                      (0u)
#define PL310_REG7_CLEAN_PA_C                                                  (0x00000001u)
#define PL310_REG7_CLEAN_PA_C_SHIFT                                            (0u)
#define PL310_REG7_CLEAN_PA_INDEX                                              (0x00003FE0u)
#define PL310_REG7_CLEAN_PA_INDEX_SHIFT                                        (5u)
#define PL310_REG7_CLEAN_PA_TAG                                                (0xFFFFC000u)
#define PL310_REG7_CLEAN_PA_TAG_SHIFT                                          (14u)
#define PL310_REG7_CLEAN_INDEX_C                                               (0x00000001u)
#define PL310_REG7_CLEAN_INDEX_C_SHIFT                                         (0u)
#define PL310_REG7_CLEAN_INDEX_INDEX                                           (0x00003FE0u)
#define PL310_REG7_CLEAN_INDEX_INDEX_SHIFT                                     (5u)
#define PL310_REG7_CLEAN_INDEX_Way                                             (0x70000000u)
#define PL310_REG7_CLEAN_INDEX_Way_SHIFT                                       (28u)
#define PL310_REG7_CLEAN_WAY_Way_bits                                          (0x000000FFu)
#define PL310_REG7_CLEAN_WAY_Way_bits_SHIFT                                    (0u)
#define PL310_REG7_CLEAN_INV_PA_C                                              (0x00000001u)
#define PL310_REG7_CLEAN_INV_PA_C_SHIFT                                        (0u)
#define PL310_REG7_CLEAN_INV_PA_INDEX                                          (0x00003FE0u)
#define PL310_REG7_CLEAN_INV_PA_INDEX_SHIFT                                    (5u)
#define PL310_REG7_CLEAN_INV_PA_TAG                                            (0xFFFFC000u)
#define PL310_REG7_CLEAN_INV_PA_TAG_SHIFT                                      (14u)
#define PL310_REG7_CLEAN_INV_INDEX_C                                           (0x00000001u)
#define PL310_REG7_CLEAN_INV_INDEX_C_SHIFT                                     (0u)
#define PL310_REG7_CLEAN_INV_INDEX_INDEX                                       (0x00003FE0u)
#define PL310_REG7_CLEAN_INV_INDEX_INDEX_SHIFT                                 (5u)
#define PL310_REG7_CLEAN_INV_INDEX_Way                                         (0x70000000u)
#define PL310_REG7_CLEAN_INV_INDEX_Way_SHIFT                                   (28u)
#define PL310_REG7_CLEAN_INV_WAY_Way_bits                                      (0x000000FFu)
#define PL310_REG7_CLEAN_INV_WAY_Way_bits_SHIFT                                (0u)
#define PL310_REG9_D_LOCKDOWN0_DATALOCK000                                     (0x000000FFu)
#define PL310_REG9_D_LOCKDOWN0_DATALOCK000_SHIFT                               (0u)
#define PL310_REG9_I_LOCKDOWN0_INSTRLOCK000                                    (0x000000FFu)
#define PL310_REG9_I_LOCKDOWN0_INSTRLOCK000_SHIFT                              (0u)
#define PL310_REG9_D_LOCKDOWN1_DATALOCK001                                     (0x000000FFu)
#define PL310_REG9_D_LOCKDOWN1_DATALOCK001_SHIFT                               (0u)
#define PL310_REG9_I_LOCKDOWN1_INSTRLOCK001                                    (0x000000FFu)
#define PL310_REG9_I_LOCKDOWN1_INSTRLOCK001_SHIFT                              (0u)
#define PL310_REG9_D_LOCKDOWN2_DATALOCK002                                     (0x000000FFu)
#define PL310_REG9_D_LOCKDOWN2_DATALOCK002_SHIFT                               (0u)
#define PL310_REG9_I_LOCKDOWN2_INSTRLOCK002                                    (0x000000FFu)
#define PL310_REG9_I_LOCKDOWN2_INSTRLOCK002_SHIFT                              (0u)
#define PL310_REG9_D_LOCKDOWN3_DATALOCK003                                     (0x000000FFu)
#define PL310_REG9_D_LOCKDOWN3_DATALOCK003_SHIFT                               (0u)
#define PL310_REG9_I_LOCKDOWN3_INSTRLOCK003                                    (0x000000FFu)
#define PL310_REG9_I_LOCKDOWN3_INSTRLOCK003_SHIFT                              (0u)
#define PL310_REG9_D_LOCKDOWN4_DATALOCK004                                     (0x000000FFu)
#define PL310_REG9_D_LOCKDOWN4_DATALOCK004_SHIFT                               (0u)
#define PL310_REG9_I_LOCKDOWN4_INSTRLOCK004                                    (0x000000FFu)
#define PL310_REG9_I_LOCKDOWN4_INSTRLOCK004_SHIFT                              (0u)
#define PL310_REG9_D_LOCKDOWN5_DATALOCK005                                     (0x000000FFu)
#define PL310_REG9_D_LOCKDOWN5_DATALOCK005_SHIFT                               (0u)
#define PL310_REG9_I_LOCKDOWN5_INSTRLOCK005                                    (0x000000FFu)
#define PL310_REG9_I_LOCKDOWN5_INSTRLOCK005_SHIFT                              (0u)
#define PL310_REG9_D_LOCKDOWN6_DATALOCK006                                     (0x000000FFu)
#define PL310_REG9_D_LOCKDOWN6_DATALOCK006_SHIFT                               (0u)
#define PL310_REG9_I_LOCKDOWN6_INSTRLOCK006                                    (0x000000FFu)
#define PL310_REG9_I_LOCKDOWN6_INSTRLOCK006_SHIFT                              (0u)
#define PL310_REG9_D_LOCKDOWN7_DATALOCK007                                     (0x000000FFu)
#define PL310_REG9_D_LOCKDOWN7_DATALOCK007_SHIFT                               (0u)
#define PL310_REG9_I_LOCKDOWN7_INSTRLOCK007                                    (0x000000FFu)
#define PL310_REG9_I_LOCKDOWN7_INSTRLOCK007_SHIFT                              (0u)
#define PL310_REG9_LOCK_LINE_EN_lockdown_by_line_enable                        (0x00000001u)
#define PL310_REG9_LOCK_LINE_EN_lockdown_by_line_enable_SHIFT                  (0u)
#define PL310_REG9_UNLOCK_WAY_unlock_all_lines_by_way_operation                (0x000000FFu)
#define PL310_REG9_UNLOCK_WAY_unlock_all_lines_by_way_operation_SHIFT          (0u)
#define PL310_REG12_ADDR_FILTERING_START_address_filtering_enable              (0x00000001u)
#define PL310_REG12_ADDR_FILTERING_START_address_filtering_enable_SHIFT        (0u)
#define PL310_REG12_ADDR_FILTERING_START_address_filtering_start               (0xFFF00000u)
#define PL310_REG12_ADDR_FILTERING_START_address_filtering_start_SHIFT         (20u)
#define PL310_REG12_ADDR_FILTERING_END_address_filtering_end                   (0xFFF00000u)
#define PL310_REG12_ADDR_FILTERING_END_address_filtering_end_SHIFT             (20u)
#define PL310_REG15_DEBUG_CTRL_DCL                                             (0x00000001u)
#define PL310_REG15_DEBUG_CTRL_DCL_SHIFT                                       (0u)
#define PL310_REG15_DEBUG_CTRL_DWB                                             (0x00000002u)
#define PL310_REG15_DEBUG_CTRL_DWB_SHIFT                                       (1u)
#define PL310_REG15_DEBUG_CTRL_SPNIDEN                                         (0x00000004u)
#define PL310_REG15_DEBUG_CTRL_SPNIDEN_SHIFT                                   (2u)
#define PL310_REG15_PREFETCH_CTRL_Prefetchoffset                               (0x0000001Fu)
#define PL310_REG15_PREFETCH_CTRL_Prefetchoffset_SHIFT                         (0u)
#define PL310_REG15_PREFETCH_CTRL_NotsameIDonexclusivesequenceenable           (0x00200000u)
#define PL310_REG15_PREFETCH_CTRL_NotsameIDonexclusivesequenceenable_SHIFT     (21u)
#define PL310_REG15_PREFETCH_CTRL_IncrdoubleLinefillenable                     (0x00800000u)
#define PL310_REG15_PREFETCH_CTRL_IncrdoubleLinefillenable_SHIFT               (23u)
#define PL310_REG15_PREFETCH_CTRL_Prefetchdropenable                           (0x01000000u)
#define PL310_REG15_PREFETCH_CTRL_Prefetchdropenable_SHIFT                     (24u)
#define PL310_REG15_PREFETCH_CTRL_DoublelinefillonWRAPreaddisable              (0x08000000u)
#define PL310_REG15_PREFETCH_CTRL_DoublelinefillonWRAPreaddisable_SHIFT        (27u)
#define PL310_REG15_PREFETCH_CTRL_Dataprefetchenable                           (0x10000000u)
#define PL310_REG15_PREFETCH_CTRL_Dataprefetchenable_SHIFT                     (28u)
#define PL310_REG15_PREFETCH_CTRL_Instructionprefetchenable                    (0x20000000u)
#define PL310_REG15_PREFETCH_CTRL_Instructionprefetchenable_SHIFT              (29u)
#define PL310_REG15_PREFETCH_CTRL_Doublelinefillenable                         (0x40000000u)
#define PL310_REG15_PREFETCH_CTRL_Doublelinefillenable_SHIFT                   (30u)
#define PL310_REG15_POWER_CTRL_standby_mode_en                                 (0x00000001u)
#define PL310_REG15_POWER_CTRL_standby_mode_en_SHIFT                           (0u)
#define PL310_REG15_POWER_CTRL_dynamic_clk_gating_en                           (0x00000002u)
#define PL310_REG15_POWER_CTRL_dynamic_clk_gating_en_SHIFT                     (1u)

#endif
