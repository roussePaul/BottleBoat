/*
 * Robot0_data.c
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

/* Block parameters (auto storage) */
P_Robot0_T Robot0_P = {
  -1.1300513526771057,                 /* Computed Parameter: TransferFcn1_A
                                        * Referenced by: '<S6>/Transfer Fcn1'
                                        */
  256.82985288116038,                  /* Computed Parameter: TransferFcn1_C
                                        * Referenced by: '<S6>/Transfer Fcn1'
                                        */
  0.1729,                              /* Expression: d
                                        * Referenced by: '<S1>/Bras de levier gauche'
                                        */
  -1.1300513526771057,                 /* Computed Parameter: TransferFcn1_A_b
                                        * Referenced by: '<S5>/Transfer Fcn1'
                                        */
  256.82985288116038,                  /* Computed Parameter: TransferFcn1_C_o
                                        * Referenced by: '<S5>/Transfer Fcn1'
                                        */
  0.1729,                              /* Expression: d
                                        * Referenced by: '<S1>/Bras de levier droit'
                                        */
  0.5,                                 /* Expression: 1/2
                                        * Referenced by: '<S2>/Gain'
                                        */
  5.78368999421631,                    /* Expression: 1/d
                                        * Referenced by: '<S2>/Gain1'
                                        */
  0.0001,                              /* Expression: 0.0001
                                        * Referenced by: '<S4>/x0'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Integrator1'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/y0'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Integrator2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/thetam0'
                                        */
  0.1729,                              /* Expression: d
                                        * Referenced by: '<S3>/Gain1'
                                        */
  0.5,                                 /* Expression: 1/2
                                        * Referenced by: '<S3>/Gain'
                                        */
  -555.0,                              /* Computed Parameter: TransferFcn_A
                                        * Referenced by: '<S5>/Transfer Fcn'
                                        */
  396.42857142857144,                  /* Computed Parameter: TransferFcn_C
                                        * Referenced by: '<S5>/Transfer Fcn'
                                        */
  0.4265,                              /* Expression: K
                                        * Referenced by: '<S5>/Gain'
                                        */
  -0.1316,                             /* Expression: -Cs
                                        * Referenced by: '<S5>/Dead Zone'
                                        */
  0.1316,                              /* Expression: Cs
                                        * Referenced by: '<S5>/Dead Zone'
                                        */
  0.4265,                              /* Expression: K
                                        * Referenced by: '<S5>/Gain1'
                                        */
  0.787954322243834,                   /* Expression: P
                                        * Referenced by: '<S8>/Proportional Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S8>/Integrator'
                                        */
  0.0,                                 /* Expression: D
                                        * Referenced by: '<S8>/Derivative Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S8>/Filter'
                                        */
  100.0,                               /* Expression: N
                                        * Referenced by: '<S8>/Filter Coefficient'
                                        */
  8.0,                                 /* Expression: Vmax
                                        * Referenced by: '<S5>/Limitation Alim'
                                        */
  -8.0,                                /* Expression: Vmin
                                        * Referenced by: '<S5>/Limitation Alim'
                                        */
  -555.0,                              /* Computed Parameter: TransferFcn_A_j
                                        * Referenced by: '<S6>/Transfer Fcn'
                                        */
  396.42857142857144,                  /* Computed Parameter: TransferFcn_C_f
                                        * Referenced by: '<S6>/Transfer Fcn'
                                        */
  0.4265,                              /* Expression: K
                                        * Referenced by: '<S6>/Gain'
                                        */
  -0.1316,                             /* Expression: -Cs
                                        * Referenced by: '<S6>/Dead Zone'
                                        */
  0.1316,                              /* Expression: Cs
                                        * Referenced by: '<S6>/Dead Zone'
                                        */
  0.4265,                              /* Expression: K
                                        * Referenced by: '<S6>/Gain1'
                                        */
  0.787954322243834,                   /* Expression: P
                                        * Referenced by: '<S7>/Proportional Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S7>/Integrator'
                                        */
  0.0,                                 /* Expression: D
                                        * Referenced by: '<S7>/Derivative Gain'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S7>/Filter'
                                        */
  100.0,                               /* Expression: N
                                        * Referenced by: '<S7>/Filter Coefficient'
                                        */
  8.0,                                 /* Expression: Vmax
                                        * Referenced by: '<S6>/Limitation Alim'
                                        */
  -8.0,                                /* Expression: Vmin
                                        * Referenced by: '<S6>/Limitation Alim'
                                        */
  47.7786820376876,                    /* Expression: I
                                        * Referenced by: '<S7>/Integral Gain'
                                        */
  47.7786820376876                     /* Expression: I
                                        * Referenced by: '<S8>/Integral Gain'
                                        */
};
