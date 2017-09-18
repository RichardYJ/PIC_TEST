/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC16LF18346
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#include <xc.h>
#include "pin_manager.h"
#include <stdbool.h>

void PIN_MANAGER_Initialize(void)
{
    LATB = 0x0;
    LATA = 0x0;
    LATC = 0x0;
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x0;
    ANSELA = 0x37;
    ANSELB = 0x0;
    ANSELC = 0xFF;
    TRISB = 0xF0;
    TRISC = 0x27; // 0xEF;  //make RC3 output also
    TRISA = 0x27;

    
    ODCONC =0x00;

    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    SSP1DATPPSbits.SSP1DATPPS = 0x0C;   //RB4->MSSP1:SDA1;
    SSP1CLKPPSbits.SSP1CLKPPS = 0x0E;   //RB6->MSSP1:SCL1;
    RA4PPSbits.RA4PPS = 0x1E;   //RA4->CLKREF:CLKR;
    RB4PPSbits.RB4PPS = 0x19;   //RB4->MSSP1:SDA1;
    RC4PPSbits.RC4PPS = 0x14;   //RC4->EUSART:TX;
    RB7PPSbits.RB7PPS = 0x1A;   //RB7->MSSP2:SCL2;
    RB6PPSbits.RB6PPS = 0x18;   //RB6->MSSP1:SCL1;
    SSP2DATPPSbits.SSP2DATPPS = 0x0D;   //RB5->MSSP2:SDA2;
    SSP2CLKPPSbits.SSP2CLKPPS = 0x0F;   //RB7->MSSP2:SCL2;
    RB5PPSbits.RB5PPS = 0x1B;   //RB5->MSSP2:SDA2;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;

}

/**
 End of File
*/
