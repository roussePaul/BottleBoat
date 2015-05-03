/*
 * BoatModele.h
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
#ifndef RTW_HEADER_BoatModele_h_
#define RTW_HEADER_BoatModele_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef BoatModele_COMMON_INCLUDES_
# define BoatModele_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* BoatModele_COMMON_INCLUDES_ */

#include "BoatModele_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtsplntypes.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

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
  real_T X_dot_ext[9];                 /* '<S1>/MATLAB Function' */
} B_BoatModele_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T m_bpLambda;                   /* '<S1>/1-D Lookup Table' */
  real_T m_yyA;                        /* '<S1>/1-D Lookup Table' */
  real_T m_yyB;                        /* '<S1>/1-D Lookup Table' */
  real_T m_yy2;                        /* '<S1>/1-D Lookup Table' */
  real_T m_up[100];                    /* '<S1>/1-D Lookup Table' */
  real_T m_y2[100];                    /* '<S1>/1-D Lookup Table' */
  real_T m_bpLambda_n;                 /* '<S1>/1-D Lookup Table4' */
  real_T m_yyA_i;                      /* '<S1>/1-D Lookup Table4' */
  real_T m_yyB_l;                      /* '<S1>/1-D Lookup Table4' */
  real_T m_yy2_k;                      /* '<S1>/1-D Lookup Table4' */
  real_T m_up_f[100];                  /* '<S1>/1-D Lookup Table4' */
  real_T m_y2_c[100];                  /* '<S1>/1-D Lookup Table4' */
  real_T m_bpLambda_k;                 /* '<S1>/1-D Lookup Table1' */
  real_T m_yyA_n;                      /* '<S1>/1-D Lookup Table1' */
  real_T m_yyB_e;                      /* '<S1>/1-D Lookup Table1' */
  real_T m_yy2_j;                      /* '<S1>/1-D Lookup Table1' */
  real_T m_up_g[100];                  /* '<S1>/1-D Lookup Table1' */
  real_T m_y2_cz[100];                 /* '<S1>/1-D Lookup Table1' */
  real_T m_bpLambda_g;                 /* '<S1>/1-D Lookup Table5' */
  real_T m_yyA_l;                      /* '<S1>/1-D Lookup Table5' */
  real_T m_yyB_i;                      /* '<S1>/1-D Lookup Table5' */
  real_T m_yy2_n;                      /* '<S1>/1-D Lookup Table5' */
  real_T m_up_n[100];                  /* '<S1>/1-D Lookup Table5' */
  real_T m_y2_g[100];                  /* '<S1>/1-D Lookup Table5' */
  real_T m_bpLambda_kf;                /* '<S1>/1-D Lookup Table2' */
  real_T m_yyA_nz;                     /* '<S1>/1-D Lookup Table2' */
  real_T m_yyB_ex;                     /* '<S1>/1-D Lookup Table2' */
  real_T m_yy2_c;                      /* '<S1>/1-D Lookup Table2' */
  real_T m_up_k[100];                  /* '<S1>/1-D Lookup Table2' */
  real_T m_y2_a[100];                  /* '<S1>/1-D Lookup Table2' */
  real_T m_bpLambda_h;                 /* '<S1>/1-D Lookup Table6' */
  real_T m_yyA_c;                      /* '<S1>/1-D Lookup Table6' */
  real_T m_yyB_i5;                     /* '<S1>/1-D Lookup Table6' */
  real_T m_yy2_h;                      /* '<S1>/1-D Lookup Table6' */
  real_T m_up_o[100];                  /* '<S1>/1-D Lookup Table6' */
  real_T m_y2_f[100];                  /* '<S1>/1-D Lookup Table6' */
  void* m_bpDataSet;                   /* '<S1>/1-D Lookup Table' */
  void* TWork[6];                      /* '<S1>/1-D Lookup Table' */
  void* SWork[7];                      /* '<S1>/1-D Lookup Table' */
  void* m_bpDataSet_c;                 /* '<S1>/1-D Lookup Table4' */
  void* TWork_a[6];                    /* '<S1>/1-D Lookup Table4' */
  void* SWork_k[7];                    /* '<S1>/1-D Lookup Table4' */
  void* m_bpDataSet_j;                 /* '<S1>/1-D Lookup Table1' */
  void* TWork_c[6];                    /* '<S1>/1-D Lookup Table1' */
  void* SWork_j[7];                    /* '<S1>/1-D Lookup Table1' */
  void* m_bpDataSet_g;                 /* '<S1>/1-D Lookup Table5' */
  void* TWork_d[6];                    /* '<S1>/1-D Lookup Table5' */
  void* SWork_kl[7];                   /* '<S1>/1-D Lookup Table5' */
  void* m_bpDataSet_h;                 /* '<S1>/1-D Lookup Table2' */
  void* TWork_m[6];                    /* '<S1>/1-D Lookup Table2' */
  void* SWork_a[7];                    /* '<S1>/1-D Lookup Table2' */
  void* m_bpDataSet_n;                 /* '<S1>/1-D Lookup Table6' */
  void* TWork_i[6];                    /* '<S1>/1-D Lookup Table6' */
  void* SWork_e[7];                    /* '<S1>/1-D Lookup Table6' */
  uint32_T m_bpIndex;                  /* '<S1>/1-D Lookup Table' */
  uint32_T m_bpIndex_n;                /* '<S1>/1-D Lookup Table4' */
  uint32_T m_bpIndex_a;                /* '<S1>/1-D Lookup Table1' */
  uint32_T m_bpIndex_j;                /* '<S1>/1-D Lookup Table5' */
  uint32_T m_bpIndex_jk;               /* '<S1>/1-D Lookup Table2' */
  uint32_T m_bpIndex_b;                /* '<S1>/1-D Lookup Table6' */
  struct {
    int_T IcNeedsLoading;
  } Integrator_IWORK;                  /* '<S1>/Integrator' */
} DW_BoatModele_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[8];         /* '<S1>/Integrator' */
} X_BoatModele_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[8];         /* '<S1>/Integrator' */
} XDot_BoatModele_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[8];      /* '<S1>/Integrator' */
} XDis_BoatModele_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T X_0[8];                       /* '<Root>/X_0' */
  real_T U[4];                         /* '<Root>/U' */
} ExtU_BoatModele_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T X[8];                         /* '<Root>/X' */
  real_T delta_s;                      /* '<Root>/delta_s' */
} ExtY_BoatModele_T;

/* Parameters (auto storage) */
struct P_BoatModele_T_ {
  real_T alphacoeff_xdata[100];        /* Variable: alphacoeff_xdata
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table'
                                        *   '<S1>/1-D Lookup Table4'
                                        */
  real_T alphacoeff_yddata[100];       /* Variable: alphacoeff_yddata
                                        * Referenced by: '<S1>/1-D Lookup Table4'
                                        */
  real_T alphacoeff_yldata[100];       /* Variable: alphacoeff_yldata
                                        * Referenced by: '<S1>/1-D Lookup Table'
                                        */
  real_T hull_xdata[100];              /* Variable: hull_xdata
                                        * Referenced by: '<S1>/1-D Lookup Table3'
                                        */
  real_T hull_ydata[100];              /* Variable: hull_ydata
                                        * Referenced by: '<S1>/1-D Lookup Table3'
                                        */
  real_T keelcoeff_xdata[100];         /* Variable: keelcoeff_xdata
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table2'
                                        *   '<S1>/1-D Lookup Table6'
                                        */
  real_T keelcoeff_yddata[100];        /* Variable: keelcoeff_yddata
                                        * Referenced by: '<S1>/1-D Lookup Table6'
                                        */
  real_T keelcoeff_yldata[100];        /* Variable: keelcoeff_yldata
                                        * Referenced by: '<S1>/1-D Lookup Table2'
                                        */
  real_T ruddercoeff_xdata[100];       /* Variable: ruddercoeff_xdata
                                        * Referenced by:
                                        *   '<S1>/1-D Lookup Table1'
                                        *   '<S1>/1-D Lookup Table5'
                                        */
  real_T ruddercoeff_yddata[100];      /* Variable: ruddercoeff_yddata
                                        * Referenced by: '<S1>/1-D Lookup Table5'
                                        */
  real_T ruddercoeff_yldata[100];      /* Variable: ruddercoeff_yldata
                                        * Referenced by: '<S1>/1-D Lookup Table1'
                                        */
  uint32_T DLookupTable_maxIndex;      /* Computed Parameter: DLookupTable_maxIndex
                                        * Referenced by: '<S1>/1-D Lookup Table'
                                        */
  uint32_T DLookupTable_dimSizes;      /* Computed Parameter: DLookupTable_dimSizes
                                        * Referenced by: '<S1>/1-D Lookup Table'
                                        */
  uint32_T DLookupTable_numYWorkElts[2];/* Computed Parameter: DLookupTable_numYWorkElts
                                         * Referenced by: '<S1>/1-D Lookup Table'
                                         */
  uint32_T DLookupTable4_maxIndex;     /* Computed Parameter: DLookupTable4_maxIndex
                                        * Referenced by: '<S1>/1-D Lookup Table4'
                                        */
  uint32_T DLookupTable4_dimSizes;     /* Computed Parameter: DLookupTable4_dimSizes
                                        * Referenced by: '<S1>/1-D Lookup Table4'
                                        */
  uint32_T DLookupTable4_numYWorkElts[2];/* Computed Parameter: DLookupTable4_numYWorkElts
                                          * Referenced by: '<S1>/1-D Lookup Table4'
                                          */
  uint32_T DLookupTable1_maxIndex;     /* Computed Parameter: DLookupTable1_maxIndex
                                        * Referenced by: '<S1>/1-D Lookup Table1'
                                        */
  uint32_T DLookupTable1_dimSizes;     /* Computed Parameter: DLookupTable1_dimSizes
                                        * Referenced by: '<S1>/1-D Lookup Table1'
                                        */
  uint32_T DLookupTable1_numYWorkElts[2];/* Computed Parameter: DLookupTable1_numYWorkElts
                                          * Referenced by: '<S1>/1-D Lookup Table1'
                                          */
  uint32_T DLookupTable5_maxIndex;     /* Computed Parameter: DLookupTable5_maxIndex
                                        * Referenced by: '<S1>/1-D Lookup Table5'
                                        */
  uint32_T DLookupTable5_dimSizes;     /* Computed Parameter: DLookupTable5_dimSizes
                                        * Referenced by: '<S1>/1-D Lookup Table5'
                                        */
  uint32_T DLookupTable5_numYWorkElts[2];/* Computed Parameter: DLookupTable5_numYWorkElts
                                          * Referenced by: '<S1>/1-D Lookup Table5'
                                          */
  uint32_T DLookupTable2_maxIndex;     /* Computed Parameter: DLookupTable2_maxIndex
                                        * Referenced by: '<S1>/1-D Lookup Table2'
                                        */
  uint32_T DLookupTable2_dimSizes;     /* Computed Parameter: DLookupTable2_dimSizes
                                        * Referenced by: '<S1>/1-D Lookup Table2'
                                        */
  uint32_T DLookupTable2_numYWorkElts[2];/* Computed Parameter: DLookupTable2_numYWorkElts
                                          * Referenced by: '<S1>/1-D Lookup Table2'
                                          */
  uint32_T DLookupTable6_maxIndex;     /* Computed Parameter: DLookupTable6_maxIndex
                                        * Referenced by: '<S1>/1-D Lookup Table6'
                                        */
  uint32_T DLookupTable6_dimSizes;     /* Computed Parameter: DLookupTable6_dimSizes
                                        * Referenced by: '<S1>/1-D Lookup Table6'
                                        */
  uint32_T DLookupTable6_numYWorkElts[2];/* Computed Parameter: DLookupTable6_numYWorkElts
                                          * Referenced by: '<S1>/1-D Lookup Table6'
                                          */
};

/* Real-time Model Data Structure */
struct tag_RTM_BoatModele_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    X_BoatModele_T *contStates;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[8];
    real_T odeF[3][8];
    ODE3_IntgData intgData;
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
    boolean_T firstInitCondFlag;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (auto storage) */
#ifdef __cplusplus

extern "C" {

#endif

  extern P_BoatModele_T BoatModele_P;

#ifdef __cplusplus

}
#endif

/* Block signals (auto storage) */
extern B_BoatModele_T BoatModele_B;

/* Continuous states (auto storage) */
extern X_BoatModele_T BoatModele_X;

/* Block states (auto storage) */
extern DW_BoatModele_T BoatModele_DW;

#ifdef __cplusplus

extern "C" {

#endif

  /* External inputs (root inport signals with auto storage) */
  extern ExtU_BoatModele_T BoatModele_U;

  /* External outputs (root outports fed by signals with auto storage) */
  extern ExtY_BoatModele_T BoatModele_Y;

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void BoatModele_initialize(void);
  extern void BoatModele_step(void);
  extern void BoatModele_terminate(void);

#ifdef __cplusplus

}
#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_BoatModele_T *const BoatModele_M;

#ifdef __cplusplus

}
#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'BoatModele'
 * '<S1>'   : 'BoatModele/4DOF nonlinear sailing yacht model'
 * '<S2>'   : 'BoatModele/4DOF nonlinear sailing yacht model/MATLAB Function'
 * '<S3>'   : 'BoatModele/4DOF nonlinear sailing yacht model/MATLAB Function1'
 */
#endif                                 /* RTW_HEADER_BoatModele_h_ */
