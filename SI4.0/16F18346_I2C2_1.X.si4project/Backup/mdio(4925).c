

#include "mdio.h"

void mdio_init()
{
	TRISB=(TRISB&~(1<<7));
	TRISB=(TRISB&~(1<<5));

}
#if 0


void SMI_Init(void)
{
	uint8_t i;
	MDC_DIR_OUT;
	MDIO_DIR_OUT;
	MDC_0;
	MDIO_1;
	Delay(5);
	MDC_1;
	Delay(5);
	for(i=0;i<=31;i++)
	{
		MDC_0;
		MDIO_1;
		MDC_1;
	}
	MDC_0;
	Delay(10);
}




void SMI_RAW_Write(uint16_t WriteData)
{
	uint8_t i;
	for(i=0;i<16;i++)
	{
		if((WriteData&0x8000)==0x8000)
			MDIO_1;
		else
			MDIO_0;
		Delay(5);
		MDC_1;
		WriteData=WriteData<<1;
		Delay(10);
		MDC_0;		
	}
	
}


void SMI_RAW_Read(uint16_t WriteData)
{
	uint8_t i;
	uint16_t TempBit = 0;
	uint16_t TempData = 0;
	MDIO_DIR_IN;
	MDC_0;
	for(i=0;i<16;i++)
	{
		Delay(5);
		MDC_0;		
		Delay(5);
		if(+++++)



		

	}
}


#if 1
void mdio_write_addr( uint8_t dev,uint16_t regAddr )
{
	uint8_t uc=0x01;
	uint8_t i=0;
	CLK_H;
	for(i=0;i<32;i++)
	{
		OUT(1);
	}
	for(i=0;i<4;i++)
	{
		OUT(L);
	}

	//PAD:0x10
	OUT(1);
	for(i=0;i<4;i++)
	{
		OUT(L);
	}
	//DAD:0x01
	for(i=0;i<4;i++)
	{
		OUT(L);
	}
	OUT(1);

	
//	for(2)
	{
		OUT(1);

		OUT(L);		
	}

	//address
	for(i=0;i<16;i++)
	{
		if( 1==regAddr&0x80 )
			OUT(1);
		else
			OUT(L);
		regAddr = regAddr<<1;
	}
	CLK_L;
	DATA_L;
}

void mdio_write_data( uint8_t dev, uint16_t data )
{
	uint8_t i=0;
	CLK_H;
	for(i=0;i<32;i++)
	{
		OUT(1);
	}
	for(i=0;i<3;i++)
	{
		OUT(1);
	}
	OUT(L);

		//PAD:0x10
	OUT(1);
	for(i=0;i<4;i++)
	{
		OUT(L);
	}
	//DAD:0x01
	for(i=0;i<4;i++)
	{
		OUT(L);
	}
	OUT(1);

	
	//	for(2)
	{
		OUT(1);

		OUT(L); 	
	}

	//data
	for(i=0;i<16;i++)
	{
		//data
		for(i=0;i<16;i++)
		{
			if( 1==data&0x80 )
				OUT(1);
			else
				OUT(L);
			data = data<<1;
		}
	}
}

uint16_t mdio_read_data(uint8_t dev)
{
#if 1
	uint16_t odata=0;
	uint8_t i=0;
	CLK_H;
	for(i=0;i<32;i++)
	{
		OUT(1);
	}
	
	OUT(L);
	OUT(L);
	OUT(1);
	OUT(1);

	//PAD:0x10
	OUT(1);
	for(i=0;i<4;i++)
	{
		OUT(L);
	}
	//DAD:0x01
	for(i=0;i<4;i++)
	{
		OUT(L);
	}
	OUT(1);

	
//	for(1)
	{
		CLK_L;
		CLK_H;
		OUT(L);
		CLK_L;
	}
	TRISB|=1<<5;

	for(i=0;i<16;i++)
	{
		CLK_H;
		odata|=PORTBbits.RB5;
		CLK_L;
		odata=odata<<1;
	}
	TRISB=(TRISB&~(1<<5));
	return odata;
#endif	
}

void mdio_write(uint8_t dev,uint16_t regAddr,uint16_t data)
{
	mdio_write_addr(dev,regAddr);
	mdio_write_data(dev,data);
}

uint16_t mdio_read(uint8_t dev,uint16_t regAddr)
{
	mdio_write_addr(dev,regAddr);
	return mdio_read_data(dev);
}
#endif


#else

//#include <reg51.h> 
//#include <string.h>
//#include <intrins.h>
#include "mdio.h"

//#define leng 0x2
#define  max 0x06
#define  s_nop_()  NOP()//;_nop_();_nop_();_nop_()//;_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_()

uint8_t INBUF_LEN=0;

uint8_t inbuf1[max];  
#if 0
//I2C运行管脚
sbit     SDA=P1^3;
sbit     SCL=P1^2;
//SMI运行管脚
//sbit     MDIO=P1^5;
//sbit     MDC=P1^6;
sbit MDC = P1^0;
sbit MDIO = P1^1;

sbit     work=P3^2;
#else
#define MDC			LATBbits.LATB7
#define MDIO_out	LATBbits.LATB5
#define MDIO_in		PORTBbits.RB5		//PORTHbits.RH3
#endif
bit read_flag= 0 ; 
bit write_flag= 0 ;
bit send_over= 0 ; 

void MDC_OUT_MDIO_OUT()
{
	TRISB=(TRISB&~(1<<7));
	TRISB=(TRISB&~(1<<5));
//	LATBbits.LATB7 = 0;
//	LATBbits.LATB5 = 0;
}


void MDC_OUT_MDIO_IN()
{
	TRISB=(TRISB&~(1<<7));
	TRISB=(TRISB|(1<<5));

//	TRISB=(TRISB&~(1<<7));
//	PORTBbits.RB5 = 1;
//	PORTBbits.RB7 = 1;
//	TRISB=(TRISB&~(1<<5));
}

void delay(uint16_t delay_time)
{
	uint16_t k= 0 ;
	do
	{
	   k++;
	}while(k<delay_time);
}


/***************************
MDC时钟的一个周期
***************************/
void SMI_Clock_01()
{
MDC=0;
s_nop_();
MDC=1;
s_nop_();
}


/***************************
MDIO输入数据0
MDIO在MDC的下降沿输出
***************************/
void SMI_Data_0()
{
MDC=0;
//s_nop_();
MDIO_out=0;
s_nop_();
MDC=1;
s_nop_();
}
/***************************
MDIO输入数据1
***************************/

void SMI_Data_1()
{
MDC=0;
//s_nop_();
MDIO_out=1;
s_nop_();
MDC=1;
s_nop_();
}

/***************************
MDIO输入数据1
***************************/
void SMI_Start() 
{
SMI_Data_0();
SMI_Data_0();
}


void SMI_R_opcode()
{
SMI_Data_1();
SMI_Data_1();
}

void SMI_W_val_opcode()
{
	SMI_Data_0();
	SMI_Data_1();
}

void SMI_W_reg_opcode()
{
	SMI_Data_0();
	SMI_Data_0();
}

/*********************************************
通过SMI写入数据，仅byte的低5位bit
PHYADDER是PHY地址为0，1，2，3，4这;第一个以太网口为0
REGADDER为PHY的寄存器地址,一共32个寄存器
*********************************************/
void SMI_adder_reg(uint8_t byte)
{
   uint8_t i;
   for(i=0;i<5;i++)
   {
    if(byte&0x10)SMI_Data_1();
    else  SMI_Data_0();
    byte=byte<<1;
    }
}

void SMI_R_TA()
{ 
  SMI_Clock_01();
//  SMI_Clock_01();
 
}

void SMI_W_TA()
{
  SMI_Data_1();
  SMI_Data_0();
}


void SMI_Idle()
{
   uint8_t i;
   for(i=0;i<32;i++)
    SMI_Data_1();
}

/*********************************************
通过SMI写取寄存器内容
PHYADDER是PHY地址为0，1，2，3，4这里第一个以太网口为0
REGADDER为PHY的寄存器地址,写一个16位数据
*********************************************/
void SMI_write_regAddr(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t value)
{
    uint16_t i;
	MDC_OUT_MDIO_OUT();			//YJ
	SMI_Idle();
	SMI_Start();
	SMI_W_reg_opcode();
	SMI_adder_reg(PHYADDER);
	SMI_adder_reg(DEVADDER);
	SMI_W_TA();
	for(i=0;i<16;i++)
	{
	  if(value&0x8000)SMI_Data_1();
	  else SMI_Data_0();
	  value=value<<1;
	}
	SMI_Idle();
}

/*********************************************
通过SMI读取寄存器内容
PHYADDER是PHY地址为0，1，2，3，4这里第一个以太网口为0
REGADDER为PHY的寄存器地址,return一个16位数据
*********************************************/
uint16_t SMI_read_value(uint8_t PHYADDER,uint8_t DEVADDER)
{
    uint16_t value,i;
	MDC_OUT_MDIO_OUT();			//YJ
//	SMI_Idle();
	SMI_Start();
	SMI_R_opcode();
	SMI_adder_reg(PHYADDER);
	SMI_adder_reg(DEVADDER);
//	MDIO_out = 1;
	SMI_R_TA();
	MDC_OUT_MDIO_IN();			//YJ
	for(i=0;i<16;i++)
	{
	  value=value<<1;
	  MDC=0;
//	  if(MDIO==1)value=value|0x0001;
	  if(MDIO_in==1)value=value|0x0001;
	  s_nop_();
      MDC=1;
      s_nop_();
	}
	MDC_OUT_MDIO_OUT();			//YJ
	SMI_Idle();
	return value;
}


uint16_t SMI_read(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regAddr)
{
	SMI_write_regAddr(PHYADDER,DEVADDER,regAddr);

	return SMI_read_value(PHYADDER,DEVADDER);
}



void SMI_write_value(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t value)
{
    uint16_t i;
	MDC_OUT_MDIO_OUT();			//YJ
//	SMI_Idle();
	SMI_Start();
	SMI_W_val_opcode();
	SMI_adder_reg(PHYADDER);
	SMI_adder_reg(DEVADDER);
	SMI_W_TA();
	for(i=0;i<16;i++)
	{
	  if(value&0x8000)SMI_Data_1();
	  else SMI_Data_0();
	  value=value<<1;
	}
	SMI_Idle();
}


void SMI_write(uint8_t PHYADDER,uint8_t DEVADDER,uint16_t regAddr,uint16_t value)
{
	SMI_write_regAddr(PHYADDER,DEVADDER,regAddr);

	SMI_write_value(PHYADDER,DEVADDER,value);

}


#if 0
/********************************
Speed的寄存器地址为0.13，10M为0，100M为1
inbuf1[1]==2
Auto为0.12
*********************************/

void Set_RTL8305_Speed(uint8_t PHYADDER,uint8_t value)
{
   uint16_t reg_data;
   bit done=0;                        //进行速率设置抄作为1
   reg_data=SMI_read(PHYADDER,0);
   if(reg_data&0x1000)
	 reg_data&=~(0x1000);

   if(value==0)
   {
     if(reg_data&0x2000)
	 {
	   reg_data&=~(0x2000);
//	   SMI_write(PHYADDER,0,reg_data);
	   done=1;
	 }
   }
   else
   {
     if(~reg_data&0x2000)
	 {
	   reg_data|=0x2000;
//	   SMI_write(PHYADDER,0,reg_data);
	   done=1;
	 }
   }
   if(done==1)SMI_write(PHYADDER,0,reg_data);
   

}


/********************************
Duplex的寄存器地址为0.8，半双工为0，全双工为1
inbuf1[1]==3
Auto为0.12
*********************************/

void Set_RTL8305_Duplex(uint8_t PHYADDER,uint8_t value)
{
   uint16_t reg_data;
   bit done=0;                        //进行速率设置抄作为1
   reg_data=SMI_read(PHYADDER,0);
   if(reg_data&0x1000)
	 reg_data&=~(0x1000);

   if(value==0)
   {
     if(reg_data&0x0100)
	 {
	   reg_data&=~(0x0100);
//	   SMI_write(PHYADDER,0,reg_data);
	   done=1;
	 }
   }
   else
   {
     if(~reg_data&0x0100)
	 {
	   reg_data|=0x0100;
//	   SMI_write(PHYADDER,0,reg_data);
	   done=1;
	 }
   }
   if(done==1)SMI_write(PHYADDER,0,reg_data);
   

}


/********************************
Auto的寄存器地址为0.12，禁用为0，使能为1
inbuf1[1]==4
*********************************/

void Set_RTL8305_Auto(uint8_t PHYADDER,uint8_t value)
{
   uint16_t reg_data;
   bit done=0;                        //进行速率设置抄作为1
   reg_data=SMI_read(PHYADDER,0);
   
   if(value==0)
   {
     if(reg_data&0x1000)
	 {
	   reg_data&=~(0x1000);
//	   SMI_write(PHYADDER,0,reg_data);
	   done=1;
	 }
   }
   else
   {
     if(~reg_data&0x1000)
	 {
	   reg_data|=0x1000;
//	   SMI_write(PHYADDER,0,reg_data);
	   done=1;
	 }
   }
   if(done==1)SMI_write(PHYADDER,0,reg_data);
   

}

/********************************
reset的寄存器地址为0.15，正常为0，复位为1
inbuf1[1]==5
*********************************/
void Set_RTL8305_reset(uint8_t PHYADDER)
{
	uint16_t reg_data;
	reg_data = SMI_read(PHYADDER, 0);
	reg_data |= (1<<15);
	SMI_write(PHYADDER, 0, reg_data);
	do                                       
	{
		reg_data = SMI_read(PHYADDER, 0);	
	}while(reg_data & (1<<15));         //检查是否复位结束
}

void RTL8305_Set()
{
    uint8_t DataBuff[2];
	uint16_t reg_data;
	if(inbuf1[1]==2)
	     Set_RTL8305_Speed(inbuf1[2],inbuf1[3]);
	else if(inbuf1[1]==3)
	     Set_RTL8305_Duplex(inbuf1[2],inbuf1[3]);
	else if(inbuf1[1]==4) 
	     Set_RTL8305_Auto(inbuf1[2],inbuf1[3]);
	else  Set_RTL8305_reset(inbuf1[2]);
	
    reg_data=SMI_read(inbuf1[2],0);
    DataBuff[1]=reg_data;
    DataBuff[0]=reg_data>>8;
   // send_string(DataBuff,2);
}

void init_serialcomm( void ) 
{ 
SCON = 0x50 ; //SCON: serail mode 1, 8-bit UART, enable ucvr 
TMOD = 0x20 ; // TMOD: timer 1, mode 2, 8-bit reload 
PCON = 0x80 ; // SMOD=1; 
TH1 = 0xFD ; // Baud:19200 fosc=11.0592MHz 
TL1 = 0xFD ;
IE = 0x90 ; // Enable Serial Interrupt 
TR1 = 1 ; //  timer 1 run 
// TI=1; 
} 

// 向串口发送一个字符 
void send_char( uint8_t ch) 
{ 
SBUF=ch; 
while (TI== 0 ); 
TI= 0 ; 
} 

// 向串口发送一个字符串，strlen为该字符串长度 
void send_string( uint8_t *str, uint16_t strlen) 
{ 
uint16_t k= 0 ; 
do 
{ 
send_char(*(str + k)); 
k++; 
} while (k < strlen); 
} 


//串口接收中断函数 
void serial () interrupt 4 using 3 
{ 
//if (RI&!send_over)
if (RI)
{ 
uint8_t ch; 
RI = 0 ; 
ch=SBUF; 
inbuf1[INBUF_LEN]=ch;
//send_char( inbuf1[INBUF_LEN]);
if(inbuf1[0]==0x55)INBUF_LEN++;
else INBUF_LEN=0;
if (INBUF_LEN==6)
{
  INBUF_LEN=0;
  
  if(inbuf1[1]==1)
  {
    read_flag= 1 ;
	send_over=1;
  }
  else write_flag= 1;

}

} 
} 



main() 
{ 
	init_serialcomm( ) ;
	//IniIP113F();
	while(1){

		if(read_flag)
		{ 
			uint16_t reg_data;
			uint8_t DataBuff[2];
			reg_data=SMI_read(inbuf1[2],inbuf1[3]);
			DataBuff[1]=reg_data;
			DataBuff[0]=reg_data>>8;
			send_char(0xaa);
			send_string(DataBuff,2); 
			delay(100);
			read_flag= 0 ; //取数标志清0
			send_over=0;
		} 
		if(write_flag)
		{
			uint16_t reg_data;
			uint8_t DataBuff[2];
			reg_data=inbuf1[5];
			reg_data|=(inbuf1[4]<<8);

			SMI_write(inbuf1[2],inbuf1[3],reg_data);
			reg_data=SMI_read(inbuf1[2],inbuf1[3]);
			DataBuff[1]=reg_data;
			DataBuff[0]=reg_data>>8;
			send_char(0xbb);
			send_string(DataBuff,2); 
			write_flag=0;
		}
	}

}

#endif


#endif

