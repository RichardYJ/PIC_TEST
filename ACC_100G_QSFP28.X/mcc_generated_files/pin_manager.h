/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC16LF18346
        Version           :  1.01
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


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA2 aliases
#define IO_RA2_TRIS               TRISA2
#define IO_RA2_LAT                LATA2
#define IO_RA2_PORT               RA2
#define IO_RA2_WPU                WPUA2
#define IO_RA2_ANS                ANSA2
#define IO_RA2_SetHigh()    do { LATA2 = 1; } while(0)
#define IO_RA2_SetLow()   do { LATA2 = 0; } while(0)
#define IO_RA2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define IO_RA2_GetValue()         PORTAbits.RA2
#define IO_RA2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define IO_RA2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define IO_RA2_SetPullup()    do { WPUA2 = 1; } while(0)
#define IO_RA2_ResetPullup()   do { WPUA2 = 0; } while(0)
#define IO_RA2_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define IO_RA2_SetDigitalMode()   do { ANSA2 = 0; } while(0)


// get/set IO_RA2 aliases
#define IO_RA2_TRIS               TRISA2
#define IO_RA2_LAT                LATA2
#define IO_RA2_PORT               RA2
#define IO_RA2_WPU                WPUA2
#define IO_RA2_ANS                ANSA2
#define IO_RA2_SetHigh()    do { LATA2 = 1; } while(0)
#define IO_RA2_SetLow()   do { LATA2 = 0; } while(0)
#define IO_RA2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define IO_RA2_GetValue()         PORTAbits.RA2
#define IO_RA2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define IO_RA2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define IO_RA2_SetPullup()    do { WPUA2 = 1; } while(0)
#define IO_RA2_ResetPullup()   do { WPUA2 = 0; } while(0)
#define IO_RA2_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define IO_RA2_SetDigitalMode()   do { ANSA2 = 0; } while(0)


// get/set IO_RA2 aliases
#define IO_RA2_TRIS               TRISA2
#define IO_RA2_LAT                LATA2
#define IO_RA2_PORT               RA2
#define IO_RA2_WPU                WPUA2
#define IO_RA2_ANS                ANSA2
#define IO_RA2_SetHigh()    do { LATA2 = 1; } while(0)
#define IO_RA2_SetLow()   do { LATA2 = 0; } while(0)
#define IO_RA2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define IO_RA2_GetValue()         PORTAbits.RA2
#define IO_RA2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define IO_RA2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define IO_RA2_SetPullup()    do { WPUA2 = 1; } while(0)
#define IO_RA2_ResetPullup()   do { WPUA2 = 0; } while(0)
#define IO_RA2_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define IO_RA2_SetDigitalMode()   do { ANSA2 = 0; } while(0)


// get/set IO_RA2 aliases
#define IO_RA2_TRIS               TRISA2
#define IO_RA2_LAT                LATA2
#define IO_RA2_PORT               RA2
#define IO_RA2_WPU                WPUA2
#define IO_RA2_ANS                ANSA2
#define IO_RA2_SetHigh()    do { LATA2 = 1; } while(0)
#define IO_RA2_SetLow()   do { LATA2 = 0; } while(0)
#define IO_RA2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define IO_RA2_GetValue()         PORTAbits.RA2
#define IO_RA2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define IO_RA2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define IO_RA2_SetPullup()    do { WPUA2 = 1; } while(0)
#define IO_RA2_ResetPullup()   do { WPUA2 = 0; } while(0)
#define IO_RA2_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define IO_RA2_SetDigitalMode()   do { ANSA2 = 0; } while(0)


// get/set IO_RA2 aliases
#define IO_RA2_TRIS               TRISA2
#define IO_RA2_LAT                LATA2
#define IO_RA2_PORT               RA2
#define IO_RA2_WPU                WPUA2
#define IO_RA2_ANS                ANSA2
#define IO_RA2_SetHigh()    do { LATA2 = 1; } while(0)
#define IO_RA2_SetLow()   do { LATA2 = 0; } while(0)
#define IO_RA2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define IO_RA2_GetValue()         PORTAbits.RA2
#define IO_RA2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define IO_RA2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define IO_RA2_SetPullup()    do { WPUA2 = 1; } while(0)
#define IO_RA2_ResetPullup()   do { WPUA2 = 0; } while(0)
#define IO_RA2_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define IO_RA2_SetDigitalMode()   do { ANSA2 = 0; } while(0)


// get/set IO_RA2 aliases
#define IO_RA2_TRIS               TRISA2
#define IO_RA2_LAT                LATA2
#define IO_RA2_PORT               RA2
#define IO_RA2_WPU                WPUA2
#define IO_RA2_ANS                ANSA2
#define IO_RA2_SetHigh()    do { LATA2 = 1; } while(0)
#define IO_RA2_SetLow()   do { LATA2 = 0; } while(0)
#define IO_RA2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define IO_RA2_GetValue()         PORTAbits.RA2
#define IO_RA2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define IO_RA2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define IO_RA2_SetPullup()    do { WPUA2 = 1; } while(0)
#define IO_RA2_ResetPullup()   do { WPUA2 = 0; } while(0)
#define IO_RA2_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define IO_RA2_SetDigitalMode()   do { ANSA2 = 0; } while(0)


// get/set IO_RC3 aliases
#define IO_RC3_TRIS               TRISC3
#define IO_RC3_LAT                LATC3
#define IO_RC3_PORT               RC3
#define IO_RC3_WPU                WPUC3
#define IO_RC3_ANS                ANSC3
#define IO_RC3_SetHigh()    do { LATC3 = 1; } while(0)
#define IO_RC3_SetLow()   do { LATC3 = 0; } while(0)
#define IO_RC3_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define IO_RC3_GetValue()         PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define IO_RC3_SetPullup()    do { WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()   do { WPUC3 = 0; } while(0)
#define IO_RC3_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()   do { ANSC3 = 0; } while(0)


// get/set IO_RC3 aliases
#define IO_RC3_TRIS               TRISC3
#define IO_RC3_LAT                LATC3
#define IO_RC3_PORT               RC3
#define IO_RC3_WPU                WPUC3
#define IO_RC3_ANS                ANSC3
#define IO_RC3_SetHigh()    do { LATC3 = 1; } while(0)
#define IO_RC3_SetLow()   do { LATC3 = 0; } while(0)
#define IO_RC3_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define IO_RC3_GetValue()         PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define IO_RC3_SetPullup()    do { WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()   do { WPUC3 = 0; } while(0)
#define IO_RC3_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()   do { ANSC3 = 0; } while(0)


// get/set IO_RC6 aliases
#define IO_RC6_TRIS               TRISC6
#define IO_RC6_LAT                LATC6
#define IO_RC6_PORT               RC6
#define IO_RC6_WPU                WPUC6
#define IO_RC6_ANS                ANSC6
#define IO_RC6_SetHigh()    do { LATC6 = 1; } while(0)
#define IO_RC6_SetLow()   do { LATC6 = 0; } while(0)
#define IO_RC6_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define IO_RC6_GetValue()         PORTCbits.RC6
#define IO_RC6_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define IO_RC6_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define IO_RC6_SetPullup()    do { WPUC6 = 1; } while(0)
#define IO_RC6_ResetPullup()   do { WPUC6 = 0; } while(0)
#define IO_RC6_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define IO_RC6_SetDigitalMode()   do { ANSC6 = 0; } while(0)


// get/set IO_RC7 aliases
#define IO_RC7_TRIS               TRISC7
#define IO_RC7_LAT                LATC7
#define IO_RC7_PORT               RC7
#define IO_RC7_WPU                WPUC7
#define IO_RC7_ANS                ANSC7
#define IO_RC7_SetHigh()    do { LATC7 = 1; } while(0)
#define IO_RC7_SetLow()   do { LATC7 = 0; } while(0)
#define IO_RC7_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define IO_RC7_GetValue()         PORTCbits.RC7
#define IO_RC7_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define IO_RC7_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define IO_RC7_SetPullup()    do { WPUC7 = 1; } while(0)
#define IO_RC7_ResetPullup()   do { WPUC7 = 0; } while(0)
#define IO_RC7_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define IO_RC7_SetDigitalMode()   do { ANSC7 = 0; } while(0)



/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);





#endif // PIN_MANAGER_H
/**
 End of File
*/