#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Commande.h"

void stepCommande(void *params, double *u, double t)
{
	StepParam* p;
	p = (StepParam*)params;

	double h = p->t_f/p->N;

	int n = floor(t/h);
	int i;

	for(i=0;i<p->dim;i++)
	{
		u[i] = p->coeff[n*p->dim+i];
	}
	
	// if(t<n*h+0.01)
	// {
	// 	for(i=0;i<p->dim;i++)
	// 	{
	// 		printf("%lf ",u[i]);
	// 	}
	// 	printf("%lf %lf\n",n*h,t);
	// }
}

Commande *newStepCommande(double t_f, int N, int dim)
{
	Commande *commande = NULL;
	commande = malloc(sizeof(Commande));

	StepParam *params = NULL;
	params = malloc(sizeof(StepParam));
	params->t_f = t_f;
	params->N = N;
	params->dim = dim;
	params->coeff = malloc(sizeof(double)*N*dim);
	commande->params = (void*)params;
	commande->commande = stepCommande;
	return commande;
}

