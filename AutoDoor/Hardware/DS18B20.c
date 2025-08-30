#include <REGX51.H>
#include "OneWire.h"


void DS18B20_ConvertT(void)
{
		OneWire_Init();
		OneWire_SendByte(0xCC);
		OneWire_SendByte(0x44);

}

float DS18B20_ReadT(void)
{
		unsigned char TLSB,TMSB;
		int Temp;
		float T;
		OneWire_Init();
		OneWire_SendByte(0xCC);
		OneWire_SendByte(0xBE);
		TLSB = OneWire_ReceiveByte();
		TMSB = OneWire_ReceiveByte();
		Temp = (TMSB<<8) | TLSB;
		T = Temp / 16.0;//第4bit開始才是整數部分
		return T;
}

