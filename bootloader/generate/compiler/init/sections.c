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
* File Name : sections.c
* $Rev: 744 $
* $Date:: 2018-11-30 14:11:22 +0900#$
* Description :
******************************************************************************/
#include "r_typedefs.h"


/* List of the section of variables with initial value */
typedef struct {
    void    *rom_s;     /* Top address on ROM    */
    void    *rom_e;     /* Bottom address on ROM */
    void    *ram_s;     /* Top address on RAM    */
} DTBL_S;

/* List of the section of variables with zero clear */
typedef struct {
    void    *b_s;       /* Top address    */
    void    *b_e;       /* Bottom address */
} BTBL_S;

extern  short   __module2_load_start;
extern  short   __module2_load_end;
extern  short   __module2_exec_start;

extern  short   __module4_load_start;
extern  short   __module4_load_end;
extern  short   __module4_exec_start;


extern  short   __bss_start;
extern  short   __bss_end;

const DTBL_S    DTBL_F[] =
{
/*  {  rom start address,     rom end address,     ram start address    },*/
    { &__module2_load_start, &__module2_load_end, &__module2_exec_start },
    {   0,  0,  0   },  /* terminator */
};


const BTBL_S    BTBL_F[] =
{
/*  {  bss start address,    bss end address     },*/
    { &__bss_start, &__bss_end },
    {   0,  0   },  /* terminator */
};


const DTBL_S    DTBL_F2[] =
{
/*  {  rom start address,     rom end address,     ram start address    },*/
    { &__module4_load_start, &__module4_load_end, &__module4_exec_start },
    {   0,  0,  0   },  /* terminator */
};



const BTBL_S    BTBL_F2[] =
{
/*  {  bss start address,    bss end address     },*/
    {   0,  0   },  /* terminator */
};



/* End of File */
