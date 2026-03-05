#include <REGX52.H>
#include <intrins.h>
#include "carMovement.h"
#include "carTracking.h"
unsigned char preCrossroads = 0;
unsigned char running = 1;

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
		// if (Crossroads >= 7) //? 如果检测到的十字路口数量大于等于7，认为车已经进入了十字路口，那么就停车，否则继续跟踪但是被时间窗口替代了
		// {
		// 	carStop();
		// }
		// else
		// {
		// 	Tracking();
		// }

		if (Period > (192000 - 1000) && Period < (192000 + 1000))
		{
			if (preCrossroads != Crossroads)
			{
				carStop();
				running = 0;
			}
			if (running)
			{
				Tracking();
			}
		}
		else
		{
			Tracking();
		}
		preCrossroads = Crossroads;
	}
}