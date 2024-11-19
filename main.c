#include <REGX52.H>
#include <intrins.h>
#include "carMovement.h"
#include "carTracking.h"

sbit det = P3^5;
sbit out = P2^4;

void Delay1000ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
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
	Timer0_Init();
	Timer1_Init();
	while(1)
	{
		carStop();
		if (det == 1)
		{
			out = 1;
		}
		else
		{
			// Tracking();
			out = 0;
		}
	}		
}