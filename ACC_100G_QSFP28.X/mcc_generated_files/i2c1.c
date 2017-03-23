/**
  MSSP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1.c

  @Summary
    This is the generated header file for the MSSP1 driver using 
    MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for MSSP1.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.16
        Device            :  PIC16LF18346
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB 	          :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "i2c1.h"
//#include "G:\WORK_PIC\XIDE\MSSP2_I2C\16F18346_I2C2_100G\16F18346_I2C2_100G.X\backup\16F18346_I2C2_1.X_bk20160920_01_i2c1_print\uart_top.h"
//#include "eusart.h"
//Don't try to use uart print for debug, because the uart print will cost too many cpu time, leadt to r/w error for I2C slave:
//The I2C slave need to be realtime

#define I2C1_SLAVE_ADDRESS 0x50    //0101 0000  -> 1010 000x
#define I2C1_SLAVE_MASK    0x7F

typedef enum
{
    SLAVE_NORMAL_DATA,
    SLAVE_DATA_ADDRESS,
} SLAVE_WRITE_DATA_TYPE;

/**
 Section: Global Variables
*/

volatile uint8_t    I2C1_slaveWriteData      = 0x55;

/**
 Section: Local Functions
*/
void I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS i2c_bus_state);



/**
  Prototype:        void I2C1_Initialize(void)
  Input:            none
  Output:           none
  Description:      I2C1_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            I2C1_Initialize();

*/
void I2C1_Initialize(void)
{
    // initialize the hardware
    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP High Speed; UA dontupdate; CKE disabled; D_nA lastbyte_address; 
    SSP1STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; CKP disabled; SSPM 7 Bit Polling; SSPOV no_overflow; 
    SSP1CON1 = 0x26;
    // ACKEN disabled; GCEN disabled; PEN disabled; ACKDT acknowledge; RSEN disabled; RCEN disabled; ACKSTAT received; SEN disabled; 
    SSP1CON2 = 0x00;
    // ACKTIM ackseq; SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x00;
    // SSP1MSK 127; 
    SSP1MSK = (I2C1_SLAVE_MASK << 1);  // adjust UI mask for R/nW bit            
    // SSP1ADD 80; 
    SSP1ADD = (I2C1_SLAVE_ADDRESS << 1);  // adjust UI address for R/nW bit

    // clear the slave interrupt flag
    PIR1bits.SSP1IF = 0;
    // enable the master interrupt
    PIE1bits.SSP1IE = 1;

}

void I2C1_ISR ( void )
{
    uint8_t     i2c_data                = 0x55;


    // NOTE: The slave driver will always acknowledge
    //       any address match.

    PIR1bits.SSP1IF = 0;        // clear the slave interrupt flag
    i2c_data        = SSP1BUF;  // read SSPBUF to clear BF
    if(1 == SSP1STATbits.R_nW)
    {
        if((1 == SSP1STATbits.D_nA) && (1 == SSP1CON2bits.ACKSTAT))
        {
            // callback routine can perform any post-read processing
            I2C1_StatusCallback(I2C1_SLAVE_READ_COMPLETED);
        }
        else
        {
            // callback routine should write data into SSPBUF
            I2C1_StatusCallback(I2C1_SLAVE_READ_REQUEST);
        }
    }
    else if(0 == SSP1STATbits.D_nA)
    {
        // this is an I2C address

        // callback routine should prepare to receive data from the master
        I2C1_StatusCallback(I2C1_SLAVE_WRITE_REQUEST);
    }
    else
    {
        I2C1_slaveWriteData   = i2c_data;

        // callback routine should process I2C1_slaveWriteData from the master
        I2C1_StatusCallback(I2C1_SLAVE_WRITE_COMPLETED);
    }

    SSP1CON1bits.CKP    = 1;    // release SCL

} // end I2C1_ISR()



/**

    Example implementation of the callback

    This slave driver emulates an EEPROM Device.
    Sequential reads from the EEPROM will return data at the next
    EEPROM address.

    Random access reads can be performed by writing a single byte
    EEPROM address, followed by 1 or more reads.

    Random access writes can be performed by writing a single byte
    EEPROM address, followed by 1 or more writes.

    Every read or write will increment the internal EEPROM address.

    When the end of the EEPROM is reached, the EEPROM address will
    continue from the start of the EEPROM.
*/

void I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS i2c_bus_state)
{


    static uint16_t eepromAddress    = 0;  //for addressing larger than 256Byte
    static uint8_t slaveWriteType   = SLAVE_NORMAL_DATA;


    switch (i2c_bus_state)
    {
        case I2C1_SLAVE_WRITE_REQUEST:
            // the master will be sending the eeprom address next
            slaveWriteType  = SLAVE_DATA_ADDRESS;
        break;


        case I2C1_SLAVE_WRITE_COMPLETED:
            switch(slaveWriteType)
            {
                case SLAVE_DATA_ADDRESS:
                    if(I2C1_slaveWriteData>=128)
                    {
                     eepromAddress    = I2C1_slaveWriteData+128*EEPROM_Buffer[127] ;   
                    }
                    else
                    {
                     eepromAddress    = I2C1_slaveWriteData;   
                    }
                break;


                case SLAVE_NORMAL_DATA:
                default:
                    EEPROM_Buffer[eepromAddress++]    = I2C1_slaveWriteData;   
                 
                    
                    if(sizeof(EEPROM_Buffer) <= eepromAddress) //this compare will cost too many mcu time, will cause SCL conflict,unless set MCU to 32MHz
                    {
                    eepromAddress = 0;    // wrap to start of eeprom page
                    }
                break;
            } // end switch(slaveWriteType)

        slaveWriteType  = SLAVE_NORMAL_DATA;
        break;

        case I2C1_SLAVE_READ_REQUEST:
            SSP1BUF = EEPROM_Buffer[eepromAddress++];
            if(sizeof(EEPROM_Buffer) <= eepromAddress)  //this compare will cost too many mcu time, will cause SCL conflict,unless set MCU to 32MHz
            {
               eepromAddress = 0;    // wrap to start of eeprom page
            }
            break;

        case I2C1_SLAVE_READ_COMPLETED:
        default:;
         
    } // end switch(i2c_bus_state)

}

