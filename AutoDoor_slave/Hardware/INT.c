#include <REGX51.H>


bit flag1 = 0;
bit flag2 = 0;

void INT_Init(void)
{
		EA  = 1;
		EX0 = 1;IT0 = 1;
		EX1 = 1;IT1 = 1;
		IP  = 0x10;
		P3_2 = 1;//當輸入時拉成高態
		P3_3 = 1;//當輸入時拉成高態
}

void int0(void) interrupt 0{
		flag1 = 1;
}

void int1(void) interrupt 2{
		flag2 = 1;
}