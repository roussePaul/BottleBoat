#include "Commande.h"
#include "Trajectoire.h"
#include <math.h>

#define KP kp
#define KV kv

double kp,kv;

void setCoeffs(double _kp, double _kv)
{
    kp = _kp;
    kv = _kv;
}

double getWCommande(double x, double y, double thetam, double v)
{
    
    double t0, y0,theta0,c0,g0;
    
    t0 = findNearest(x,y);
    
    y0 = -getSignedDistance(t0,x,y);
    c0 = getCourbure(t0);
    g0 = getDerivCourbure(t0);
    theta0 = getAngle(t0);
    
	double theta = thetam - theta0;


	double w0 = v*cos(theta) / (1.0 - c0*y0);
    double signeW0 = (w0>0)?1.0:-1.0;
	double w1 = y0*(g0*sin(theta) - KP*cos(theta))* cos(theta) / (1.0 - c0*y0);
	double w2 = sin(theta) * ( c0*sin(theta) - KV*cos(theta)*signeW0 );
	double w3 = c0;

    //printf("%lf %lf %lf %lf %lf\n",t0, y0,c0,g0,theta0);

    //printf("%lf %lf %lf %lf\n", w0,w1,w2,w3);

	double w = w0*(w1 + w2 + w3);
    
    return w;
}
    