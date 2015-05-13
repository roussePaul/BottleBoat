/*
 * BoatDynamic.h
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
#ifndef RTW_HEADER_BoatDynamic_h_
#define RTW_HEADER_BoatDynamic_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef BoatDynamic_COMMON_INCLUDES_
# define BoatDynamic_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* BoatDynamic_COMMON_INCLUDES_ */

#include "BoatDynamic_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtsplntypes.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
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
# define rtmGetT(rtm)                  ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T m_bpLambda;                   /* '<Root>/1-D Lookup Table' */
  real_T m_yyA;                        /* '<Root>/1-D Lookup Table' */
  real_T m_yyB;                        /* '<Root>/1-D Lookup Table' */
  real_T m_yy2;                        /* '<Root>/1-D Lookup Table' */
  real_T m_up[100];                    /* '<Root>/1-D Lookup Table' */
  real_T m_y2[100];                    /* '<Root>/1-D Lookup Table' */
  real_T m_bpLambda_f;                 /* '<Root>/1-D Lookup Table4' */
  real_T m_yyA_p;                      /* '<Root>/1-D Lookup Table4' */
  real_T m_yyB_j;                      /* '<Root>/1-D Lookup Table4' */
  real_T m_yy2_l;                      /* '<Root>/1-D Lookup Table4' */
  real_T m_up_o[100];                  /* '<Root>/1-D Lookup Table4' */
  real_T m_y2_a[100];                  /* '<Root>/1-D Lookup Table4' */
  real_T m_bpLambda_g;                 /* '<Root>/1-D Lookup Table1' */
  real_T m_yyA_n;                      /* '<Root>/1-D Lookup Table1' */
  real_T m_yyB_n;                      /* '<Root>/1-D Lookup Table1' */
  real_T m_yy2_h;                      /* '<Root>/1-D Lookup Table1' */
  real_T m_up_b[100];                  /* '<Root>/1-D Lookup Table1' */
  real_T m_y2_e[100];                  /* '<Root>/1-D Lookup Table1' */
  real_T m_bpLambda_n;                 /* '<Root>/1-D Lookup Table5' */
  real_T m_yyA_i;                      /* '<Root>/1-D Lookup Table5' */
  real_T m_yyB_l;                      /* '<Root>/1-D Lookup Table5' */
  real_T m_yy2_k;                      /* '<Root>/1-D Lookup Table5' */
  real_T m_up_f[100];                  /* '<Root>/1-D Lookup Table5' */
  real_T m_y2_c[100];                  /* '<Root>/1-D Lookup Table5' */
  real_T m_bpLambda_k;                 /* '<Root>/1-D Lookup Table2' */
  real_T m_yyA_ng;                     /* '<Root>/1-D Lookup Table2' */
  real_T m_yyB_e;                      /* '<Root>/1-D Lookup Table2' */
  real_T m_yy2_j;                      /* '<Root>/1-D Lookup Table2' */
  real_T m_up_g[100];                  /* '<Root>/1-D Lookup Table2' */
  real_T m_y2_cz[100];                 /* '<Root>/1-D Lookup Table2' */
  real_T m_bpLambda_gp;                /* '<Root>/1-D Lookup Table6' */
  real_T m_yyA_l;                      /* '<Root>/1-D Lookup Table6' */
  real_T m_yyB_i;                      /* '<Root>/1-D Lookup Table6' */
  real_T m_yy2_n;                      /* '<Root>/1-D Lookup Table6' */
  real_T m_up_n[100];                  /* '<Root>/1-D Lookup Table6' */
  real_T m_y2_g[100];                  /* '<Root>/1-D Lookup Table6' */
  void* m_bpDataSet;                   /* '<Root>/1-D Lookup Table' */
  void* TWork[6];                      /* '<Root>/1-D Lookup Table' */
  void* SWork[7];                      /* '<Root>/1-D Lookup Table' */
  void* m_bpDataSet_d;                 /* '<Root>/1-D Lookup Table4' */
  void* TWork_d[6];                    /* '<Root>/1-D Lookup Table4' */
  void* SWork_n[7];                    /* '<Root>/1-D Lookup Table4' */
  void* m_bpDataSet_k;                 /* '<Root>/1-D Lookup Table1' */
  void* TWork_j[6];                    /* '<Root>/1-D Lookup Table1' */
  void* SWork_j[7];                    /* '<Root>/1-D Lookup Table1' */
  void* m_bpDataSet_c;                 /* '<Root>/1-D Lookup Table5' */
  void* TWork_a[6];                    /* '<Root>/1-D Lookup Table5' */
  void* SWork_k[7];                    /* '<Root>/1-D Lookup Table5' */
  void* m_bpDataSet_j;                 /* '<Root>/1-D Lookup Table2' */
  void* TWork_c[6];                    /* '<Root>/1-D Lookup Table2' */
  void* SWork_jo[7];                   /* '<Root>/1-D Lookup Table2' */
  void* m_bpDataSet_g;                 /* '<Root>/1-D Lookup Table6' */
  void* TWork_dh[6];                   /* '<Root>/1-D Lookup Table6' */
  void* SWork_kl[7];                   /* '<Root>/1-D Lookup Table6' */
  uint32_T m_bpIndex;                  /* '<Root>/1-D Lookup Table' */
  uint32_T m_bpIndex_m;                /* '<Root>/1-D Lookup Table4' */
  uint32_T m_bpIndex_b;                /* '<Root>/1-D Lookup Table1' */
  uint32_T m_bpIndex_n;                /* '<Root>/1-D Lookup Table5' */
  uint32_T m_bpIndex_a;                /* '<Root>/1-D Lookup Table2' */
  uint32_T m_bpIndex_j;                /* '<Root>/1-D Lookup Table6' */
} DW_BoatDynamic_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T wind[2];                      /* '<Root>/wind' */
  real_T V_in[12];                     /* '<Root>/V_in' */
} ExtU_BoatDynamic_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T X_dot[9];                     /* '<Root>/X_dot' */
} ExtY_BoatDynamic_T;

/* Parameters (auto storage) */
struct P_BoatDynamic_T_ {
  real_T alphacoeff_xdata[100];        /* Variable: alphacoeff_xdata
                                        * Referenced by:
                                        *   '<Root>/1-D Lookup Table'
                                        *   '<Root>/1-D Lookup Table4'
                                        */
  real_T alphacoeff_yddata[100];       /* Variable: alphacoeff_yddata
                                        * Referenced by: '<Root>/1-D Lookup Table4'
                                        */
  real_T alphacoeff_yldata[100];       /* Variable: alphacoeff_yldata
                                        * Referenced by: '<Root>/1-D Lookup Table'
                                        */
  real_T hull_xdata[100];              /* Variable: hull_xdata
                                        * Referenced by: '<Root>/1-D Lookup Table3'
                                        */
  real_T hull_ydata[100];              /* Variable: hull_ydata
                                        * Referenced by: '<Root>/1-D Lookup Table3'
                                        */
  real_T keelcoeff_xdata[100];         /* Variable: keelcoeff_xdata
                                        * Referenced by:
                                        *   '<Root>/1-D Lookup Table2'
                                        *   '<Root>/1-D Lookup Table6'
                                        */
  real_T keelcoeff_yddata[100];        /* Variable: keelcoeff_yddata
                                        * Referenced by: '<Root>/1-D Lookup Table6'
                                        */
  real_T keelcoeff_yldata[100];        /* Variable: keelcoeff_yldata
                                        * Referenced by: '<Root>/1-D Lookup Table2'
                                        */
  real_T ruddercoeff_xdata[100];       /* Variable: ruddercoeff_xdata
                                        * Referenced by:
                                        *   '<Root>/1-D Lookup Table1'
                                        *   '<Root>/1-D Lookup Table5'
                                        */
  real_T ruddercoeff_yddata[100];      /* Variable: ruddercoeff_yddata
                                        * Referenced by: '<Root>/1-D Lookup Table5'
                                        */
  real_T ruddercoeff_yldata[100];      /* Variable: ruddercoeff_yldata
                                        * Referenced by: '<Root>/1-D Lookup Table1'
                                        */
  uint32_T DLookupTable_maxIndex;      /* Computed Parameter: DLookupTable_maxIndex
                                        * Referenced by: '<Root>/1-D Lookup Table'
                                        */
  uint32_T DLookupTable_dimSizes;      /* Computed Parameter: DLookupTable_dimSizes
                                        * Referenced by: '<Root>/1-D Lookup Table'
                                        */
  uint32_T DLookupTable_numYWorkElts[2];/* Computed Parameter: DLookupTable_numYWorkElts
                                         * Referenced by: '<Root>/1-D Lookup Table'
                                         */
  uint32_T DLookupTable4_maxIndex;     /* Computed Parameter: DLookupTable4_maxIndex
                                        * Referenced by: '<Root>/1-D Lookup Table4'
                                        */
  uint32_T DLookupTable4_dimSizes;     /* Computed Parameter: DLookupTable4_dimSizes
                                        * Referenced by: '<Root>/1-D Lookup Table4'
                                        */
  uint32_T DLookupTable4_numYWorkElts[2];/* Computed Parameter: DLookupTable4_numYWorkElts
                                          * Referenced by: '<Root>/1-D Lookup Table4'
                                          */
  uint32_T DLookupTable1_maxIndex;     /* Computed Parameter: DLookupTable1_maxIndex
                                        * Referenced by: '<Root>/1-D Lookup Table1'
                                        */
  uint32_T DLookupTable1_dimSizes;     /* Computed Parameter: DLookupTable1_dimSizes
                                        * Referenced by: '<Root>/1-D Lookup Table1'
                                        */
  uint32_T DLookupTable1_numYWorkElts[2];/* Computed Parameter: DLookupTable1_numYWorkElts
                                          * Referenced by: '<Root>/1-D Lookup Table1'
                                          */
  uint32_T DLookupTable5_maxIndex;     /* Computed Parameter: DLookupTable5_maxIndex
                                        * Referenced by: '<Root>/1-D Lookup Table5'
                                        */
  uint32_T DLookupTable5_dimSizes;     /* Computed Parameter: DLookupTable5_dimSizes
                                        * Referenced by: '<Root>/1-D Lookup Table5'
                                        */
  uint32_T DLookupTable5_numYWorkElts[2];/* Computed Parameter: DLookupTable5_numYWorkElts
                                          * Referenced by: '<Root>/1-D Lookup Table5'
                                          */
  uint32_T DLookupTable2_maxIndex;     /* Computed Parameter: DLookupTable2_maxIndex
                                        * Referenced by: '<Root>/1-D Lookup Table2'
                                        */
  uint32_T DLookupTable2_dimSizes;     /* Computed Parameter: DLookupTable2_dimSizes
                                        * Referenced by: '<Root>/1-D Lookup Table2'
                                        */
  uint32_T DLookupTable2_numYWorkElts[2];/* Computed Parameter: DLookupTable2_numYWorkElts
                                          * Referenced by: '<Root>/1-D Lookup Table2'
                                          */
  uint32_T DLookupTable6_maxIndex;     /* Computed Parameter: DLookupTable6_maxIndex
                                        * Referenced by: '<Root>/1-D Lookup Table6'
                                        */
  uint32_T DLookupTable6_dimSizes;     /* Computed Parameter: DLookupTable6_dimSizes
                                        * Referenced by: '<Root>/1-D Lookup Table6'
                                        */
  uint32_T DLookupTable6_numYWorkElts[2];/* Computed Parameter: DLookupTable6_numYWorkElts
                                          * Referenced by: '<Root>/1-D Lookup Table6'
                                          */
};

/* Real-time Model Data Structure */
struct tag_RTM_BoatDynamic_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_BoatDynamic_T BoatDynamic_P;

/* Block states (auto storage) */
extern DW_BoatDynamic_T BoatDynamic_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_BoatDynamic_T BoatDynamic_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_BoatDynamic_T BoatDynamic_Y;

/* Model entry point functions */
extern void BoatDynamic_initialize(void);
extern void BoatDynamic_step(void);
extern void BoatDynamic_terminate(void);

/* Real-time Model object */
extern RT_MODEL_BoatDynamic_T *const BoatDynamic_M;

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
 * '<Root>' : 'BoatDynamic'
 * '<S1>'   : 'BoatDynamic/MATLAB Function'
 * '<S2>'   : 'BoatDynamic/MATLAB Function1'
 */
#endif                                 /* RTW_HEADER_BoatDynamic_h_ */
