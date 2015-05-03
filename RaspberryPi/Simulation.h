#ifndef SIMULATION_H
#define SIMULATION_H

#include <math.h>
#include "Modele/BoatModele.h"
#include "Commande.h"

struct FullStateBackup{
	X_BoatModele_T x;
	ExtU_BoatModele_T u;
	ExtY_BoatModele_T y;
};
typedef struct FullStateBackup FullStateBackup;

void initSimulation();
void olSimulation(double t);
void clSimulation(double t, void (*commande)(void*,double*,double),void* param);
ExtY_BoatModele_T* olPredict(double t);
ExtY_BoatModele_T clPredict(double t, void (*commande)(void*,double*,double),void* param);

void terminateSimulation();

#endif