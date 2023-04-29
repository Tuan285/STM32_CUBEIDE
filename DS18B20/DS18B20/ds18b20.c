#include "ds18b20.h"
/*******************************************************************************
Noi Dung      :   Ham doc du lieu tu DS18B20
Tham Bien     :   Khong
Tra Ve        :   Gia tri doc duoc
*******************************************************************************/
float ds18b20_read(void)
{
 uint8_t busy=0, temp1, temp2;
 uint16_t temp3,TimeOut;
 float result;
 OneWire_Reset();
 OneWire_Write(0xCC);
 OneWire_Write(0x44);
 while ((busy==0)&&TimeOut<2000)
 {
		busy = OneWire_Read();
 }
 OneWire_Reset();
 OneWire_Write(0xCC);
 OneWire_Write(0xBE);
 temp1 = OneWire_Read();
 temp2 = OneWire_Read();
 temp3 = temp2;
 temp3<<=8;
 temp3|=temp1;
 result = (float) temp3 / 16.0;
 Delay_ms(200);
 return(result);
}  
 
