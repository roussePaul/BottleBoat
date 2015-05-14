#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Simulation.h"


void initSimulation()
{
    BoatModele_initialize();
}

ExtU_BoatModele_T getU(double t, void (*commande)(void*,double*,double),void* param)
{
    ExtU_BoatModele_T u;
    int i;
    for(i=0;i<8;i++)
        u.X_0[i] = 0;
    double c[2];
    commande(param,c,t);
    u.U[0] = c[0];
    u.U[1] = 0;
    u.U[2] = 0;
    u.U[3] = c[1];

    return u;
}

void olSimulation(double t)
{
    double currentTime = *(BoatModele_M->Timing.t);
    
    while( *(BoatModele_M->Timing.t) - currentTime < t )
        BoatModele_step();
}

void clSimulation(double t_f, void (*commande)(void*,double*,double),void* param)
{
    double currentTime = *(BoatModele_M->Timing.t);
    double t;

    while( *(BoatModele_M->Timing.t) - currentTime < t_f )
    {
        t = *(BoatModele_M->Timing.t);
        BoatModele_U = getU(t,commande,param);
        BoatModele_step();
	
        //printf("u = %lf %lf x = %lf %lf, t = %lf\n",BoatModele_U.U[0],BoatModele_U.U[3],BoatModele_Y.X[0],BoatModele_Y.X[1],t);
        
    }
}

ExtY_BoatModele_T* olPredict(double t)
{
    ExtY_BoatModele_T *prediction;
    prediction = malloc(sizeof(ExtY_BoatModele_T));
    
    
    olSimulation(t);
    
    *prediction = BoatModele_Y;
    
    return prediction;
}

FullStateBackup saveState()
{
    FullStateBackup backup;

    backup.x = BoatModele_X;
    backup.y = BoatModele_Y;
    backup.u = BoatModele_U;
    return backup;
}

void restoreState(FullStateBackup backup)
{
    BoatModele_X = backup.x;
    BoatModele_U = backup.u;
    BoatModele_Y = backup.y;
}


ExtY_BoatModele_T clPredict(double t, void (*commande)(void*,double*,double),void* param)
{
    ExtY_BoatModele_T prediction;

    // Backup saving    
    FullStateBackup backup;
    backup = saveState();

    // Saving
    clSimulation(t,commande,param);

    // Get final state
    prediction = BoatModele_Y;

    // Restore
    restoreState(backup);

    
    return prediction;
}

void terminateSimulation()
{
    BoatModele_terminate();
}

/*
int main(int argc, char **argv)
{
    initSimulation();
    ExtY_BoatModele_T *prediction = NULL;
    prediction = olPredict(100);
    printf("%lf %lf\n",prediction->X[0],prediction->X[1]);
    terminateSimulation();

    return 0;
}
*/
