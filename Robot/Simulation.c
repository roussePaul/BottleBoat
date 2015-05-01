#include "stdio.h"
#include "stdlib.h"

#include "Simulation.h"


void initSimulation()
{
    Robot0_initialize();
}



void simulateDuring(double t)
{
    double currentTime = *(Robot0_M->Timing.t);
    
    while( *(Robot0_M->Timing.t) - currentTime < t )
        Robot0_step();
}

ExtY_Robot0_T* Predict(double t)
{
    ExtY_Robot0_T *prediction;
    prediction = malloc(sizeof(ExtY_Robot0_T));
    
    X_Robot0_T currentState;
    ExtU_Robot0_T currentInput;
    ExtY_Robot0_T currentOutput;
    
    currentState = Robot0_X;
    currentInput = Robot0_U;
    currentOutput = Robot0_Y;
    
    simulateDuring(t);
    
    *prediction = Robot0_Y;
    
    Robot0_X = currentState;
    Robot0_U = currentInput;
    Robot0_Y = currentOutput;
    
    
    return prediction;
}

void terminateSimulation()
{
    Robot0_terminate();
}