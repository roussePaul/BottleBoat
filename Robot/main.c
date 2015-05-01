#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


//#define DISABLE_PLOT

#include "Simulation.h"
#include "Commande.h"
#include "Trajectoire.h"

#include "webPlot/webplot.h"

#include <gsl/gsl_multimin.h>


double distAvr(const gsl_vector * _x, void * params)
{
    double distavr=0;
    
    double kp,kv;
    kp = gsl_vector_get(_x,0);
    kv = gsl_vector_get(_x,1);
    
    
    setCoeffs(kp,kv);
    
    
    initSimulation();
    Robot0_P.thetam0_Value = getAngle(0.0);
    
    Robot0_U.v_ref = 1.0;
        
    double x,y,t,w,d;
    do{
        x = Robot0_Y.x;
        y = Robot0_Y.y;
        
        t = findNearest(x, y);
        
        d = getSignedDistance(t, x, y);
        w = getWCommande(x, y, Robot0_Y.thetam, Robot0_Y.v);
        
        Robot0_U.w_ref = w;
        
        simulateDuring(0.01);
        
        PLOT("traj","%lf %lf", Robot0_Y.x, Robot0_Y.y);
        PLOT("dist","%lf %lf", *(Robot0_M->Timing.t), d);
        PLOT("rot","%lf %lf", *(Robot0_M->Timing.t), w);
        PLOT("t","%lf %lf", *(Robot0_M->Timing.t), t);
        
        distavr = (fabs(d)<distavr)?distavr:fabs(d);
        
    }while(*(Robot0_M->Timing.t)<100.0 && t!=1.0);
    
    terminateSimulation();
    
    return distavr;
    
}

int main()
{
    
    CLEARPLOT("traj");
    CLEARPLOT("dist");
    CLEARPLOT("commande");
    CLEARPLOT("rot");
    CLEARPLOT("t");
    
    gsl_vector *ss, *x;
    gsl_multimin_function minex_func;
    
    x = gsl_vector_alloc (2);
    gsl_vector_set (x, 0, 42.6);
    gsl_vector_set (x, 1,  74);
    
    plotTrajectoire("commande");
    
    printf("Distance moyenne: %lf\n", distAvr(x,NULL));
    gsl_vector_set (x, 0, 30.0);
    gsl_vector_set (x, 1, 10.0);
    
    printf("Distance moyenne: %lf\n", distAvr(x,NULL));
    return 0;

    
    gsl_multimin_fminimizer *s;
    const gsl_multimin_fminimizer_type *T = gsl_multimin_fminimizer_nmsimplex2;
    s = gsl_multimin_fminimizer_alloc (T, 2);
    
    
    
    /* Starting point */
    x = gsl_vector_alloc (2);
    gsl_vector_set (x, 0, 30.0);
    gsl_vector_set (x, 1, 10.0);
    
    
    /* Set initial step sizes to 1 */
    ss = gsl_vector_alloc (2);
    gsl_vector_set_all (ss, 1.0);

    /* Initialize method and iterate */
    minex_func.n = 2;
    minex_func.f = &distAvr;
    minex_func.params = NULL;

    gsl_multimin_fminimizer_set (s, &minex_func, x, ss);

    int iter,status;
    double size;
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

      printf ("%5d %10.3f %10.3f f() = %7.8f size = %.1e\n", 
              iter,
              gsl_vector_get (s->x, 0), 
              gsl_vector_get (s->x, 1), 
              s->fval, size);
              
        fflush(stdout);
    }
  while (status == GSL_CONTINUE && iter < 500);
  
  gsl_vector_free(x);
  gsl_vector_free(ss);
  gsl_multimin_fminimizer_free (s);
  
    return 0;
}
