#include <REGX52.H>
#include <intrins.h>
#include "carMovement.h"

sbit Left_0 =   P3^7;
sbit Left_1 =   P3^6;
sbit Middle_0 = P3^5; 
sbit Middle_1 = P1^2; 
sbit Right_0 =  P1^1;
sbit Right_1 =  P1^0;

unsigned char valueState = 0;
unsigned char previousStates = 0;

//黑线是0，白线是1
void ChangeState() //调整小车冲出赛道的状态
{
    if (previousStates == 0)
    {
        carMoveBackward();
    }
    else if (previousStates == 1)
    {
        carSharpRight(); //我不确定SharpRight是不是有点太sharp了
    }
    else if (previousStates == 2)
    {
        carSharpLeft();
    }
}

void Tracking()
{
    //左边检查到黑线，但是右边nil
    if ((Left_0 == 0 || Left_1 == 0 || Middle_0 == 0) && (Right_0 == 1 && Right_1 == 1 && Middle_1 == 1))
    {
        if (Left_0 == 0)
        {
            carSharpLeft();
        }
        else if (Left_1 == 0)
        {
            carTurnLeft(2);
        }
        else if (Middle_0 == 0)
        {
            carTurnLeft(1);
        }
    }
    //右边检查到黑线，但是左边是nil
    else if ((Left_0 == 1 && Left_1 == 1 && Middle_0 == 1) && (Right_0 == 0 || Right_1 == 0 || Middle_1 == 0))
    {
        if (Right_1 == 0)
        {
            carSharpRight();
        }
        else if (Right_0 = 0)
        {
            carTurnRight(2);
        }
        else if (Middle_1 == 0)
        {
            carTurnRight(1);
        }
    }
    else if ((Left_0 == 0 && Left_1 == 0 && Middle_0 == 0 && Middle_1 == 0 && Right_0 == 0 && Right_1 == 0) || (Middle_0 == 0 && Middle_1 == 0) || (Middle_0 == 0 && Middle_1 == 0 && Right_0 == 0 && Left_0 == 0))
    { 
        carMoveForward(2); //暴力直走
    }
    else if ((Left_0 == 1 && Left_1 == 1 && Middle_0 == 1 && Middle_1 == 1 && Right_0 == 1 && Right_1 == 1))
    {
        ChangeState(); //sb小车冲出赛道了 用函数调整一下
    }
    else
    {
     
    }
    

    if (valueState != States)   /*记忆上一次的状态*/
    {
        previousStates = valueState;
        valueState = States;
    }
}