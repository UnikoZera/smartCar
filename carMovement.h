#ifndef __CARMOVEMENT_H__
#define __CARMOVEMENT_H__
    void carMoveForward(short int level);
    void carTurnRight(short int level);
    void carTurnLeft(short int level);
    void carStop();
    void carMoveBackward();
    void carSharpRight();
    void carSharpLeft();
    void Timer0_Init();
    void Timer1_Init();
    extern char States;
    extern char Fliping;
#endif