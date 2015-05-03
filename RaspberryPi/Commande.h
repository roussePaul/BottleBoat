#ifndef COMMANDE_H
#define COMMANDE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Modele/BoatModele.h"

struct Commande{
	void (*commande)(void *, double*,double);
	void* params;
};

typedef struct Commande Commande;

struct StepParam{
	double t_f;
	int N;
	int dim;
	double* coeff;
};
typedef struct StepParam StepParam;

void stepCommande(void *params, double *u, double t);
Commande *newStepCommande(double t_f, int N, int dim);


#endif