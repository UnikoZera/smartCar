#include <REGX52.H>
#include <intrins.h>
#include "carMovement.h"
#include "carTracking.h"

sbit a = P1^0;
sbit b = P1^1;

void main()
{
	Timer0_Init();
	Timer1_Init();
	while(1)
	{
		// carStop();
		Tracking();

		// if (a==0)
		// {
		// 	b = 0;
		// else
		// {
		// 	b = 1;
		// }
	}
}