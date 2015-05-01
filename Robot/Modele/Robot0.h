/*
 * Robot0.h
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
#ifndef RTW_HEADER_Robot0_h_
#define RTW_HEADER_Robot0_h_
#ifndef Robot0_COMMON_INCLUDES_
# define Robot0_COMMON_INCLUDES_
#include <float.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#endif                                 /* Robot0_COMMON_INCLUDES_ */

#include "Robot0_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T Brasdeleviergauche;           /* '<S1>/Bras de levier gauche' */
  real_T Brasdelevierdroit;            /* '<S1>/Bras de levier droit' */
  real_T Gain1;                        /* '<S2>/Gain1' */
  real_T Sum;                          /* '<S3>/Sum' */
  real_T Sum1;                         /* '<S3>/Sum1' */
  real_T Product;                      /* '<S4>/Product' */
  real_T Product1;                     /* '<S4>/Product1' */
  real_T TransferFcn;                  /* '<S5>/Transfer Fcn' */
  real_T DeadZone;                     /* '<S5>/Dead Zone' */
  real_T FilterCoefficient;            /* '<S8>/Filter Coefficient' */
  real_T Sum_n;                        /* '<S5>/Sum' */
  real_T TransferFcn_c;                /* '<S6>/Transfer Fcn' */
  real_T DeadZone_h;                   /* '<S6>/Dead Zone' */
  real_T FilterCoefficient_o;          /* '<S7>/Filter Coefficient' */
  real_T Sum_h;                        /* '<S6>/Sum' */
  real_T IntegralGain;                 /* '<S7>/Integral Gain' */
  real_T IntegralGain_g;               /* '<S8>/Integral Gain' */
} B_Robot0_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S1>/Scope1' */

  struct {
    void *LoggedData;
  } Scope2_PWORK;                      /* '<S1>/Scope2' */

  struct {
    void *LoggedData;
  } Scope1_PWORK_n;                    /* '<S5>/Scope1' */

  struct {
    void *LoggedData;
  } Scope1_PWORK_j;                    /* '<S6>/Scope1' */
} DW_Robot0_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T TransferFcn1_CSTATE;          /* '<S6>/Transfer Fcn1' */
  real_T TransferFcn1_CSTATE_f;        /* '<S5>/Transfer Fcn1' */
  real_T Integrator1_CSTATE;           /* '<S4>/Integrator1' */
  real_T Integrator2_CSTATE;           /* '<S4>/Integrator2' */
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
  real_T TransferFcn_CSTATE;           /* '<S5>/Transfer Fcn' */
  real_T Integrator_CSTATE_k;          /* '<S8>/Integrator' */
  real_T Filter_CSTATE;                /* '<S8>/Filter' */
  real_T TransferFcn_CSTATE_a;         /* '<S6>/Transfer Fcn' */
  real_T Integrator_CSTATE_b;          /* '<S7>/Integrator' */
  real_T Filter_CSTATE_b;              /* '<S7>/Filter' */
} X_Robot0_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T TransferFcn1_CSTATE;          /* '<S6>/Transfer Fcn1' */
  real_T TransferFcn1_CSTATE_f;        /* '<S5>/Transfer Fcn1' */
  real_T Integrator1_CSTATE;           /* '<S4>/Integrator1' */
  real_T Integrator2_CSTATE;           /* '<S4>/Integrator2' */
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
  real_T TransferFcn_CSTATE;           /* '<S5>/Transfer Fcn' */
  real_T Integrator_CSTATE_k;          /* '<S8>/Integrator' */
  real_T Filter_CSTATE;                /* '<S8>/Filter' */
  real_T TransferFcn_CSTATE_a;         /* '<S6>/Transfer Fcn' */
  real_T Integrator_CSTATE_b;          /* '<S7>/Integrator' */
  real_T Filter_CSTATE_b;              /* '<S7>/Filter' */
} XDot_Robot0_T;

/* State disabled  */
typedef struct {
  boolean_T TransferFcn1_CSTATE;       /* '<S6>/Transfer Fcn1' */
  boolean_T TransferFcn1_CSTATE_f;     /* '<S5>/Transfer Fcn1' */
  boolean_T Integrator1_CSTATE;        /* '<S4>/Integrator1' */
  boolean_T Integrator2_CSTATE;        /* '<S4>/Integrator2' */
  boolean_T Integrator_CSTATE;         /* '<S4>/Integrator' */
  boolean_T TransferFcn_CSTATE;        /* '<S5>/Transfer Fcn' */
  boolean_T Integrator_CSTATE_k;       /* '<S8>/Integrator' */
  boolean_T Filter_CSTATE;             /* '<S8>/Filter' */
  boolean_T TransferFcn_CSTATE_a;      /* '<S6>/Transfer Fcn' */
  boolean_T Integrator_CSTATE_b;       /* '<S7>/Integrator' */
  boolean_T Filter_CSTATE_b;           /* '<S7>/Filter' */
} XDis_Robot0_T;

#ifndef ODE5_INTG
#define ODE5_INTG

/* ODE5 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[6];                        /* derivatives */
} ODE5_IntgData;

#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T v_ref;                        /* '<Root>/v_ref' */
  real_T w_ref;                        /* '<Root>/w_ref' */
} ExtU_Robot0_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T v;                            /* '<Root>/v' */
  real_T w;                            /* '<Root>/w' */
  real_T x;                            /* '<Root>/x' */
  real_T y;                            /* '<Root>/y' */
  real_T thetam;                       /* '<Root>/thetam' */
} ExtY_Robot0_T;

/* Parameters (auto storage) */
struct P_Robot0_T_ {
  real_T TransferFcn1_A;               /* Computed Parameter: TransferFcn1_A
                                        * Referenced by: '<S6>/Transfer Fcn1'
                                        */
  real_T TransferFcn1_C;               /* Computed Parameter: TransferFcn1_C
                                        * Referenced by: '<S6>/Transfer Fcn1'
                                        */
  real_T Brasdeleviergauche_Gain;      /* Expression: d
                                        * Referenced by: '<S1>/Bras de levier gauche'
                                        */
  real_T TransferFcn1_A_b;             /* Computed Parameter: TransferFcn1_A_b
                                        * Referenced by: '<S5>/Transfer Fcn1'
                                        */
  real_T TransferFcn1_C_o;             /* Computed Parameter: TransferFcn1_C_o
                                        * Referenced by: '<S5>/Transfer Fcn1'
                                        */
  real_T Brasdelevierdroit_Gain;       /* Expression: d
                                        * Referenced by: '<S1>/Bras de levier droit'
                                        */
  real_T Gain_Gain;                    /* Expression: 1/2
                                        * Referenced by: '<S2>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 1/d
                                        * Referenced by: '<S2>/Gain1'
                                        */
  real_T x0_Value;                     /* Expression: 0.0001
                                        * Referenced by: '<S4>/x0'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<S4>/Integrator1'
                                        */
  real_T y0_Value;                     /* Expression: 0
                                        * Referenced by: '<S4>/y0'
                                        */
  real_T Integrator2_IC;               /* Expression: 0
                                        * Referenced by: '<S4>/Integrator2'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S4>/Integrator'
                                        */
  real_T thetam0_Value;                /* Expression: 0
                                        * Referenced by: '<S4>/thetam0'
                                        */
  real_T Gain1_Gain_j;                 /* Expression: d
                                        * Referenced by: '<S3>/Gain1'
                                        */
  real_T Gain_Gain_f;                  /* Expression: 1/2
                                        * Referenced by: '<S3>/Gain'
                                        */
  real_T TransferFcn_A;                /* Computed Parameter: TransferFcn_A
                                        * Referenced by: '<S5>/Transfer Fcn'
                                        */
  real_T TransferFcn_C;                /* Computed Parameter: TransferFcn_C
                                        * Referenced by: '<S5>/Transfer Fcn'
                                        */
  real_T Gain_Gain_c;                  /* Expression: K
                                        * Referenced by: '<S5>/Gain'
                                        */
  real_T DeadZone_Start;               /* Expression: -Cs
                                        * Referenced by: '<S5>/Dead Zone'
                                        */
  real_T DeadZone_End;                 /* Expression: Cs
                                        * Referenced by: '<S5>/Dead Zone'
                                        */
  real_T Gain1_Gain_o;                 /* Expression: K
                                        * Referenced by: '<S5>/Gain1'
                                        */
  real_T ProportionalGain_Gain;        /* Expression: P
                                        * Referenced by: '<S8>/Proportional Gain'
                                        */
  real_T Integrator_IC_n;              /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S8>/Integrator'
                                        */
  real_T DerivativeGain_Gain;          /* Expression: D
                                        * Referenced by: '<S8>/Derivative Gain'
                                        */
  real_T Filter_IC;                    /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S8>/Filter'
                                        */
  real_T FilterCoefficient_Gain;       /* Expression: N
                                        * Referenced by: '<S8>/Filter Coefficient'
                                        */
  real_T LimitationAlim_UpperSat;      /* Expression: Vmax
                                        * Referenced by: '<S5>/Limitation Alim'
                                        */
  real_T LimitationAlim_LowerSat;      /* Expression: Vmin
                                        * Referenced by: '<S5>/Limitation Alim'
                                        */
  real_T TransferFcn_A_j;              /* Computed Parameter: TransferFcn_A_j
                                        * Referenced by: '<S6>/Transfer Fcn'
                                        */
  real_T TransferFcn_C_f;              /* Computed Parameter: TransferFcn_C_f
                                        * Referenced by: '<S6>/Transfer Fcn'
                                        */
  real_T Gain_Gain_c5;                 /* Expression: K
                                        * Referenced by: '<S6>/Gain'
                                        */
  real_T DeadZone_Start_b;             /* Expression: -Cs
                                        * Referenced by: '<S6>/Dead Zone'
                                        */
  real_T DeadZone_End_i;               /* Expression: Cs
                                        * Referenced by: '<S6>/Dead Zone'
                                        */
  real_T Gain1_Gain_n;                 /* Expression: K
                                        * Referenced by: '<S6>/Gain1'
                                        */
  real_T ProportionalGain_Gain_i;      /* Expression: P
                                        * Referenced by: '<S7>/Proportional Gain'
                                        */
  real_T Integrator_IC_i;              /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S7>/Integrator'
                                        */
  real_T DerivativeGain_Gain_g;        /* Expression: D
                                        * Referenced by: '<S7>/Derivative Gain'
                                        */
  real_T Filter_IC_k;                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S7>/Filter'
                                        */
  real_T FilterCoefficient_Gain_g;     /* Expression: N
                                        * Referenced by: '<S7>/Filter Coefficient'
                                        */
  real_T LimitationAlim_UpperSat_g;    /* Expression: Vmax
                                        * Referenced by: '<S6>/Limitation Alim'
                                        */
  real_T LimitationAlim_LowerSat_m;    /* Expression: Vmin
                                        * Referenced by: '<S6>/Limitation Alim'
                                        */
  real_T IntegralGain_Gain;            /* Expression: I
                                        * Referenced by: '<S7>/Integral Gain'
                                        */
  real_T IntegralGain_Gain_p;          /* Expression: I
                                        * Referenced by: '<S8>/Integral Gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Robot0_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    real_T *contStates;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[11];
    real_T odeF[6][11];
    ODE5_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_Robot0_T Robot0_P;

/* Block signals (auto storage) */
extern B_Robot0_T Robot0_B;

/* Continuous states (auto storage) */
extern X_Robot0_T Robot0_X;

/* Block states (auto storage) */
extern DW_Robot0_T Robot0_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_Robot0_T Robot0_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_Robot0_T Robot0_Y;

/* Model entry point functions */
extern void Robot0_initialize(void);
extern void Robot0_step(void);
extern void Robot0_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Robot0_T *const Robot0_M;

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
 * hilite_system('Robot/Robot')    - opens subsystem Robot/Robot
 * hilite_system('Robot/Robot/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Robot'
 * '<S1>'   : 'Robot/Robot'
 * '<S2>'   : 'Robot/Robot/Conv'
 * '<S3>'   : 'Robot/Robot/Conversion'
 * '<S4>'   : 'Robot/Robot/Modèle du mvt'
 * '<S5>'   : 'Robot/Robot/Moteur droit'
 * '<S6>'   : 'Robot/Robot/Moteur gauche'
 * '<S7>'   : 'Robot/Robot/PID1'
 * '<S8>'   : 'Robot/Robot/PID2'
 */
#endif                                 /* RTW_HEADER_Robot0_h_ */
