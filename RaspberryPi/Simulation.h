#ifndef H_SIMULATION
#define H_SIMULATION

#include <math.h>
#include "Modele/BoatModele.h"

void initSimulation();
void simulateDuring(double t);
ExtY_BoatModele_T* Predict(double t);
void terminateSimulation();

#endif