#include <REGX52.H>
#include <intrins.h>
#include "carMovement.h"

sbit Left_0 =   P0^4;
sbit Left_1 =   P0^5;
sbit Middle_0 = P0^3; 
sbit Middle_1 = P0^2; 
sbit Right_0 =  P0^1;
sbit Right_1 =  P0^0;

unsigned char valueState = 0;
unsigned char previousStates = 0;
unsigned char Crossroads = 0;
unsigned char CanCounter = 1;

//黑线是1，白线是0
void Delay100us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 43;
	while (--i);
}

void Delay6000ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void ChangeState() //调整小车冲出赛道的状态
{
    carStop();
    if (previousStates == 0)
    {
        carMoveBackward();
    }
    else if (previousStates == 1)
    {
        carSharpRight();
    }
    else if (previousStates == 2)
    {
        carSharpLeft();
    }
}

void Tracking()
{
    if (valueState != States)
    {
        previousStates = valueState;
        valueState = States;
    }
    //左边检查到黑线，但是右边nil
    if ((Left_0 == 1 || Left_1 == 1 || Middle_0 == 1) && (Right_0 == 0 && Middle_1 == 0 && Right_1 == 0))
    {
        if (Left_0 == 1)
        {
            carTurnLeft(3);
        }
        else if (Left_1 == 1)
        {
            carTurnLeft(2);
        }
        else if (Middle_0 == 1)
        {
            carTurnLeft(1);
        }
    }
    //右边检查到黑线，但是左边是nil
    else if ((Left_0 == 0 && Left_1 == 0 && Middle_0 == 0) && (Right_0 == 1|| Middle_1 == 1 || Right_1 == 1))
    {
        if (Right_1 == 1)
        {
           carTurnRight(3);
        }
        if (Right_0 == 1)
        {
            carTurnRight(2);
        }
        else if (Middle_1 == 1)
        {
            carTurnRight(1);
        }
    }
    else if ((Left_0 == 1 && Left_1 == 1 && Middle_0 == 1 && Middle_1 == 1 && Right_0 == 1 && Right_1 == 1) || (Middle_0 == 1 && Middle_1 == 1) || (Middle_0 == 1 && Middle_1 == 1 && Right_0 == 1 && Left_0 == 1))
    { 
        carMoveForward(2); //暴力直走
    }
    else if ((Left_0 == 0 && Left_1 == 0 && Middle_0 == 0 && Middle_1 == 0 && Right_0 == 0 && Right_1 == 0))
    {
        ChangeState();
    }
    else
    {
        carStop();
    }

    if (valueState != States)
    {
        Delay100us();
    }
}

void CrossroadDetection()
{
    if (((Left_0 == 1 && Left_1 == 1 && Middle_0 == 1 && Middle_1 == 1 && Right_0 == 1 && Right_1 == 1) || (Left_1 == 1 && Middle_0 == 1 && Middle_1 == 1 && Right_0 == 1)) && CanCounter == 1)
    {
        Crossroads += 1;
        CanCounter = 0;
    }

    if (CanCounter == 0)
    {
        Delay6000ms();
        CanCounter == 1;
    }
}