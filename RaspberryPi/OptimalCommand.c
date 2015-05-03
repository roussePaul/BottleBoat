#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>



#include "Modele/BoatModele.h"
#include "Simulation.h"
#include "Commande.h"

#include <gsl/gsl_multimin.h>


double cout(const gsl_vector * _x, void * _params)
{

  double t_f = 40;
  int N=5;
  int dim = 2;
  int i;

  Commande *commande = NULL;
  commande = newStepCommande(t_f, N, dim);
  StepParam *params = (StepParam*)commande->params;

  for(i=0;i<N*dim;i++)
    params->coeff[i] = gsl_vector_get(_x,i);

  // for(i=0;i<N*dim;i++)
  //   printf("%lf ",gsl_vector_get(_x,i));
  // printf("\n");

  initSimulation();

  ExtY_BoatModele_T predict = clPredict(t_f, commande->commande,commande->params);

  double u = predict.X[0];
  double v = predict.X[1];

  terminateSimulation();

  return -sqrt(u*u+v*v);
}


int main()
{

    gsl_vector *x,*ss;
    gsl_multimin_function minex_func;
    
    x = gsl_vector_alloc (10);
    
    gsl_multimin_fminimizer *s;
    const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex2;
    s = gsl_multimin_fminimizer_alloc (T, 10);
    
    
    
    // Starting point 
    x = gsl_vector_alloc (10);
    gsl_vector_set_all (x, 0.0);

    // Initialize method and iterate 
    minex_func.n = 10;
    minex_func.f = &cout;
    minex_func.params = NULL;


    // Set initial step sizes to 1 
    ss = gsl_vector_alloc (10);
    gsl_vector_set_all (ss, 1.0);


    gsl_multimin_fminimizer_set (s, &minex_func, x, ss);

    int iter,status;
    double size;
    iter=0;
    do
    {
      iter++;
      printf("iteration...");
      status = gsl_multimin_fminimizer_iterate(s);
      
      if (status) 
        break;

      size = gsl_multimin_fminimizer_size (s);
      status = gsl_multimin_test_size (size, 1e-8);

      if (status == GSL_SUCCESS)
        {
          printf ("converged to minimum at\n");
        }

      printf ("%5d f(%lf) = %7.8f size = %.1e\n", iter,gsl_vector_get(s->x,0),s->fval, size);
              
        fflush(stdout);
    }
  while (status == GSL_CONTINUE && iter < 500);
  
  int i;
  for(i=0;i<10;i++)
    printf("%lf ",gsl_vector_get(s->x,i));
  printf("\n");

  gsl_vector_free(x);
  gsl_vector_free(ss);
  gsl_multimin_fminimizer_free (s);
  
    return 0;
}

