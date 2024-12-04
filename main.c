#include <REGX52.H>
#include <intrins.h>
#include "carMovement.h"
#include "carTracking.h"

sbit LED = P1^0; //Light up the LED when the car stops LMAO!!!
unsigned char canDash = 1; //dash for windows

void Delay500ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	Delay500ms();
	Timer0_Init();
	Timer1_Init();
	while(1)
	{
		CrossroadDetection();
		if (Crossroads >= 6)
		{
			carStop();
			LED = 1; //light up the LED!!!
		}
		else
		{
			Tracking();
			LED = 0;
		}
	}
}