#include <REGX51.H>
#include "DS18B20.h"
#include "Delay.h"
#include "INT.h"
#include "Timer0_Servo.h"
#include "LCD1602.h"
#include "Uart.h"

#define LED P0
#define BUZZER P3_4

unsigned char HighData;
unsigned char LowData;
char i = 0;
void main()
{
		Timer0_Init();
		UART_Init();
		
		while(1)
		{
			//P0 = UART_Receive();
			if(i == 0)
			{
				HighData = UART_Receive();
				i++;
				P0 = 0xf0;
			}
			else if(i == 1)
			{
				LowData = UART_Receive();
				i++;
				P0 = 0x0f;
			}
			else
			{
				ton_Servo = ( HighData << 8 ) | LowData;
				i = 0;
			}
			
		}//end while
}
