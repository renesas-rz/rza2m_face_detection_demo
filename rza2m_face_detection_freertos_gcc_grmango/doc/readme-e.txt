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
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name : [RZ/A2M] DRP Parallel Operation Sample Program
* File Name   : readme-e.txt
*******************************************************************************/
/*******************************************************************************
*   
*             ：Aug. 03,2021 Rev.2.02.00    Update driver to the latest version
*******************************************************************************/

1. Before Use

  This sample code has been tested using the GR-MANGO Rev.B board
  with the RZ/A2M group R7S921058. 
  Use this readme file, the application note, and the sample code as a reference 
  for your software development.


  ****************************** CAUTION ******************************
   This sample code are all reference, and no one to guarantee the 
   operation. Please use this sample code for the technical 
   reference when customers develop software.
  ****************************** CAUTION ******************************


2. System Verification

  This sample code was developed and tested with the following components:

    CPU                                 : RZ/A2M
    Board                               : GR-MANGO Rev.B board
                                          HDMI board output (Control IC: Low Power HDMI Transmitter EP952)
    Compiler                            : GNU ARM Embedded 6.3.1.20170620
    Integrated development environment  : e2 studio Version 7.8.0.
    Camera                              : Raspberry Pi Camera V2
    Monitor                             : Monitor compatible with Full-WXGA(1366*768) resolution

3. About Sample Code

    In the example, we connect the Sony IMX219 CMOS sensor through MIPI interface, input a 1280x720 resolution image, 
	and use DRP in RZ/A2M to perform Simple ISP processing and image scaling processing on the input image, 
	and then run a light and efficient mask face detection mode

    This loader program conforms to the specification of Macronix MX25L51245G. When using another serial flash memory, 
    change the source code of the loader program project [rza2m_sflash_boot_loader_gcc] that is included in 
    "RZ/A2M Group Example of Booting from Serial Flash Memory" application note according to the specifications of 
    the flash memory, and then generate the new load module. The project debug configuration uses the loader program
    after changing the file name of the generated load module to "rza2_qspi_flash_ddr_bootloader.elf".


4. Operation Confirmation Conditions

  (1) Boot mode
    - Boot mode 6
      Boot from OctaFlash(SPI mode) connected to OctaFlash space.
      * The program can not be operated if the boot mode except the above is specified.

  (2) Operating frequency
      The RZ/A2M clock pulse oscillator module is set to ensure that the RZ/A2M clocks on the CPU board
      board have the following frequencies:
      (The frequencies indicate the values in the state that the clock with 24MHz
      is input to the EXTAL pin in RZ/A2M clock mode 1.)
      - CPU clock (I clock)                 : 528MHz
      - Image processing clock (G clock)    : 264MHz
      - Internal bus clock (B clock)        : 132MHz
      - Peripheral clock1 (P1 clock)        :  66MHz
      - Peripheral clock0 (P0 clock)        :  33MHz
      - OM_CK/OM_CK#                        : 132MHz
      - CKIO                                : 132MHz

  (3) OctaFlash (connected to OctaFlash space) used
    - Manufacturer  : Macronix Inc.
    - Product No.   : MX25UW12845GXDIO0

  (4) Setting for cache
      Initial setting for the L1 and L2 caches is executed by the MMU. 
      Refer to the "RZ/A2M group Example of Initialization" application note about "Setting for MMU" for 
      the valid/invalid area of L1 and L2 caches.


5. Operational Procedure

  Use the following procedure to execute these sample code.

  (1) Setting up sample code
    Copy the sample code directory to the e2 studio workspace directory
    in the host PC (eg: "C:\e2studio_Workspace").


  (2) Activating integrated development environment
    Activate the integrated development environment e2 studio.

  (3) Building application program
    After importing project of sample code by the e2 studio menu, build the project 
    and generate the executable file.


  (4) Downloading sample code
    Connect GR-MANGO CN1 and PC via USB cable.
    PC detects the GR-MANGO as MBED drive.
    Drag-and-drop the binary file to the MBED drive.

  (5) Executing sample code
    Connect the camera to GR-MANGO CN13, and connect display to CN9 via HDMI cable.
    Ensure that complete to download program, and push reset button on GR-PEACH.
	
  (6) Push SW2 button to switch demo mode: face+mask, face only, mask only

/* End of File */
