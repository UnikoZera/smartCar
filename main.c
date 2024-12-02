#include <REGX52.H>
#include <intrins.h>
#include "carMovement.h"
#include "carTracking.h"

void main()
{
	Timer0_Init();
	Timer1_Init();
	while(1)
	{
		CrossroadDetection();
		Tracking();
		// carStop();
	}
}