/*
 * BoatModele_types.h
 *
 * Code generation for model "BoatModele".
 *
 * Model version              : 1.11
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sat May  2 23:14:17 2015
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_BoatModele_types_h_
#define RTW_HEADER_BoatModele_types_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"

/* Custom Type definition for MATLAB Function: '<S1>/MATLAB Function1' */
#ifndef struct_srLgvkCzuuZn3rWrmrpDanB
#define struct_srLgvkCzuuZn3rWrmrpDanB

struct srLgvkCzuuZn3rWrmrpDanB
{
  real_T m;
  real_T Ixx;
  real_T Izz;
  real_T Ixz;
  real_T a11;
  real_T a22;
  real_T a44;
  real_T a66;
  real_T a24;
  real_T a26;
  real_T a46;
  real_T vt;
  real_T alpha_w;
  real_T rho_a;
  real_T As;
  real_T h0;
  real_T h1;
  real_T z_s;
  real_T xs;
  real_T ys;
  real_T zs;
  real_T Xce;
  real_T Xm;
  real_T rho_w;
  real_T Ar;
  real_T d_r;
  real_T zeta_r;
  real_T x_r;
  real_T z_r;
  real_T xr;
  real_T yr;
  real_T zr;
  real_T Ak;
  real_T d_k;
  real_T zeta_k;
  real_T x_k;
  real_T z_k;
  real_T xk;
  real_T yk;
  real_T zk;
  real_T x_h;
  real_T z_h;
  real_T xh;
  real_T yh;
  real_T zh;
  real_T w_c;
  real_T x_c;
  real_T y_bm;
  real_T a;
  real_T b;
  real_T c;
  real_T d;
};

#endif                                 /*struct_srLgvkCzuuZn3rWrmrpDanB*/

#ifndef typedef_srLgvkCzuuZn3rWrmrpDanB_BoatM_T
#define typedef_srLgvkCzuuZn3rWrmrpDanB_BoatM_T

typedef struct srLgvkCzuuZn3rWrmrpDanB srLgvkCzuuZn3rWrmrpDanB_BoatM_T;

#endif                                 /*typedef_srLgvkCzuuZn3rWrmrpDanB_BoatM_T*/

/* Parameters (auto storage) */
typedef struct P_BoatModele_T_ P_BoatModele_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_BoatModele_T RT_MODEL_BoatModele_T;

#endif                                 /* RTW_HEADER_BoatModele_types_h_ */
