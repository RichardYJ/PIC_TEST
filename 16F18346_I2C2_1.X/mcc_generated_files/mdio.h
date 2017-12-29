#ifndef _MDIO_H
#define _MDIO_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <xc.h>
#include <pic.h>


#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

void mdio_init();
void MDIO_write(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regAddr,uint16_t regData);
uint16_t MDIO_read(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regAddr);

#ifdef __cplusplus  
    }

#endif

#endif 

