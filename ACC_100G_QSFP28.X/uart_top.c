#include "mcc_generated_files/mcc.h"
#include "uart_top.h"
#include "golden_eagle_i2c.h"


void uart_send_char(uint8_t *buffer)            // ?????
{ 
	char * temp_ptr = buffer;
	while(*temp_ptr != '\0')
	{
		//while(PIR1bits.TXIF == 0);
		//TXREG = *temp_ptr++;
        while(0 == PIR1bits.TXIF)
        {
        }
        TX1REG = *temp_ptr++;    // Write the data byte to the USART.
	}	

}

void uart_send_byte(char temp)               // ??????
{ 
	//while(PIR1bits.TXIF == 0);
	//TXREG = temp;	
        while(0 == PIR1bits.TXIF)
        {
        }
        TX1REG = temp;    // Write the data byte to the USART.
}

void uart_send_dec(uint32_t decValue)
{
    if(decValue/1000)   uart_send_byte(decValue/1000+'0');	
	decValue = decValue%1000;
	uart_send_byte(decValue/100+'0');
	decValue = decValue%100;
	uart_send_byte(decValue/10+'0');
	decValue = decValue%10;
	uart_send_byte(decValue+'0');
}

void uart_send_hex(uint8_t hexValue)
{
    uint8_t  hexH;
    uint8_t  hexL;
  
    hexH = hexValue/16;
    hexL = hexValue - (16*hexH);
    
    if(hexH > 9) EUSART_Write(hexH+55); //convert to ASCII A~F
    else EUSART_Write(hexH+48); //convert to ASCII 0~9
    
    if(hexL > 9) EUSART_Write(hexL+55); //convert to ASCII A~F
    else EUSART_Write(hexL+48); //convert to ASCII 0~9
}

void uart_send_hex16(uint16_t hexValue)
{
    uint8_t  hexH;
    uint8_t  hexM1;
    uint8_t  hexM2;
    uint8_t  hexL;
  
    hexH = hexValue/16/16/16;
    hexM1 = hexValue/16/16-(hexH*16);
    hexM2 = hexValue/16-(hexH*16*16)-(hexM1*16);
    hexL = hexValue-(hexH*16*16*16)-(hexM1*16*16)-(hexM2*16);
    
    if(hexH > 9) EUSART_Write(hexH+55); //convert to ASCII A~F
    else EUSART_Write(hexH+48); //convert to ASCII 0~9
    
    if(hexM1 > 9) EUSART_Write(hexM1+55); //convert to ASCII A~F
    else EUSART_Write(hexM1+48); //convert to ASCII 0~9
    
    if(hexM2 > 9) EUSART_Write(hexM2+55); //convert to ASCII A~F
    else EUSART_Write(hexM2+48); //convert to ASCII 0~9
    
    if(hexL > 9) EUSART_Write(hexL+55); //convert to ASCII A~F
    else EUSART_Write(hexL+48); //convert to ASCII 0~9
}