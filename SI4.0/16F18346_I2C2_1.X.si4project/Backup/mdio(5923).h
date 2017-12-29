#ifndef _MDIO_H
#define _MDIO_H

/**
  Section: Included Files
*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <xc.h>
#include <pic.h>


#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif



#define CLK_H	(LATBbits.LATB7 =1)
#define CLK_L	(LATBbits.LATB7 =0)

#define DATA(x)	(LATBbits.LATB5 =x)
#define DATA_L	(LATBbits.LATB5 =0)
#define DATA_H	(LATBbits.LATB5 =1)

#define H 1
#define L 0


#define OUT(x)	do{		\
	uint16_t i=0x7ff;	\
	CLK_L;              \
    while(--i);i=0x7ff; \
	LATBbits.LATB5 = x; \
	while(--i);			\
	CLK_H;i=0x7ff;		\
	while(--i);i=0x7ff; \
    while(--i);         \
					}while(0)

/*
			CLK_L; \
			LATBbits.LATB5 = x; \
			__delay_ms(1);	\
			CLK_H;	\
			__delay_ms(1);	\
*/

void mdio_init();
//void mdio_write(uint8_t dev,uint16_t regAddr,uint16_t data);
//uint16_t mdio_read_data(uint8_t dev);
void SMI_write(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regAddr,uint16_t value);
uint16_t SMI_read(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regAddr);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_MDIO_H

