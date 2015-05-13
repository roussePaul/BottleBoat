/*
 * BoatDynamic.c
 *
 * Code generation for model "BoatDynamic".
 *
 * Model version              : 1.5
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Mon May  4 11:09:21 2015
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "BoatDynamic.h"
#include "BoatDynamic_private.h"

/* Block states (auto storage) */
DW_BoatDynamic_T BoatDynamic_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_BoatDynamic_T BoatDynamic_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_BoatDynamic_T BoatDynamic_Y;

/* Real-time model */
RT_MODEL_BoatDynamic_T BoatDynamic_M_;
RT_MODEL_BoatDynamic_T *const BoatDynamic_M = &BoatDynamic_M_;

/* Forward declaration for local functions */
static void BoatDynamic_mldivide(const real_T A[16], real_T B[4]);

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
  if (u0 <= bp0[0UL]) {
    iLeft = 0UL;
    frac = (u0 - bp0[0UL]) / (bp0[1UL] - bp0[0UL]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1UL;
    iLeft = 0UL;
    iRght = maxIndex;
    while (iRght - iLeft > 1UL) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1UL;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1UL] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1UL;
    frac = (u0 - bp0[maxIndex - 1UL]) / (bp0[maxIndex] - bp0[maxIndex - 1UL]);
  }

  /* Interpolation 1-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  return (table[iLeft + 1UL] - table[iLeft]) * frac + table[iLeft];
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
  if (u <= bp[0UL]) {
    bpIndex = 0UL;
    *fraction = (u - bp[0UL]) / (bp[1UL] - bp[0UL]);
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d(u, bp, maxIndex >> 1UL, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1UL] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex - 1UL;
    *fraction = (u - bp[maxIndex - 1UL]) / (bp[maxIndex] - bp[maxIndex - 1UL]);
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
  iLeft = 0UL;
  iRght = maxIndex;
  while (iRght - iLeft > 1UL) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      iLeft = bpIdx;
    }

    bpIdx = (iRght + iLeft) >> 1UL;
  }

  return iLeft;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int16_T u0_0;
  int16_T u1_0;
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

/* Function for MATLAB Function: '<Root>/MATLAB Function' */
static void BoatDynamic_mldivide(const real_T A[16], real_T B[4])
{
  real_T temp;
  real_T b_A[16];
  int8_T ipiv[4];
  int16_T j;
  int16_T c;
  int16_T ix;
  real_T s;
  int16_T jy;
  int16_T c_ix;
  int16_T d;
  int16_T ijA;
  int16_T b_kAcol;
  memcpy(&b_A[0L], &A[0L], sizeof(real_T) << 4U);
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
void BoatDynamic_step(void)
{
  /* local block i/o variables */
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
  real_T phi;
  real_T nu[4];
  real_T M[16];
  real_T Ls;
  real_T Ds;
  real_T alpha_ar;
  real_T Lr;
  real_T Dr;
  real_T Lk;
  real_T Dk;
  real_T D_hull[4];
  real_T eta_dot[4];
  real_T nu_dot[4];
  real_T e[4];
  real_T rtb_DLookupTable3;
  real_T M_0[16];
  real_T b[9];
  real_T tmp[9];
  real_T b_0[9];
  int16_T i;
  real_T b_1[3];
  int32_T tmp_0[16];
  int32_T tmp_1[16];
  real_T c[9];
  real_T tmp_2[9];
  int16_T i_0;
  real_T tmp_3[16];
  real_T tmp_4[16];
  real_T tmp_5[4];
  real_T tmp_6[4];
  real_T alpha_as_idx_1;

  /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
   *  Inport: '<Root>/V_in'
   *  Inport: '<Root>/wind'
   */
  /* MATLAB Function 'MATLAB Function1': '<S2>:1' */
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
  /*  (N), crew weight 20000 */
  /*  (m), crew position */
  /*  (m), yacht beam */
  /* '<S2>:1:21' */
  /*  the norm of wind velocity */
  /* '<S2>:1:22' */
  /*  the direction of wind (coming from the north, ie going south) */
  /*  retrieve the system state from the field input vector "V_in" */
  /* '<S2>:1:29' */
  /* '<S2>:1:30' */
  /* '<S2>:1:31' */
  /* '<S2>:1:32' */
  /* '<S2>:1:33' */
  /* '<S2>:1:34' */
  /*  retrieve the input signals from the vector "V_in" */
  /* '<S2>:1:38' */
  /* '<S2>:1:39' */
  /* '<S2>:1:41' */
  /*  evaluate the matrix M and C in the model */
  /*  calculate the tau vector, ie forces and moments generated from: */
  /*  the sail */
  /* '<S2>:1:55' */
  /* '<S2>:1:56' */
  alpha_as = log(11.58 * cos(BoatDynamic_U.V_in[6]) / 0.0005) /
    10.050181931686932;

  /* '<S2>:1:57' */
  /* '<S2>:1:58' */
  /* '<S2>:1:59' */
  /*  wind expressed in the body frame */
  /* '<S2>:1:60' */
  /* '<S2>:1:61' */
  b[0] = 1.0;
  b[3] = 0.0;
  b[6] = 0.0;
  b[1] = 0.0;
  b[4] = cos(-BoatDynamic_U.V_in[6]);
  b[7] = -sin(-BoatDynamic_U.V_in[6]);
  b[2] = 0.0;
  b[5] = sin(-BoatDynamic_U.V_in[6]);
  b[8] = cos(-BoatDynamic_U.V_in[6]);
  tmp[0] = cos(-BoatDynamic_U.V_in[7]);
  tmp[3] = -sin(-BoatDynamic_U.V_in[7]);
  tmp[6] = 0.0;
  tmp[1] = sin(-BoatDynamic_U.V_in[7]);
  tmp[4] = cos(-BoatDynamic_U.V_in[7]);
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

  v_akv = BoatDynamic_U.wind[0] * cos(BoatDynamic_U.wind[1]) * alpha_as;
  alpha_as_idx_1 = BoatDynamic_U.wind[0] * sin(BoatDynamic_U.wind[1]) * alpha_as;
  v_aku = alpha_as * 0.0;
  for (i = 0; i < 3; i++) {
    b_1[i] = b_0[i + 6] * v_aku + (b_0[i + 3] * alpha_as_idx_1 + b_0[i] * v_akv);
  }

  /* '<S2>:1:62' */
  /* '<S2>:1:63' */
  /* '<S2>:1:64' */
  alpha_aw = rt_atan2d_snf((b_1[1] - BoatDynamic_U.V_in[9]) -
    (BoatDynamic_U.V_in[11] * 0.0 - BoatDynamic_U.V_in[10] * -11.58), -((b_1[0]
    - BoatDynamic_U.V_in[8]) - (-0.0 - BoatDynamic_U.V_in[11] * 0.0)));

  /* % (sail luffing or not) */
  if (alpha_aw - BoatDynamic_U.V_in[3] > BoatDynamic_U.V_in[1]) {
    /* '<S2>:1:67' */
    /* '<S2>:1:68' */
    delta_s = BoatDynamic_U.V_in[1];
  } else if (alpha_aw - BoatDynamic_U.V_in[3] < -BoatDynamic_U.V_in[1]) {
    /* '<S2>:1:69' */
    /* '<S2>:1:70' */
    delta_s = -BoatDynamic_U.V_in[1];
  } else {
    /* '<S2>:1:72' */
    delta_s = alpha_aw - BoatDynamic_U.V_in[3];
  }

  /* '<S2>:1:74' */
  delta_s += BoatDynamic_U.V_in[3];

  /* '<S2>:1:76' */
  alpha_as = alpha_aw - delta_s;

  /* '<S2>:1:78' */
  rtb_attack_sail = alpha_as;

  /*  fit the input angle of attack into the interval [-pi,pi] */
  if (alpha_as > 3.1415926535897931) {
    /* '<S2>:1:81' */
    /* '<S2>:1:82' */
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
      /* '<S2>:1:84' */
      /* '<S2>:1:85' */
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
  /* '<S2>:1:90' */
  /* '<S2>:1:91' */
  /* '<S2>:1:92' */
  /* '<S2>:1:93' */
  alpha_as = rt_atan2d_snf((-BoatDynamic_U.V_in[9] - BoatDynamic_U.V_in[11] *
    -8.2) + BoatDynamic_U.V_in[10] * -0.78, -(BoatDynamic_U.V_in[11] * 0.0 +
    -BoatDynamic_U.V_in[8])) - BoatDynamic_U.V_in[0];

  /* '<S2>:1:95' */
  rtb_attack_rudder = alpha_as;

  /*  fit the input angle of attack into the interval [-pi,pi] */
  if (alpha_as > 3.1415926535897931) {
    /* '<S2>:1:98' */
    /* '<S2>:1:99' */
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
      /* '<S2>:1:101' */
      /* '<S2>:1:102' */
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
  /* '<S2>:1:107' */
  v_aku = BoatDynamic_U.V_in[11] * 0.0 + -BoatDynamic_U.V_in[8];

  /* '<S2>:1:108' */
  v_akv = (-BoatDynamic_U.V_in[9] - BoatDynamic_U.V_in[11] * 0.0) +
    BoatDynamic_U.V_in[10] * -0.58;

  /* '<S2>:1:109' */
  alpha_ak = rt_atan2d_snf(v_akv, -v_aku);

  /* '<S2>:1:112' */
  rtb_attack_keel = alpha_ak;

  /*  fit the input angle of attack into the interval [-pi,pi] */
  if (alpha_ak > 3.1415926535897931) {
    /* '<S2>:1:115' */
    /* '<S2>:1:116' */
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
      /* '<S2>:1:118' */
      /* '<S2>:1:119' */
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
  /* '<S2>:1:126' */
  /* '<S2>:1:128' */

  /* Lookup_n-D: '<Root>/1-D Lookup Table'
   * About '<Root>/1-D Lookup Table':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable = look_SplNBinXZcd(1U, &rtb_attack_sail, (rt_LUTSplineWork*)
    &BoatDynamic_DW.SWork[0]);

  /* Lookup_n-D: '<Root>/1-D Lookup Table4'
   * About '<Root>/1-D Lookup Table4':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable4 = look_SplNBinXZcd(1U, &rtb_attack_sail, (rt_LUTSplineWork*)
    &BoatDynamic_DW.SWork_n[0]);

  /* Lookup_n-D: '<Root>/1-D Lookup Table1'
   * About '<Root>/1-D Lookup Table1':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable1 = look_SplNBinXZcd(1U, &rtb_attack_rudder, (rt_LUTSplineWork*)
    &BoatDynamic_DW.SWork_j[0]);

  /* Lookup_n-D: '<Root>/1-D Lookup Table5'
   * About '<Root>/1-D Lookup Table5':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable5 = look_SplNBinXZcd(1U, &rtb_attack_rudder, (rt_LUTSplineWork*)
    &BoatDynamic_DW.SWork_k[0]);

  /* Lookup_n-D: '<Root>/1-D Lookup Table2'
   * About '<Root>/1-D Lookup Table2':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable2 = look_SplNBinXZcd(1U, &rtb_attack_keel, (rt_LUTSplineWork*)
    &BoatDynamic_DW.SWork_jo[0]);

  /* Lookup_n-D: '<Root>/1-D Lookup Table6'
   * About '<Root>/1-D Lookup Table6':
   *       Table size:  100
   *    Interpolation:  Spline
   *    Extrapolation:  Linear
   *   Breakpt Search:  Binary
   *    Breakpt Cache:  OFF
   */
  rtb_DLookupTable6 = look_SplNBinXZcd(1U, &rtb_attack_keel, (rt_LUTSplineWork*)
    &BoatDynamic_DW.SWork_kl[0]);

  /* Lookup_n-D: '<Root>/1-D Lookup Table3' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function1'
   */
  rtb_DLookupTable3 = look1_binlxpw(sqrt(v_aku * v_aku + v_akv * v_akv),
    BoatDynamic_P.hull_xdata, BoatDynamic_P.hull_ydata, 99UL);

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/V_in'
   *  Inport: '<Root>/wind'
   */
  /* MATLAB Function 'MATLAB Function': '<S1>:1' */
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
  /* '<S1>:1:19' */
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
  /*  (N), crew weight 20000 */
  /*  (m), crew position */
  /*  (m), yacht beam */
  /* '<S1>:1:21' */
  /*  the norm of wind velocity */
  /* '<S1>:1:22' */
  /*  the direction of wind (coming from the north, ie going south) */
  /*  retrieve the system state from the field input vector "V_in" */
  /* '<S1>:1:29' */
  phi = BoatDynamic_U.V_in[6];

  /* '<S1>:1:30' */
  /* '<S1>:1:31' */
  /* '<S1>:1:32' */
  /* '<S1>:1:33' */
  /* '<S1>:1:34' */
  /* '<S1>:1:35' */
  /*  retrieve the input signals from the vector "V_in" */
  /* '<S1>:1:39' */
  /* '<S1>:1:40' */
  /* '<S1>:1:41' */
  /*  evaluate the matrix M and C in the model */
  /* '<S1>:1:44' */
  /* '<S1>:1:45' */
  /* '<S1>:1:47' */
  /* '<S1>:1:48' */
  /* '<S1>:1:50' */
  tmp_0[0] = 25900L;
  tmp_0[4] = 0L;
  tmp_0[8] = 0L;
  tmp_0[12] = 0L;
  tmp_0[1] = 0L;
  tmp_0[5] = 25900L;
  tmp_0[9] = 0L;
  tmp_0[13] = 0L;
  tmp_0[2] = 0L;
  tmp_0[6] = 0L;
  tmp_0[10] = 133690L;
  tmp_0[14] = -2180L;
  tmp_0[3] = 0L;
  tmp_0[7] = 0L;
  tmp_0[11] = -2180L;
  tmp_0[15] = 24760L;
  tmp_1[0] = 970L;
  tmp_1[4] = 0L;
  tmp_1[8] = 0L;
  tmp_1[12] = 0L;
  tmp_1[1] = 0L;
  tmp_1[5] = 17430L;
  tmp_1[9] = -13160L;
  tmp_1[13] = -6190L;
  tmp_1[2] = 0L;
  tmp_1[6] = -13160L;
  tmp_1[10] = 106500L;
  tmp_1[14] = 4730L;
  tmp_1[3] = 0L;
  tmp_1[7] = -6190L;
  tmp_1[11] = 4730L;
  tmp_1[15] = 101650L;
  for (i = 0; i < 4; i++) {
    M[i << 2] = tmp_0[i << 2] + tmp_1[i << 2];
    M[1 + (i << 2)] = tmp_0[(i << 2) + 1] + tmp_1[(i << 2) + 1];
    M[2 + (i << 2)] = tmp_0[(i << 2) + 2] + tmp_1[(i << 2) + 2];
    M[3 + (i << 2)] = tmp_0[(i << 2) + 3] + tmp_1[(i << 2) + 3];
  }

  /*  calculate the tau vector, ie forces and moments generated from: */
  /*  the sail */
  /* '<S1>:1:54' */
  /* '<S1>:1:55' */
  alpha_as = log(11.58 * cos(BoatDynamic_U.V_in[6]) / 0.0005) /
    10.050181931686932;

  /* '<S1>:1:56' */
  /* '<S1>:1:57' */
  /* '<S1>:1:58' */
  /*  wind expressed in the body frame */
  /* '<S1>:1:59' */
  /* '<S1>:1:60' */
  c[0] = 1.0;
  c[3] = 0.0;
  c[6] = 0.0;
  c[1] = 0.0;
  c[4] = cos(-BoatDynamic_U.V_in[6]);
  c[7] = -sin(-BoatDynamic_U.V_in[6]);
  c[2] = 0.0;
  c[5] = sin(-BoatDynamic_U.V_in[6]);
  c[8] = cos(-BoatDynamic_U.V_in[6]);
  tmp_2[0] = cos(-BoatDynamic_U.V_in[7]);
  tmp_2[3] = -sin(-BoatDynamic_U.V_in[7]);
  tmp_2[6] = 0.0;
  tmp_2[1] = sin(-BoatDynamic_U.V_in[7]);
  tmp_2[4] = cos(-BoatDynamic_U.V_in[7]);
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

  v_akv = BoatDynamic_U.wind[0] * cos(BoatDynamic_U.wind[1]) * alpha_as;
  alpha_as_idx_1 = BoatDynamic_U.wind[0] * sin(BoatDynamic_U.wind[1]) * alpha_as;
  v_aku = alpha_as * 0.0;
  for (i = 0; i < 3; i++) {
    b_1[i] = b[i + 6] * v_aku + (b[i + 3] * alpha_as_idx_1 + b[i] * v_akv);
  }

  v_aku = (b_1[0] - BoatDynamic_U.V_in[8]) - (-0.0 - BoatDynamic_U.V_in[11] *
    0.0);
  v_akv = (b_1[1] - BoatDynamic_U.V_in[9]) - (BoatDynamic_U.V_in[11] * 0.0 -
    BoatDynamic_U.V_in[10] * -11.58);

  /* '<S1>:1:61' */
  /* '<S1>:1:62' */
  /* '<S1>:1:63' */
  alpha_aw = rt_atan2d_snf(v_akv, -v_aku);

  /*  (sail luffing or not) */
  if (alpha_aw - BoatDynamic_U.V_in[3] > BoatDynamic_U.V_in[1]) {
    /* '<S1>:1:66' */
    /* '<S1>:1:67' */
    delta_s = BoatDynamic_U.V_in[1];
  } else if (alpha_aw - BoatDynamic_U.V_in[3] < -BoatDynamic_U.V_in[1]) {
    /* '<S1>:1:68' */
    /* '<S1>:1:69' */
    delta_s = -BoatDynamic_U.V_in[1];
  } else {
    /* '<S1>:1:71' */
    delta_s = alpha_aw - BoatDynamic_U.V_in[3];
  }

  /* '<S1>:1:73' */
  delta_s += BoatDynamic_U.V_in[3];

  /* '<S1>:1:80' */
  Ls = (v_aku * v_aku + v_akv * v_akv) * 102.0 * rtb_DLookupTable;

  /* '<S1>:1:81' */
  Ds = (v_aku * v_aku + v_akv * v_akv) * 102.0 * rtb_DLookupTable4;

  /* '<S1>:1:83' */
  /*  the rudder */
  /* '<S1>:1:87' */
  alpha_as = BoatDynamic_U.V_in[11] * 0.0 + -BoatDynamic_U.V_in[8];

  /* '<S1>:1:88' */
  v_aku = (-BoatDynamic_U.V_in[9] - BoatDynamic_U.V_in[11] * -8.2) +
    BoatDynamic_U.V_in[10] * -0.78;

  /* '<S1>:1:89' */
  alpha_ar = rt_atan2d_snf(v_aku, -alpha_as);

  /* [Clr,Cdr] = ruddercoef(alpha_a); */
  /* '<S1>:1:96' */
  /* '<S1>:1:98' */
  Lr = (alpha_as * alpha_as + v_aku * v_aku) * 599.625 * rtb_DLookupTable1;

  /* '<S1>:1:99' */
  Dr = (rtb_DLookupTable1 * rtb_DLookupTable1 * 1.17 / 18.145839167134646 +
        rtb_DLookupTable5) * ((alpha_as * alpha_as + v_aku * v_aku) * 599.625);

  /* '<S1>:1:101' */
  /*  the tau vector is finally given by: */
  /* '<S1>:1:105' */
  /*  calculate the damping forces and moments: */
  /*  from the keel */
  /* '<S1>:1:109' */
  v_aku = BoatDynamic_U.V_in[11] * 0.0 + -BoatDynamic_U.V_in[8];

  /* '<S1>:1:110' */
  v_akv = (-BoatDynamic_U.V_in[9] - BoatDynamic_U.V_in[11] * 0.0) +
    BoatDynamic_U.V_in[10] * -0.58;

  /* '<S1>:1:111' */
  alpha_ak = rt_atan2d_snf(v_akv, -v_aku);

  /* '<S1>:1:117' */
  /* '<S1>:1:119' */
  Lk = (v_aku * v_aku + v_akv * v_akv) * 4458.75 * rtb_DLookupTable2;

  /* '<S1>:1:120' */
  Dk = (rtb_DLookupTable2 * rtb_DLookupTable2 * 8.7 / 27.269464056130911 +
        rtb_DLookupTable6) * ((v_aku * v_aku + v_akv * v_akv) * 4458.75);

  /* '<S1>:1:122' */
  /*  from the hull */
  /* '<S1>:1:125' */
  /* '<S1>:1:126' */
  /* '<S1>:1:128' */
  alpha_as = rt_atan2d_snf(((-BoatDynamic_U.V_in[9] - BoatDynamic_U.V_in[11] *
    0.0) + BoatDynamic_U.V_in[10] * -1.18) / cos(BoatDynamic_U.V_in[6]),
    -(BoatDynamic_U.V_in[11] * 0.0 + -BoatDynamic_U.V_in[8]));

  /* '<S1>:1:132' */
  D_hull[0] = rtb_DLookupTable3 * cos(alpha_as);
  D_hull[1] = -rtb_DLookupTable3 * sin(alpha_as) * cos(BoatDynamic_U.V_in[6]);
  D_hull[2] = rtb_DLookupTable3 * sin(alpha_as) * cos(BoatDynamic_U.V_in[6]) *
    -1.18;
  D_hull[3] = -rtb_DLookupTable3 * sin(alpha_as) * cos(BoatDynamic_U.V_in[6]) *
    0.0;

  /*  from heel and yaw */
  /*  (compute first eta_dot and thereby phi_dot and psi_dot) */
  /* '<S1>:1:136' */
  /* '<S1>:1:137' */
  M_0[0] = cos(BoatDynamic_U.V_in[7]);
  M_0[4] = -sin(BoatDynamic_U.V_in[7]) * cos(BoatDynamic_U.V_in[6]);
  M_0[8] = 0.0;
  M_0[12] = 0.0;
  M_0[1] = sin(BoatDynamic_U.V_in[7]);
  M_0[5] = cos(BoatDynamic_U.V_in[7]) * cos(BoatDynamic_U.V_in[6]);
  M_0[9] = 0.0;
  M_0[13] = 0.0;
  M_0[2] = 0.0;
  M_0[6] = 0.0;
  M_0[10] = 1.0;
  M_0[14] = 0.0;
  M_0[3] = 0.0;
  M_0[7] = 0.0;
  M_0[11] = 0.0;
  M_0[15] = cos(BoatDynamic_U.V_in[6]);
  for (i = 0; i < 4; i++) {
    alpha_as_idx_1 = M_0[i + 12] * BoatDynamic_U.V_in[11] + (M_0[i + 8] *
      BoatDynamic_U.V_in[10] + (M_0[i + 4] * BoatDynamic_U.V_in[9] + M_0[i] *
      BoatDynamic_U.V_in[8]));
    eta_dot[i] = alpha_as_idx_1;
  }

  /* '<S1>:1:138' */
  /* '<S1>:1:139' */
  /* '<S1>:1:141' */
  /*  compute total damping vector D */
  /* '<S1>:1:144' */
  /*  righting moment plus internal moving mass system (ie transversal weight) */
  /* '<S1>:1:147' */
  alpha_as = BoatDynamic_U.V_in[6] * 180.0 / 3.1415926535897931;

  /* '<S1>:1:148' */
  v_aku = -BoatDynamic_U.V_in[2] * 60000.0 * 3.6 * cos(BoatDynamic_U.V_in[6]);

  /* '<S1>:1:149' */
  v_akv = -BoatDynamic_U.V_in[2] * 60000.0 * -8.0 * sin(fabs(BoatDynamic_U.V_in
    [6]));

  /* '<S1>:1:150' */
  /*  computation of nu_dot */
  /* '<S1>:1:153' */
  tmp_3[0] = 0.0;
  tmp_3[4] = -25900.0 * BoatDynamic_U.V_in[11];
  tmp_3[8] = 0.0;
  tmp_3[12] = 0.0;
  tmp_3[1] = 25900.0 * BoatDynamic_U.V_in[11];
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
  tmp_4[12] = (-17430.0 * BoatDynamic_U.V_in[9] - -13160.0 * BoatDynamic_U.V_in
               [10]) - -6190.0 * BoatDynamic_U.V_in[11];
  tmp_4[1] = 0.0;
  tmp_4[5] = 0.0;
  tmp_4[9] = 0.0;
  tmp_4[13] = 970.0 * BoatDynamic_U.V_in[8];
  tmp_4[2] = 0.0;
  tmp_4[6] = 0.0;
  tmp_4[10] = 0.0;
  tmp_4[14] = 0.0;
  tmp_4[3] = (17430.0 * BoatDynamic_U.V_in[9] + -13160.0 * BoatDynamic_U.V_in[10])
    + -6190.0 * BoatDynamic_U.V_in[11];
  tmp_4[7] = -970.0 * BoatDynamic_U.V_in[8];
  tmp_4[11] = 0.0;
  tmp_4[15] = 0.0;
  for (i = 0; i < 4; i++) {
    alpha_as_idx_1 = tmp_3[i + 12] * BoatDynamic_U.V_in[11] + (tmp_3[i + 8] *
      BoatDynamic_U.V_in[10] + (tmp_3[i + 4] * BoatDynamic_U.V_in[9] + tmp_3[i] *
      BoatDynamic_U.V_in[8]));
    tmp_5[i] = alpha_as_idx_1;
  }

  for (i = 0; i < 4; i++) {
    alpha_as_idx_1 = tmp_4[i + 12] * BoatDynamic_U.V_in[11] + (tmp_4[i + 8] *
      BoatDynamic_U.V_in[10] + (tmp_4[i + 4] * BoatDynamic_U.V_in[9] + tmp_4[i] *
      BoatDynamic_U.V_in[8]));
    tmp_6[i] = alpha_as_idx_1;
  }

  nu_dot[0] = tmp_5[0] + tmp_6[0];
  nu_dot[1] = tmp_5[1] + tmp_6[1];
  nu_dot[2] = tmp_5[2] + tmp_6[2];
  nu_dot[3] = tmp_5[3] + tmp_6[3];
  for (i = 0; i < 16; i++) {
    M_0[i] = -M[i];
  }

  BoatDynamic_mldivide(M_0, nu_dot);
  e[0] = (-Lk * sin(alpha_ak) + Dk * cos(alpha_ak)) + D_hull[0];
  e[1] = (-Lk * cos(alpha_ak) - Dk * sin(alpha_ak)) + D_hull[1];
  e[2] = (-(-Lk * cos(alpha_ak) - Dk * sin(alpha_ak)) * -0.58 + D_hull[2]) +
    120000.0 * eta_dot[2] * fabs(eta_dot[2]);
  e[3] = (-(Lk * cos(alpha_ak) + Dk * sin(alpha_ak)) * 0.0 + D_hull[3]) +
    50000.0 * eta_dot[3] * fabs(eta_dot[3]) * cos(phi);
  BoatDynamic_mldivide(M, e);
  nu[0] = 0.0;
  nu[1] = 0.0;
  nu[2] = (alpha_as * alpha_as * -5.89 + 8160.0 * alpha_as) + v_aku;
  nu[3] = v_akv;
  BoatDynamic_mldivide(M, nu);
  D_hull[0] = (Ls * sin(alpha_aw) - Ds * cos(alpha_aw)) + (Lr * sin(alpha_ar) -
    Dr * cos(alpha_ar));
  D_hull[1] = (Ls * cos(alpha_aw) + Ds * sin(alpha_aw)) + (Lr * cos(alpha_ar) +
    Dr * sin(alpha_ar));
  D_hull[2] = -(Ls * cos(alpha_aw) + Ds * sin(alpha_aw)) * -11.58 + -(Lr * cos
    (alpha_ar) + Dr * sin(alpha_ar)) * -0.78;
  D_hull[3] = (-(Ls * sin(alpha_aw) - Ds * cos(alpha_aw)) * 0.6 * sin(delta_s) +
               (Ls * cos(alpha_aw) + Ds * sin(alpha_aw)) * (0.3 - 0.6 * cos
    (delta_s))) + (Lr * cos(alpha_ar) + Dr * sin(alpha_ar)) * -8.2;
  BoatDynamic_mldivide(M, D_hull);
  nu_dot[0] = ((nu_dot[0] - e[0]) - nu[0]) + D_hull[0];
  nu_dot[1] = ((nu_dot[1] - e[1]) - nu[1]) + D_hull[1];
  nu_dot[2] = ((nu_dot[2] - e[2]) - nu[2]) + D_hull[2];

  /* Outport: '<Root>/X_dot' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  /*  output the derivative of the state extended with the sail angle */
  /* '<S1>:1:157' */
  BoatDynamic_Y.X_dot[0] = eta_dot[0];
  BoatDynamic_Y.X_dot[1] = eta_dot[1];
  BoatDynamic_Y.X_dot[2] = eta_dot[2];
  BoatDynamic_Y.X_dot[3] = eta_dot[3];
  BoatDynamic_Y.X_dot[4] = nu_dot[0];
  BoatDynamic_Y.X_dot[5] = nu_dot[1];
  BoatDynamic_Y.X_dot[6] = nu_dot[2];
  BoatDynamic_Y.X_dot[7] = ((nu_dot[3] - e[3]) - nu[3]) + D_hull[3];
  BoatDynamic_Y.X_dot[8] = delta_s;

  /* Matfile logging */
  rt_UpdateTXYLogVars(BoatDynamic_M->rtwLogInfo,
                      (&BoatDynamic_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.1s, 0.0s] */
    if ((rtmGetTFinal(BoatDynamic_M)!=-1) &&
        !((rtmGetTFinal(BoatDynamic_M)-BoatDynamic_M->Timing.taskTime0) >
          BoatDynamic_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(BoatDynamic_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++BoatDynamic_M->Timing.clockTick0)) {
    ++BoatDynamic_M->Timing.clockTickH0;
  }

  BoatDynamic_M->Timing.taskTime0 = BoatDynamic_M->Timing.clockTick0 *
    BoatDynamic_M->Timing.stepSize0 + BoatDynamic_M->Timing.clockTickH0 *
    BoatDynamic_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void BoatDynamic_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)BoatDynamic_M, 0,
                sizeof(RT_MODEL_BoatDynamic_T));
  rtmSetTFinal(BoatDynamic_M, 10.0);
  BoatDynamic_M->Timing.stepSize0 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    BoatDynamic_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(BoatDynamic_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(BoatDynamic_M->rtwLogInfo, (NULL));
    rtliSetLogT(BoatDynamic_M->rtwLogInfo, "tout");
    rtliSetLogX(BoatDynamic_M->rtwLogInfo, "");
    rtliSetLogXFinal(BoatDynamic_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(BoatDynamic_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(BoatDynamic_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(BoatDynamic_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(BoatDynamic_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &BoatDynamic_Y.X_dot[0]
      };

      rtliSetLogYSignalPtrs(BoatDynamic_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        9
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        9
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        2
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "BoatDynamic/X_dot" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          1,
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

      rtliSetLogYSignalInfo(BoatDynamic_M->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
    }

    rtliSetLogY(BoatDynamic_M->rtwLogInfo, "yout");
  }

  /* states (dwork) */
  (void) memset((void *)&BoatDynamic_DW, 0,
                sizeof(DW_BoatDynamic_T));

  /* external inputs */
  (void) memset((void *)&BoatDynamic_U, 0,
                sizeof(ExtU_BoatDynamic_T));

  /* external outputs */
  (void) memset(&BoatDynamic_Y.X_dot[0], 0,
                9U*sizeof(real_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(BoatDynamic_M->rtwLogInfo, 0.0, rtmGetTFinal
    (BoatDynamic_M), BoatDynamic_M->Timing.stepSize0, (&rtmGetErrorStatus
    (BoatDynamic_M)));

  /* Start for Lookup_n-D: '<Root>/1-D Lookup Table' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatDynamic_DW.TWork[0];
    void **bpDataSet = (void **) &BoatDynamic_DW.m_bpDataSet;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatDynamic_P.DLookupTable_dimSizes;
    TWork_start->m_tableData = (void *) BoatDynamic_P.alphacoeff_yldata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatDynamic_DW.m_bpIndex;
    TWork_start->m_bpLambda = (void *) &BoatDynamic_DW.m_bpLambda;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatDynamic_P.DLookupTable_maxIndex;
    bpDataSet[0] = (void *)BoatDynamic_P.alphacoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatDynamic_DW.SWork[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatDynamic_DW.TWork[0];
    rt_SplWk->m_yyA = &BoatDynamic_DW.m_yyA;
    rt_SplWk->m_yyB = &BoatDynamic_DW.m_yyB;
    rt_SplWk->m_yy2 = &BoatDynamic_DW.m_yy2;
    rt_SplWk->m_up = &BoatDynamic_DW.m_up[0];
    rt_SplWk->m_y2 = &BoatDynamic_DW.m_y2[0];
    rt_SplWk->m_numYWorkElts = BoatDynamic_P.DLookupTable_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<Root>/1-D Lookup Table4' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatDynamic_DW.TWork_d[0];
    void **bpDataSet = (void **) &BoatDynamic_DW.m_bpDataSet_d;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatDynamic_P.DLookupTable4_dimSizes;
    TWork_start->m_tableData = (void *) BoatDynamic_P.alphacoeff_yddata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatDynamic_DW.m_bpIndex_m;
    TWork_start->m_bpLambda = (void *) &BoatDynamic_DW.m_bpLambda_f;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatDynamic_P.DLookupTable4_maxIndex;
    bpDataSet[0] = (void *)BoatDynamic_P.alphacoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatDynamic_DW.SWork_n[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatDynamic_DW.TWork_d[0];
    rt_SplWk->m_yyA = &BoatDynamic_DW.m_yyA_p;
    rt_SplWk->m_yyB = &BoatDynamic_DW.m_yyB_j;
    rt_SplWk->m_yy2 = &BoatDynamic_DW.m_yy2_l;
    rt_SplWk->m_up = &BoatDynamic_DW.m_up_o[0];
    rt_SplWk->m_y2 = &BoatDynamic_DW.m_y2_a[0];
    rt_SplWk->m_numYWorkElts = BoatDynamic_P.DLookupTable4_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<Root>/1-D Lookup Table1' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatDynamic_DW.TWork_j[0];
    void **bpDataSet = (void **) &BoatDynamic_DW.m_bpDataSet_k;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatDynamic_P.DLookupTable1_dimSizes;
    TWork_start->m_tableData = (void *) BoatDynamic_P.ruddercoeff_yldata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatDynamic_DW.m_bpIndex_b;
    TWork_start->m_bpLambda = (void *) &BoatDynamic_DW.m_bpLambda_g;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatDynamic_P.DLookupTable1_maxIndex;
    bpDataSet[0] = (void *)BoatDynamic_P.ruddercoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatDynamic_DW.SWork_j[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatDynamic_DW.TWork_j[0];
    rt_SplWk->m_yyA = &BoatDynamic_DW.m_yyA_n;
    rt_SplWk->m_yyB = &BoatDynamic_DW.m_yyB_n;
    rt_SplWk->m_yy2 = &BoatDynamic_DW.m_yy2_h;
    rt_SplWk->m_up = &BoatDynamic_DW.m_up_b[0];
    rt_SplWk->m_y2 = &BoatDynamic_DW.m_y2_e[0];
    rt_SplWk->m_numYWorkElts = BoatDynamic_P.DLookupTable1_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<Root>/1-D Lookup Table5' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatDynamic_DW.TWork_a[0];
    void **bpDataSet = (void **) &BoatDynamic_DW.m_bpDataSet_c;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatDynamic_P.DLookupTable5_dimSizes;
    TWork_start->m_tableData = (void *) BoatDynamic_P.ruddercoeff_yddata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatDynamic_DW.m_bpIndex_n;
    TWork_start->m_bpLambda = (void *) &BoatDynamic_DW.m_bpLambda_n;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatDynamic_P.DLookupTable5_maxIndex;
    bpDataSet[0] = (void *)BoatDynamic_P.ruddercoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatDynamic_DW.SWork_k[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatDynamic_DW.TWork_a[0];
    rt_SplWk->m_yyA = &BoatDynamic_DW.m_yyA_i;
    rt_SplWk->m_yyB = &BoatDynamic_DW.m_yyB_l;
    rt_SplWk->m_yy2 = &BoatDynamic_DW.m_yy2_k;
    rt_SplWk->m_up = &BoatDynamic_DW.m_up_f[0];
    rt_SplWk->m_y2 = &BoatDynamic_DW.m_y2_c[0];
    rt_SplWk->m_numYWorkElts = BoatDynamic_P.DLookupTable5_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<Root>/1-D Lookup Table2' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatDynamic_DW.TWork_c[0];
    void **bpDataSet = (void **) &BoatDynamic_DW.m_bpDataSet_j;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatDynamic_P.DLookupTable2_dimSizes;
    TWork_start->m_tableData = (void *) BoatDynamic_P.keelcoeff_yldata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatDynamic_DW.m_bpIndex_a;
    TWork_start->m_bpLambda = (void *) &BoatDynamic_DW.m_bpLambda_k;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatDynamic_P.DLookupTable2_maxIndex;
    bpDataSet[0] = (void *)BoatDynamic_P.keelcoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatDynamic_DW.SWork_jo[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatDynamic_DW.TWork_c[0];
    rt_SplWk->m_yyA = &BoatDynamic_DW.m_yyA_ng;
    rt_SplWk->m_yyB = &BoatDynamic_DW.m_yyB_e;
    rt_SplWk->m_yy2 = &BoatDynamic_DW.m_yy2_j;
    rt_SplWk->m_up = &BoatDynamic_DW.m_up_g[0];
    rt_SplWk->m_y2 = &BoatDynamic_DW.m_y2_cz[0];
    rt_SplWk->m_numYWorkElts = BoatDynamic_P.DLookupTable2_numYWorkElts;
  }

  /* Start for Lookup_n-D: '<Root>/1-D Lookup Table6' */
  {
    rt_LUTnWork *TWork_start = (rt_LUTnWork *) &BoatDynamic_DW.TWork_dh[0];
    void **bpDataSet = (void **) &BoatDynamic_DW.m_bpDataSet_g;
    TWork_start->m_dimSizes = (const uint32_T *)
      &BoatDynamic_P.DLookupTable6_dimSizes;
    TWork_start->m_tableData = (void *) BoatDynamic_P.keelcoeff_yddata;
    TWork_start->m_bpDataSet = bpDataSet;
    TWork_start->m_bpIndex = &BoatDynamic_DW.m_bpIndex_j;
    TWork_start->m_bpLambda = (void *) &BoatDynamic_DW.m_bpLambda_gp;
    TWork_start->m_maxIndex = (const uint32_T *)
      &BoatDynamic_P.DLookupTable6_maxIndex;
    bpDataSet[0] = (void *)BoatDynamic_P.keelcoeff_xdata;
  }

  {
    rt_LUTSplineWork *rt_SplWk = (rt_LUTSplineWork*)&BoatDynamic_DW.SWork_kl[0];
    rt_SplWk->m_TWork = (rt_LUTnWork*)&BoatDynamic_DW.TWork_dh[0];
    rt_SplWk->m_yyA = &BoatDynamic_DW.m_yyA_l;
    rt_SplWk->m_yyB = &BoatDynamic_DW.m_yyB_i;
    rt_SplWk->m_yy2 = &BoatDynamic_DW.m_yy2_n;
    rt_SplWk->m_up = &BoatDynamic_DW.m_up_n[0];
    rt_SplWk->m_y2 = &BoatDynamic_DW.m_y2_g[0];
    rt_SplWk->m_numYWorkElts = BoatDynamic_P.DLookupTable6_numYWorkElts;
  }
}

/* Model terminate function */
void BoatDynamic_terminate(void)
{
  /* (no terminate code required) */
}
