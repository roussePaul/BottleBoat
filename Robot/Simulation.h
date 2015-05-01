#ifndef H_SIMULATION
#define H_SIMULATION

#include "Modele/Robot0.h"

void initSimulation();
void simulateDuring(double t);
ExtY_Robot0_T* Predict(double t);
void terminateSimulation();

#endif