#include <REGX51.H>
#include "I2C_8051.h"
#include "Delay.h"

#define SLAVE 0x4E //0x27 << 1

void WriteInst4bits(unsigned char inst_4b)
{
		start();
		send_8bits(SLAVE);  
		ack_receive();
		send_8bits(0x0C);         //EN=1 RW=0 RS=0
		ack_receive();
		send_8bits((inst_4b&0xF0)+0x0C); //??D7-D4
		ack_receive();
		send_8bits(0x08); //EN=0 ?????
		ack_receive();
		stop();
}

void WriteInst(unsigned char inst)
{ 
		start();
		send_8bits(SLAVE);  
		ack_receive();
		send_8bits(0x0C);         //EN=1 RW=0 RS=1
		ack_receive();
		send_8bits((inst&0xF0)+0x0C);   //???
		ack_receive();
		send_8bits(0x08);   //EN=0 ????
		ack_receive();

		send_8bits(0x0C);         //EN=1
		ack_receive();
		send_8bits((inst<<4)+0x0C);    //???
		ack_receive();
		send_8bits(0x08);    //EN=0 ????
		ack_receive();
		stop();
} 

void WriteData(unsigned char data_)
{
		start();
		send_8bits(SLAVE);  
		ack_receive();
	
		send_8bits(0x0D);         //EN=1 RW=0 RS=1
		ack_receive();
		send_8bits((data_&0xF0)+0x0D);  
		ack_receive();
		send_8bits(0x09);  
		ack_receive();
	
		send_8bits(0x0D);         //EN=1 RW=0 RS=1
		ack_receive();
		send_8bits((data_<<4)+0x0D);   
		ack_receive();
		send_8bits(0x09);   
		ack_receive();
		
		stop();
} 

void WriteString(unsigned char* string)
{
		while(*string )
		{
			WriteData(*string);
			string++;
		}
}

void initial(void)
{
		delay(15000);

		WriteInst4bits(0x30); 
		delay(4100);

		WriteInst4bits(0x30); 
		delay(100);

		WriteInst4bits(0x30); 
		delay(100);

		WriteInst4bits(0x20); 

		WriteInst(0x28); 
		WriteInst(0x08); 
		WriteInst(0x01); 
		WriteInst(0x06); 
		WriteInst(0x0E); 
		WriteInst(0x0C);  
}

void CG_RAM_write(unsigned char* ptr)
{
    WriteInst(0x40);
		while(*ptr)
		{
				WriteData(*ptr++);
		}
}

void dis_p(char row,column)
{
		char change_p;
		row--;column--;
		change_p = 0x80 + (row*0x40 + column);
		WriteInst(change_p);
}
void WriteNum(unsigned char Num)
{
		WriteData(Num + '0');
}

void WriteFloat(float T,unsigned char row,unsigned char column)
{
		unsigned char Temp_H[3];
		unsigned char Temp_L[4];
		
		if(T<0)
		{
				dis_p(row,column);
				WriteString("-");
				T = -T;
		}
		else
		{
				dis_p(row,column);
				WriteString("+");
		}
		
		Temp_H[0] = (unsigned int)T / 100  % 10;
		Temp_H[1] = (unsigned int)T / 10 % 10;
		Temp_H[2] = (unsigned int)T / 1 % 10;
		dis_p(row,column+1);
		WriteData(Temp_H[0] + '0');
		dis_p(row,column+2);
		WriteData(Temp_H[1] + '0');
		dis_p(row,column+3);
		WriteData(Temp_H[2] + '0');
		dis_p(row,column+4);
		WriteString(".");
		Temp_L[0] = ( (unsigned long)(T*10000)%10000 ) /1000 %10;
		Temp_L[1] = ( (unsigned long)(T*10000)%10000 ) /100 %10;
		Temp_L[2] = ( (unsigned long)(T*10000)%10000 ) /10 %10;
		Temp_L[3] = ( (unsigned long)(T*10000)%10000 ) /1 %10;
		dis_p(row,column+5);
		WriteData(Temp_L[0] + '0');
		dis_p(row,column+6);
		WriteData(Temp_L[1] + '0');
		dis_p(row,column+7);
		WriteData(Temp_L[2] + '0');
		dis_p(row,column+8);
		WriteData(Temp_L[3] + '0');
}

