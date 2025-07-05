#include <REGX51.H>

//--Servo PWM---
unsigned int dutytime_Servo=55536; //65536 - 45536 = 20000
unsigned int ton_Servo=10000; 
unsigned int toff_Servo=10000; 
unsigned int temp_Servo; //當頻率過高時，要用temp優化，避免值算錯誤

void Timer0_Init(void)
{
    EA = 1; ET0 = 1;

    TMOD=0x01; 

		TH0 = (65536 - dutytime_Servo) / 256;
		TL0 = (65536 - dutytime_Servo) % 256;

    TR0=1;
}

void timer0_isr(void) interrupt 1{
		TR0 = 0;
		
		if(P2_0==1){
				temp_Servo = (65536-toff_Servo); 
			
				TH0= temp_Servo / 256;
				TL0= temp_Servo % 256;

				P2_0=0;
		}
		else{
				temp_Servo = (65536-ton_Servo);
			
				TH0=temp_Servo / 256;
				TL0=temp_Servo % 256;

				P2_0=1;
		}
		
		TR0 = 1;
}