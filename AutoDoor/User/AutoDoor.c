#include <REGX51.H>
#include "DS18B20.h"
#include "Delay.h"
#include "INT.h"
#include "Timer0_Servo.h"
#include "LCD1602.h"
#include "Uart.h"

#define LED P0
#define BUZZER P3_4

float T;

void main()
{
		DS18B20_ConvertT();
		delay(60000);
	
		INT_Init();
		Timer0_Init();
		UART_Init();

		initial();
		dis_p(1,1);
		WriteString("TEMP:");
		dis_p(2,9);
		WriteString("Right V");
		dis_p(2,1);
		WriteString("Left V");
		
		while(1)
		{
			UART_Transmit(ton_Servo >> 8);   // 傳送高位
			UART_Transmit(ton_Servo & 0xFF); // 傳送低位
			
			DS18B20_ConvertT();
			T = DS18B20_ReadT();
			WriteFloat(T,1,7);
			
			if(flag1 == 0 && flag2 == 0)     //呼吸窗模式
			{
					// 20~24度 對應 1200~2200 ton_Servo
					ton_Servo = 250*(T-8)-3800;
					// 傳送伺服角度高位與低位
					
					delay(50000); // 角度更新間隔
			}
			else												    //警報模式
			{
					ton_Servo = 2200; //警報時全開
				
					//警示燈+蜂鳴聲
					LED = 0x0f;
					BUZZER = 1;
					delay(5000);												
					LED = 0xf0;
					BUZZER = 0;
					delay(5000);
					
					if(flag1 == 1)
					{
							dis_p(2,9);
							WriteString("Right X");
					}
					if(flag2 == 1)
					{
							dis_p(2,1);
							WriteString("Left X");
					}
			}
		}//end while
}
