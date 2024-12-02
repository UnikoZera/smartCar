#include <REGX52.H>
#include <intrins.h>

sbit IN1F = P2^0;
sbit IN2F = P2^1;
sbit IN3F = P2^2;
sbit IN4F = P2^3;
sbit IN1B = P2^4;
sbit IN2B = P2^5;
sbit IN3B = P2^6;
sbit IN4B = P2^7;

#define PWM_PERIOD 64
unsigned char dutyCycle1 = 32; //Left
unsigned char dutyCycle2 = 32; //Right
unsigned char States = 0;
unsigned char specialStates = 0;
unsigned char Fliping = 0; //1 means enable, 0 means disable

void Timer0_Init(void)
{
    TMOD |= 0x01;
    TH0 = 0xFF;
    TL0 = 0x00; 
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void Timer1_Init(void)
{
    TMOD |= 0x10;
    TH1 = 0xFF;
    TL1 = 0x00; 
    ET1 = 1;
    TR1 = 1;
}

void Timer0_ISR(void) interrupt 1
{
    static unsigned char pwmCounter1 = 0;
    TH0 = 0xFF;
    TL0 = 0x00;

    pwmCounter1++;
    if (pwmCounter1 >= PWM_PERIOD)
    {
        pwmCounter1 = 0;
    }

    if (pwmCounter1 < dutyCycle1 && (States != 3 && States != 4 && specialStates == 0))
    {
        if (Fliping == 1 && States == 2)
        {
            IN1F = 1;
            IN2F = 0;
            IN1B = 0;
            IN2B = 1;
        }
        else
        {
            IN1F = 0;
            IN2F = 1;
            IN1B = 1;
            IN2B = 0;
        }
    }
    else if (pwmCounter1 >= dutyCycle1 && (States != 3 && States != 4 && specialStates == 0))
    {
        IN1F = 0;
        IN2F = 0;
        IN1B = 0;
        IN2B = 0;
    }
}

void Timer1_ISR(void) interrupt 3
{
    static unsigned char pwmCounter2 = 0;
    TH1 = 0xFF;
    TL1 = 0x00;

    pwmCounter2++;
    if (pwmCounter2 >= PWM_PERIOD)
    {
        pwmCounter2 = 0;
    }

    if (pwmCounter2 < dutyCycle2 && (States != 3 && States != 4 && specialStates == 0))
    {
        if (Fliping == 1 && States == 1)
        {
            IN3F = 0;
            IN4F = 1;
            IN3B = 0;
            IN4B = 1;
        }
        else
        {
            IN3F = 1;
            IN4F = 0;
            IN3B = 1;
            IN4B = 0;
        }
    }
    else if (pwmCounter2 >= dutyCycle2 && (States != 3 && States != 4 && specialStates == 0))
    {
        IN3F = 0;
        IN4F = 0;
        IN3B = 0;
        IN4B = 0;
    }
}

void carMoveForward(short int level)
{
    States = 0;
    specialStates = 0;
    if (level == 1)
    {
        dutyCycle1 = 16;
        dutyCycle2 = 16;
    }
    else if (level == 2)
    {
        dutyCycle1 = 32;
        dutyCycle2 = 32;
    }
    else if (level == 3)
    {
        dutyCycle1 = 63;
        dutyCycle2 = 63;
    }
}

void carTurnRight(short int level)
{
    specialStates = 0;
	States = 1;
    if (level == 1)
    {
        Fliping = 0;
        dutyCycle1 = 48;
        dutyCycle2 = 32;
    }
    else if (level == 2)
    {
        Fliping = 1;
        dutyCycle1 = 48;
        dutyCycle2 = 32;
    }
    else if (level == 3)
    {
        Fliping = 1;
        dutyCycle1 = 48;
        dutyCycle2 = 48;
    }
}

void carTurnLeft(short int level)
{
    specialStates = 0;
    States = 2;
    if (level == 1)
    {
        Fliping = 0;
        dutyCycle1 = 32;
        dutyCycle2 = 48;
    }
    else if (level == 2)
    {
        Fliping = 1;
        dutyCycle1 = 32;
        dutyCycle2 = 48;
    }
    else if (level == 3)
    {
        Fliping = 1;
        dutyCycle1 = 48;
        dutyCycle2 = 48;
    }
}

void carStop()
{
    specialStates = 0;
    States = 3;
    IN1F = 0;
    IN2F = 0;
    IN3F = 0;
    IN4F = 0;
    IN1B = 0;
    IN2B = 0;
    IN3B = 0;
    IN4B = 0;
}

void carMoveBackward()
{
    specialStates = 1;
	IN1F = 1;
	IN2F = 0;
	IN3F = 0;
	IN4F = 1;

    IN1B = 0;
    IN2B = 1;
    IN3B = 0;
    IN4B = 1;
}

void carSharpRight()
{
    specialStates = 1;
	IN1F = 0;
	IN2F = 1;
	IN3F = 0;
	IN4F = 1;

    IN1B = 1;
    IN2B = 0;
    IN3B = 0;
    IN4B = 1;
}

void carSharpLeft()
{
    specialStates = 1;
	IN1F = 1;
	IN2F = 0;
	IN3F = 1;
	IN4F = 0;

    IN1B = 0;
    IN2B = 1;
    IN3B = 1;
    IN4B = 0;
}