
 
#include "mcc_generated_files/mcc.h"
#include "golden_eagle_i2c.h"
#include "uart_top.h"



uint8_t timeOut = 0;


int GE_I2C2_HexWrite(uint16_t RegAddr, uint16_t RegValue)
{
   
   unsigned char dataValue[]= {0x00,0x00};
   unsigned char dataAddr[]= {0x00,0x00};

   dataAddr[0]=((RegAddr>>8)&0xff);
   dataAddr[1]=(RegAddr);
   dataValue[0]=((RegValue>>8)&0xff);
   dataValue[1]=(RegValue);
    
   if(GE_I2C2_ByteWrite(&dataAddr,&dataValue,sizeof(dataAddr)))  
       return 1;
   else  
       return 0;
}
uint16_t GE_I2C2_HexRead(uint16_t RegAddr)
{
   uint16_t RegValue;
    
   unsigned char dataValue[]= {0x00,0x00};
   unsigned char dataAddr[]= {0x00,0x00};

   dataAddr[0]=((RegAddr>>8)&0xff);
   dataAddr[1]=(RegAddr);

    
   GE_I2C2_ByteRead(&dataAddr,&dataValue,sizeof(dataAddr));
  
   	RegValue = dataValue[0]<<8;
    RegValue = RegValue+dataValue[1];
    return RegValue;
}

int GE_I2C2_ByteHLWrite(uint8_t RegAddrH,uint8_t RegAddrL,uint8_t RegValueH, uint8_t RegValueL)
{
   
   unsigned char dataValue[]= {0x00,0x00};
   unsigned char dataAddr[]= {0x00,0x00};

   dataAddr[0]=RegAddrH;
   dataAddr[1]=RegAddrL;
   dataValue[0]=RegValueH;
   dataValue[1]=RegValueL;
    
   if(GE_I2C2_ByteWrite(&dataAddr,&dataValue,sizeof(dataAddr)))  
       return 1;
   else  
       return 0;
}
uint16_t GE_I2C2_ByteHLRead(uint8_t RegAddrH,uint8_t RegAddrL)
{
   uint16_t RegValue;
    
   unsigned char dataValue[]= {0x00,0x00};
   unsigned char dataAddr[]= {0x00,0x00};

   dataAddr[0]=RegAddrH;
   dataAddr[1]=RegAddrL;
    
   GE_I2C2_ByteRead(&dataAddr,&dataValue,sizeof(dataAddr));
  
   	RegValue = dataValue[0]<<8;
    RegValue = RegValue+dataValue[1];
    return RegValue;
}


int GE_I2C2_ByteWrite(uint8_t *dataAddress, uint8_t *data2Byte, uint8_t addlen)
{
   uint8_t writeBuffer[PAGE_LIMIT+3];
   uint8_t buflen;
  
   //Copy address bytes to the write buffer so it can be sent first 
    for(int i = 0; i < addlen; i++)
    {
        writeBuffer[i] = dataAddress[i];
    }
    
   //Check if this is an address write or a data write.
   //if(data2Byte[0] != NULL)
   
   {
       writeBuffer[addlen] = data2Byte[0];
       writeBuffer[addlen+1] = data2Byte[1];
       buflen = addlen+2; 
#if 1       
       #if MY_PRINTF_EN == 1
       uart_send_char("Wr ");
       uart_send_hex(dataAddress[0]);
       uart_send_hex(dataAddress[1]);
       uart_send_char(" ");
       uart_send_hex(data2Byte[0]);
       uart_send_hex(data2Byte[1]);
       uart_send_byte('\r'); uart_send_byte('\n');
       #endif
#else

#if MY_PRINTF_EN == 1	//yj20170414
//		uart_send_char("Wr ");
		uart_send_char("0x");
		uart_send_hex(dataAddress[0]);
		uart_send_char(",");
		uart_send_char("0x");
		uart_send_hex(dataAddress[1]);
		uart_send_char(",");
		uart_send_char("0x");
		uart_send_hex(data2Byte[0]);
		uart_send_char(",");
		uart_send_char("0x");
		uart_send_hex(data2Byte[1]);
		uart_send_byte('\r'); uart_send_byte('\n');
#endif
#endif
     }        
    
   //else
      // buflen = addlen;
   
    //set status to Message Pending to send the data
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
    
    //This variable is the built in acknowledge polling mechanism. This counts how many retries the system has already done to send the data.
    timeOut = 0;
    
    //While the message has not failed...
    while(status != I2C2_MESSAGE_FAIL)
    {
        // Initiate a write to EEPROM
            I2C2_MasterWrite(writeBuffer,buflen,SLAVE_ADDRESS,&status);

        // wait for the message to be sent or status has changed.
            while(status == I2C2_MESSAGE_PENDING);
       // if transfer is complete, break the loop
            if (status == I2C2_MESSAGE_COMPLETE)
                break;
                // if transfer fails, break the loop
            if (status == I2C2_MESSAGE_FAIL)
                break;
        //Max retry is set for max Ack polling. If the Acknowledge bit is not set, this will just loop again until the write command is acknowledged
            if (timeOut == MAX_RETRY)
                break;
            else
                timeOut++;
    }
    
                // if the transfer failed, stop at this point
                if (status == I2C2_MESSAGE_FAIL)
                return 1;
}

int GE_I2C2_AddrWrite(uint8_t *dataAddress, uint8_t addlen)
{
   uint8_t writeBuffer[PAGE_LIMIT+3];
   uint8_t buflen;
  
   //Copy address bytes to the write buffer so it can be sent first 
    for(int i = 0; i < addlen; i++)
    {
        writeBuffer[i] = dataAddress[i];
    }
    
       buflen = addlen; //address only
   
    //set status to Message Pending to send the data
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
    
    //This variable is the built in acknowledge polling mechanism. This counts how many retries the system has already done to send the data.
    timeOut = 0;
    
    //While the message has not failed...
    while(status != I2C2_MESSAGE_FAIL)
    {
        // Initiate a write to EEPROM
            I2C2_MasterWrite(writeBuffer,buflen,SLAVE_ADDRESS,&status);

        // wait for the message to be sent or status has changed.
            while(status == I2C2_MESSAGE_PENDING);
       // if transfer is complete, break the loop
            if (status == I2C2_MESSAGE_COMPLETE)
                break;
                // if transfer fails, break the loop
            if (status == I2C2_MESSAGE_FAIL)
                break;
        //Max retry is set for max Ack polling. If the Acknowledge bit is not set, this will just loop again until the write command is acknowledged
            if (timeOut == MAX_RETRY)
                break;
            else
                timeOut++;
    }
    
                // if the transfer failed, stop at this point
                if (status == I2C2_MESSAGE_FAIL)
                return 1;
}

uint8_t GE_I2C2_ByteRead(uint8_t *dataAddress,uint8_t *data2Byte, uint8_t addlen)
{
    int check;
    
    //Write the address to the slave
    check = GE_I2C2_AddrWrite(dataAddress,addlen);
    
    //If not successful, return to function
    if(check == 1)
        return;
    
    //Get ready to send data
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
    //Set up for ACK polling
    timeOut = 0;
    
    //While the code has not detected message failure..
    while(status != I2C2_MESSAGE_FAIL)
    {      
        // Initiate a Read to EEPROM 
            I2C2_MasterRead(data2Byte,2,SLAVE_ADDRESS,&status);  //use data2Byte , not &data2Byte, why?
            
        // wait for the message to be sent or status has changed.
            while(status == I2C2_MESSAGE_PENDING);
            
        // if transfer is complete, break the loop
            if (status == I2C2_MESSAGE_COMPLETE)
                break;
            
        // if transfer fails, break the loop
            if (status == I2C2_MESSAGE_FAIL)
                break;
            
        // check for max retry and skip this byte
            if (timeOut == MAX_RETRY)
                break;
            else
                timeOut++;
    }
      #if MY_PRINTF_EN == 1		//yj20170414
       uart_send_char("Rd ");
       uart_send_hex(dataAddress[0]);
       uart_send_hex(dataAddress[1]);
       uart_send_char("==");
       uart_send_hex(data2Byte[0]);
       uart_send_hex(data2Byte[1]);
       uart_send_byte('\r'); uart_send_byte('\n');
       #endif
       return 1;
       
}

int GE_I2C2_BufferWrite(uint8_t *dataAddress, uint8_t *dataBuffer, uint8_t addlen, uint8_t buflen)
{
    uint8_t writeBuffer[PAGE_LIMIT+3];
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
    
    //Set Address as the bytes to be written first
    for(int i = 0; i < addlen; i++)
    {
        writeBuffer[i] = dataAddress[i];
    }
    
    //Ensure that the page limit is not breached so as to avoid overwriting other data
    if(buflen > PAGE_LIMIT)
        buflen = PAGE_LIMIT;
    
    //Copy data bytes to write buffer
    for(int j = 0; j < buflen; j++)
    {
        writeBuffer[addlen+j] = dataBuffer[j];
    }
    //Set up for ACK polling
    timeOut = 0;
    
    while(status != I2C2_MESSAGE_FAIL)
    {
        // Initiate a write to EEPROM
            I2C2_MasterWrite(writeBuffer,buflen+addlen,SLAVE_ADDRESS,&status);

        // wait for the message to be sent or status has changed.
            while(status == I2C2_MESSAGE_PENDING);
       // if transfer is complete, break the loop
            if (status == I2C2_MESSAGE_COMPLETE)
                break;
                // if transfer fails, break the loop
            if (status == I2C2_MESSAGE_FAIL)
                break;

        //check for max retry and skip this byte
            if (timeOut == MAX_RETRY)
                break;
            else
                timeOut++;
    }
                // if the transfer failed, stop at this point
                if (status == I2C2_MESSAGE_FAIL)
                return 1;

}
void GE_I2C2_BufferRead(uint8_t *dataAddress, uint8_t *dataBuffer, uint8_t addlen,uint8_t buflen)
{
    int check = 0;
    I2C2_MESSAGE_STATUS status = I2C2_MESSAGE_PENDING;
    
    //Write Address from where to read
    check = GE_I2C2_ByteWrite(dataAddress,NULL,addlen);
    
    //check if address write is successful
    if(check == 1)
        return;
   
    //Set up for ACK polling
    timeOut = 0;
    
    while(status != I2C2_MESSAGE_FAIL){      
        // Initiate a Read to EEPROM 
        I2C2_MasterRead(dataBuffer,buflen,SLAVE_ADDRESS,&status);
            
        // wait for the message to be sent or status has changed.
        while(status == I2C2_MESSAGE_PENDING);
        
        // if transfer is complete, break the loop
        if (status == I2C2_MESSAGE_COMPLETE)
            break;
            
        // if transfer fails, break the loop
        if (status == I2C2_MESSAGE_FAIL)
                break;
            
        // check for max retry and skip this byte
        if (timeOut == MAX_RETRY)
            break;
        else
                timeOut++;
        } 
}



inline static T bitset(T value, T new_value, int lbit, int width)
{
    T mask = ((ONE<<width)-ONE);
    value &= ~(mask<<lbit);
    value |= (new_value & mask) << lbit;
    return value;
}

inline static void GE_I2C2_bitset(uint16_t addr, uint16_t new_value, int lbit, int width)
{
    uint16_t readout = GE_I2C2_HexRead(addr);
    readout = bitset(readout, new_value, lbit, width);
    GE_I2C2_HexWrite(addr, readout);
}


#if 1	
void GE_reload_default(void)
{
    int i=0;
   // GE_I2C2_HexWrite(0x980d,0x0777);
   // GE_I2C2_HexWrite(0x980d,0x0000);//Logic Reset
  // GE_I2C2_HexWrite(0x980d,0x0888);//Software Reset  ,will cause I2C repeat write because no ack
 
   
    GE_I2C2_HexWrite(0x9900,0x9dc0);
    GE_I2C2_HexWrite(0x9901,0x2104);
    GE_I2C2_HexWrite(0x9902,0x8F10);   
    GE_I2C2_HexWrite(0x9815,0x0000);
    GE_I2C2_bitset(0x6002,0x1,15,1);
    GE_I2C2_bitset(0x7000,0x0,1,1);
  
GE_I2C2_bitset(0x7000,0x0,1,1);
GE_I2C2_bitset(0x7400,0x0,1,1);
GE_I2C2_bitset(0x80a3,0x0,6,1);
GE_I2C2_bitset(0x84a3,0x0,6,1);
GE_I2C2_bitset(0x6012,0x1,15,1);
GE_I2C2_bitset(0x7100,0x0,1,1);
GE_I2C2_bitset(0x7500,0x0,1,1);
GE_I2C2_bitset(0x81a3,0x0,6,1);
GE_I2C2_bitset(0x85a3,0x0,6,1);
GE_I2C2_bitset(0x6022,0x1,15,1);
GE_I2C2_bitset(0x7200,0x0,1,1);
GE_I2C2_bitset(0x7600,0x0,1,1);
GE_I2C2_bitset(0x82a3,0x0,6,1);
GE_I2C2_bitset(0x86a3,0x0,6,1);
GE_I2C2_bitset(0x6032,0x1,15,1);
GE_I2C2_bitset(0x7300,0x0,1,1);
GE_I2C2_bitset(0x7700,0x0,1,1);
GE_I2C2_bitset(0x83a3,0x0,6,1);
GE_I2C2_bitset(0x87a3,0x0,6,1);

for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8079+i*0x0100,0x1,11,1);
    }
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8063+i*0x0100,0x1,7,1);
    }
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8064+i*0x0100,0x1,15,1);	
    GE_I2C2_bitset(0x8064+i*0x0100,0x1,7,1);
    }
for(i=0;i<8;i++) {
    GE_I2C2_HexWrite(0x8076+i*0x0100,0x0084);
    }
for(i=0;i<8;i++) {
    GE_I2C2_HexWrite(0x8077+i*0x0100,0x1882);
    }
for(i=0;i<4;i++) {
    GE_I2C2_HexWrite(0x8078+i*0x0100,0x8c3c);  //agc of a side
    }
for(i=4;i<8;i++) {
    GE_I2C2_HexWrite(0x8078+i*0x0100,0x8c38); //agc of b side
    }

for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8002+i*0x0100,0x04,12,4);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8000+i*0x0100,0x0D05,0,14);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8007+i*0x0100,0x0D7A,0,14);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8083+i*0x0100,0x0E05,0,14);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8084+i*0x0100,0x0F7A,0,14);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8085+i*0x0100,0x0F05,0,14);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8086+i*0x0100,0x0F05,0,14);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8087+i*0x0100,0x0d0a,0,14);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8088+i*0x0100,0x0d75,0,14);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x804d+i*0x0100,0x00,0,11);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x804e+i*0x0100,0x00,0,11);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8081+i*0x0100,0x00,0,11);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8082+i*0x0100,0x00,0,11);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8075+i*0x0100,0x06,8,6);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8079+i*0x0100,0x06,8,6);
}
for(i=0;i<8;i++) {
    GE_I2C2_bitset(0x8079+i*0x0100,0x1,15,1);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8079+i*0x0100,0x1,15,1);
}
for(i=0;i<8;i++) {
GE_I2C2_HexWrite(0x80FE+i*0x0100,0x29A8);
}
for(i=0;i<8;i++) {
GE_I2C2_HexWrite(0x80FD+i*0x0100,0x3244);
}
for(i=0;i<8;i++) {
GE_I2C2_HexWrite(0x80FC+i*0x0100,0x5236);
}
for(i=0;i<8;i++) {
GE_I2C2_HexWrite(0x80F8+i*0x0100,0xB778);
}
for(i=0;i<8;i++) {
GE_I2C2_HexWrite(0x80F5+i*0x0100,0x61E0);
}
for(i=0;i<8;i++) {
GE_I2C2_HexWrite(0x80F1+i*0x0100,0x7000);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x80F9+i*0x0100,0x2D,1,6);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8003+i*0x0100,0x0,9,1);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8050+i*0x0100,0x040,0,12);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8005+i*0x0100,0xA,12,4);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8001+i*0x0100,0x0,15,1);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8003+i*0x0100,0x2,12,4);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8006+i*0x0100,0xA,12,4);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8008+i*0x0100,0xA,8,4);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x80A0+i*0x0100,0x1,7,1);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8061+i*0x0100,0x0,8,1);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8082+i*0x0100,0xD,12,4);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8079+i*0x0100,0x50,0,6);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x80FE+i*0x0100,0x4,4,3);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8008+i*0x0100,0x5,12,4);
}
for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8087+i*0x0100,0x3,14,2);
}

    GE_I2C2_HexWrite(0x980d,0x0777);
    GE_I2C2_HexWrite(0x980d,0x0000);//Logic Reset
}
#endif


void GE_PRBS31_test(void)
{
    uint16_t i;
    
    for(i=0;i<8;i++) {
GE_I2C2_bitset(0x80A0+i*0x0100,0x7,13,3);  //set prbs31 = 111
GE_I2C2_bitset(0x80A0+i*0x0100,0x5,13,3);  //set prbs31 =101
GE_I2C2_bitset(0x80A0+i*0x0100,0x7,13,3);  //set prbs31 =111
GE_I2C2_bitset(0x80A0+i*0x0100,0x3,8,2);  //11
GE_I2C2_bitset(0x80A0+i*0x0100,0x1,11,1);  //01
}   
   for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8081+i*0x0100,0x1,11,1);  //set 8x81[11]  =1
GE_I2C2_bitset(0x8081+i*0x0100,0x0,11,1);  //set 8x81[11]  =0
}
   for(i=0;i<8;i++) {
GE_I2C2_bitset(0x8061+i*0x0100,0x1,15,1); //set 8x61[15]  =1
GE_I2C2_bitset(0x8061+i*0x0100,0x0,15,1); //set 8x61[15]  =1
}
    
    
}


int32_t get_int32(const unsigned char* data)
{
    uint32_t result = 0;
    int i;
    for (i=0; i<4; i++) {
        result<<=8; 
        result |= data[i];
    }
    return result;
}

uint16_t get_int16(const unsigned char* data)
{
    uint16_t result = 0;
    int i;
    for (i=0; i<2; i++) {
        result<<=8;
        result |= data[i];
    }
    return result;
}


void GE_set_polarity(void)
{
       //Cable side   6m awg30 cable
	GE_I2C2_bitset(0x8461,0x1,14,1); //BR0

    //GE_I2C2_bitset(0x8561,0x1,14,1); //BR1
    //GE_I2C2_bitset(0x8661,0x1,14,1);  //BR2 
    //GE_I2C2_bitset(0x8761,0x1,14,1);  //BR3
    
   //Cable side  2m awg30 cable
   //GE_I2C2_bitset(0x8561,0x1,14,1); //BR1
   //GE_I2C2_bitset(0x8761,0x1,14,1);  //BR2
   
   //Gold Finger
    //GE_I2C2_bitset(0x8061,0x1,14,1);  //AR0
    //GE_I2C2_bitset(0x8161,0x1,14,1);  //AR1
    //GE_I2C2_bitset(0x8261,0x1,14,1);  //AR2
   //
    
}


void GE_state_reset(void)
{
    uint16_t i;
    
	for(i=0;i<8;i++) {
		GE_I2C2_bitset(0x80A1+i*0x0100,0x1,11,1);  //  0x8x8a[11]->1
		GE_I2C2_bitset(0x80A1+i*0x0100,0x0,11,1);  //  0x8x8a[11]->0
	}     
}

void GE_abRs_reset(void)
{
    uint16_t i;
    
	for(i=0;i<8;i++) {
		GE_I2C2_bitset(0x8081+i*0x0100,0x1,11,1);  //  0x8x81[11]->1
		__delay_ms(10);
		GE_I2C2_bitset(0x8081+i*0x0100,0x0,11,1);  //  0x8x81[11]->0
		__delay_ms(10);
	}
}
