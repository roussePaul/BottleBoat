/*
 * DOF_sf.c
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
#include <math.h>
#include "DOF_sf.h"
#include "DOF_sf_private.h"
#include "simstruc.h"
#include "fixedpoint.h"
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

extern void *DOF_malloc(SimStruct *S);

#endif

#ifndef __RTW_UTFREE__
#if defined (MATLAB_MEX_FILE)

extern void * utMalloc(size_t);
extern void utFree(void *);

#endif
#endif                                 /* #ifndef __RTW_UTFREE__ */

/* Forward declaration for local functions */
static real_T DOF_rt_atan2d_snf(real_T u0, real_T u1);
static real_T DOF_rt_roundd_snf(real_T u);
static void DOF_mldivide(const real_T A[16], real_T B[4]);

#if defined(MATLAB_MEX_FILE)
#include "rt_nonfinite.c"
#endif

static const char_T *RT_MEMORY_ALLOCATION_ERROR =
  "memory allocation error in generated S-Function";
real_T DOF_look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex)
{
  real_T frac;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

static real_T DOF_rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

static real_T DOF_rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for MATLAB Function: '<S1>/MATLAB Function' */
static void DOF_mldivide(const real_T A[16], real_T B[4])
{
  real_T temp;
  real_T b_A[16];
  int8_T ipiv[4];
  int32_T j;
  int32_T c;
  int32_T ix;
  real_T s;
  int32_T jy;
  int32_T c_ix;
  int32_T d;
  int32_T ijA;
  int32_T b_kAcol;
  memcpy(&b_A[0], &A[0], sizeof(real_T) << 4U);
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  for (j = 0; j < 3; j++) {
    c = j * 5;
    jy = 0;
    ix = c;
    temp = fabs(b_A[c]);
    for (b_kAcol = 2; b_kAcol <= 4 - j; b_kAcol++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > temp) {
        jy = b_kAcol - 1;
        temp = s;
      }
    }

    if (b_A[c + jy] != 0.0) {
      if (jy != 0) {
        ipiv[j] = (int8_T)((j + jy) + 1);
        b_kAcol = j + jy;
        temp = b_A[j];
        b_A[j] = b_A[b_kAcol];
        b_A[b_kAcol] = temp;
        ix = j + 4;
        b_kAcol += 4;
        temp = b_A[ix];
        b_A[ix] = b_A[b_kAcol];
        b_A[b_kAcol] = temp;
        ix += 4;
        b_kAcol += 4;
        temp = b_A[ix];
        b_A[ix] = b_A[b_kAcol];
        b_A[b_kAcol] = temp;
        ix += 4;
        b_kAcol += 4;
        temp = b_A[ix];
        b_A[ix] = b_A[b_kAcol];
        b_A[b_kAcol] = temp;
      }

      ix = (c - j) + 4;
      for (b_kAcol = c + 1; b_kAcol + 1 <= ix; b_kAcol++) {
        b_A[b_kAcol] /= b_A[c];
      }
    }

    b_kAcol = c;
    jy = c + 4;
    for (ix = 1; ix <= 3 - j; ix++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0) {
        c_ix = c + 1;
        d = (b_kAcol - j) + 8;
        for (ijA = 5 + b_kAcol; ijA + 1 <= d; ijA++) {
          b_A[ijA] += b_A[c_ix] * -temp;
          c_ix++;
        }
      }

      jy += 4;
      b_kAcol += 4;
    }
  }

  if (ipiv[0] != 1) {
    temp = B[0];
    B[0] = B[ipiv[0] - 1];
    B[ipiv[0] - 1] = temp;
  }

  if (ipiv[1] != 2) {
    temp = B[1];
    B[1] = B[ipiv[1] - 1];
    B[ipiv[1] - 1] = temp;
  }

  if (ipiv[2] != 3) {
    temp = B[2];
    B[2] = B[ipiv[2] - 1];
    B[ipiv[2] - 1] = temp;
  }

  if (B[0] != 0.0) {
    for (jy = 1; jy + 1 < 5; jy++) {
      B[jy] -= B[0] * b_A[jy];
    }
  }

  if (B[1] != 0.0) {
    for (jy = 2; jy + 1 < 5; jy++) {
      B[jy] -= b_A[jy + 4] * B[1];
    }
  }

  if (B[2] != 0.0) {
    for (jy = 3; jy + 1 < 5; jy++) {
      B[jy] -= b_A[jy + 8] * B[2];
    }
  }

  if (B[3] != 0.0) {
    B[3] /= b_A[15];
    for (jy = 0; jy + 1 < 4; jy++) {
      B[jy] -= b_A[jy + 12] * B[3];
    }
  }

  if (B[2] != 0.0) {
    B[2] /= b_A[10];
    for (jy = 0; jy + 1 < 3; jy++) {
      B[jy] -= b_A[jy + 8] * B[2];
    }
  }

  if (B[1] != 0.0) {
    B[1] /= b_A[5];
    for (jy = 0; jy + 1 < 2; jy++) {
      B[jy] -= b_A[jy + 4] * B[1];
    }
  }

  if (B[0] != 0.0) {
    B[0] /= b_A[0];
  }
}

/* Initial conditions for root system: '<Root>' */
#define MDL_INITIALIZE_CONDITIONS

static void mdlInitializeConditions(SimStruct *S)
{
  B_DOF_T *_rtB;
  _rtB = ((B_DOF_T *) ssGetLocalBlockIO(S));

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  if (ssIsFirstInitCond(S)) {
    ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[0] = 0.0;
    ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[1] = 0.0;
    ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[2] = 0.0;
    ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[3] = 0.0;
    ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[4] = 0.0;
    ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[5] = 0.0;
    ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[6] = 0.0;
    ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[7] = 0.0;
  }

  ((int_T*) ssGetDWork(S, 0))[0] = 1;
}

/* Start for root system: '<Root>' */
#define MDL_START

static void mdlStart(SimStruct *S)
{
  /* instance underlying S-Function data */
#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#  if defined(MATLAB_MEX_FILE)

  /* non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* Check for invalid switching between solver types */
  if (ssIsVariableStepSolver(S)) {
    ssSetErrorStatus(S, "This Simulink Coder generated "
                     "S-Function cannot be used in a simulation with "
                     "a solver type of variable-step "
                     "because this S-Function was created from a model with "
                     "solver type of fixed-step and it has continuous time blocks. "
                     "See the Solver page of the simulation parameters dialog.");
    return;
  }

  if (fabs(ssGetFixedStepSize(S) - 0.05) > mxGetEps()*100*0.05) {
    ssSetErrorStatus(S, "This Simulink Coder generated "
                     "S-Function cannot be used in a simulation with "
                     "the current fixed step size "
                     "because this S-Function was created from a model with "
                     "a fixed step size of 0.05 and had both "
                     "continuous blocks and discrete blocks running at this rate. "
                     "See the Solver page of the simulation parameters dialog.");
    return;
  }

#  endif

  DOF_malloc(S);
  if (ssGetErrorStatus(S) != (NULL) ) {
    return;
  }

#endif

  {
  }
}

/* Outputs for root system: '<Root>' */
static void mdlOutputs(SimStruct *S, int_T tid)
{
  /* local block i/o variables */
  real_T rtb_Integrator[8];
  real_T alpha_aw;
  real_T delta_s;
  real_T alpha_as;
  real_T alpha_ak;
  real_T v_akv;
  real_T nu[4];
  real_T M[16];
  real_T Ls;
  real_T Ds;
  real_T alpha_ar;
  real_T Lr;
  real_T D_hull[4];
  real_T eta_dot[4];
  real_T nu_dot[4];
  real_T e[4];
  real_T rtb_TmpSignalConversionAtSFun_m[11];
  real_T rtb_DLookupTable;
  real_T rtb_DLookupTable4;
  real_T rtb_DLookupTable1;
  real_T rtb_DLookupTable2;
  real_T rtb_DLookupTable3;
  real_T rtb_DLookupTable5;
  real_T rtb_DLookupTable6;
  int32_T i;
  real_T M_0[16];
  real_T b[9];
  real_T tmp[9];
  real_T b_0[9];
  real_T b_1[3];
  int32_T tmp_0[16];
  int32_T tmp_1[16];
  real_T c[9];
  real_T tmp_2[9];
  int32_T i_0;
  real_T tmp_3[16];
  real_T tmp_4[16];
  real_T tmp_5[4];
  real_T tmp_6[4];
  real_T alpha_as_idx_1;
  B_DOF_T *_rtB;
  _rtB = ((B_DOF_T *) ssGetLocalBlockIO(S));
  if (ssIsContinuousTask(S, tid)) {
    /* Integrator: '<S1>/Integrator' incorporates:
     *  Inport: '<Root>/X(0)'
     */
    if (((int_T*) ssGetDWork(S, 0))[0]) {
      ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[0] = *((const real_T**)
        ssGetInputPortSignalPtrs(S, 0))[0];
      ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[1] = *((const real_T**)
        ssGetInputPortSignalPtrs(S, 0))[1];
      ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[2] = *((const real_T**)
        ssGetInputPortSignalPtrs(S, 0))[2];
      ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[3] = *((const real_T**)
        ssGetInputPortSignalPtrs(S, 0))[3];
      ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[4] = *((const real_T**)
        ssGetInputPortSignalPtrs(S, 0))[4];
      ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[5] = *((const real_T**)
        ssGetInputPortSignalPtrs(S, 0))[5];
      ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[6] = *((const real_T**)
        ssGetInputPortSignalPtrs(S, 0))[6];
      ((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[7] = *((const real_T**)
        ssGetInputPortSignalPtrs(S, 0))[7];
    }

    {
      int_T i1;
      real_T *y0 = &rtb_Integrator[0];
      real_T *xc = &((X_DOF_T *) ssGetContStates(S))->Integrator_CSTATE[0];
      for (i1=0; i1 < 8; i1++) {
        y0[i1] = xc[i1];
      }
    }

    /* SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport1' incorporates:
     *  Inport: '<Root>/U'
     *  MATLAB Function: '<S1>/MATLAB Function1'
     */
    rtb_TmpSignalConversionAtSFun_m[1] = *((const real_T **)
      ssGetInputPortSignalPtrs(S, 1))[1];
    for (i = 0; i < 8; i++) {
      /* Outport: '<Root>/X' */
      ((real_T *)ssGetOutputPortSignal(S, 0))[i] = rtb_Integrator[i];
      rtb_TmpSignalConversionAtSFun_m[i + 3] = rtb_Integrator[i];
    }

    /* End of SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport1' */

    /* MATLAB Function: '<S1>/MATLAB Function1' */
    /* MATLAB Function '4DOF nonlinear sailing yacht model/MATLAB Function1': '<S3>:1' */
    /*  interpreted Matlab function "f.m" for the Simulink file "SailingYachtModel.slx" */
    /*  This function describes the dynamics of a 4DOF sailing yacht model */
    /*  and gives the derivative of the state X and the sail angle delta_s. */
    /*  The input vector V_in contains the system state and the control input vector.  */
    /*  */
    /*  For the model description, notations, equations and parameters, */
    /*  see Xiao and Jouffroy, "Modeling and nonlinear heading control of sailing */
    /*  yachts", IEEE Journal of Oceanic Engineering, vol. 39, no. 2., pp. 256-268, 2014. */
    /*   */
    /*  Jerome Jouffroy, Jiaxi He and Lin Xiao, 2014. */
    /*  University of Southern Denmark. */
    /*  use the system parameters */
    /*  (kg),mass of the vehicle */
    /*  moment of inertia */
    /*  (kg),added mass coef. */
    /* '<S3>:1:31' */
    /*  the norm of wind velocity */
    /* '<S3>:1:32' */
    /*  the direction of wind (coming from the north, ie going south) */
    /*  (kg/m^3), air density */
    /*  (m^2), sail area */
    /* '<S3>:1:36' */
    /*  (m), roughness height */
    /* '<S3>:1:37' */
    /*  (m), reference height */
    /* '<S3>:1:38' */
    /*  (m), (x,y,z) is the CoE */
    /* '<S3>:1:39' */
    /* '<S3>:1:40' */
    /* '<S3>:1:41' */
    /*  (m), (x,y,z) is the CoE */
    /*  (m), distance along the mast to the CoE */
    /*  (m), x-coordinate of the mast  */
    /*  (kg/m^3), water density */
    /*  (m^2), rudder area */
    /*  rudder draft */
    /*  rudder efficiency */
    /*  (m), (x,y,z) is the CoE */
    /*  (m^2), keel area */
    /*  keel draft */
    /*  keel efficiency */
    /*  (m), (x,y,z) is the CoE */
    /*  (N), crew weight 20000 */
    /*  (m), crew position */
    /*  (m), yacht beam */
    /*  retrieve the system state from the field input vector "V_in" */
    /* '<S3>:1:86' */
    /* '<S3>:1:87' */
    /* '<S3>:1:88' */
    /* '<S3>:1:89' */
    /* '<S3>:1:90' */
    /* '<S3>:1:91' */
    /*  retrieve the input signals from the vector "V_in" */
    /* '<S3>:1:96' */
    /*  evaluate the matrix M and C in the model */
    /*  calculate the tau vector, ie forces and moments generated from: */
    /*  the sail */
    /* '<S3>:1:110' */
    /* '<S3>:1:111' */
    alpha_as = log(11.58 * cos(rtb_TmpSignalConversionAtSFun_m[5]) / 0.0005) /
      10.050181931686932;

    /* '<S3>:1:112' */
    /* '<S3>:1:113' */
    /* '<S3>:1:114' */
    /*  wind expressed in the body frame */
    /* '<S3>:1:115' */
    /* '<S3>:1:116' */
    b[0] = 1.0;
    b[3] = 0.0;
    b[6] = 0.0;
    b[1] = 0.0;
    b[4] = cos(-rtb_TmpSignalConversionAtSFun_m[5]);
    b[7] = -sin(-rtb_TmpSignalConversionAtSFun_m[5]);
    b[2] = 0.0;
    b[5] = sin(-rtb_TmpSignalConversionAtSFun_m[5]);
    b[8] = cos(-rtb_TmpSignalConversionAtSFun_m[5]);
    tmp[0] = cos(-rtb_TmpSignalConversionAtSFun_m[6]);
    tmp[3] = -sin(-rtb_TmpSignalConversionAtSFun_m[6]);
    tmp[6] = 0.0;
    tmp[1] = sin(-rtb_TmpSignalConversionAtSFun_m[6]);
    tmp[4] = cos(-rtb_TmpSignalConversionAtSFun_m[6]);
    tmp[7] = 0.0;
    tmp[2] = 0.0;
    tmp[5] = 0.0;
    tmp[8] = 1.0;
    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        b_0[i + 3 * i_0] = 0.0;
        b_0[i + 3 * i_0] += tmp[3 * i_0] * b[i];
        b_0[i + 3 * i_0] += tmp[3 * i_0 + 1] * b[i + 3];
        b_0[i + 3 * i_0] += tmp[3 * i_0 + 2] * b[i + 6];
      }
    }

    v_akv = alpha_as * -10.0;
    alpha_as_idx_1 = alpha_as * 1.2246467991473533E-15;
    alpha_ak = alpha_as * 0.0;
    for (i = 0; i < 3; i++) {
      b_1[i] = b_0[i + 6] * alpha_ak + (b_0[i + 3] * alpha_as_idx_1 + b_0[i] *
        v_akv);
    }

    /* '<S3>:1:117' */
    /* '<S3>:1:118' */
    /* '<S3>:1:119' */
    alpha_aw = DOF_rt_atan2d_snf((b_1[1] - rtb_TmpSignalConversionAtSFun_m[8]) -
                                 (rtb_TmpSignalConversionAtSFun_m[10] * 0.0 -
      rtb_TmpSignalConversionAtSFun_m[9] * -11.58), -((b_1[0] -
      rtb_TmpSignalConversionAtSFun_m[7]) - (-0.0 -
      rtb_TmpSignalConversionAtSFun_m[10] * 0.0)));

    /*  (sail luffing or not) */
    if (alpha_aw > rtb_TmpSignalConversionAtSFun_m[1]) {
      /* '<S3>:1:122' */
      /* '<S3>:1:123' */
      delta_s = rtb_TmpSignalConversionAtSFun_m[1];
    } else if (alpha_aw < -rtb_TmpSignalConversionAtSFun_m[1]) {
      /* '<S3>:1:124' */
      /* '<S3>:1:125' */
      delta_s = -rtb_TmpSignalConversionAtSFun_m[1];
    } else {
      /* '<S3>:1:127' */
      delta_s = alpha_aw;
    }

    /* '<S3>:1:130' */
    alpha_as = alpha_aw - delta_s;

    /* '<S3>:1:132' */
    /*  fit the input angle of attack into the interval [-pi,pi] */
    if (alpha_as > 3.1415926535897931) {
      /* '<S3>:1:135' */
      /* '<S3>:1:136' */
      alpha_as = (alpha_as + 3.1415926535897931) / 6.2831853071795862;
      if (fabs(alpha_as - DOF_rt_roundd_snf(alpha_as)) <= 2.2204460492503131E-16
          * alpha_as) {
        alpha_as = 0.0;
      } else {
        alpha_as = (alpha_as - floor(alpha_as)) * 6.2831853071795862;
      }

      alpha_as -= 3.1415926535897931;
    } else {
      if (alpha_as < -3.1415926535897931) {
        /* '<S3>:1:138' */
        /* '<S3>:1:139' */
        alpha_as = (alpha_as - 3.1415926535897931) / -6.2831853071795862;
        if (fabs(alpha_as - DOF_rt_roundd_snf(alpha_as)) <=
            2.2204460492503131E-16 * alpha_as) {
          alpha_as = 0.0;
        } else {
          alpha_as = (alpha_as - floor(alpha_as)) * -6.2831853071795862;
        }

        alpha_as += 3.1415926535897931;
      }
    }

    /*  interpolation */
    /* '<S3>:1:144' */
    alpha_as = alpha_as / 3.1415926535897931 * 180.0;

    /* Lookup_n-D: '<S1>/1-D Lookup Table' */
    rtb_DLookupTable = DOF_look1_binlxpw(alpha_as, DOF_ConstP.pooled1,
      DOF_ConstP.DLookupTable_tab, 99999U);

    /* Lookup_n-D: '<S1>/1-D Lookup Table4' */
    rtb_DLookupTable4 = DOF_look1_binlxpw(alpha_as, DOF_ConstP.pooled1,
      DOF_ConstP.DLookupTable4_ta, 99999U);

    /* SignalConversion: '<S4>/TmpSignal ConversionAt SFunction Inport1' incorporates:
     *  Inport: '<Root>/U'
     *  MATLAB Function: '<S1>/MATLAB Function2'
     */
    rtb_TmpSignalConversionAtSFun_m[0] = *((const real_T **)
      ssGetInputPortSignalPtrs(S, 1))[0];
    memcpy(&rtb_TmpSignalConversionAtSFun_m[3], &rtb_Integrator[0], sizeof
           (real_T) << 3U);

    /* MATLAB Function: '<S1>/MATLAB Function2' */
    /* MATLAB Function '4DOF nonlinear sailing yacht model/MATLAB Function2': '<S4>:1' */
    /*  interpreted Matlab function "f.m" for the Simulink file "SailingYachtModel.slx" */
    /*  This function describes the dynamics of a 4DOF sailing yacht model */
    /*  and gives the derivative of the state X and the sail angle delta_s. */
    /*  The input vector V_in contains the system state and the control input vector.  */
    /*  */
    /*  For the model description, notations, equations and parameters, */
    /*  see Xiao and Jouffroy, "Modeling and nonlinear heading control of sailing */
    /*  yachts", IEEE Journal of Oceanic Engineering, vol. 39, no. 2., pp. 256-268, 2014. */
    /*   */
    /*  Jerome Jouffroy, Jiaxi He and Lin Xiao, 2014. */
    /*  University of Southern Denmark. */
    /*  use the system parameters */
    /*  (kg),mass of the vehicle */
    /*  moment of inertia */
    /*  (kg),added mass coef. */
    /*  the norm of wind velocity */
    /*  the direction of wind (coming from the north, ie going south) */
    /*  (kg/m^3), air density */
    /*  (m^2), sail area */
    /*  (m), roughness height */
    /*  (m), reference height */
    /*  (m), (x,y,z) is the CoE */
    /*  (m), distance along the mast to the CoE */
    /*  (m), x-coordinate of the mast  */
    /*  (kg/m^3), water density */
    /*  (m^2), rudder area */
    /*  rudder draft */
    /*  rudder efficiency */
    /*  (m), (x,y,z) is the CoE */
    /* '<S4>:1:50' */
    /* '<S4>:1:51' */
    /* '<S4>:1:52' */
    /*  (m), (x,y,z) is the CoE */
    /*  (m^2), keel area */
    /*  keel draft */
    /*  keel efficiency */
    /*  (m), (x,y,z) is the CoE */
    /*  (N), crew weight 20000 */
    /*  (m), crew position */
    /*  (m), yacht beam */
    /*  retrieve the system state from the field input vector "V_in" */
    /* '<S4>:1:87' */
    /* '<S4>:1:88' */
    /* '<S4>:1:89' */
    /* '<S4>:1:90' */
    /*  retrieve the input signals from the vector "V_in" */
    /* '<S4>:1:94' */
    /*  evaluate the matrix M and C in the model */
    /*  calculate the tau vector, ie forces and moments generated from: */
    /*  the sail */
    /*  wind expressed in the body frame */
    /*  the rudder */
    /* '<S4>:1:120' */
    /* '<S4>:1:121' */
    /* '<S4>:1:122' */
    /* '<S4>:1:123' */
    alpha_as = DOF_rt_atan2d_snf((-rtb_TmpSignalConversionAtSFun_m[8] -
      rtb_TmpSignalConversionAtSFun_m[10] * -8.2) +
      rtb_TmpSignalConversionAtSFun_m[9] * -0.78,
      -(rtb_TmpSignalConversionAtSFun_m[10] * 0.0 +
        -rtb_TmpSignalConversionAtSFun_m[7])) - rtb_TmpSignalConversionAtSFun_m
      [0];

    /* '<S4>:1:125' */
    /*  fit the input angle of attack into the interval [-pi,pi] */
    if (alpha_as > 3.1415926535897931) {
      /* '<S4>:1:128' */
      /* '<S4>:1:129' */
      alpha_as = (alpha_as + 3.1415926535897931) / 6.2831853071795862;
      if (fabs(alpha_as - DOF_rt_roundd_snf(alpha_as)) <= 2.2204460492503131E-16
          * alpha_as) {
        alpha_as = 0.0;
      } else {
        alpha_as = (alpha_as - floor(alpha_as)) * 6.2831853071795862;
      }

      alpha_as -= 3.1415926535897931;
    } else {
      if (alpha_as < -3.1415926535897931) {
        /* '<S4>:1:131' */
        /* '<S4>:1:132' */
        alpha_as = (alpha_as - 3.1415926535897931) / -6.2831853071795862;
        if (fabs(alpha_as - DOF_rt_roundd_snf(alpha_as)) <=
            2.2204460492503131E-16 * alpha_as) {
          alpha_as = 0.0;
        } else {
          alpha_as = (alpha_as - floor(alpha_as)) * -6.2831853071795862;
        }

        alpha_as += 3.1415926535897931;
      }
    }

    /*  interpolation */
    /* '<S4>:1:137' */
    alpha_as = alpha_as / 3.1415926535897931 * 180.0;

    /* Lookup_n-D: '<S1>/1-D Lookup Table1' */
    rtb_DLookupTable1 = DOF_look1_binlxpw(alpha_as, DOF_ConstP.pooled1,
      DOF_ConstP.pooled2, 99999U);

    /* Lookup_n-D: '<S1>/1-D Lookup Table5' */
    rtb_DLookupTable5 = DOF_look1_binlxpw(alpha_as, DOF_ConstP.pooled1,
      DOF_ConstP.pooled3, 99999U);

    /* SignalConversion: '<S5>/TmpSignal ConversionAt SFunction Inport1' incorporates:
     *  MATLAB Function: '<S1>/MATLAB Function3'
     */
    memcpy(&rtb_TmpSignalConversionAtSFun_m[3], &rtb_Integrator[0], sizeof
           (real_T) << 3U);

    /* MATLAB Function: '<S1>/MATLAB Function3' */
    /* MATLAB Function '4DOF nonlinear sailing yacht model/MATLAB Function3': '<S5>:1' */
    /*  interpreted Matlab function "f.m" for the Simulink file "SailingYachtModel.slx" */
    /*  This function describes the dynamics of a 4DOF sailing yacht model */
    /*  and gives the derivative of the state X and the sail angle delta_s. */
    /*  The input vector V_in contains the system state and the control input vector.  */
    /*  */
    /*  For the model description, notations, equations and parameters, */
    /*  see Xiao and Jouffroy, "Modeling and nonlinear heading control of sailing */
    /*  yachts", IEEE Journal of Oceanic Engineering, vol. 39, no. 2., pp. 256-268, 2014. */
    /*   */
    /*  Jerome Jouffroy, Jiaxi He and Lin Xiao, 2014. */
    /*  University of Southern Denmark. */
    /*  use the system parameters */
    /*  (kg),mass of the vehicle */
    /*  moment of inertia */
    /*  (kg),added mass coef. */
    /*  the norm of wind velocity */
    /*  the direction of wind (coming from the north, ie going south) */
    /*  (kg/m^3), air density */
    /*  (m^2), sail area */
    /*  (m), roughness height */
    /*  (m), reference height */
    /*  (m), (x,y,z) is the CoE */
    /*  (m), distance along the mast to the CoE */
    /*  (m), x-coordinate of the mast  */
    /*  (kg/m^3), water density */
    /*  (m^2), rudder area */
    /*  rudder draft */
    /*  rudder efficiency */
    /*  (m), (x,y,z) is the CoE */
    /*  (m^2), keel area */
    /*  keel draft */
    /*  keel efficiency */
    /*  (m), (x,y,z) is the CoE */
    /* '<S5>:1:60' */
    /* '<S5>:1:61' */
    /* '<S5>:1:62' */
    /*  (m), (x,y,z) is the CoE */
    /*  (N), crew weight 20000 */
    /*  (m), crew position */
    /*  (m), yacht beam */
    /*  retrieve the system state from the field input vector "V_in" */
    /* '<S5>:1:88' */
    /* '<S5>:1:89' */
    /* '<S5>:1:90' */
    /* '<S5>:1:91' */
    /*  retrieve the input signals from the vector "V_in" */
    /*  evaluate the matrix M and C in the model */
    /*  calculate the tau vector, ie forces and moments generated from: */
    /*  the sail */
    /*  wind expressed in the body frame */
    /*  calculate the damping forces and moments: */
    /*  from the keel */
    /* '<S5>:1:124' */
    /* '<S5>:1:125' */
    /* '<S5>:1:126' */
    alpha_ak = DOF_rt_atan2d_snf((-rtb_TmpSignalConversionAtSFun_m[8] -
      rtb_TmpSignalConversionAtSFun_m[10] * 0.0) +
      rtb_TmpSignalConversionAtSFun_m[9] * -0.58,
      -(rtb_TmpSignalConversionAtSFun_m[10] * 0.0 +
        -rtb_TmpSignalConversionAtSFun_m[7]));

    /* '<S5>:1:129' */
    /*  fit the input angle of attack into the interval [-pi,pi] */
    if (alpha_ak > 3.1415926535897931) {
      /* '<S5>:1:132' */
      /* '<S5>:1:133' */
      alpha_as = (alpha_ak + 3.1415926535897931) / 6.2831853071795862;
      if (fabs(alpha_as - DOF_rt_roundd_snf(alpha_as)) <= 2.2204460492503131E-16
          * alpha_as) {
        alpha_as = 0.0;
      } else {
        alpha_as = (alpha_as - floor(alpha_as)) * 6.2831853071795862;
      }

      alpha_ak = alpha_as - 3.1415926535897931;
    } else {
      if (alpha_ak < -3.1415926535897931) {
        /* '<S5>:1:135' */
        /* '<S5>:1:136' */
        alpha_as = (alpha_ak - 3.1415926535897931) / -6.2831853071795862;
        if (fabs(alpha_as - DOF_rt_roundd_snf(alpha_as)) <=
            2.2204460492503131E-16 * alpha_as) {
          alpha_as = 0.0;
        } else {
          alpha_as = (alpha_as - floor(alpha_as)) * -6.2831853071795862;
        }

        alpha_ak = alpha_as + 3.1415926535897931;
      }
    }

    /*  interpolation */
    /* '<S5>:1:141' */
    alpha_ak = alpha_ak / 3.1415926535897931 * 180.0;

    /* Lookup_n-D: '<S1>/1-D Lookup Table2' */
    rtb_DLookupTable2 = DOF_look1_binlxpw(alpha_ak, DOF_ConstP.pooled1,
      DOF_ConstP.pooled2, 99999U);

    /* Lookup_n-D: '<S1>/1-D Lookup Table6' */
    rtb_DLookupTable6 = DOF_look1_binlxpw(alpha_ak, DOF_ConstP.pooled1,
      DOF_ConstP.pooled3, 99999U);

    /* SignalConversion: '<S6>/TmpSignal ConversionAt SFunction Inport1' incorporates:
     *  MATLAB Function: '<S1>/MATLAB Function4'
     */
    memcpy(&rtb_TmpSignalConversionAtSFun_m[3], &rtb_Integrator[0], sizeof
           (real_T) << 3U);

    /* MATLAB Function: '<S1>/MATLAB Function4' */
    /* MATLAB Function '4DOF nonlinear sailing yacht model/MATLAB Function4': '<S6>:1' */
    /*  interpreted Matlab function "f.m" for the Simulink file "SailingYachtModel.slx" */
    /*  This function describes the dynamics of a 4DOF sailing yacht model */
    /*  and gives the derivative of the state X and the sail angle delta_s. */
    /*  The input vector V_in contains the system state and the control input vector.  */
    /*  */
    /*  For the model description, notations, equations and parameters, */
    /*  see Xiao and Jouffroy, "Modeling and nonlinear heading control of sailing */
    /*  yachts", IEEE Journal of Oceanic Engineering, vol. 39, no. 2., pp. 256-268, 2014. */
    /*   */
    /*  Jerome Jouffroy, Jiaxi He and Lin Xiao, 2014. */
    /*  University of Southern Denmark. */
    /*  use the system parameters */
    /*  (kg),mass of the vehicle */
    /*  moment of inertia */
    /*  (kg),added mass coef. */
    /*  the norm of wind velocity */
    /*  the direction of wind (coming from the north, ie going south) */
    /*  (kg/m^3), air density */
    /*  (m^2), sail area */
    /*  (m), roughness height */
    /*  (m), reference height */
    /*  (m), (x,y,z) is the CoE */
    /*  (m), distance along the mast to the CoE */
    /*  (m), x-coordinate of the mast  */
    /*  (kg/m^3), water density */
    /*  (m^2), rudder area */
    /*  rudder draft */
    /*  rudder efficiency */
    /*  (m), (x,y,z) is the CoE */
    /*  (m^2), keel area */
    /*  keel draft */
    /*  keel efficiency */
    /*  (m), (x,y,z) is the CoE */
    /* '<S6>:1:60' */
    /* '<S6>:1:61' */
    /* '<S6>:1:62' */
    /*  (m), (x,y,z) is the CoE */
    /*  (N), crew weight 20000 */
    /*  (m), crew position */
    /*  (m), yacht beam */
    /*  retrieve the system state from the field input vector "V_in" */
    /* '<S6>:1:88' */
    /* '<S6>:1:89' */
    /* '<S6>:1:90' */
    /* '<S6>:1:91' */
    /*  retrieve the input signals from the vector "V_in" */
    /*  evaluate the matrix M and C in the model */
    /*  calculate the tau vector, ie forces and moments generated from: */
    /*  the sail */
    /*  wind expressed in the body frame */
    /*  calculate the damping forces and moments: */
    /*  from the keel */
    /* '<S6>:1:123' */
    alpha_as = rtb_TmpSignalConversionAtSFun_m[10] * 0.0 +
      -rtb_TmpSignalConversionAtSFun_m[7];

    /* '<S6>:1:124' */
    v_akv = (-rtb_TmpSignalConversionAtSFun_m[8] -
             rtb_TmpSignalConversionAtSFun_m[10] * 0.0) +
      rtb_TmpSignalConversionAtSFun_m[9] * -0.58;

    /*  from the hull */
    /* '<S6>:1:131' */
    /* '<S6>:1:133' */
    alpha_as = sqrt(alpha_as * alpha_as + v_akv * v_akv);

    /* Lookup_n-D: '<S1>/1-D Lookup Table3' */
    rtb_DLookupTable3 = DOF_look1_binlxpw(alpha_as, DOF_ConstP.DLookupTable3_bp,
      DOF_ConstP.DLookupTable3_ta, 99999U);

    /* SignalConversion: '<S2>/TmpSignal ConversionAt SFunction Inport1' incorporates:
     *  Inport: '<Root>/U'
     *  MATLAB Function: '<S1>/MATLAB Function'
     */
    rtb_TmpSignalConversionAtSFun_m[1] = *((const real_T **)
      ssGetInputPortSignalPtrs(S, 1))[1];
    rtb_TmpSignalConversionAtSFun_m[2] = *((const real_T **)
      ssGetInputPortSignalPtrs(S, 1))[2];
    memcpy(&rtb_TmpSignalConversionAtSFun_m[3], &rtb_Integrator[0], sizeof
           (real_T) << 3U);

    /* MATLAB Function: '<S1>/MATLAB Function' */
    /* MATLAB Function '4DOF nonlinear sailing yacht model/MATLAB Function': '<S2>:1' */
    /*  interpreted Matlab function "f.m" for the Simulink file "SailingYachtModel.slx" */
    /*  This function describes the dynamics of a 4DOF sailing yacht model */
    /*  and gives the derivative of the state X and the sail angle delta_s. */
    /*  The input vector V_in contains the system state and the control input vector.  */
    /*  */
    /*  For the model description, notations, equations and parameters, */
    /*  see Xiao and Jouffroy, "Modeling and nonlinear heading control of sailing */
    /*  yachts", IEEE Journal of Oceanic Engineering, vol. 39, no. 2., pp. 256-268, 2014. */
    /*   */
    /*  Jerome Jouffroy, Jiaxi He and Lin Xiao, 2014. */
    /*  University of Southern Denmark. */
    /*  use the system parameters */
    /* '<S2>:1:19' */
    /*  (kg),mass of the vehicle */
    /* '<S2>:1:20' */
    /* '<S2>:1:21' */
    /* '<S2>:1:22' */
    /*  moment of inertia */
    /* '<S2>:1:23' */
    /* '<S2>:1:24' */
    /* '<S2>:1:25' */
    /* '<S2>:1:26' */
    /* '<S2>:1:27' */
    /* '<S2>:1:28' */
    /* '<S2>:1:29' */
    /*  (kg),added mass coef. */
    /* '<S2>:1:31' */
    /*  the norm of wind velocity */
    /* '<S2>:1:32' */
    /*  the direction of wind (coming from the north, ie going south) */
    /* '<S2>:1:34' */
    /*  (kg/m^3), air density */
    /* '<S2>:1:35' */
    /*  (m^2), sail area */
    /* '<S2>:1:36' */
    /*  (m), roughness height */
    /* '<S2>:1:37' */
    /*  (m), reference height */
    /* '<S2>:1:38' */
    /*  (m), (x,y,z) is the CoE */
    /* '<S2>:1:39' */
    /* '<S2>:1:40' */
    /* '<S2>:1:41' */
    /*  (m), (x,y,z) is the CoE */
    /* '<S2>:1:42' */
    /*  (m), distance along the mast to the CoE */
    /* '<S2>:1:43' */
    /*  (m), x-coordinate of the mast  */
    /* '<S2>:1:45' */
    /*  (kg/m^3), water density */
    /* '<S2>:1:46' */
    /*  (m^2), rudder area */
    /* '<S2>:1:47' */
    /*  rudder draft */
    /* '<S2>:1:48' */
    /*  rudder efficiency */
    /*  (m), (x,y,z) is the CoE */
    /* '<S2>:1:51' */
    /* '<S2>:1:52' */
    /* '<S2>:1:53' */
    /*  (m), (x,y,z) is the CoE */
    /* '<S2>:1:55' */
    /*  (m^2), keel area */
    /* '<S2>:1:56' */
    /*  keel draft */
    /* '<S2>:1:57' */
    /*  keel efficiency */
    /*  (m), (x,y,z) is the CoE */
    /* '<S2>:1:60' */
    /* '<S2>:1:61' */
    /* '<S2>:1:62' */
    /*  (m), (x,y,z) is the CoE */
    /* '<S2>:1:66' */
    /* '<S2>:1:67' */
    /* '<S2>:1:68' */
    /*  (m), (x,y,z) is the CoE */
    /* '<S2>:1:70' */
    /*  (N), crew weight 20000 */
    /* '<S2>:1:71' */
    /*  (m), crew position */
    /* '<S2>:1:72' */
    /*  (m), yacht beam */
    /* '<S2>:1:74' */
    /* '<S2>:1:75' */
    /* '<S2>:1:76' */
    /* '<S2>:1:77' */
    /*  retrieve the system state from the field input vector "V_in" */
    /* '<S2>:1:86' */
    /* '<S2>:1:87' */
    /* '<S2>:1:88' */
    /* '<S2>:1:89' */
    /* '<S2>:1:90' */
    /* '<S2>:1:91' */
    /* '<S2>:1:92' */
    /*  retrieve the input signals from the vector "V_in" */
    /* '<S2>:1:96' */
    /* '<S2>:1:97' */
    /*  evaluate the matrix M and C in the model */
    /* '<S2>:1:100' */
    /* '<S2>:1:101' */
    /* '<S2>:1:103' */
    /* '<S2>:1:104' */
    /* '<S2>:1:106' */
    tmp_0[0] = 25900;
    tmp_0[4] = 0;
    tmp_0[8] = 0;
    tmp_0[12] = 0;
    tmp_0[1] = 0;
    tmp_0[5] = 25900;
    tmp_0[9] = 0;
    tmp_0[13] = 0;
    tmp_0[2] = 0;
    tmp_0[6] = 0;
    tmp_0[10] = 133690;
    tmp_0[14] = -2180;
    tmp_0[3] = 0;
    tmp_0[7] = 0;
    tmp_0[11] = -2180;
    tmp_0[15] = 24760;
    tmp_1[0] = 970;
    tmp_1[4] = 0;
    tmp_1[8] = 0;
    tmp_1[12] = 0;
    tmp_1[1] = 0;
    tmp_1[5] = 17430;
    tmp_1[9] = -13160;
    tmp_1[13] = -6190;
    tmp_1[2] = 0;
    tmp_1[6] = -13160;
    tmp_1[10] = 106500;
    tmp_1[14] = 4730;
    tmp_1[3] = 0;
    tmp_1[7] = -6190;
    tmp_1[11] = 4730;
    tmp_1[15] = 101650;
    for (i = 0; i < 4; i++) {
      M[i << 2] = tmp_0[i << 2] + tmp_1[i << 2];
      M[1 + (i << 2)] = tmp_0[(i << 2) + 1] + tmp_1[(i << 2) + 1];
      M[2 + (i << 2)] = tmp_0[(i << 2) + 2] + tmp_1[(i << 2) + 2];
      M[3 + (i << 2)] = tmp_0[(i << 2) + 3] + tmp_1[(i << 2) + 3];
    }

    /*  calculate the tau vector, ie forces and moments generated from: */
    /*  the sail */
    /* '<S2>:1:110' */
    /* '<S2>:1:111' */
    alpha_as = log(11.58 * cos(rtb_TmpSignalConversionAtSFun_m[5]) / 0.0005) /
      10.050181931686932;

    /* '<S2>:1:112' */
    /* '<S2>:1:113' */
    /* '<S2>:1:114' */
    /*  wind expressed in the body frame */
    /* '<S2>:1:115' */
    /* '<S2>:1:116' */
    c[0] = 1.0;
    c[3] = 0.0;
    c[6] = 0.0;
    c[1] = 0.0;
    c[4] = cos(-rtb_TmpSignalConversionAtSFun_m[5]);
    c[7] = -sin(-rtb_TmpSignalConversionAtSFun_m[5]);
    c[2] = 0.0;
    c[5] = sin(-rtb_TmpSignalConversionAtSFun_m[5]);
    c[8] = cos(-rtb_TmpSignalConversionAtSFun_m[5]);
    tmp_2[0] = cos(-rtb_TmpSignalConversionAtSFun_m[6]);
    tmp_2[3] = -sin(-rtb_TmpSignalConversionAtSFun_m[6]);
    tmp_2[6] = 0.0;
    tmp_2[1] = sin(-rtb_TmpSignalConversionAtSFun_m[6]);
    tmp_2[4] = cos(-rtb_TmpSignalConversionAtSFun_m[6]);
    tmp_2[7] = 0.0;
    tmp_2[2] = 0.0;
    tmp_2[5] = 0.0;
    tmp_2[8] = 1.0;
    for (i = 0; i < 3; i++) {
      for (i_0 = 0; i_0 < 3; i_0++) {
        b[i + 3 * i_0] = 0.0;
        b[i + 3 * i_0] += tmp_2[3 * i_0] * c[i];
        b[i + 3 * i_0] += tmp_2[3 * i_0 + 1] * c[i + 3];
        b[i + 3 * i_0] += tmp_2[3 * i_0 + 2] * c[i + 6];
      }
    }

    v_akv = alpha_as * -10.0;
    alpha_as_idx_1 = alpha_as * 1.2246467991473533E-15;
    alpha_ak = alpha_as * 0.0;
    for (i = 0; i < 3; i++) {
      b_1[i] = b[i + 6] * alpha_ak + (b[i + 3] * alpha_as_idx_1 + b[i] * v_akv);
    }

    alpha_ak = (b_1[0] - rtb_TmpSignalConversionAtSFun_m[7]) - (-0.0 -
      rtb_TmpSignalConversionAtSFun_m[10] * 0.0);
    v_akv = (b_1[1] - rtb_TmpSignalConversionAtSFun_m[8]) -
      (rtb_TmpSignalConversionAtSFun_m[10] * 0.0 -
       rtb_TmpSignalConversionAtSFun_m[9] * -11.58);

    /* '<S2>:1:117' */
    /* '<S2>:1:118' */
    /* '<S2>:1:119' */
    alpha_aw = DOF_rt_atan2d_snf(v_akv, -alpha_ak);

    /*  (sail luffing or not) */
    if (alpha_aw > rtb_TmpSignalConversionAtSFun_m[1]) {
      /* '<S2>:1:122' */
      /* '<S2>:1:123' */
      delta_s = rtb_TmpSignalConversionAtSFun_m[1];
    } else if (alpha_aw < -rtb_TmpSignalConversionAtSFun_m[1]) {
      /* '<S2>:1:124' */
      /* '<S2>:1:125' */
      delta_s = -rtb_TmpSignalConversionAtSFun_m[1];
    } else {
      /* '<S2>:1:127' */
      delta_s = alpha_aw;
    }

    /* '<S2>:1:135' */
    Ls = (alpha_ak * alpha_ak + v_akv * v_akv) * 102.0 * rtb_DLookupTable;

    /* '<S2>:1:136' */
    Ds = (alpha_ak * alpha_ak + v_akv * v_akv) * 102.0 * rtb_DLookupTable4;

    /* '<S2>:1:138' */
    /*  the rudder */
    /* '<S2>:1:142' */
    alpha_as = rtb_TmpSignalConversionAtSFun_m[10] * 0.0 +
      -rtb_TmpSignalConversionAtSFun_m[7];

    /* '<S2>:1:143' */
    v_akv = (-rtb_TmpSignalConversionAtSFun_m[8] -
             rtb_TmpSignalConversionAtSFun_m[10] * -8.2) +
      rtb_TmpSignalConversionAtSFun_m[9] * -0.78;

    /* '<S2>:1:144' */
    alpha_ar = DOF_rt_atan2d_snf(v_akv, -alpha_as);

    /* [Clr,Cdr] = ruddercoef(alpha_a); */
    /* '<S2>:1:151' */
    /* '<S2>:1:153' */
    Lr = (alpha_as * alpha_as + v_akv * v_akv) * 599.625 * rtb_DLookupTable1;

    /* '<S2>:1:154' */
    rtb_DLookupTable4 = (rtb_DLookupTable1 * rtb_DLookupTable1 * 1.17 /
                         18.145839167134646 + rtb_DLookupTable5) * ((alpha_as *
      alpha_as + v_akv * v_akv) * 599.625);

    /* '<S2>:1:156' */
    /*  the tau vector is finally given by: */
    /* '<S2>:1:160' */
    /*  calculate the damping forces and moments: */
    /*  from the keel */
    /* '<S2>:1:164' */
    alpha_as = rtb_TmpSignalConversionAtSFun_m[10] * 0.0 +
      -rtb_TmpSignalConversionAtSFun_m[7];

    /* '<S2>:1:165' */
    v_akv = (-rtb_TmpSignalConversionAtSFun_m[8] -
             rtb_TmpSignalConversionAtSFun_m[10] * 0.0) +
      rtb_TmpSignalConversionAtSFun_m[9] * -0.58;

    /* '<S2>:1:166' */
    alpha_ak = DOF_rt_atan2d_snf(v_akv, -alpha_as);

    /* '<S2>:1:172' */
    /* '<S2>:1:174' */
    rtb_DLookupTable1 = (alpha_as * alpha_as + v_akv * v_akv) * 4458.75 *
      rtb_DLookupTable2;

    /* '<S2>:1:175' */
    alpha_as = (rtb_DLookupTable2 * rtb_DLookupTable2 * 8.7 / 27.269464056130911
                + rtb_DLookupTable6) * ((alpha_as * alpha_as + v_akv * v_akv) *
      4458.75);

    /* '<S2>:1:177' */
    /*  from the hull */
    /* '<S2>:1:180' */
    /* '<S2>:1:181' */
    /* '<S2>:1:183' */
    v_akv = DOF_rt_atan2d_snf(((-rtb_TmpSignalConversionAtSFun_m[8] -
      rtb_TmpSignalConversionAtSFun_m[10] * 0.0) +
      rtb_TmpSignalConversionAtSFun_m[9] * -1.18) / cos
      (rtb_TmpSignalConversionAtSFun_m[5]), -(rtb_TmpSignalConversionAtSFun_m[10]
      * 0.0 + -rtb_TmpSignalConversionAtSFun_m[7]));

    /* '<S2>:1:187' */
    /*  from heel and yaw */
    /*  (compute first eta_dot and thereby phi_dot and psi_dot) */
    /* '<S2>:1:191' */
    /* '<S2>:1:192' */
    M_0[0] = cos(rtb_TmpSignalConversionAtSFun_m[6]);
    M_0[4] = -sin(rtb_TmpSignalConversionAtSFun_m[6]) * cos
      (rtb_TmpSignalConversionAtSFun_m[5]);
    M_0[8] = 0.0;
    M_0[12] = 0.0;
    M_0[1] = sin(rtb_TmpSignalConversionAtSFun_m[6]);
    M_0[5] = cos(rtb_TmpSignalConversionAtSFun_m[6]) * cos
      (rtb_TmpSignalConversionAtSFun_m[5]);
    M_0[9] = 0.0;
    M_0[13] = 0.0;
    M_0[2] = 0.0;
    M_0[6] = 0.0;
    M_0[10] = 1.0;
    M_0[14] = 0.0;
    M_0[3] = 0.0;
    M_0[7] = 0.0;
    M_0[11] = 0.0;
    M_0[15] = cos(rtb_TmpSignalConversionAtSFun_m[5]);
    for (i = 0; i < 4; i++) {
      alpha_as_idx_1 = M_0[i + 12] * rtb_TmpSignalConversionAtSFun_m[10] +
        (M_0[i + 8] * rtb_TmpSignalConversionAtSFun_m[9] + (M_0[i + 4] *
          rtb_TmpSignalConversionAtSFun_m[8] + M_0[i] *
          rtb_TmpSignalConversionAtSFun_m[7]));
      eta_dot[i] = alpha_as_idx_1;
    }

    /* '<S2>:1:193' */
    /* '<S2>:1:194' */
    /* '<S2>:1:196' */
    /*  compute total damping vector D */
    /* '<S2>:1:199' */
    /*  righting moment plus internal moving mass system (ie transversal weight) */
    /* '<S2>:1:202' */
    rtb_DLookupTable = rtb_TmpSignalConversionAtSFun_m[5] * 180.0 /
      3.1415926535897931;

    /* '<S2>:1:203' */
    /* '<S2>:1:204' */
    /* '<S2>:1:205' */
    /*  computation of nu_dot */
    /* '<S2>:1:208' */
    tmp_3[0] = 0.0;
    tmp_3[4] = -25900.0 * rtb_TmpSignalConversionAtSFun_m[10];
    tmp_3[8] = 0.0;
    tmp_3[12] = 0.0;
    tmp_3[1] = 25900.0 * rtb_TmpSignalConversionAtSFun_m[10];
    tmp_3[5] = 0.0;
    tmp_3[9] = 0.0;
    tmp_3[13] = 0.0;
    tmp_3[2] = 0.0;
    tmp_3[6] = 0.0;
    tmp_3[10] = 0.0;
    tmp_3[14] = 0.0;
    tmp_3[3] = 0.0;
    tmp_3[7] = 0.0;
    tmp_3[11] = 0.0;
    tmp_3[15] = 0.0;
    tmp_4[0] = 0.0;
    tmp_4[4] = 0.0;
    tmp_4[8] = 0.0;
    tmp_4[12] = (-17430.0 * rtb_TmpSignalConversionAtSFun_m[8] - -13160.0 *
                 rtb_TmpSignalConversionAtSFun_m[9]) - -6190.0 *
      rtb_TmpSignalConversionAtSFun_m[10];
    tmp_4[1] = 0.0;
    tmp_4[5] = 0.0;
    tmp_4[9] = 0.0;
    tmp_4[13] = 970.0 * rtb_TmpSignalConversionAtSFun_m[7];
    tmp_4[2] = 0.0;
    tmp_4[6] = 0.0;
    tmp_4[10] = 0.0;
    tmp_4[14] = 0.0;
    tmp_4[3] = (17430.0 * rtb_TmpSignalConversionAtSFun_m[8] + -13160.0 *
                rtb_TmpSignalConversionAtSFun_m[9]) + -6190.0 *
      rtb_TmpSignalConversionAtSFun_m[10];
    tmp_4[7] = -970.0 * rtb_TmpSignalConversionAtSFun_m[7];
    tmp_4[11] = 0.0;
    tmp_4[15] = 0.0;
    for (i = 0; i < 4; i++) {
      alpha_as_idx_1 = tmp_3[i + 12] * rtb_TmpSignalConversionAtSFun_m[10] +
        (tmp_3[i + 8] * rtb_TmpSignalConversionAtSFun_m[9] + (tmp_3[i + 4] *
          rtb_TmpSignalConversionAtSFun_m[8] + tmp_3[i] *
          rtb_TmpSignalConversionAtSFun_m[7]));
      tmp_5[i] = alpha_as_idx_1;
    }

    for (i = 0; i < 4; i++) {
      alpha_as_idx_1 = tmp_4[i + 12] * rtb_TmpSignalConversionAtSFun_m[10] +
        (tmp_4[i + 8] * rtb_TmpSignalConversionAtSFun_m[9] + (tmp_4[i + 4] *
          rtb_TmpSignalConversionAtSFun_m[8] + tmp_4[i] *
          rtb_TmpSignalConversionAtSFun_m[7]));
      tmp_6[i] = alpha_as_idx_1;
    }

    nu_dot[0] = tmp_5[0] + tmp_6[0];
    nu_dot[1] = tmp_5[1] + tmp_6[1];
    nu_dot[2] = tmp_5[2] + tmp_6[2];
    nu_dot[3] = tmp_5[3] + tmp_6[3];
    for (i = 0; i < 16; i++) {
      M_0[i] = -M[i];
    }

    DOF_mldivide(M_0, nu_dot);
    e[0] = (-rtb_DLookupTable1 * sin(alpha_ak) + alpha_as * cos(alpha_ak)) +
      rtb_DLookupTable3 * cos(v_akv);
    e[1] = (-rtb_DLookupTable1 * cos(alpha_ak) - alpha_as * sin(alpha_ak)) +
      -rtb_DLookupTable3 * sin(v_akv) * cos(rtb_TmpSignalConversionAtSFun_m[5]);
    e[2] = (-(-rtb_DLookupTable1 * cos(alpha_ak) - alpha_as * sin(alpha_ak)) *
            -0.58 + rtb_DLookupTable3 * sin(v_akv) * cos
            (rtb_TmpSignalConversionAtSFun_m[5]) * -1.18) + 120000.0 * eta_dot[2]
      * fabs(eta_dot[2]);
    e[3] = (-(rtb_DLookupTable1 * cos(alpha_ak) + alpha_as * sin(alpha_ak)) *
            0.0 + -rtb_DLookupTable3 * sin(v_akv) * cos
            (rtb_TmpSignalConversionAtSFun_m[5]) * 0.0) + 50000.0 * eta_dot[3] *
      fabs(eta_dot[3]) * cos(rtb_TmpSignalConversionAtSFun_m[5]);
    DOF_mldivide(M, e);
    nu[0] = 0.0;
    nu[1] = 0.0;
    nu[2] = (rtb_DLookupTable * rtb_DLookupTable * -5.89 + 8160.0 *
             rtb_DLookupTable) + -rtb_TmpSignalConversionAtSFun_m[2] * 60000.0 *
      3.6 * cos(rtb_TmpSignalConversionAtSFun_m[5]);
    nu[3] = -rtb_TmpSignalConversionAtSFun_m[2] * 60000.0 * -8.0 * sin(fabs
      (rtb_TmpSignalConversionAtSFun_m[5]));
    DOF_mldivide(M, nu);
    D_hull[0] = (Ls * sin(alpha_aw) - Ds * cos(alpha_aw)) + (Lr * sin(alpha_ar)
      - rtb_DLookupTable4 * cos(alpha_ar));
    D_hull[1] = (Ls * cos(alpha_aw) + Ds * sin(alpha_aw)) + (Lr * cos(alpha_ar)
      + rtb_DLookupTable4 * sin(alpha_ar));
    D_hull[2] = -(Ls * cos(alpha_aw) + Ds * sin(alpha_aw)) * -11.58 + -(Lr * cos
      (alpha_ar) + rtb_DLookupTable4 * sin(alpha_ar)) * -0.78;
    D_hull[3] = (-(Ls * sin(alpha_aw) - Ds * cos(alpha_aw)) * 0.6 * sin(delta_s)
                 + (Ls * cos(alpha_aw) + Ds * sin(alpha_aw)) * (0.3 - 0.6 * cos
      (delta_s))) + (Lr * cos(alpha_ar) + rtb_DLookupTable4 * sin(alpha_ar)) *
      -8.2;
    DOF_mldivide(M, D_hull);
    nu_dot[0] = ((nu_dot[0] - e[0]) - nu[0]) + D_hull[0];
    nu_dot[1] = ((nu_dot[1] - e[1]) - nu[1]) + D_hull[1];
    nu_dot[2] = ((nu_dot[2] - e[2]) - nu[2]) + D_hull[2];

    /* '<S2>:1:210' */
    /*  output the derivative of the state extended with the sail angle */
    /* '<S2>:1:213' */
    _rtB->X_dot_ext[0] = eta_dot[0];
    _rtB->X_dot_ext[1] = eta_dot[1];
    _rtB->X_dot_ext[2] = eta_dot[2];
    _rtB->X_dot_ext[3] = eta_dot[3];
    _rtB->X_dot_ext[4] = nu_dot[0];
    _rtB->X_dot_ext[5] = nu_dot[1];
    _rtB->X_dot_ext[6] = nu_dot[2];
    _rtB->X_dot_ext[7] = ((nu_dot[3] - e[3]) - nu[3]) + D_hull[3];
    _rtB->X_dot_ext[8] = delta_s;

    /* Outport: '<Root>/delta_s' */
    ((real_T *)ssGetOutputPortSignal(S, 1))[0] = _rtB->X_dot_ext[8];
  }

  UNUSED_PARAMETER(tid);
}

/* Update for root system: '<Root>' */
#define MDL_UPDATE

static void mdlUpdate(SimStruct *S, int_T tid)
{
  B_DOF_T *_rtB;
  _rtB = ((B_DOF_T *) ssGetLocalBlockIO(S));
  if (ssIsContinuousTask(S, tid)) {
    /* Update for Integrator: '<S1>/Integrator' */
    ((int_T*) ssGetDWork(S, 0))[0] = 0;
  }

  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
#define MDL_DERIVATIVES

static void mdlDerivatives(SimStruct *S)
{
  B_DOF_T *_rtB;
  _rtB = ((B_DOF_T *) ssGetLocalBlockIO(S));

  /* Derivatives for Integrator: '<S1>/Integrator' */
  {
    {
      int_T i1;
      const real_T *u0 = &_rtB->X_dot_ext[0];
      real_T *xdot = &((XDot_DOF_T *) ssGetdX(S))->Integrator_CSTATE[0];
      for (i1=0; i1 < 8; i1++) {
        xdot[i1] = u0[i1];
      }
    }
  }
}

/* Termination for root system: '<Root>' */
static void mdlTerminate(SimStruct *S)
{

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)

  if (ssGetUserData(S) != (NULL) ) {
    rt_FREE(ssGetLocalBlockIO(S));
  }

  rt_FREE(ssGetUserData(S));

#endif

}

#if defined(RT_MALLOC) || defined(MATLAB_MEX_FILE)
#  include "DOF_mid.h"
#endif

/* Function to initialize sizes. */
static void mdlInitializeSizes(SimStruct *S)
{
  ssSetNumSampleTimes(S, 2);           /* Number of sample times */
  ssSetNumContStates(S, 8);            /* Number of continuous states */
  ssSetNumNonsampledZCs(S, 0);         /* Number of nonsampled ZCs */

  /* Number of output ports */
  if (!ssSetNumOutputPorts(S, 2))
    return;

  /* outport number: 0 */
  if (!ssSetOutputPortVectorDimension(S, 0, 8))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 0, 0.0);
  ssSetOutputPortOffsetTime(S, 0, 0.0);
  ssSetOutputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);

  /* outport number: 1 */
  if (!ssSetOutputPortVectorDimension(S, 1, 1))
    return;
  if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
    ssSetOutputPortDataType(S, 1, SS_DOUBLE);
  }

  ssSetOutputPortSampleTime(S, 1, 0.0);
  ssSetOutputPortOffsetTime(S, 1, 0.0);
  ssSetOutputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);

  /* Number of input ports */
  if (!ssSetNumInputPorts(S, 2))
    return;

  /* inport number: 0 */
  {
    if (!ssSetInputPortVectorDimension(S, 0, 8))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 0, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortSampleTime(S, 0, 0.05);
    ssSetInputPortOffsetTime(S, 0, 0.0);
    ssSetInputPortOverWritable(S, 0, 0);
    ssSetInputPortOptimOpts(S, 0, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  /* inport number: 1 */
  {
    if (!ssSetInputPortVectorDimension(S, 1, 3))
      return;
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY) {
      ssSetInputPortDataType(S, 1, SS_DOUBLE);
    }

    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortSampleTime(S, 1, 0.05);
    ssSetInputPortOffsetTime(S, 1, 0.0);
    ssSetInputPortOverWritable(S, 1, 0);
    ssSetInputPortOptimOpts(S, 1, SS_NOT_REUSABLE_AND_GLOBAL);
  }

  ssSetRTWGeneratedSFcn(S, 1);         /* Generated S-function */

  /* DWork */
  if (!ssSetNumDWork(S, 1)) {
    return;
  }

  /* '<S1>/Integrator': IWORK */
  ssSetDWorkName(S, 0, "DWORK0");
  ssSetDWorkWidth(S, 0, 1);
  ssSetDWorkDataType(S, 0, SS_INTEGER);

  /* Tunable Parameters */
  ssSetNumSFcnParams(S, 0);

  /* Number of expected parameters */
#if defined(MATLAB_MEX_FILE)

  if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) {

#if defined(MDL_CHECK_PARAMETERS)

    mdlCheckParameters(S);

#endif                                 /* MDL_CHECK_PARAMETERS */

    if (ssGetErrorStatus(S) != (NULL) ) {
      return;
    }
  } else {
    return;                            /* Parameter mismatch will be reported by Simulink */
  }

#endif                                 /* MATLAB_MEX_FILE */

  /* Options */
  ssSetOptions(S, (SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE |
                   SS_OPTION_PORT_SAMPLE_TIMES_ASSIGNED ));

#if SS_SFCN_FOR_SIM

  {
    ssSupportsMultipleExecInstances(S, true);
    ssHasStateInsideForEachSS(S, false);
  }

#endif

}

/* Function to initialize sample times. */
static void mdlInitializeSampleTimes(SimStruct *S)
{
  /* task periods */
  ssSetSampleTime(S, 0, 0.0);
  ssSetSampleTime(S, 1, 0.05);

  /* task offsets */
  ssSetOffsetTime(S, 0, 0.0);
  ssSetOffsetTime(S, 1, 0.0);
}

#if defined(MATLAB_MEX_FILE)
# include "fixedpoint.c"
# include "simulink.c"
#else
# undef S_FUNCTION_NAME
# define S_FUNCTION_NAME               DOF_sf
# include "cg_sfun.h"
#endif                                 /* defined(MATLAB_MEX_FILE) */
