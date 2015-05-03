/*
 * BoatModele.cpp
 *
 * Code generation for model "BoatModele".
 *
 * Model version              : 1.11
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C++ source code generated on : Sun May  3 10:05:32 2015
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "BoatModele.h"
#include "BoatModele_private.h"

/* Block signals (auto storage) */
B_BoatModele_T BoatModele_B;

/* Continuous states */
X_BoatModele_T BoatModele_X;

/* Block states (auto storage) */
DW_BoatModele_T BoatModele_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_BoatModele_T BoatModele_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_BoatModele_T BoatModele_Y;

/* Real-time model */
RT_MODEL_BoatModele_T BoatModele_M_;
RT_MODEL_BoatModele_T *const BoatModele_M = &BoatModele_M_;

/* Forward declaration for local functions */
static void BoatModele_mldivide(const real_T A[16], real_T B[4]);

/* n-D Spline interpolation function */
real_T look_SplNBinXZcd(uint32_T numDims, const real_T* u, const
  rt_LUTSplineWork * const SWork)
{
  /*
   *   n-D column-major table lookup operating on real_T with:
   *       - Spline interpolation
   *       - Linear extrapolation
   *       - Binary breakpoint search
   *       - Index search starts at the same place each time
   */
  rt_LUTnWork * const TWork_look = SWork->m_TWork;
  real_T* const fraction = (real_T*) TWork_look->m_bpLambda;
  uint32_T* const bpIdx = TWork_look->m_bpIndex;
  const uint32_T* const maxIndex = TWork_look->m_maxIndex;
  uint32_T k;
  for (k = 0U; k < numDims; k++) {
    const real_T* const bpData = ((const real_T * const *)
      TWork_look->m_bpDataSet)[k];
    bpIdx[k] = plook_binx(u[k], &bpData[0], maxIndex[k], &fraction[k]);
  }

  return(intrp_NSplcd(numDims, SWork, 2U));
}

/*
 * Second derivative initialization function for spline
 * for last dimension.
 */
void rt_Spline2Derivd(const real_T *x, const real_T *y, uint32_T n, real_T *u,
                      real_T *y2)
{
  real_T p, qn, sig, un;
  uint32_T n1, i, k;
  n1 = n - 1U;
  y2[0U] = 0.0;
  u[0U] = 0.0;
  for (i = 1U; i < n1; i++) {
    real_T dxm1 = x[i] - x[i - 1U];
    real_T dxp1 = x[i + 1U] - x[i];
    real_T dxpm = dxp1 + dxm1;
    sig = dxm1 / dxpm;
    p = (sig * y2[i - 1U]) + 2.0;
    y2[i] = (sig - 1.0) / p;
    u[i] = ((y[i + 1U] - y[i]) / dxp1) - ((y[i] - y[i - 1U]) / dxm1);
    u[i] = (((6.0 * u[i]) / dxpm) - (sig * u[i - 1U])) / p;
  }

  qn = 0.0;
  un = 0.0;
  y2[n1] = (un - (qn * u[n1 - 1U])) / ((qn * y2[n1 - 1U]) + 1.0);
  for (k = n1; k > 0U; k--) {
    y2[k-1U] = (y2[k-1U] * y2[k]) + u[k-1U];
  }

  return;
}

/* n-D natural spline calculation function */
real_T intrp_NSplcd(uint32_T numDims, const rt_LUTSplineWork * const splWork,
                    uint32_T extrapMethod)
{
  uint32_T il;
  uint32_T iu, k, i;
  real_T h, s, p, smsq, pmsq;

  /* intermediate results work areas "this" and "next" */
  const rt_LUTnWork *TWork_interp = (const rt_LUTnWork *)splWork->m_TWork;
  const real_T *fraction = (real_T *) TWork_interp->m_bpLambda;
  const real_T *yp = (real_T *) TWork_interp->m_tableData;
  real_T *yyA = (real_T *) splWork->m_yyA;
  real_T *yyB = (real_T *) splWork->m_yyB;
  real_T *yy2 = (real_T *) splWork->m_yy2;
  real_T *up = (real_T *) splWork->m_up;
  real_T *y2 = (real_T *) splWork->m_y2;
  const real_T **bpDataSet = (const real_T **) TWork_interp->m_bpDataSet;
  const real_T *xp = bpDataSet[0U];
  real_T *yy = yyA;
  uint32_T bufBank = 0U;
  uint32_T len = TWork_interp->m_maxIndex[0U] + 1U;

  /* If table and bps are tunable calculate 1st dim 2nd deriv */
  /* Generate first dimension's second derivatives */
  for (i = 0U; i < splWork->m_numYWorkElts[0U]; i++) {
    rt_Spline2Derivd(xp, yp, len, up, y2);
    yp = &yp[len];
    y2 = &y2[len];
  }

  /* Set pointers back to beginning */
  yp = (const real_T *) TWork_interp->m_tableData;
  y2 = (real_T *) splWork->m_y2;

  /* Generate at-point splines in each dimension */
  for (k = 0U; k < numDims; k++ ) {
    /* this dimension's input setup */
    xp = bpDataSet[k];
    len = TWork_interp->m_maxIndex[k] + 1U;
    il = TWork_interp->m_bpIndex[k];
    iu = il + 1U;
    h = xp[iu] - xp[il];
    p = fraction[k];
    s = 1.0 - p;
    pmsq = p * ((p*p) - 1.0);
    smsq = s * ((s*s) - 1.0);

    /*
     * Calculate spline curves for input in this
     * dimension at each value of the higher
     * other dimensions\' points in the table.
     */
    if ((p > 1.0) && (extrapMethod == 2U) ) {
      real_T slope;
      for (i = 0U; i < splWork->m_numYWorkElts[k]; i++) {
        slope = (yp[iu] - yp[il]) + ((y2[il]*h*h)*(1.0/6.0));
        yy[i] = yp[iu] + (slope * (p-1.0));
        yp = &yp[len];
        y2 = &y2[len];
      }
    } else if ((p < 0.0) && (extrapMethod == 2U) ) {
      real_T slope;
      for (i = 0U; i < splWork->m_numYWorkElts[k]; i++) {
        slope = (yp[iu] - yp[il]) - ((y2[iu]*h*h)*(1.0/6.0));
        yy[i] = yp[il] + (slope * p);
        yp = &yp[len];
        y2 = &y2[len];
      }
    } else {
      for (i = 0U; i < splWork->m_numYWorkElts[k]; i++) {
        yy[i] = yp[il] + p * (yp[iu] - yp[il]) +
          ((smsq * y2[il] + pmsq * y2[iu])*h*h)*(1.0/6.0);
        yp = &yp[len];
        y2 = &y2[len];
      }
    }

    /* set pointers to new result and calculate second derivatives */
    yp = yy;
    y2 = yy2;
    if (splWork->m_numYWorkElts[k+1U] > 0U ) {
      uint32_T nextLen = TWork_interp->m_maxIndex[k+1U] + 1U;
      const real_T *nextXp = bpDataSet[k+1U];
      for (i = 0U; i < splWork->m_numYWorkElts[k+1U]; i++) {
        rt_Spline2Derivd(nextXp, yp, nextLen, up, y2);
        yp = &yp[nextLen];
        y2 = &y2[nextLen];
      }
    }

    /*
     * Set work vectors yp, y2 and yy for next iteration;
     * the yy just calculated becomes the yp in the
     * next iteration, y2 was just calculated for these
     * new points and the yy buffer is swapped to the space
     * for storing the next iteration\'s results.
     */
    yp = yy;
    y2 = yy2;

    /*
     * Swap buffers for next dimension and
     * toggle bufBank for next iteration.
     */
    if (bufBank == 0U) {
      yy = yyA;
      bufBank = 1U;
    } else {
      yy = yyB;
      bufBank = 0U;
    }
  }

  return( yp[0U] );
}

real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
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

uint32_T plook_binx(real_T u, const real_T bp[], uint32_T maxIndex, real_T
                    *fraction)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0U]) {
    bpIndex = 0U;
    *fraction = (u - bp[0U]) / (bp[1U] - bp[0U]);
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d(u, bp, maxIndex >> 1U, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = (u - bp[maxIndex - 1U]) / (bp[maxIndex] - bp[maxIndex - 1U]);
  }

  return bpIndex;
}

uint32_T binsearch_u32d(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T bpIdx;

  /* Binary Search */
  bpIdx = startIndex;
  iLeft = 0U;
  iRght = maxIndex;
  while (iRght - iLeft > 1U) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      iLeft = bpIdx;
    }

    bpIdx = (iRght + iLeft) >> 1U;
  }

  return iLeft;
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 8;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  BoatModele_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  BoatModele_step();
  BoatModele_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  BoatModele_step();
  BoatModele_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
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

    y = atan2((real_T)u0_0, (real_T)u1_0);
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

real_T rt_roundd_snf(real_T u)
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
static void BoatModele_mldivide(const real_T A[16], real_T B[4])
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

/* Model step function */
void BoatModele_step(void)
{
  /* local block i/o variables */
  real_T rtb_Integrator[8];
  real_T rtb_DLookupTable;
  real_T rtb_DLookupTable4;
  real_T rtb_DLookupTable1;
  real_T rtb_DLookupTable5;
  real_T rtb_DLookupTable2;
  real_T rtb_DLookupTable6;
  real_T rtb_attack_sail;
  real_T rtb_attack_rudder;
  real_T rtb_attack_keel;
  real_T alpha_aw;
  real_T delta_s;
  real_T alpha_as;
  real_T v_aku;
  real_T v_akv;
  real_T alpha_ak;
  real_T nu[4];
  real_T Ls;
  real_T Ds;
  real_T alpha_ar;
  real_T Lr;
  real_T Dr;
  real_T Lk;
  real_T D_hull[4];
  real_T eta_dot[4];
  real_T nu_dot[4];
  static const real_T b[16] = { 26870.0, 0.0, 0.0, 0.0, 0.0, 43330.0, -13160.0,
    -6190.0, 0.0, -13160.0, 240190.0, 2550.0, 0.0, -6190.0, 2550.0, 126410.0 };

  static const real_T c[16] = { -26870.0, -0.0, -0.0, -0.0, -0.0, -43330.0,
    13160.0, 6190.0, -0.0, 13160.0, -240190.0, -2550.0, -0.0, 6190.0, -2550.0,
    -126410.0 };

  real_T g[4];
  real_T rtb_TmpSignalConversionAtSFunct[12];
  real_T rtb_DLookupTable3;
  int32_T i;
  real_T c_0[9];
  real_T tmp[9];
  real_T c_1[9];
  real_T c_2[3];
  real_T e[9];
  real_T tmp_0[9];
  int32_T i_0;
  real_T tmp_1[16];
  real_T tmp_2[16];
  real_T tmp_3[16];
  real_T tmp_4[4];
  real_T tmp_5[4];
  real_T V_awb_idx_1;
  if (rtmIsMajorTimeStep(BoatModele_M)) {
    /* set solver stop time */
    if (!(BoatModele_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&BoatModele_M->solverInfo,
                            ((BoatModele_M->Timing.clockTickH0 + 1) *
        BoatModele_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&BoatModele_M->solverInfo,
                            ((BoatModele_M->Timing.clockTick0 + 1) *
        BoatModele_M->Timing.stepSize0 + BoatModele_M->Timing.clockTickH0 *
        BoatModele_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(BoatModele_M)) {
    BoatModele_M->Timing.t[0] = rtsiGetT(&BoatModele_M->solverInfo);
  }

  /* Integrator: '<S1>/Integrator' */
  if (BoatModele_DW.Integrator_IWORK.IcNeedsLoading) {
    {
      int_T i1;
      real_T *xc = &BoatModele_X.Integrator_CSTATE[0];
      const real_T *u1 = &BoatModele_U.X_0[0];
      for (i1=0; i1 < 8; i1++) {
        xc[i1] = u1[i1];
      }
    }
  }

  {
    int_T i1;
    real_T *y0 = &rtb_Integrator[0];
    real_T *xc = &BoatModele_X.Integrator_CSTATE[0];
    for (i1=0; i1 < 8; i1++) {
      y0[i1] = xc[i1];
    }
  }

  /* SignalConversion: '<S3>/TmpSignal ConversionAt SFunction Inport1' incorporates:
   *  Inport: '<Root>/U'
   *  MATLAB Function: '<S1>/MATLAB Function1'
   */
  rtb_TmpSignalConversionAtSFunct[0] = BoatModele_U.U[0];
  rtb_TmpSignalConversionAtSFunct[1] = BoatModele_U.U[1];
  rtb_TmpSignalConversionAtSFunct[3] = BoatModele_U.U[3];
  for (i = 0; i < 8; i++) {
    /* Outport: '<Root>/X' */
    BoatModele_Y.X[i] = rtb_Integrator[i];
    rtb_TmpSignalConversionAtSFunct[i + 4] = rtb_Integrator[i];
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
  /*  retrieve the system state from the field input vector "V_in" */
  /* '<S3>:1:25' */
  /* '<S3>:1:26' */
  /* '<S3>:1:27' */
  /* '<S3>:1:28' */
  /* '<S3>:1:29' */
  /* '<S3>:1:30' */
  /*  retrieve the input signals from the vector "V_in" */
  /* '<S3>:1:34' */
  /* '<S3>:1:35' */
  /* '<S3>:1:37' */
  /*  evaluate the matrix M and C in the model */
  /*  calculate the tau vector, ie forces and moments generated from: */
  /*  the sail */
  /* '<S3>:1:52' */
  alpha_as = log(11.58 * cos(rtb_TmpSignalConversionAtSFunct[6]) / 0.0005) /
    10.050181931686932;

  /* '<S3>:1:53' */
  /* '<S3>:1:54' */
  /* '<S3>:1:55' */
  /*  wind expressed in the body frame */
  /* '<S3>:1:56' */
  /* '<S3>:1:57' */
  c_0[0] = 1.0;
  c_0[3] = 0.0;
  c_0[6] = 0.0;
  c_0[1] = 0.0;
  c_0[4] = cos(-rtb_TmpSignalConversionAtSFunct[6]);
  c_0[7] = -sin(-rtb_TmpSignalConversionAtSFunct[6]);
  c_0[2] = 0.0;
  c_0[5] = sin(-rtb_TmpSignalConversionAtSFunct[6]);
  c_0[8] = cos(-rtb_TmpSignalConversionAtSFunct[6]);
  tmp[0] = cos(-rtb_TmpSignalConversionAtSFunct[7]);
  tmp[3] = -sin(-rtb_TmpSignalConversionAtSFunct[7]);
  tmp[6] = 0.0;
  tmp[1] = sin(-rtb_TmpSignalConversionAtSFunct[7]);
  tmp[4] = cos(-rtb_TmpSignalConversionAtSFunct[7]);
  tmp[7] = 0.0;
  tmp[2] = 0.0;
  tmp[5] = 0.0;
  tmp[8] = 1.0;
  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      c_1[i + 3 * i_0] = 0.0;
      c_1[i + 3 * i_0] += tmp[3 * i_0] * c_0[i];
      c_1[i + 3 * i_0] += tmp[3 * i_0 + 1] * c_0[i + 3];
      c_1[i + 3 * i_0] += tmp[3 * i_0 + 2] * c_0[i + 6];
    }
  }

  for (i = 0; i < 3; i++) {
    c_2[i] = c_1[i + 6] * (alpha_as * 0.0) + (c_1[i + 3] * (alpha_as *
      1.2246467991473533E-15) + alpha_as * -10.0 * c_1[i]);
  }

  /* '<S3>:1:58' */
  /* '<S3>:1:59' */
  /* '<S3>:1:60' */
  alpha_aw = rt_atan2d_snf((c_2[1] - rtb_TmpSignalConversionAtSFunct[9]) -
    (rtb_TmpSignalConversionAtSFunct[11] * 0.0 -
     rtb_TmpSignalConversionAtSFunct[10] * -11.58), -((c_2[0] -
    rtb_TmpSignalConversionAtSFunct[8]) - (-0.0 -
    rtb_TmpSignalConversionAtSFunct[11] * 0.0)));

  /* % (sail luffing or not) */
  if (alpha_aw - rtb_TmpSignalConversionAtSFunct[3] >
      rtb_TmpSignalConversionAtSFunct[1]) {
    /* '<S3>:1:63' */
    /* '<S3>:1:64' */
    delta_s = rtb_TmpSignalConversionAtSFunct[1];
  } else if (alpha_aw - rtb_TmpSignalConversionAtSFunct[3] <
             -rtb_TmpSignalConversionAtSFunct[1]) {
    /* '<S3>:1:65' */
    /* '<S3>:1:66' */
    delta_s = -rtb_TmpSignalConversionAtSFunct[1];
  } else {
    /* '<S3>:1:68' */
    delta_s = alpha_aw - rtb_TmpSignalConversionAtSFunct[3];
  }

  /* '<S3>:1:70' */
  delta_s += rtb_TmpSignalConversionAtSFunct[3];

  /* '<S3>:1:72' */
  alpha_as = alpha_aw - delta_s;

  /* '<S3>:1:74' */
  rtb_attack_sail = alpha_as;

  /*  fit the input angle of attack into the interval [-pi,pi] */
  if (alpha_as > 3.1415926535897931) {
    /* '<S3>:1:77' */
    /* '<S3>:1:78' */
    alpha_as = (alpha_as + 3.1415926535897931) / 6.2831853071795862;
    if (fabs(alpha_as - rt_roundd_snf(alpha_as)) <= 2.2204460492503131E-16 *
        alpha_as) {
      alpha_as = 0.0;
    } else {
      alpha_as = (alpha_as - floor(alpha_as)) * 6.2831853071795862;
    }

    rtb_attack_sail = alpha_as - 3.1415926535897931;
  } else {
    if (alpha_as < -3.1415926535897931) {
      /* '<S3>:1:80' */
      /* '<S3>:1:81' */
      alpha_as = (alpha_as - 3.1415926535897931) / -6.2831853071795862;
      if (fabs(alpha_as - rt_roundd_snf(alpha_as)) <= 2.2204460492503131E-16 *
          alpha_as) {
        alpha_as = 0.0;
      } else {
        alpha_as = (alpha_as - floor(alpha_as)) * -6.2831853071795862;
      }

      rtb_attack_sail = alpha_as + 3.1415926535897931;
    }
  }

  /* % the rudder */
  /* '<S3>:1:86' */
  /* '<S3>:1:87' */
  /* '<S3>:1:88' */
  /* '<S3>:1:89' */
  alpha_as = rt_atan2d_snf((-rtb_TmpSignalConversionAtSFunct[9] -
    rtb_TmpSignalConversionAtSFunct[11] * -8.2) +
    rtb_TmpSignalConversionAtSFunct[10] * -0.78,
    -(rtb_TmpSignalConversionAtSFunct[11] * 0.0 +
      -rtb_TmpSignalConversionAtSFunct[8])) - rtb_TmpSignalConversionAtSFunct[0];

  /* '<S3>:1:91' */
  rtb_attack_rudder = alpha_as;

  /*  fit the input angle of attack into the interval [-pi,pi] */
  if (alpha_as > 3.1415926535897931) {
    /* '<S3>:1:94' */
    /* '<S3>:1:95' */
    alpha_as = (alpha_as + 3.1415926535897931) / 6.2831853071795862;
    if (fabs(alpha_as - rt_roundd_snf(alpha_as)) <= 2.2204460492503131E-16 *
        alpha_as) {
      alpha_as = 0.0;
    } else {
      alpha_as = (alpha_as - floor(alpha_as)) * 6.2831853071795862;
    }

    rtb_attack_rudder = alpha_as - 3.1415926535897931;
  } else {
    if (alpha_as < -3.1415926535897931) {
      /* '<S3>:1:97' */
      /* '<S3>:1:98' */
      alpha_as = (alpha_as - 3.1415926535897931) / -6.2831853071795862;
      if (fabs(alpha_as - rt_roundd_snf(alpha_as)) <= 2.2204460492503131E-16 *
          alpha_as) {
        alpha_as = 0.0;
      } else {
        alpha_as = (alpha_as - floor(alpha_as)) * -6.2831853071795862;
      }

      rtb_attack_rudder = alpha_as + 3.1415926535897931;
    }
  }

  /* % the keel */
  /* '<S3>:1:103' */
  v_aku = rtb_TmpSignalConversionAtSFunct[11] * 0.0 +
    -rtb_TmpSignalConversionAtSFunct[8];

  /* '<S3>:1:104' */
  v_akv = (-rtb_TmpSignalConversionAtSFunct[9] -
           rtb_TmpSignalConversionAtSFunct[11] * 0.0) +
    rtb_TmpSignalConversionAtSFunct[10] * -0.58;

  /* '<S3>:1:105' */
  alpha_ak = rt_atan2d_snf(v_akv, -v_aku);

  /* '<S3>:1:108' */
  rtb_attack_keel = alpha_ak;

  /*  fit the input angle of attack into the interval [-pi,pi] */
  if (alpha_ak > 3.1415926535897931) {
    /* '<S3>:1:111' */
    /* '<S3>:1:112' */
    alpha_as = (alpha_ak + 3.1415926535897931) / 6.2831853071795862;
    if (fabs(alpha_as - rt_roundd_snf(alpha_as)) <= 2.2204460492503131E-16 *
        alpha_as) {
      alpha_as = 0.0;
    } else {
      alpha_as = (alpha_as - floor(alpha_as)) * 6.2831853071795862;
    }

    rtb_attack_keel = alpha_as - 3.1415926535897931;
  } else {
    if (alpha_ak < -3.1415926535897931) {
      /* '<S3>:1:114' */
      /* '<S3>:1:115' */
      alpha_as = (alpha_ak - 3.1415926535897931) / -6.2831853071795862;
      if (fabs(alpha_as - rt_roundd_snf(alpha_as)) <= 2.2204460492503131E-16 *
          alpha_as) {
        alpha_as = 0.0;
      } else {
        alpha_as = (alpha_as - floor(alpha_as)) * -6.2831853071795862;
      }

      rtb_attack_keel = alpha_as + 3.1415926535897931;
    }
  }

  /* % from the hull */
  /* '<S3>:1:122' */
  /* '<S3>:1:124' */

  /* Lookup_n-D: '<S1>/1-D Lookup Table'
   * About '<S1>/1-D Lookup Table':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable = look_SplNBinXZcd(1U, &rtb_attack_sail, (rt_LUTSplineWork*)
    &BoatModele_DW.SWork[0]);

  /* Lookup_n-D: '<S1>/1-D Lookup Table4'
   * About '<S1>/1-D Lookup Table4':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable4 = look_SplNBinXZcd(1U, &rtb_attack_sail, (rt_LUTSplineWork*)
    &BoatModele_DW.SWork_k[0]);

  /* Lookup_n-D: '<S1>/1-D Lookup Table1'
   * About '<S1>/1-D Lookup Table1':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable1 = look_SplNBinXZcd(1U, &rtb_attack_rudder, (rt_LUTSplineWork*)
    &BoatModele_DW.SWork_j[0]);

  /* Lookup_n-D: '<S1>/1-D Lookup Table5'
   * About '<S1>/1-D Lookup Table5':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable5 = look_SplNBinXZcd(1U, &rtb_attack_rudder, (rt_LUTSplineWork*)
    &BoatModele_DW.SWork_kl[0]);

  /* Lookup_n-D: '<S1>/1-D Lookup Table2'
   * About '<S1>/1-D Lookup Table2':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable2 = look_SplNBinXZcd(1U, &rtb_attack_keel, (rt_LUTSplineWork*)
    &BoatModele_DW.SWork_a[0]);

  /* Lookup_n-D: '<S1>/1-D Lookup Table6'
   * About '<S1>/1-D Lookup Table6':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable6 = look_SplNBinXZcd(1U, &rtb_attack_keel, (rt_LUTSplineWork*)
    &BoatModele_DW.SWork_e[0]);

  /* Lookup_n-D: '<S1>/1-D Lookup Table3' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function1'
   */
  rtb_DLookupTable3 = look1_binlxpw(sqrt(v_aku * v_aku + v_akv * v_akv),
    *(real_T (*)[100])&BoatModele_P.hull_xdata[0], *(real_T (*)[100])&
    BoatModele_P.hull_ydata[0], 99U);

  /* SignalConversion: '<S2>/TmpSignal ConversionAt SFunction Inport1' incorporates:
   *  Inport: '<Root>/U'
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  rtb_TmpSignalConversionAtSFunct[1] = BoatModele_U.U[1];
  rtb_TmpSignalConversionAtSFunct[2] = BoatModele_U.U[2];
  rtb_TmpSignalConversionAtSFunct[3] = BoatModele_U.U[3];
  memcpy(&rtb_TmpSignalConversionAtSFunct[4], &rtb_Integrator[0], sizeof(real_T)
         << 3U);

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
  /*  retrieve the system state from the field input vector "V_in" */
  /* '<S2>:1:25' */
  /* '<S2>:1:26' */
  /* '<S2>:1:27' */
  /* '<S2>:1:28' */
  /* '<S2>:1:29' */
  /* '<S2>:1:30' */
  /* '<S2>:1:31' */
  /*  retrieve the input signals from the vector "V_in" */
  /* '<S2>:1:35' */
  /* '<S2>:1:36' */
  /* '<S2>:1:37' */
  /*  evaluate the matrix M and C in the model */
  /* '<S2>:1:41' */
  /* '<S2>:1:44' */
  /*  calculate the tau vector, ie forces and moments generated from: */
  /*  the sail */
  /* '<S2>:1:51' */
  alpha_as = log(11.58 * cos(rtb_TmpSignalConversionAtSFunct[6]) / 0.0005) /
    10.050181931686932;

  /* '<S2>:1:52' */
  /* '<S2>:1:53' */
  /* '<S2>:1:54' */
  /*  wind expressed in the body frame */
  /* '<S2>:1:55' */
  /* '<S2>:1:56' */
  e[0] = 1.0;
  e[3] = 0.0;
  e[6] = 0.0;
  e[1] = 0.0;
  e[4] = cos(-rtb_TmpSignalConversionAtSFunct[6]);
  e[7] = -sin(-rtb_TmpSignalConversionAtSFunct[6]);
  e[2] = 0.0;
  e[5] = sin(-rtb_TmpSignalConversionAtSFunct[6]);
  e[8] = cos(-rtb_TmpSignalConversionAtSFunct[6]);
  tmp_0[0] = cos(-rtb_TmpSignalConversionAtSFunct[7]);
  tmp_0[3] = -sin(-rtb_TmpSignalConversionAtSFunct[7]);
  tmp_0[6] = 0.0;
  tmp_0[1] = sin(-rtb_TmpSignalConversionAtSFunct[7]);
  tmp_0[4] = cos(-rtb_TmpSignalConversionAtSFunct[7]);
  tmp_0[7] = 0.0;
  tmp_0[2] = 0.0;
  tmp_0[5] = 0.0;
  tmp_0[8] = 1.0;
  for (i = 0; i < 3; i++) {
    for (i_0 = 0; i_0 < 3; i_0++) {
      c_0[i + 3 * i_0] = 0.0;
      c_0[i + 3 * i_0] += tmp_0[3 * i_0] * e[i];
      c_0[i + 3 * i_0] += tmp_0[3 * i_0 + 1] * e[i + 3];
      c_0[i + 3 * i_0] += tmp_0[3 * i_0 + 2] * e[i + 6];
    }
  }

  for (i = 0; i < 3; i++) {
    c_2[i] = c_0[i + 6] * (alpha_as * 0.0) + (c_0[i + 3] * (alpha_as *
      1.2246467991473533E-15) + alpha_as * -10.0 * c_0[i]);
  }

  v_akv = (c_2[0] - rtb_TmpSignalConversionAtSFunct[8]) - (-0.0 -
    rtb_TmpSignalConversionAtSFunct[11] * 0.0);
  V_awb_idx_1 = (c_2[1] - rtb_TmpSignalConversionAtSFunct[9]) -
    (rtb_TmpSignalConversionAtSFunct[11] * 0.0 -
     rtb_TmpSignalConversionAtSFunct[10] * -11.58);

  /* '<S2>:1:57' */
  /* '<S2>:1:58' */
  /* '<S2>:1:59' */
  alpha_aw = rt_atan2d_snf(V_awb_idx_1, -v_akv);

  /*  (sail luffing or not) */
  if (alpha_aw - rtb_TmpSignalConversionAtSFunct[3] >
      rtb_TmpSignalConversionAtSFunct[1]) {
    /* '<S2>:1:62' */
    /* '<S2>:1:63' */
    delta_s = rtb_TmpSignalConversionAtSFunct[1];
  } else if (alpha_aw - rtb_TmpSignalConversionAtSFunct[3] <
             -rtb_TmpSignalConversionAtSFunct[1]) {
    /* '<S2>:1:64' */
    /* '<S2>:1:65' */
    delta_s = -rtb_TmpSignalConversionAtSFunct[1];
  } else {
    /* '<S2>:1:67' */
    delta_s = alpha_aw - rtb_TmpSignalConversionAtSFunct[3];
  }

  /* '<S2>:1:69' */
  delta_s += rtb_TmpSignalConversionAtSFunct[3];

  /* '<S2>:1:76' */
  Ls = (v_akv * v_akv + V_awb_idx_1 * V_awb_idx_1) * 102.0 * rtb_DLookupTable;

  /* '<S2>:1:77' */
  Ds = (v_akv * v_akv + V_awb_idx_1 * V_awb_idx_1) * 102.0 * rtb_DLookupTable4;

  /* '<S2>:1:79' */
  /*  the rudder */
  /* '<S2>:1:83' */
  alpha_as = rtb_TmpSignalConversionAtSFunct[11] * 0.0 +
    -rtb_TmpSignalConversionAtSFunct[8];

  /* '<S2>:1:84' */
  v_aku = (-rtb_TmpSignalConversionAtSFunct[9] -
           rtb_TmpSignalConversionAtSFunct[11] * -8.2) +
    rtb_TmpSignalConversionAtSFunct[10] * -0.78;

  /* '<S2>:1:85' */
  alpha_ar = rt_atan2d_snf(v_aku, -alpha_as);

  /* [Clr,Cdr] = ruddercoef(alpha_a); */
  /* '<S2>:1:92' */
  /* '<S2>:1:94' */
  Lr = (alpha_as * alpha_as + v_aku * v_aku) * 599.625 * rtb_DLookupTable1;

  /* '<S2>:1:95' */
  Dr = (rtb_DLookupTable1 * rtb_DLookupTable1 * 1.17 / 18.145839167134646 +
        rtb_DLookupTable5) * ((alpha_as * alpha_as + v_aku * v_aku) * 599.625);

  /* '<S2>:1:97' */
  /*  the tau vector is finally given by: */
  /* '<S2>:1:101' */
  /*  calculate the damping forces and moments: */
  /*  from the keel */
  /* '<S2>:1:105' */
  v_aku = rtb_TmpSignalConversionAtSFunct[11] * 0.0 +
    -rtb_TmpSignalConversionAtSFunct[8];

  /* '<S2>:1:106' */
  v_akv = (-rtb_TmpSignalConversionAtSFunct[9] -
           rtb_TmpSignalConversionAtSFunct[11] * 0.0) +
    rtb_TmpSignalConversionAtSFunct[10] * -0.58;

  /* '<S2>:1:107' */
  alpha_ak = rt_atan2d_snf(v_akv, -v_aku);

  /* '<S2>:1:113' */
  /* '<S2>:1:115' */
  Lk = (v_aku * v_aku + v_akv * v_akv) * 4458.75 * rtb_DLookupTable2;

  /* '<S2>:1:116' */
  alpha_as = (rtb_DLookupTable2 * rtb_DLookupTable2 * 8.7 / 27.269464056130911 +
              rtb_DLookupTable6) * ((v_aku * v_aku + v_akv * v_akv) * 4458.75);

  /* '<S2>:1:118' */
  /*  from the hull */
  /* '<S2>:1:121' */
  /* '<S2>:1:122' */
  /* '<S2>:1:124' */
  v_aku = rt_atan2d_snf(((-rtb_TmpSignalConversionAtSFunct[9] -
    rtb_TmpSignalConversionAtSFunct[11] * 0.0) +
    rtb_TmpSignalConversionAtSFunct[10] * -1.18) / cos
                        (rtb_TmpSignalConversionAtSFunct[6]),
                        -(rtb_TmpSignalConversionAtSFunct[11] * 0.0 +
    -rtb_TmpSignalConversionAtSFunct[8]));

  /* '<S2>:1:128' */
  /*  from heel and yaw */
  /*  (compute first eta_dot and thereby phi_dot and psi_dot) */
  /* '<S2>:1:132' */
  /* '<S2>:1:133' */
  tmp_1[0] = cos(rtb_TmpSignalConversionAtSFunct[7]);
  tmp_1[4] = -sin(rtb_TmpSignalConversionAtSFunct[7]) * cos
    (rtb_TmpSignalConversionAtSFunct[6]);
  tmp_1[8] = 0.0;
  tmp_1[12] = 0.0;
  tmp_1[1] = sin(rtb_TmpSignalConversionAtSFunct[7]);
  tmp_1[5] = cos(rtb_TmpSignalConversionAtSFunct[7]) * cos
    (rtb_TmpSignalConversionAtSFunct[6]);
  tmp_1[9] = 0.0;
  tmp_1[13] = 0.0;
  tmp_1[2] = 0.0;
  tmp_1[6] = 0.0;
  tmp_1[10] = 1.0;
  tmp_1[14] = 0.0;
  tmp_1[3] = 0.0;
  tmp_1[7] = 0.0;
  tmp_1[11] = 0.0;
  tmp_1[15] = cos(rtb_TmpSignalConversionAtSFunct[6]);
  for (i = 0; i < 4; i++) {
    v_akv = tmp_1[i + 12] * rtb_TmpSignalConversionAtSFunct[11] + (tmp_1[i + 8] *
      rtb_TmpSignalConversionAtSFunct[10] + (tmp_1[i + 4] *
      rtb_TmpSignalConversionAtSFunct[9] + tmp_1[i] *
      rtb_TmpSignalConversionAtSFunct[8]));
    eta_dot[i] = v_akv;
  }

  /* '<S2>:1:134' */
  /* '<S2>:1:135' */
  /* '<S2>:1:137' */
  /*  compute total damping vector D */
  /* '<S2>:1:140' */
  /*  righting moment plus internal moving mass system (ie transversal weight) */
  /* '<S2>:1:143' */
  v_akv = rtb_TmpSignalConversionAtSFunct[6] * 180.0 / 3.1415926535897931;

  /* '<S2>:1:144' */
  /* '<S2>:1:145' */
  /* '<S2>:1:146' */
  /*  computation of nu_dot */
  /* '<S2>:1:149' */
  tmp_2[0] = 0.0;
  tmp_2[4] = -25900.0 * rtb_TmpSignalConversionAtSFunct[11];
  tmp_2[8] = 0.0;
  tmp_2[12] = 0.0;
  tmp_2[1] = 25900.0 * rtb_TmpSignalConversionAtSFunct[11];
  tmp_2[5] = 0.0;
  tmp_2[9] = 0.0;
  tmp_2[13] = 0.0;
  tmp_2[2] = 0.0;
  tmp_2[6] = 0.0;
  tmp_2[10] = 0.0;
  tmp_2[14] = 0.0;
  tmp_2[3] = 0.0;
  tmp_2[7] = 0.0;
  tmp_2[11] = 0.0;
  tmp_2[15] = 0.0;
  tmp_3[0] = 0.0;
  tmp_3[4] = 0.0;
  tmp_3[8] = 0.0;
  tmp_3[12] = (-17430.0 * rtb_TmpSignalConversionAtSFunct[9] - -13160.0 *
               rtb_TmpSignalConversionAtSFunct[10]) - -6190.0 *
    rtb_TmpSignalConversionAtSFunct[11];
  tmp_3[1] = 0.0;
  tmp_3[5] = 0.0;
  tmp_3[9] = 0.0;
  tmp_3[13] = 970.0 * rtb_TmpSignalConversionAtSFunct[8];
  tmp_3[2] = 0.0;
  tmp_3[6] = 0.0;
  tmp_3[10] = 0.0;
  tmp_3[14] = 0.0;
  tmp_3[3] = (17430.0 * rtb_TmpSignalConversionAtSFunct[9] + -13160.0 *
              rtb_TmpSignalConversionAtSFunct[10]) + -6190.0 *
    rtb_TmpSignalConversionAtSFunct[11];
  tmp_3[7] = -970.0 * rtb_TmpSignalConversionAtSFunct[8];
  tmp_3[11] = 0.0;
  tmp_3[15] = 0.0;
  for (i = 0; i < 4; i++) {
    V_awb_idx_1 = tmp_2[i + 12] * rtb_TmpSignalConversionAtSFunct[11] + (tmp_2[i
      + 8] * rtb_TmpSignalConversionAtSFunct[10] + (tmp_2[i + 4] *
      rtb_TmpSignalConversionAtSFunct[9] + tmp_2[i] *
      rtb_TmpSignalConversionAtSFunct[8]));
    tmp_4[i] = V_awb_idx_1;
  }

  for (i = 0; i < 4; i++) {
    V_awb_idx_1 = tmp_3[i + 12] * rtb_TmpSignalConversionAtSFunct[11] + (tmp_3[i
      + 8] * rtb_TmpSignalConversionAtSFunct[10] + (tmp_3[i + 4] *
      rtb_TmpSignalConversionAtSFunct[9] + tmp_3[i] *
      rtb_TmpSignalConversionAtSFunct[8]));
    tmp_5[i] = V_awb_idx_1;
  }

  nu_dot[0] = tmp_4[0] + tmp_5[0];
  nu_dot[1] = tmp_4[1] + tmp_5[1];
  nu_dot[2] = tmp_4[2] + tmp_5[2];
  nu_dot[3] = tmp_4[3] + tmp_5[3];
  BoatModele_mldivide(c, nu_dot);
  g[0] = (-Lk * sin(alpha_ak) + alpha_as * cos(alpha_ak)) + rtb_DLookupTable3 *
    cos(v_aku);
  g[1] = (-Lk * cos(alpha_ak) - alpha_as * sin(alpha_ak)) + -rtb_DLookupTable3 *
    sin(v_aku) * cos(rtb_TmpSignalConversionAtSFunct[6]);
  g[2] = (-(-Lk * cos(alpha_ak) - alpha_as * sin(alpha_ak)) * -0.58 +
          rtb_DLookupTable3 * sin(v_aku) * cos(rtb_TmpSignalConversionAtSFunct[6])
          * -1.18) + 120000.0 * eta_dot[2] * fabs(eta_dot[2]);
  g[3] = (-(Lk * cos(alpha_ak) + alpha_as * sin(alpha_ak)) * 0.0 +
          -rtb_DLookupTable3 * sin(v_aku) * cos(rtb_TmpSignalConversionAtSFunct
           [6]) * 0.0) + 50000.0 * eta_dot[3] * fabs(eta_dot[3]) * cos
    (rtb_TmpSignalConversionAtSFunct[6]);
  BoatModele_mldivide(b, g);
  nu[0] = 0.0;
  nu[1] = 0.0;
  nu[2] = (v_akv * v_akv * -5.89 + 8160.0 * v_akv) +
    -rtb_TmpSignalConversionAtSFunct[2] * 60000.0 * 3.6 * cos
    (rtb_TmpSignalConversionAtSFunct[6]);
  nu[3] = -rtb_TmpSignalConversionAtSFunct[2] * 60000.0 * -8.0 * sin(fabs
    (rtb_TmpSignalConversionAtSFunct[6]));
  BoatModele_mldivide(b, nu);
  D_hull[0] = (Ls * sin(alpha_aw) - Ds * cos(alpha_aw)) + (Lr * sin(alpha_ar) -
    Dr * cos(alpha_ar));
  D_hull[1] = (Ls * cos(alpha_aw) + Ds * sin(alpha_aw)) + (Lr * cos(alpha_ar) +
    Dr * sin(alpha_ar));
  D_hull[2] = -(Ls * cos(alpha_aw) + Ds * sin(alpha_aw)) * -11.58 + -(Lr * cos
    (alpha_ar) + Dr * sin(alpha_ar)) * -0.78;
  D_hull[3] = (-(Ls * sin(alpha_aw) - Ds * cos(alpha_aw)) * 0.6 * sin(delta_s) +
               (Ls * cos(alpha_aw) + Ds * sin(alpha_aw)) * (0.3 - 0.6 * cos
    (delta_s))) + (Lr * cos(alpha_ar) + Dr * sin(alpha_ar)) * -8.2;
  BoatModele_mldivide(b, D_hull);
  nu_dot[0] = ((nu_dot[0] - g[0]) - nu[0]) + D_hull[0];
  nu_dot[1] = ((nu_dot[1] - g[1]) - nu[1]) + D_hull[1];
  nu_dot[2] = ((nu_dot[2] - g[2]) - nu[2]) + D_hull[2];

  /*  output the derivative of the state extended with the sail angle */
  /* '<S2>:1:153' */
  BoatModele_B.X_dot_ext[0] = eta_dot[0];
  BoatModele_B.X_dot_ext[1] = eta_dot[1];
  BoatModele_B.X_dot_ext[2] = eta_dot[2];
  BoatModele_B.X_dot_ext[3] = eta_dot[3];
  BoatModele_B.X_dot_ext[4] = nu_dot[0];
  BoatModele_B.X_dot_ext[5] = nu_dot[1];
  BoatModele_B.X_dot_ext[6] = nu_dot[2];
  BoatModele_B.X_dot_ext[7] = ((nu_dot[3] - g[3]) - nu[3]) + D_hull[3];
  BoatModele_B.X_dot_ext[8] = delta_s;

  /* Outport: '<Root>/delta_s' */
  BoatModele_Y.delta_s = BoatModele_B.X_dot_ext[8];
  if (rtmIsMajorTimeStep(BoatModele_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(BoatModele_M->rtwLogInfo, (BoatModele_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(BoatModele_M)) {
    /* Update for Integrator: '<S1>/Integrator' */
    BoatModele_DW.Integrator_IWORK.IcNeedsLoading = 0;
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(BoatModele_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(BoatModele_M)!=-1) &&
          !((rtmGetTFinal(BoatModele_M)-(((BoatModele_M->Timing.clockTick1+
               BoatModele_M->Timing.clockTickH1* 4294967296.0)) * 0.1)) >
            (((BoatModele_M->Timing.clockTick1+BoatModele_M->Timing.clockTickH1*
               4294967296.0)) * 0.1) * (DBL_EPSILON))) {
        rtmSetErrorStatus(BoatModele_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&BoatModele_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++BoatModele_M->Timing.clockTick0)) {
      ++BoatModele_M->Timing.clockTickH0;
    }

    BoatModele_M->Timing.t[0] = rtsiGetSolverStopTime(&BoatModele_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.1s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.1, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      BoatModele_M->Timing.clockTick1++;
      if (!BoatModele_M->Timing.clockTick1) {
        BoatModele_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void BoatModele_derivatives(void)
{
  /* Derivatives for Integrator: '<S1>/Integrator' */
  {
    {
      int_T i1;
      const real_T *u0 = &BoatModele_B.X_dot_ext[0];
      real_T *xdot = &((XDot_BoatModele_T *) BoatModele_M->ModelData.derivs)
        ->Integrator_CSTATE[0];
      for (i1=0; i1 < 8; i1++) {
        xdot[i1] = u0[i1];
      }
    }
  }
}

/* Model initialize function */
void BoatModele_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)BoatModele_M, 0,
                sizeof(RT_MODEL_BoatModele_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&BoatModele_M->solverInfo,
                          &BoatModele_M->Timing.simTimeStep);
    rtsiSetTPtr(&BoatModele_M->solverInfo, &rtmGetTPtr(BoatModele_M));
    rtsiSetStepSizePtr(&BoatModele_M->solverInfo,
                       &BoatModele_M->Timing.stepSize0);
    rtsiSetdXPtr(&BoatModele_M->solverInfo, &BoatModele_M->ModelData.derivs);
    rtsiSetContStatesPtr(&BoatModele_M->solverInfo, (real_T **)
                         &BoatModele_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&BoatModele_M->solverInfo,
      &BoatModele_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&BoatModele_M->solverInfo, (&rtmGetErrorStatus
      (BoatModele_M)));
    rtsiSetRTModelPtr(&BoatModele_M->solverInfo, BoatModele_M);
  }

  rtsiSetSimTimeStep(&BoatModele_M->solverInfo, MAJOR_TIME_STEP);
  BoatModele_M->ModelData.intgData.y = BoatModele_M->ModelData.odeY;
  BoatModele_M->ModelData.intgData.f[0] = BoatModele_M->ModelData.odeF[0];
  BoatModele_M->ModelData.intgData.f[1] = BoatModele_M->ModelData.odeF[1];
  BoatModele_M->ModelData.intgData.f[2] = BoatModele_M->ModelData.odeF[2];
  BoatModele_M->ModelData.contStates = ((X_BoatModele_T *) &BoatModele_X);
  rtsiSetSolverData(&BoatModele_M->solverInfo, (void *)
                    &BoatModele_M->ModelData.intgData);
  rtsiSetSolverName(&BoatModele_M->solverInfo,"ode3");
  rtmSetTPtr(BoatModele_M, &BoatModele_M->Timing.tArray[0]);
  rtmSetTFinal(BoatModele_M, 10.0);
  BoatModele_M->Timing.stepSize0 = 0.1;
  rtmSetFirstInitCond(BoatModele_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    BoatModele_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(BoatModele_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(BoatModele_M->rtwLogInfo, (NULL));
    rtliSetLogT(BoatModele_M->rtwLogInfo, "tout");
    rtliSetLogX(BoatModele_M->rtwLogInfo, "");
    rtliSetLogXFinal(BoatModele_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(BoatModele_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(BoatModele_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(BoatModele_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(BoatModele_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &BoatModele_Y.X[0],
        &BoatModele_Y.delta_s
      };

      rtliSetLogYSignalPtrs(BoatModele_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        8,
        1
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1,
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        8,
        1
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0,
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL),
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4,
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0,
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "",
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "BoatModele/X",
        "BoatModele/delta_s" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          2,
          rt_LoggedOutputWidths,
          rt_LoggedOutputNumDimensions,
          rt_LoggedOutputDimensions,
          rt_LoggedOutputIsVarDims,
          rt_LoggedCurrentSignalDimensions,
          rt_LoggedCurrentSignalDimensionsSize,
          rt_LoggedOutputDataTypeIds,
          rt_LoggedOutputComplexSignals,
          (NULL),

          { rt_LoggedOutputLabels },
          (NULL),
          (NULL),
          (NULL),

          { rt_LoggedOutputBlockNames },

          { (NULL) },
          (NULL),
          rt_RTWLogDataTypeConvert
        }
      };

      rtliSetLogYSignalInfo(BoatModele_M->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
    }

    rtliSetLogY(BoatModele_M->rtwLogInfo, "yout");
  }

  /* block I/O */
  (void) memset(((void *) &BoatModele_B), 0,
                sizeof(B_BoatModele_T));

  /* states (continuous) */
  {
    (void) memset((void *)&BoatModele_X, 0,
                  sizeof(X_BoatModele_T));
  }

  /* states (dwork) */
  (void) memset((void *)&BoatModele_DW, 0,
                sizeof(DW_BoatModele_T));

  /* external inputs */
  (void) memset((void *)&BoatModele_U, 0,
                sizeof(ExtU_BoatModele_T));

  /* external outputs */
  (void) memset((void *)&BoatModele_Y, 0,
                sizeof(ExtY_BoatModele_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(BoatModele_M->rtwLogInfo, 0.0, rtmGetTFinal
    (BoatModele_M), BoatModele_M->Timing.stepSize0, (&rtmGetErrorStatus
    (BoatModele_M)));

  /* Start for Lookup_n-D: '<S1>/1-D Lookup Table' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatModele_DW.TWork[0];
    void **bpDataSet = (void **) &BoatModele_DW.m_bpDataSet;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatModele_P.DLookupTable_dimSizes;
    TWork_start->m_tableData = (void *) BoatModele_P.alphacoeff_yldata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatModele_DW.m_bpIndex;
    TWork_start->m_bpLambda = (void *) &BoatModele_DW.m_bpLambda;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatModele_P.DLookupTable_maxIndex;
    bpDataSet[0] = (void *)BoatModele_P.alphacoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatModele_DW.SWork[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatModele_DW.TWork[0];
    rt_SplWk->m_yyA = &BoatModele_DW.m_yyA;
    rt_SplWk->m_yyB = &BoatModele_DW.m_yyB;
    rt_SplWk->m_yy2 = &BoatModele_DW.m_yy2;
    rt_SplWk->m_up = &BoatModele_DW.m_up[0];
    rt_SplWk->m_y2 = &BoatModele_DW.m_y2[0];
    rt_SplWk->m_numYWorkElts = BoatModele_P.DLookupTable_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<S1>/1-D Lookup Table4' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatModele_DW.TWork_a[0];
    void **bpDataSet = (void **) &BoatModele_DW.m_bpDataSet_c;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatModele_P.DLookupTable4_dimSizes;
    TWork_start->m_tableData = (void *) BoatModele_P.alphacoeff_yddata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatModele_DW.m_bpIndex_n;
    TWork_start->m_bpLambda = (void *) &BoatModele_DW.m_bpLambda_n;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatModele_P.DLookupTable4_maxIndex;
    bpDataSet[0] = (void *)BoatModele_P.alphacoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatModele_DW.SWork_k[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatModele_DW.TWork_a[0];
    rt_SplWk->m_yyA = &BoatModele_DW.m_yyA_i;
    rt_SplWk->m_yyB = &BoatModele_DW.m_yyB_l;
    rt_SplWk->m_yy2 = &BoatModele_DW.m_yy2_k;
    rt_SplWk->m_up = &BoatModele_DW.m_up_f[0];
    rt_SplWk->m_y2 = &BoatModele_DW.m_y2_c[0];
    rt_SplWk->m_numYWorkElts = BoatModele_P.DLookupTable4_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<S1>/1-D Lookup Table1' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatModele_DW.TWork_c[0];
    void **bpDataSet = (void **) &BoatModele_DW.m_bpDataSet_j;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatModele_P.DLookupTable1_dimSizes;
    TWork_start->m_tableData = (void *) BoatModele_P.ruddercoeff_yldata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatModele_DW.m_bpIndex_a;
    TWork_start->m_bpLambda = (void *) &BoatModele_DW.m_bpLambda_k;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatModele_P.DLookupTable1_maxIndex;
    bpDataSet[0] = (void *)BoatModele_P.ruddercoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatModele_DW.SWork_j[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatModele_DW.TWork_c[0];
    rt_SplWk->m_yyA = &BoatModele_DW.m_yyA_n;
    rt_SplWk->m_yyB = &BoatModele_DW.m_yyB_e;
    rt_SplWk->m_yy2 = &BoatModele_DW.m_yy2_j;
    rt_SplWk->m_up = &BoatModele_DW.m_up_g[0];
    rt_SplWk->m_y2 = &BoatModele_DW.m_y2_cz[0];
    rt_SplWk->m_numYWorkElts = BoatModele_P.DLookupTable1_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<S1>/1-D Lookup Table5' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatModele_DW.TWork_d[0];
    void **bpDataSet = (void **) &BoatModele_DW.m_bpDataSet_g;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatModele_P.DLookupTable5_dimSizes;
    TWork_start->m_tableData = (void *) BoatModele_P.ruddercoeff_yddata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatModele_DW.m_bpIndex_j;
    TWork_start->m_bpLambda = (void *) &BoatModele_DW.m_bpLambda_g;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatModele_P.DLookupTable5_maxIndex;
    bpDataSet[0] = (void *)BoatModele_P.ruddercoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatModele_DW.SWork_kl[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatModele_DW.TWork_d[0];
    rt_SplWk->m_yyA = &BoatModele_DW.m_yyA_l;
    rt_SplWk->m_yyB = &BoatModele_DW.m_yyB_i;
    rt_SplWk->m_yy2 = &BoatModele_DW.m_yy2_n;
    rt_SplWk->m_up = &BoatModele_DW.m_up_n[0];
    rt_SplWk->m_y2 = &BoatModele_DW.m_y2_g[0];
    rt_SplWk->m_numYWorkElts = BoatModele_P.DLookupTable5_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<S1>/1-D Lookup Table2' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatModele_DW.TWork_m[0];
    void **bpDataSet = (void **) &BoatModele_DW.m_bpDataSet_h;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatModele_P.DLookupTable2_dimSizes;
    TWork_start->m_tableData = (void *) BoatModele_P.keelcoeff_yldata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatModele_DW.m_bpIndex_jk;
    TWork_start->m_bpLambda = (void *) &BoatModele_DW.m_bpLambda_kf;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatModele_P.DLookupTable2_maxIndex;
    bpDataSet[0] = (void *)BoatModele_P.keelcoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatModele_DW.SWork_a[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatModele_DW.TWork_m[0];
    rt_SplWk->m_yyA = &BoatModele_DW.m_yyA_nz;
    rt_SplWk->m_yyB = &BoatModele_DW.m_yyB_ex;
    rt_SplWk->m_yy2 = &BoatModele_DW.m_yy2_c;
    rt_SplWk->m_up = &BoatModele_DW.m_up_k[0];
    rt_SplWk->m_y2 = &BoatModele_DW.m_y2_a[0];
    rt_SplWk->m_numYWorkElts = BoatModele_P.DLookupTable2_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<S1>/1-D Lookup Table6' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatModele_DW.TWork_i[0];
    void **bpDataSet = (void **) &BoatModele_DW.m_bpDataSet_n;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatModele_P.DLookupTable6_dimSizes;
    TWork_start->m_tableData = (void *) BoatModele_P.keelcoeff_yddata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatModele_DW.m_bpIndex_b;
    TWork_start->m_bpLambda = (void *) &BoatModele_DW.m_bpLambda_h;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatModele_P.DLookupTable6_maxIndex;
    bpDataSet[0] = (void *)BoatModele_P.keelcoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatModele_DW.SWork_e[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatModele_DW.TWork_i[0];
    rt_SplWk->m_yyA = &BoatModele_DW.m_yyA_c;
    rt_SplWk->m_yyB = &BoatModele_DW.m_yyB_i5;
    rt_SplWk->m_yy2 = &BoatModele_DW.m_yy2_h;
    rt_SplWk->m_up = &BoatModele_DW.m_up_o[0];
    rt_SplWk->m_y2 = &BoatModele_DW.m_y2_f[0];
    rt_SplWk->m_numYWorkElts = BoatModele_P.DLookupTable6_numYWorkElts;
  }

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  if (rtmIsFirstInitCond(BoatModele_M)) {
    BoatModele_X.Integrator_CSTATE[0] = 0.0;
    BoatModele_X.Integrator_CSTATE[1] = 0.0;
    BoatModele_X.Integrator_CSTATE[2] = 0.0;
    BoatModele_X.Integrator_CSTATE[3] = 0.0;
    BoatModele_X.Integrator_CSTATE[4] = 0.0;
    BoatModele_X.Integrator_CSTATE[5] = 0.0;
    BoatModele_X.Integrator_CSTATE[6] = 0.0;
    BoatModele_X.Integrator_CSTATE[7] = 0.0;
  }

  BoatModele_DW.Integrator_IWORK.IcNeedsLoading = 1;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(BoatModele_M)) {
    rtmSetFirstInitCond(BoatModele_M, 0);
  }
}

/* Model terminate function */
void BoatModele_terminate(void)
{
  /* (no terminate code required) */
}
