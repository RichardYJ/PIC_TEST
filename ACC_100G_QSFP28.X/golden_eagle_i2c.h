/* 
 * File:   golden_eagle_i2c.h
 * Author: Administrator
 *
 * Created on August 3, 2016, 10:59 AM
 */

#ifndef GOLDEN_EAGLE_I2C_H
#define	GOLDEN_EAGLE_I2C_H


#ifdef	__cplusplus
extern "C" {
#endif
    
#define MAX_RETRY         100
#define SLAVE_ADDRESS     0x10 //GE  sad4=1,sad3=0,sad2=0,sad1=0,sad0=0
#define PAGE_LIMIT         16  // Change as stated on EEPROM device datasheet
    
#define T uint16_t
#define ONE ((T)1)


int GE_I2C2_ByteWrite(uint8_t *dataAddress, uint8_t *data2Byte, uint8_t addlen);
uint8_t GE_I2C2_ByteRead(uint8_t *dataAddress, uint8_t *data2Byte,uint8_t addlen);
int GE_I2C2_BufferWrite(uint8_t *dataAddress, uint8_t *dataBuffer,  uint8_t addlen, uint8_t buflen);
void GE_I2C2_BufferRead(uint8_t *dataAddress, uint8_t *dataBuffer,  uint8_t addlen, uint8_t buflen);
int GE_I2C2_HexWrite(uint16_t RegAddr, uint16_t RegValue);
uint16_t GE_I2C2_HexRead(uint16_t RegAddr);
int GE_I2C2_ByteHLWrite(uint8_t RegAddrH,uint8_t RegAddrL,uint8_t RegValueH, uint8_t RegValueL);
uint16_t GE_I2C2_ByteHLRead(uint8_t RegAddrH,uint8_t RegAddrL);
int GE_I2C2_AddrWrite(uint8_t *dataAddress, uint8_t addlen);
inline static T bitset(T value, T new_value, int lbit, int width);
inline static void GE_I2C2_bitset(uint16_t addr, uint16_t new_value, int lbit, int width);
void GE_reload_default(void);
void GE_PRBS31_test(void);
int32_t get_int32(const unsigned char* data);
uint16_t get_int16(const unsigned char* data);
void GE_set_polarity(void);
void GE_state_reset(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GOLDEN_EAGLE_I2C_H */

