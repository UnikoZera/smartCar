#include <REGX52.H>
#include <intrins.h>
#include "carMovement.h"
#include "carTracking.h"
unsigned char value = 0;

void Delay300ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 3;
	j = 26;
	k = 223;
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
	Delay300ms();
	Timer0_Init();
	Timer1_Init();
	while(1)
	{
		CrossroadDetection();
		// if (Crossroads >= 7)
		// {
		// 	carStop();
		// }
		// else
		// {
		// 	Tracking();
		// }

		if (Period > 192000)
		{
			if (value != Period)
			carStop();
		}
		else if (Period == 192000)
		{
			value = Crossroads;
		}
		else
		{
			Tracking();
		}
	}
}