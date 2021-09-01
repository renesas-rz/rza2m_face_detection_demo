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
* File Name   : linker_script.ld
* $Rev: 731 $
* $Date:: 2018-11-21 10:56:39 +0900#$
* Description : Linker Script File
*******************************************************************************/

MEMORY {
    VECTOR_TABLE      (rx)  : ORIGIN = 0x20000000, LENGTH = 0x00000100
    HARDWARE_INIT_ROM (rx)  : ORIGIN = 0x20000200, LENGTH = 0x00003E00
    ROM               (rx)  : ORIGIN = 0x20004000, LENGTH = 0x0000C000
    HARDWARE_INIT_RAM (rwx) : ORIGIN = 0x80024000, LENGTH = 0x00003E00
    STACK             (rw)  : ORIGIN = 0x80028000, LENGTH = 0x00010000
    RAM               (rwx) : ORIGIN = 0x80038000, LENGTH = 0x002C8000
}

__application_base_address = 0x20010000;

SECTIONS
{
    LOAD_MODULE1 : {
        KEEP(* (VECTOR_TABLE))      /*asm*/
    } > VECTOR_TABLE

    __vector_table_base = ADDR(LOAD_MODULE1);


    LOAD_MODULE4 : ALIGN( 0x20 ) {
        */r_spibsc_setup.o (.text .text.* .rodata .rodata.*)
        */r_spibsc_setup.o (.data .data.*)
        . = ALIGN( 0x4 );
    } > HARDWARE_INIT_RAM AT > HARDWARE_INIT_ROM

    __module4_load_start  = LOADADDR(LOAD_MODULE4);
    __module4_exec_start  = ADDR(LOAD_MODULE4);
    __module4_load_end    = LOADADDR(LOAD_MODULE4) + SIZEOF(LOAD_MODULE4);



    LOAD_MODULE2 : ALIGN( 0x20 ) {
        /* This section used by "hardware setup" and must to be assigned to the Internal RAM. */
        "*/r_cpg/*.o"      (.text .text.* .rodata .rodata.*)
        EXCLUDE_FILE ("*/r_spibsc_adjust_timing_data.o") "*/r_spibsc/*.o"   (.text .text.* .rodata .rodata.*)
        "*/hwsetup.o"      (.text .text.* .rodata .rodata.*)

        *(.data .data.*)

        . = ALIGN( 0x4 );
    } > HARDWARE_INIT_RAM AT > HARDWARE_INIT_ROM

    __module2_load_start  = LOADADDR(LOAD_MODULE2);
    __module2_exec_start  = ADDR(LOAD_MODULE2);
    __module2_load_end    = LOADADDR(LOAD_MODULE2) + SIZEOF(LOAD_MODULE2);

    LOAD_MODULE3 : ALIGN( 0x20 ) {
        KEEP(* (RESET_HANDLER))     /*asm*/

        . = ALIGN( 0x80 );
        * (INIT_SECTION)            /*asm*/
        *(.text .text.*)
        *(.rodata .rodata.*)

    } > ROM

    .bss (NOLOAD) : ALIGN( 0x20 ) {
        __bss_start = .;

        *(.bss .bss.* COMMON)

        . = ALIGN( 0x4 );
        __bss_end = .;

    } > RAM

    .stack (NOLOAD) : ALIGN( 0x10 ) {
        __svc_stack_start = .;
        . += 0x00002000;
        . = ALIGN( 0x10 );
        __svc_stack_end = .;

    } > STACK

    .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > ROM

    .ARM.exidx :
    {
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
    } > ROM

}
/*EOF*/
