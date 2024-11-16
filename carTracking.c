#include <REGX52.H>
#include <intrins.h>
#include "carMovement.h"

sbit Left_0 =   P1^4;
sbit Left_1 =   P1^5;
sbit Left_2 =   P1^6;
sbit Middle_0 = P1^7; 
sbit Middle_1 = P0^4; 
sbit Right_0 =  P0^5;
sbit Right_1 =  P0^6;
sbit Right_2 =  P0^7;

unsigned char valueState = 0;
unsigned char previousStates = 0;

//黑线是1，白线是0
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
    if ((Left_0 == 1 || Left_1 == 1 || Left_2 == 1 || Middle_0 == 1) && (Right_0 == 0 && Right_1 == 0 && Right_2 == 0 && Middle_1 == 0))
    {
        if (Left_0 == 1)
        {
            carSharpLeft();
        }
        else if (Left_1 == 1)
        {
            Fliping = 1;
            carTurnLeft(3);
        }
        else if (Left_2 == 1)
        {
            Fliping = 0;
            carTurnLeft(2);
        }
        else if (Middle_0 == 1)
        {
            Fliping = 0;
            carTurnLeft(1);
        }
    }
    //右边检查到黑线，但是左边是nil
    else if ( (Left_0 == 0 && Left_1 == 0 && Left_2 == 0 && Middle_0 == 0) && (Right_0 == 1 || Right_1 == 1 || Right_2 == 1 || Middle_1 == 1))
    {
        if (Right_0 == 1)
        {
            carSharpRight();
        }
        else if (Right_1 == 1)
        {
            Fliping = 0;
            carTurnRight(2);
        }
        else if (Right_2 == 1)
        {
            Fliping = 1;
            carTurnRight(3);
        }
        else if (Middle_1 == 1)
        {
            Fliping = 0;
            carTurnRight(1);
        }
    }
    else if ((Left_0 == 1 && Left_1 == 1 && Left_2 == 1 && Middle_0 == 1 && Middle_1 == 1 && Right_0 == 1 && Right_1 == 1 && Right_2 == 1) || (Middle_0 == 1 && Middle_1 == 1) || (Middle_0 == 1 && Middle_1 == 1 && Left_2 == 1 && Right_0 == 1) || (Middle_0 == 1 && Middle_1 == 1 && Left_2 == 1 && Left_1 == 1 && Right_0 == 1 && Right_2 == 1))
    { 
        carMoveForward(1); //暴力直走
    }
    else if ((Left_0 == 0 && Left_1 == 0 && Left_2 == 0 && Middle_0 == 0 && Middle_1 == 0 && Right_0 == 0 && Right_1 == 0 && Right_2 == 0))
    {
        ChangeState(); //sb小车冲出赛道了 用函数调整一下
    }
    else
    {
        //什么情况？我也不知道要干什么 你自己看着办吧
    }
    

    if (valueState != States)   /*记忆上一次的状态*/
    {
        previousStates = valueState;
        valueState = States;
    }
}