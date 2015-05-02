/*
 * DOF_sf.h
 *
 * Code generation for model "DOF_sf".
 *
 * Model version              : 1.935
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sat May  2 12:55:28 2015
 *
 * Target selection: rtwsfcn.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#ifndef RTW_HEADER_DOF_sf_h_
#define RTW_HEADER_DOF_sf_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef DOF_sf_COMMON_INCLUDES_
# define DOF_sf_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME                DOF_sf
#define S_FUNCTION_LEVEL               2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if !defined(MATLAB_MEX_FILE)
#include "rt_matrx.h"
#endif

#if !defined(RTW_SFUNCTION_DEFINES)
#define RTW_SFUNCTION_DEFINES

typedef struct {
  void *blockIO;
  void *defaultParam;
  void *nonContDerivSig;
} LocalS;

#define ssSetLocalBlockIO(S, io)       ((LocalS *)ssGetUserData(S))->blockIO = ((void *)(io))
#define ssGetLocalBlockIO(S)           ((LocalS *)ssGetUserData(S))->blockIO
#define ssSetLocalDefaultParam(S, paramVector) ((LocalS *)ssGetUserData(S))->defaultParam = (paramVector)
#define ssGetLocalDefaultParam(S)      ((LocalS *)ssGetUserData(S))->defaultParam
#define ssSetLocalNonContDerivSig(S, pSig) ((LocalS *)ssGetUserData(S))->nonContDerivSig = (pSig)
#define ssGetLocalNonContDerivSig(S)   ((LocalS *)ssGetUserData(S))->nonContDerivSig
#endif
#endif                                 /* DOF_sf_COMMON_INCLUDES_ */

#include "DOF_sf_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rtGetInf.h"

/* Block signals (auto storage) */
typedef struct {
  real_T X_dot_ext[9];                 /* '<S1>/MATLAB Function' */
} B_DOF_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[8];         /* '<S1>/Integrator' */
} X_DOF_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[8];         /* '<S1>/Integrator' */
} XDot_DOF_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[8];      /* '<S1>/Integrator' */
} XDis_DOF_T;

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: alphacoeff_yldata
   * Referenced by: '<S1>/1-D Lookup Table'
   */
  real_T DLookupTable_tab[100000];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/1-D Lookup Table'
   *   '<S1>/1-D Lookup Table1'
   *   '<S1>/1-D Lookup Table2'
   *   '<S1>/1-D Lookup Table4'
   *   '<S1>/1-D Lookup Table5'
   *   '<S1>/1-D Lookup Table6'
   */
  real_T pooled1[100000];

  /* Expression: alphacoeff_yddata
   * Referenced by: '<S1>/1-D Lookup Table4'
   */
  real_T DLookupTable4_ta[100000];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/1-D Lookup Table1'
   *   '<S1>/1-D Lookup Table2'
   */
  real_T pooled2[100000];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S1>/1-D Lookup Table5'
   *   '<S1>/1-D Lookup Table6'
   */
  real_T pooled3[100000];

  /* Expression: hull_ydata
   * Referenced by: '<S1>/1-D Lookup Table3'
   */
  real_T DLookupTable3_ta[100000];

  /* Expression: hull_xdata
   * Referenced by: '<S1>/1-D Lookup Table3'
   */
  real_T DLookupTable3_bp[100000];
} ConstP_DOF_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T *X0[8];                       /* '<Root>/X(0)' */
  real_T *U[3];                        /* '<Root>/U' */
} ExternalUPtrs_DOF_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T *X[8];                        /* '<Root>/X' */
  real_T *delta_s;                     /* '<Root>/delta_s' */
} ExtY_DOF_T;

/* Constant parameters (auto storage) */
extern const ConstP_DOF_T DOF_ConstP;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('SailingYachtModel2/4DOF nonlinear sailing yacht model')    - opens subsystem SailingYachtModel2/4DOF nonlinear sailing yacht model
 * hilite_system('SailingYachtModel2/4DOF nonlinear sailing yacht model/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SailingYachtModel2'
 * '<S1>'   : 'SailingYachtModel2/4DOF nonlinear sailing yacht model'
 * '<S2>'   : 'SailingYachtModel2/4DOF nonlinear sailing yacht model/MATLAB Function'
 * '<S3>'   : 'SailingYachtModel2/4DOF nonlinear sailing yacht model/MATLAB Function1'
 * '<S4>'   : 'SailingYachtModel2/4DOF nonlinear sailing yacht model/MATLAB Function2'
 * '<S5>'   : 'SailingYachtModel2/4DOF nonlinear sailing yacht model/MATLAB Function3'
 * '<S6>'   : 'SailingYachtModel2/4DOF nonlinear sailing yacht model/MATLAB Function4'
 */
#endif                                 /* RTW_HEADER_DOF_sf_h_ */
