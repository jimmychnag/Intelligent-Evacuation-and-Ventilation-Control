#include <REGX51.H>

//---ds18b20 OneWire-----
sbit OneWire_DQ = P3^7;


//ds18b20初始化為先拉高再拉低後，延遲480微秒後，再釋放
unsigned char OneWire_Init(void)
{
		unsigned char i;
		unsigned char AckBit;
		OneWire_DQ = 1;
		OneWire_DQ = 0;
		
		i = 247; while(--i); //delay 500us(480us)
	
		OneWire_DQ = 1;
	
		i = 32; while(--i); // delay 70us(60~240us)
		
		AckBit = OneWire_DQ;
	
		i = 247; while(--i); //delay 500us(480us)
	
		return AckBit;
}

void OneWire_SendBit(unsigned char Bit)
{
		unsigned char i;

		OneWire_DQ = 0;
		i = 4; while(--i);  // 10u
		OneWire_DQ = Bit;
		i = 24; while(--i); // 50u
		OneWire_DQ = 1;
}

unsigned char OneWire_ReceiveBit(void)
{
		unsigned char Bit;
		unsigned char i;

		OneWire_DQ = 0;
		i = 2; while(--i);  // 5u
		OneWire_DQ = 1;
		i = 2; while(--i);  // 5u
		Bit = OneWire_DQ;
		i = 24; while(--i); // 50u

		return Bit;
}

void OneWire_SendByte(unsigned char Byte)
{
		unsigned char i;
	  for(i = 0 ; i < 8 ; i ++)
		{
				OneWire_SendBit(Byte & (0x01 << i));//低位先行
		}
}

unsigned char OneWire_ReceiveByte(void)
{
		unsigned char i;
		unsigned char Byte = 0x00;
	  for(i = 0 ; i < 8 ; i ++)
		{
				if(OneWire_ReceiveBit())
				{
						Byte |= 0x01 << i;
				}
		}
		return Byte;
}