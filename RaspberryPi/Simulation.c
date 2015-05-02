#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Simulation.h"


void initSimulation()
{
    BoatModele_initialize();
}



void simulateDuring(double t)
{
    double currentTime = *(BoatModele_M->Timing.t);
    
    while( *(BoatModele_M->Timing.t) - currentTime < t )
        BoatModele_step();
}

ExtY_BoatModele_T* Predict(double t)
{
    ExtY_BoatModele_T *prediction;
    prediction = malloc(sizeof(ExtY_BoatModele_T));
    
    
    simulateDuring(t);
    
    *prediction = BoatModele_Y;
    
    return prediction;
}

void terminateSimulation()
{
    BoatModele_terminate();
}

void main(int argc, char **argv)
{
    initSimulation();
    ExtY_BoatModele_T *prediction = NULL;
    prediction = Predict(100);
    printf("%lf %lf\n",prediction->Out1[0],prediction->Out1[1]);
    terminateSimulation();
}