/*
 * Robot0.c
 *
 * Code generation for model "Robot0".
 *
 * Model version              : 1.6
 * Simulink Coder version : 8.4 (R2013a) 13-Feb-2013
 * C source code generated on : Wed Jun 18 18:03:08 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "Robot0.h"
#include "Robot0_private.h"

/* Block signals (auto storage) */
B_Robot0_T Robot0_B;

/* Continuous states */
X_Robot0_T Robot0_X;

/* Block states (auto storage) */
DW_Robot0_T Robot0_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_Robot0_T Robot0_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_Robot0_T Robot0_Y;

/* Real-time model */
RT_MODEL_Robot0_T Robot0_M_;
RT_MODEL_Robot0_T *const Robot0_M = &Robot0_M_;

/*
 * This function updates continuous states using the ODE5 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE5_A[6] = {
    1.0/5.0, 3.0/10.0, 4.0/5.0, 8.0/9.0, 1.0, 1.0
  };

  static const real_T rt_ODE5_B[6][6] = {
    { 1.0/5.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

    { 3.0/40.0, 9.0/40.0, 0.0, 0.0, 0.0, 0.0 },

    { 44.0/45.0, -56.0/15.0, 32.0/9.0, 0.0, 0.0, 0.0 },

    { 19372.0/6561.0, -25360.0/2187.0, 64448.0/6561.0, -212.0/729.0, 0.0, 0.0 },

    { 9017.0/3168.0, -355.0/33.0, 46732.0/5247.0, 49.0/176.0, -5103.0/18656.0,
      0.0 },

    { 35.0/384.0, 0.0, 500.0/1113.0, 125.0/192.0, -2187.0/6784.0, 11.0/84.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE5_IntgData *id = (ODE5_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T *f4 = id->f[4];
  real_T *f5 = id->f[5];
  real_T hB[6];
  int_T i;
  int_T nXc = 11;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Robot0_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE5_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[0]);
  rtsiSetdX(si, f1);
  Robot0_step();
  Robot0_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE5_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[1]);
  rtsiSetdX(si, f2);
  Robot0_step();
  Robot0_derivatives();

  /* f(:,4) = feval(odefile, t + hA(3), y + f*hB(:,3), args(:)(*)); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE5_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[2]);
  rtsiSetdX(si, f3);
  Robot0_step();
  Robot0_derivatives();

  /* f(:,5) = feval(odefile, t + hA(4), y + f*hB(:,4), args(:)(*)); */
  for (i = 0; i <= 3; i++) {
    hB[i] = h * rt_ODE5_B[3][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3]);
  }

  rtsiSetT(si, t + h*rt_ODE5_A[3]);
  rtsiSetdX(si, f4);
  Robot0_step();
  Robot0_derivatives();

  /* f(:,6) = feval(odefile, t + hA(5), y + f*hB(:,5), args(:)(*)); */
  for (i = 0; i <= 4; i++) {
    hB[i] = h * rt_ODE5_B[4][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f5);
  Robot0_step();
  Robot0_derivatives();

  /* tnew = t + hA(6);
     ynew = y + f*hB(:,6); */
  for (i = 0; i <= 5; i++) {
    hB[i] = h * rt_ODE5_B[5][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2] +
                   f3[i]*hB[3] + f4[i]*hB[4] + f5[i]*hB[5]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Robot0_step(void)
{
  /* local block i/o variables */
  real_T rtb_TransferFcn1;
  real_T rtb_Filter;
  real_T rtb_Filter_f;
  real_T rtb_Sum_k;
  real_T rtb_Gain;
  real_T rtb_Sum_d;
  real_T rtb_Sum1_k;
  real_T rtb_Sum2;
  real_T u;
  if (rtmIsMajorTimeStep(Robot0_M)) {
    /* set solver stop time */
    if (!(Robot0_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Robot0_M->solverInfo,
                            ((Robot0_M->Timing.clockTickH0 + 1) *
        Robot0_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Robot0_M->solverInfo, ((Robot0_M->Timing.clockTick0
        + 1) * Robot0_M->Timing.stepSize0 + Robot0_M->Timing.clockTickH0 *
        Robot0_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Robot0_M)) {
    Robot0_M->Timing.t[0] = rtsiGetT(&Robot0_M->solverInfo);
  }

  /* TransferFcn: '<S6>/Transfer Fcn1' */
  rtb_TransferFcn1 = Robot0_P.TransferFcn1_C*Robot0_X.TransferFcn1_CSTATE;

  /* Gain: '<S1>/Bras de levier gauche' */
  Robot0_B.Brasdeleviergauche = Robot0_P.Brasdeleviergauche_Gain *
    rtb_TransferFcn1;

  /* TransferFcn: '<S5>/Transfer Fcn1' */
  rtb_Filter = Robot0_P.TransferFcn1_C_o*Robot0_X.TransferFcn1_CSTATE_f;

  /* Gain: '<S1>/Bras de levier droit' */
  Robot0_B.Brasdelevierdroit = Robot0_P.Brasdelevierdroit_Gain * rtb_Filter;

  /* Gain: '<S2>/Gain' incorporates:
   *  Sum: '<S2>/Sum'
   */
  rtb_Filter_f = (Robot0_B.Brasdeleviergauche + Robot0_B.Brasdelevierdroit) *
    Robot0_P.Gain_Gain;

  /* Gain: '<S2>/Gain1' incorporates:
   *  Sum: '<S2>/Sum1'
   */
  Robot0_B.Gain1 = (Robot0_B.Brasdeleviergauche - Robot0_B.Brasdelevierdroit) *
    Robot0_P.Gain1_Gain;

  /* Sum: '<S4>/Sum1' incorporates:
   *  Constant: '<S4>/x0'
   *  Integrator: '<S4>/Integrator1'
   */
  rtb_Sum1_k = Robot0_P.x0_Value + Robot0_X.Integrator1_CSTATE;

  /* Sum: '<S4>/Sum2' incorporates:
   *  Constant: '<S4>/y0'
   *  Integrator: '<S4>/Integrator2'
   */
  rtb_Sum2 = Robot0_P.y0_Value + Robot0_X.Integrator2_CSTATE;

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/thetam0'
   *  Integrator: '<S4>/Integrator'
   */
  rtb_Sum_k = Robot0_X.Integrator_CSTATE + Robot0_P.thetam0_Value;
  if (rtmIsMajorTimeStep(Robot0_M)) {
    /* Gain: '<S3>/Gain' incorporates:
     *  Gain: '<S3>/Gain1'
     *  Inport: '<Root>/w_ref'
     */
    rtb_Gain = Robot0_P.Gain1_Gain_j * Robot0_U.w_ref * Robot0_P.Gain_Gain_f;

    /* Sum: '<S3>/Sum' incorporates:
     *  Inport: '<Root>/v_ref'
     */
    Robot0_B.Sum = Robot0_U.v_ref - rtb_Gain;
  }

  /* Sum: '<S1>/Sum' */
  rtb_Sum_d = Robot0_B.Sum - Robot0_B.Brasdelevierdroit;
  if (rtmIsMajorTimeStep(Robot0_M)) {
    /* Sum: '<S3>/Sum1' incorporates:
     *  Inport: '<Root>/v_ref'
     */
    Robot0_B.Sum1 = Robot0_U.v_ref + rtb_Gain;
  }

  /* Product: '<S4>/Product' incorporates:
   *  Trigonometry: '<S4>/Trigonometric Function'
   */
  Robot0_B.Product = rtb_Filter_f * cos(rtb_Sum_k);

  /* Product: '<S4>/Product1' incorporates:
   *  Trigonometry: '<S4>/Trigonometric Function1'
   */
  Robot0_B.Product1 = rtb_Filter_f * sin(rtb_Sum_k);

  /* TransferFcn: '<S5>/Transfer Fcn' */
  Robot0_B.TransferFcn = Robot0_P.TransferFcn_C*Robot0_X.TransferFcn_CSTATE;
  if (rtmIsMajorTimeStep(Robot0_M)) {
  }

  /* Gain: '<S5>/Gain' */
  rtb_Gain = Robot0_P.Gain_Gain_c * Robot0_B.TransferFcn;

  /* DeadZone: '<S5>/Dead Zone' */
  if (rtb_Gain > Robot0_P.DeadZone_End) {
    Robot0_B.DeadZone = rtb_Gain - Robot0_P.DeadZone_End;
  } else if (rtb_Gain >= Robot0_P.DeadZone_Start) {
    Robot0_B.DeadZone = 0.0;
  } else {
    Robot0_B.DeadZone = rtb_Gain - Robot0_P.DeadZone_Start;
  }

  /* End of DeadZone: '<S5>/Dead Zone' */

  /* Gain: '<S5>/Gain1' */
  rtb_Gain = Robot0_P.Gain1_Gain_o * rtb_Filter;

  /* Integrator: '<S8>/Filter' */
  rtb_Filter = Robot0_X.Filter_CSTATE;

  /* Gain: '<S8>/Filter Coefficient' incorporates:
   *  Gain: '<S8>/Derivative Gain'
   *  Sum: '<S8>/SumD'
   */
  Robot0_B.FilterCoefficient = (Robot0_P.DerivativeGain_Gain * rtb_Sum_d -
    rtb_Filter) * Robot0_P.FilterCoefficient_Gain;

  /* Sum: '<S8>/Sum' incorporates:
   *  Gain: '<S8>/Proportional Gain'
   *  Integrator: '<S8>/Integrator'
   */
  u = (Robot0_P.ProportionalGain_Gain * rtb_Sum_d + Robot0_X.Integrator_CSTATE_k)
    + Robot0_B.FilterCoefficient;

  /* Saturate: '<S5>/Limitation Alim' */
  if (u >= Robot0_P.LimitationAlim_UpperSat) {
    u = Robot0_P.LimitationAlim_UpperSat;
  } else {
    if (u <= Robot0_P.LimitationAlim_LowerSat) {
      u = Robot0_P.LimitationAlim_LowerSat;
    }
  }

  /* Sum: '<S5>/Sum' incorporates:
   *  Saturate: '<S5>/Limitation Alim'
   */
  Robot0_B.Sum_n = u - rtb_Gain;

  /* TransferFcn: '<S6>/Transfer Fcn' */
  Robot0_B.TransferFcn_c = Robot0_P.TransferFcn_C_f*
    Robot0_X.TransferFcn_CSTATE_a;
  if (rtmIsMajorTimeStep(Robot0_M)) {
  }

  /* Gain: '<S6>/Gain' */
  rtb_Gain = Robot0_P.Gain_Gain_c5 * Robot0_B.TransferFcn_c;

  /* DeadZone: '<S6>/Dead Zone' */
  if (rtb_Gain > Robot0_P.DeadZone_End_i) {
    Robot0_B.DeadZone_h = rtb_Gain - Robot0_P.DeadZone_End_i;
  } else if (rtb_Gain >= Robot0_P.DeadZone_Start_b) {
    Robot0_B.DeadZone_h = 0.0;
  } else {
    Robot0_B.DeadZone_h = rtb_Gain - Robot0_P.DeadZone_Start_b;
  }

  /* End of DeadZone: '<S6>/Dead Zone' */

  /* Sum: '<S1>/Sum1' */
  rtb_Gain = Robot0_B.Sum1 - Robot0_B.Brasdeleviergauche;

  /* Outport: '<Root>/v' */
  Robot0_Y.v = rtb_Filter_f;

  /* Outport: '<Root>/w' */
  Robot0_Y.w = Robot0_B.Gain1;

  /* Outport: '<Root>/x' */
  Robot0_Y.x = rtb_Sum1_k;

  /* Outport: '<Root>/y' */
  Robot0_Y.y = rtb_Sum2;

  /* Outport: '<Root>/thetam' */
  Robot0_Y.thetam = rtb_Sum_k;

  /* Gain: '<S7>/Filter Coefficient' incorporates:
   *  Gain: '<S7>/Derivative Gain'
   *  Integrator: '<S7>/Filter'
   *  Sum: '<S7>/SumD'
   */
  Robot0_B.FilterCoefficient_o = (Robot0_P.DerivativeGain_Gain_g * rtb_Gain -
    Robot0_X.Filter_CSTATE_b) * Robot0_P.FilterCoefficient_Gain_g;

  /* Sum: '<S7>/Sum' incorporates:
   *  Gain: '<S7>/Proportional Gain'
   *  Integrator: '<S7>/Integrator'
   */
  u = (Robot0_P.ProportionalGain_Gain_i * rtb_Gain +
       Robot0_X.Integrator_CSTATE_b) + Robot0_B.FilterCoefficient_o;

  /* Saturate: '<S6>/Limitation Alim' */
  if (u >= Robot0_P.LimitationAlim_UpperSat_g) {
    u = Robot0_P.LimitationAlim_UpperSat_g;
  } else {
    if (u <= Robot0_P.LimitationAlim_LowerSat_m) {
      u = Robot0_P.LimitationAlim_LowerSat_m;
    }
  }

  /* Sum: '<S6>/Sum' incorporates:
   *  Gain: '<S6>/Gain1'
   *  Saturate: '<S6>/Limitation Alim'
   */
  Robot0_B.Sum_h = u - Robot0_P.Gain1_Gain_n * rtb_TransferFcn1;

  /* Gain: '<S7>/Integral Gain' */
  Robot0_B.IntegralGain = Robot0_P.IntegralGain_Gain * rtb_Gain;

  /* Gain: '<S8>/Integral Gain' */
  Robot0_B.IntegralGain_g = Robot0_P.IntegralGain_Gain_p * rtb_Sum_d;
  if (rtmIsMajorTimeStep(Robot0_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(Robot0_M->rtwLogInfo, (Robot0_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Robot0_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Robot0_M)!=-1) &&
          !((rtmGetTFinal(Robot0_M)-(((Robot0_M->Timing.clockTick1+
               Robot0_M->Timing.clockTickH1* 4294967296.0)) * 0.2)) >
            (((Robot0_M->Timing.clockTick1+Robot0_M->Timing.clockTickH1*
               4294967296.0)) * 0.2) * (DBL_EPSILON))) {
        rtmSetErrorStatus(Robot0_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&Robot0_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Robot0_M->Timing.clockTick0)) {
      ++Robot0_M->Timing.clockTickH0;
    }

    Robot0_M->Timing.t[0] = rtsiGetSolverStopTime(&Robot0_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      Robot0_M->Timing.clockTick1++;
      if (!Robot0_M->Timing.clockTick1) {
        Robot0_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Robot0_derivatives(void)
{
  XDot_Robot0_T *_rtXdot;
  _rtXdot = ((XDot_Robot0_T *) Robot0_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<S6>/Transfer Fcn1' */
  {
    ((XDot_Robot0_T *) Robot0_M->ModelData.derivs)->TransferFcn1_CSTATE =
      Robot0_B.DeadZone_h;
    ((XDot_Robot0_T *) Robot0_M->ModelData.derivs)->TransferFcn1_CSTATE +=
      (Robot0_P.TransferFcn1_A)*Robot0_X.TransferFcn1_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S5>/Transfer Fcn1' */
  {
    ((XDot_Robot0_T *) Robot0_M->ModelData.derivs)->TransferFcn1_CSTATE_f =
      Robot0_B.DeadZone;
    ((XDot_Robot0_T *) Robot0_M->ModelData.derivs)->TransferFcn1_CSTATE_f +=
      (Robot0_P.TransferFcn1_A_b)*Robot0_X.TransferFcn1_CSTATE_f;
  }

  /* Derivatives for Integrator: '<S4>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = Robot0_B.Product;

  /* Derivatives for Integrator: '<S4>/Integrator2' */
  _rtXdot->Integrator2_CSTATE = Robot0_B.Product1;

  /* Derivatives for Integrator: '<S4>/Integrator' */
  _rtXdot->Integrator_CSTATE = Robot0_B.Gain1;

  /* Derivatives for TransferFcn: '<S5>/Transfer Fcn' */
  {
    ((XDot_Robot0_T *) Robot0_M->ModelData.derivs)->TransferFcn_CSTATE =
      Robot0_B.Sum_n;
    ((XDot_Robot0_T *) Robot0_M->ModelData.derivs)->TransferFcn_CSTATE +=
      (Robot0_P.TransferFcn_A)*Robot0_X.TransferFcn_CSTATE;
  }

  /* Derivatives for Integrator: '<S8>/Integrator' */
  _rtXdot->Integrator_CSTATE_k = Robot0_B.IntegralGain_g;

  /* Derivatives for Integrator: '<S8>/Filter' */
  _rtXdot->Filter_CSTATE = Robot0_B.FilterCoefficient;

  /* Derivatives for TransferFcn: '<S6>/Transfer Fcn' */
  {
    ((XDot_Robot0_T *) Robot0_M->ModelData.derivs)->TransferFcn_CSTATE_a =
      Robot0_B.Sum_h;
    ((XDot_Robot0_T *) Robot0_M->ModelData.derivs)->TransferFcn_CSTATE_a +=
      (Robot0_P.TransferFcn_A_j)*Robot0_X.TransferFcn_CSTATE_a;
  }

  /* Derivatives for Integrator: '<S7>/Integrator' */
  _rtXdot->Integrator_CSTATE_b = Robot0_B.IntegralGain;

  /* Derivatives for Integrator: '<S7>/Filter' */
  _rtXdot->Filter_CSTATE_b = Robot0_B.FilterCoefficient_o;
}

/* Model initialize function */
void Robot0_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Robot0_M, 0,
                sizeof(RT_MODEL_Robot0_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Robot0_M->solverInfo, &Robot0_M->Timing.simTimeStep);
    rtsiSetTPtr(&Robot0_M->solverInfo, &rtmGetTPtr(Robot0_M));
    rtsiSetStepSizePtr(&Robot0_M->solverInfo, &Robot0_M->Timing.stepSize0);
    rtsiSetdXPtr(&Robot0_M->solverInfo, &Robot0_M->ModelData.derivs);
    rtsiSetContStatesPtr(&Robot0_M->solverInfo, &Robot0_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&Robot0_M->solverInfo,
      &Robot0_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&Robot0_M->solverInfo, (&rtmGetErrorStatus(Robot0_M)));
    rtsiSetRTModelPtr(&Robot0_M->solverInfo, Robot0_M);
  }

  rtsiSetSimTimeStep(&Robot0_M->solverInfo, MAJOR_TIME_STEP);
  Robot0_M->ModelData.intgData.y = Robot0_M->ModelData.odeY;
  Robot0_M->ModelData.intgData.f[0] = Robot0_M->ModelData.odeF[0];
  Robot0_M->ModelData.intgData.f[1] = Robot0_M->ModelData.odeF[1];
  Robot0_M->ModelData.intgData.f[2] = Robot0_M->ModelData.odeF[2];
  Robot0_M->ModelData.intgData.f[3] = Robot0_M->ModelData.odeF[3];
  Robot0_M->ModelData.intgData.f[4] = Robot0_M->ModelData.odeF[4];
  Robot0_M->ModelData.intgData.f[5] = Robot0_M->ModelData.odeF[5];
  Robot0_M->ModelData.contStates = ((real_T *) &Robot0_X);
  rtsiSetSolverData(&Robot0_M->solverInfo, (void *)&Robot0_M->ModelData.intgData);
  rtsiSetSolverName(&Robot0_M->solverInfo,"ode5");
  rtmSetTPtr(Robot0_M, &Robot0_M->Timing.tArray[0]);
  rtmSetTFinal(Robot0_M, 1.4000000000000001);
  Robot0_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    Robot0_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Robot0_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Robot0_M->rtwLogInfo, (NULL));
    rtliSetLogT(Robot0_M->rtwLogInfo, "tout");
    rtliSetLogX(Robot0_M->rtwLogInfo, "");
    rtliSetLogXFinal(Robot0_M->rtwLogInfo, "");
    rtliSetSigLog(Robot0_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Robot0_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Robot0_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(Robot0_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(Robot0_M->rtwLogInfo, 1);

    /*
     * Set pointers to the data and signal info for each output
     */
    {
      static void * rt_LoggedOutputSignalPtrs[] = {
        &Robot0_Y.v,
        &Robot0_Y.w,
        &Robot0_Y.x,
        &Robot0_Y.y,
        &Robot0_Y.thetam
      };

      rtliSetLogYSignalPtrs(Robot0_M->rtwLogInfo, ((LogSignalPtrsType)
        rt_LoggedOutputSignalPtrs));
    }

    {
      static int_T rt_LoggedOutputWidths[] = {
        1,
        1,
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputNumDimensions[] = {
        1,
        1,
        1,
        1,
        1
      };

      static int_T rt_LoggedOutputDimensions[] = {
        1,
        1,
        1,
        1,
        1
      };

      static boolean_T rt_LoggedOutputIsVarDims[] = {
        0,
        0,
        0,
        0,
        0
      };

      static void* rt_LoggedCurrentSignalDimensions[] = {
        (NULL),
        (NULL),
        (NULL),
        (NULL),
        (NULL)
      };

      static int_T rt_LoggedCurrentSignalDimensionsSize[] = {
        4,
        4,
        4,
        4,
        4
      };

      static BuiltInDTypeId rt_LoggedOutputDataTypeIds[] = {
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE,
        SS_DOUBLE
      };

      static int_T rt_LoggedOutputComplexSignals[] = {
        0,
        0,
        0,
        0,
        0
      };

      static const char_T *rt_LoggedOutputLabels[] = {
        "",
        "",
        "",
        "",
        "" };

      static const char_T *rt_LoggedOutputBlockNames[] = {
        "Robot0/v",
        "Robot0/w",
        "Robot0/x",
        "Robot0/y",
        "Robot0/thetam" };

      static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert[] = {
        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 },

        { 0, SS_DOUBLE, SS_DOUBLE, 0, 0, 0, 1.0, 0, 0.0 }
      };

      static RTWLogSignalInfo rt_LoggedOutputSignalInfo[] = {
        {
          5,
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

      rtliSetLogYSignalInfo(Robot0_M->rtwLogInfo, rt_LoggedOutputSignalInfo);

      /* set currSigDims field */
      rt_LoggedCurrentSignalDimensions[0] = &rt_LoggedOutputWidths[0];
      rt_LoggedCurrentSignalDimensions[1] = &rt_LoggedOutputWidths[1];
      rt_LoggedCurrentSignalDimensions[2] = &rt_LoggedOutputWidths[2];
      rt_LoggedCurrentSignalDimensions[3] = &rt_LoggedOutputWidths[3];
      rt_LoggedCurrentSignalDimensions[4] = &rt_LoggedOutputWidths[4];
    }

    rtliSetLogY(Robot0_M->rtwLogInfo, "yout");
  }

  /* block I/O */
  (void) memset(((void *) &Robot0_B), 0,
                sizeof(B_Robot0_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Robot0_X, 0,
                  sizeof(X_Robot0_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Robot0_DW, 0,
                sizeof(DW_Robot0_T));

  /* external inputs */
  (void) memset((void *)&Robot0_U, 0,
                sizeof(ExtU_Robot0_T));

  /* external outputs */
  (void) memset((void *)&Robot0_Y, 0,
                sizeof(ExtY_Robot0_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Robot0_M->rtwLogInfo, 0.0, rtmGetTFinal
    (Robot0_M), Robot0_M->Timing.stepSize0, (&rtmGetErrorStatus(Robot0_M)));

  /* InitializeConditions for TransferFcn: '<S6>/Transfer Fcn1' */
  Robot0_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Transfer Fcn1' */
  Robot0_X.TransferFcn1_CSTATE_f = 0.0;

  /* InitializeConditions for Integrator: '<S4>/Integrator1' */
  Robot0_X.Integrator1_CSTATE = Robot0_P.Integrator1_IC;

  /* InitializeConditions for Integrator: '<S4>/Integrator2' */
  Robot0_X.Integrator2_CSTATE = Robot0_P.Integrator2_IC;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  Robot0_X.Integrator_CSTATE = Robot0_P.Integrator_IC;

  /* InitializeConditions for TransferFcn: '<S5>/Transfer Fcn' */
  Robot0_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S8>/Integrator' */
  Robot0_X.Integrator_CSTATE_k = Robot0_P.Integrator_IC_n;

  /* InitializeConditions for Integrator: '<S8>/Filter' */
  Robot0_X.Filter_CSTATE = Robot0_P.Filter_IC;

  /* InitializeConditions for TransferFcn: '<S6>/Transfer Fcn' */
  Robot0_X.TransferFcn_CSTATE_a = 0.0;

  /* InitializeConditions for Integrator: '<S7>/Integrator' */
  Robot0_X.Integrator_CSTATE_b = Robot0_P.Integrator_IC_i;

  /* InitializeConditions for Integrator: '<S7>/Filter' */
  Robot0_X.Filter_CSTATE_b = Robot0_P.Filter_IC_k;
}

/* Model terminate function */
void Robot0_terminate(void)
{
  /* (no terminate code required) */
}
