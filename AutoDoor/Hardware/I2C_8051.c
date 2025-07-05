#include <REGX51.H>
#include "Delay.h"

sbit scl = P1^7;
sbit sda = P1^6;

void scl_w(bit value)
{
		if(value == 0)
		{
			scl = 0;
			delay(5);
		}
		else
		{
			scl = 1;
			delay(5);
		}
}

void sda_w(bit value)
{
		if(value == 0)
		{
			sda = 0;
			delay(5);
		}
		else
		{
			sda = 1;
			delay(5);
		}
}

bit sda_r(void)
{
		bit value;
	  value = sda;
		delay(5);
		return value;
}

void start()
{
		scl_w(1);
		sda_w(1);
		sda_w(0);
		scl_w(0);
}

void send_8bits(unsigned char value)
{
		unsigned char i ;
		for(i = 0 ; i < 8 ; i++)
		{
			sda_w( !!( value & (0x80 >> i) ));
			scl_w(1);
			scl_w(0);
		}
}

bit ack_receive(void)
{
		bit value;

		sda_w(1);
		
		scl_w(1);
		value = sda_r();
		scl_w(0);
		return value;
}

void ack_send(void)
{
		scl_w(0);
		sda_w(0);
		scl_w(1);
		scl_w(0);
}

void stop(void)
{
		sda_w(0);
		scl_w(1);
		sda_w(1);
}