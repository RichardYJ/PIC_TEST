#include "mdio.h"

void mdio_init()
{
	TRISB=(TRISB&~(1<<7));
	TRISB=(TRISB&~(1<<5));
}

#define MDC			LATBbits.LATB7
#define MDIO_out	LATBbits.LATB5
#define MDIO_in		PORTBbits.RB5		

void MDIO_OUT()
{
	TRISB=(TRISB&~(1<<5));
}

void MDIO_IN()
{
	TRISB=(TRISB|(1<<5));
}

void MDIO_Clock_01()
{
	MDC=0;
	NOP();
	MDC=1;
	NOP();
}

void MDIO_Data_0()
{
	MDC=0;
	MDIO_out=0;
	NOP();
	MDC=1;
	NOP();
}

void MDIO_Data_1()
{
	MDC=0;
	MDIO_out=1;
	NOP();
	MDC=1;
	NOP();
}

void MDIO_Start() 
{
	MDIO_Data_0();
	MDIO_Data_0();
}

void MDIO_R_opcode()
{
	MDIO_Data_1();
	MDIO_Data_1();
}

void MDIO_W_val_opcode()
{
	MDIO_Data_0();
	MDIO_Data_1();
}

void MDIO_W_reg_opcode()
{
	MDIO_Data_0();
	MDIO_Data_0();
}

void MDIO_adder_reg(uint8_t byte)
{
	uint8_t i;
	for(i=0;i<5;i++)
	{
		if(byte&0x10)MDIO_Data_1();
		else  MDIO_Data_0();
		byte=byte<<1;
	}
}

void MDIO_R_TA()
{ 
	MDIO_Clock_01();
	MDIO_Clock_01();
}

void MDIO_W_TA()
{
	MDIO_Data_1();
	MDIO_Data_0();
}


void MDIO_Idle()
{
	uint8_t i;
	for(i=0;i<32;i++)
		MDIO_Data_1();
}

void MDIO_write_regAddr(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regData)
{
    uint16_t i;
	MDIO_OUT();			
	MDIO_Idle();				
	MDIO_Start();
	MDIO_W_reg_opcode();
	MDIO_adder_reg(PHYADDER);
	MDIO_adder_reg(DEVADDER);
	MDIO_W_TA();
	for(i=0;i<16;i++)
	{
		if(regData&0x8000)MDIO_Data_1();
		else MDIO_Data_0();
		regData=regData<<1;
	}
	MDIO_Idle();
}

uint16_t MDIO_read_value(uint8_t PHYADDER,uint8_t DEVADDER)
{
    uint16_t tmp,i;
	MDIO_OUT();			
	MDIO_Start();
	MDIO_R_opcode();
	MDIO_adder_reg(PHYADDER);
	MDIO_adder_reg(DEVADDER);
	
	MDIO_IN();			
	MDIO_R_TA();
	for(i=0;i<16;i++)
	{
		tmp=tmp<<1;
		MDC=0;
		NOP();
		MDC=1;
		if(MDIO_in==1)tmp=tmp|0x0001;
		NOP();
	}
	MDIO_OUT();			
	MDIO_Idle();

	return tmp;
}


uint16_t MDIO_read(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regAddr)
{
	MDIO_write_regAddr(PHYADDER,DEVADDER,regAddr);
	return MDIO_read_value(PHYADDER,DEVADDER);
}


void MDIO_write_value(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regData)
{
    uint16_t i;
	MDIO_OUT();			
	MDIO_Start();
	MDIO_W_val_opcode();
	MDIO_adder_reg(PHYADDER);
	MDIO_adder_reg(DEVADDER);
	MDIO_W_TA();
	for(i=0;i<16;i++)
	{
		if(regData&0x8000)MDIO_Data_1();
		else MDIO_Data_0();
		regData=regData<<1;
	}
}


void MDIO_write(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regAddr,uint16_t regData)
{
	MDIO_write_regAddr(PHYADDER,DEVADDER,regAddr);
	MDIO_write_value(PHYADDER,DEVADDER,regData);
}


