@/*******************************************************************************
@* DISCLAIMER
@* This software is supplied by Renesas Electronics Corporation and is only
@* intended for use with Renesas products. No other uses are authorized. This
@* software is owned by Renesas Electronics Corporation and is protected under
@* all applicable laws, including copyright laws.
@* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
@* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
@* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
@* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
@* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
@* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
@* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
@* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
@* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
@* Renesas reserves the right, without notice, to make changes to this software
@* and to discontinue the availability of this software. By using this software,
@* you agree to the additional terms and conditions found by accessing the
@* following link:
@* http://www.renesas.com/disclaimer
@* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
@*******************************************************************************/
@/*******************************************************************************
@* File Name   : reset_handler.asm
@* $Rev: 758 $
@* $Date:: 2018-12-07 16:39:53 +0900#$
@* Description : Reset handler
@*******************************************************************************/


@ Standard definitions of mode bits and interrupt (I & F) flags in PSRs
    .EQU    USR_MODE,   0x10
    .EQU    FIQ_MODE,   0x11
    .EQU    IRQ_MODE,   0x12
    .EQU    SVC_MODE,   0x13
    .EQU    ABT_MODE,   0x17
    .EQU    UND_MODE,   0x1b
    .EQU    SYS_MODE,   0x1f
    .EQU    Thum_bit,   0x20            @ CPSR/SPSR Thumb bit

@==================================================================
@ Entry point for the Reset handler
@==================================================================
    .section    RESET_HANDLER, #execinstr
    .arm

    .extern  __svc_stack_end     @ Linker symbol from scatter file

    .weak    DTBL_F
    .weak    BTBL_F

    .weak    DTBL_F2
    .weak    BTBL_F2

    .extern  vector_table
    .extern  R_SC_HardwareSetup
    .extern  Enable_VFP
    .extern  INITSCT
    .extern  __application_base_address
    .extern  r_spibsc_setup


    .global  reset_handler

@******************************************************************************
@ Function Name : reset_handler
@ Description   : This function is the assembler function executed after reset
@               : cancellation. After initial setting for the stack pointer or 
@               : the MMU and reset cancellation, executes initial setting for 
@               : the minimum required peripheral functions.
@******************************************************************************
reset_handler:

@===================================================================
@ Clock Setting
@ Set FRQCR.IFC : CPU Clock 1/8(132MHz) -> 1/2(528MHz)
@===================================================================
    @; Set standby_mode_en of REG15 Power Control Register
    LDR  r0, =0x1F003F80            @;; Address(REG15 Power Control Register)
    LDR  r1, =0x00000001            @;; Setting Value (REG15 Power Control Register)
    STR  r1, [r0]                   @;; REG15_POWER_CTRL = 0x00000001
    LDR  r1, [r0]                   @;; dummy read

    @; FRQCR = 0x0012 PLL(x88), I:B:P1:P0 = 22:5.5:2.75:1.375
    LDR  r0, =0xFCFE0010            @;; Address(FRQCR Register)
    LDR  r1, =0x0012                @;; Setting Value(FRQCR Register)
    STRH r1, [r0]                   @;; FRQCR = 0x0012
    LDRH r0, [r0]                   @;; dummy read

@===================================================================
@ Set Vector Base Address Register (VBAR) to point to initializer routine
@===================================================================
    LDR r0, =vector_table
    MCR p15, 0, r0, c12, c0, 0

@==================================================================
@ Disable cache and MMU in case it was left enabled from an earlier run
@ This does not need to be done from a cold reset 
@==================================================================
    MRC  p15, 0, r0, c1, c0, 0      @;; Read CP15 System Control register (SCTLR)
    BIC  r0, r0, #(0x1 << 13)       @;; Set Low Vectors
    BIC  r0, r0, #(0x1 << 12)       @;; Clear I bit 12 to disable I Cache
    BIC  r0, r0, #(0x1 <<  2)       @;; Clear C bit  2 to disable D Cache
    BIC  r0, r0, #0x1               @;; Clear M bit  0 to disable MMU
    MCR  p15, 0, r0, c1, c0, 0      @;; Write value back to CP15 System Control register

@==================================================================
@ Setting up Stack Area (SVC)
@==================================================================
    CPS  #SVC_MODE                  @;; SVC Mode
    LDR  sp, =__svc_stack_end


@==================================================================
@ Section initialize for r_spibsc_setup
@==================================================================
    LDR  r0, =DTBL_F2                @;; ROM to RAM table for r_spibsc_setup
    LDR  r1, =BTBL_F2                @;; RAM zero fill table for r_spibsc_setup
    LDR  r12,=INITSCT                @;; Function for Initialize sections
    BLX  r12                         @;; Call


@==================================================================
@ Hardware initialize
@ Initialize SPIBSC (16.5MHz, )
@==================================================================
    LDR  r12,=r_spibsc_setup       @;; Save this in register for possible long jump
    BLX  r12                       @;; Hardware Initialize




@==================================================================
@ Section initialize for R_SC_HardwareSetup
@==================================================================
    LDR  r0, =DTBL_F                @;; ROM to RAM table for R_SC_HardwareSetup
    LDR  r1, =BTBL_F                @;; RAM zero fill table for R_SC_HardwareSetup
    LDR  r12,=INITSCT               @;; Function for Initialize sections
    BLX  r12                        @;; Call

#if defined(__ARM_FP) || defined(__ARM_NEON_FP)
@===================================================================
@ Enable the vfp
@===================================================================
    LDR  r12,=Enable_VFP            @;; Save this in register for possible long jump
    BLX  r12                        @;; Call to enable the vfp
#endif

@==================================================================
@ Hardware initialize
@ Initialize CPG, BSC for CS2 and CS3, and enable On-Chip Data-Retention RAM
@==================================================================
    LDR  r12,=R_SC_HardwareSetup   @;; Save this in register for possible long jump
    BLX  r12                        @;; Hardware Initialize

@==================================================================
@ check application signature
@==================================================================
    BL   chk_signature

@==================================================================
@ Jump to application program
@==================================================================
    LDR  r12,=__application_base_address
    BX   r12

@==================================================================
@ Subroutine for check application signature
@==================================================================
chk_signature:
    LDR r0, =__application_base_address
    LDR r1, =signature1
    ADD r0, r0, #0x20               ;@ signature offset = vector + 0x0020
    LDR r2, [r1], #4
    LDR r3, [r0], #4
    CMP r2, r3
    LDREQ r2, [r1], #4
    LDREQ r3, [r0], #4
    CMPEQ r2, r3
    LDREQ r2, [r1], #4
    LDREQ r3, [r0], #4
    CMPEQ r2, r3
    LDREQ r2, [r1], #4
    LDREQ r3, [r0], #4
    CMPEQ r2, r3
    LDREQ r1, =signature2
    LDREQ r2, [r1], #4
    LDREQ r3, [r0], #4
    CMPEQ r2, r3
    LDREQ r2, [r1], #4
    LDREQ r3, [r0], #4
    CMPEQ r2, r3
    LDREQ r2, [r1], #4
    LDREQ r3, [r0], #4
    CMPEQ r2, r3
    LDREQ r2, [r1], #4
    LDREQ r3, [r0], #4
    CMPEQ r2, r3
    BXEQ  lr
1:
    B   1b


@==================================================================
@ application validation signature
@==================================================================
    .section .rodata.signature_fragment
    .align 2
signature2:
    .ascii "rogramTest.     "
    .align 2
signature1:
    .ascii ".BootLoad_ValidP"
    .align 2


    .END
