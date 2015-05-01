#ifndef H_TRAJECTOIRE
#define H_TRAJECTOIRE


void getTrajectoirePoint(double t, double *x, double *y);
double functionToMinimize(double t, void* params);
double findNearest(double x, double y);

double dx(double t, void* params);


double getCourbure(double t);
double getDerivCourbure(double t);
double getAngle(double t);
double getDistance(double t, double x, double y);
double getSignedDistance(double t, double x, double y);

void plotTrajectoire(char* titre);

#endif // H_TRAJECTOIRE
