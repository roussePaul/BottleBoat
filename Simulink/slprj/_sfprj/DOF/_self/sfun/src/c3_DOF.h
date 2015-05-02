#ifndef __c3_DOF_h__
#define __c3_DOF_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
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

#ifndef typedef_c3_srLgvkCzuuZn3rWrmrpDanB
#define typedef_c3_srLgvkCzuuZn3rWrmrpDanB

typedef struct srLgvkCzuuZn3rWrmrpDanB c3_srLgvkCzuuZn3rWrmrpDanB;

#endif                                 /*typedef_c3_srLgvkCzuuZn3rWrmrpDanB*/

#ifndef typedef_SFc3_DOFInstanceStruct
#define typedef_SFc3_DOFInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  boolean_T c3_isStable;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_DOF;
} SFc3_DOFInstanceStruct;

#endif                                 /*typedef_SFc3_DOFInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_DOF_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_DOF_get_check_sum(mxArray *plhs[]);
extern void c3_DOF_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
