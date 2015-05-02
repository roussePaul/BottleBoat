/*
 * DOF_mid.h
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
 *
 * SOURCES: DOF_sf.c
 */

#include "simstruc.h"
#include "DOF_sf.h"
#if defined(MATLAB_MEX_FILE) || defined(RT_MALLOC)

static int_T RegNumInputPorts(SimStruct *S, int_T nInputPorts)
{
  _ssSetNumInputPorts(S,nInputPorts);
  return true;
}

static int_T RegNumOutputPorts(SimStruct *S, int_T nOutputPorts)
{
  _ssSetNumOutputPorts(S,nOutputPorts);
  return true;
}

static int_T FcnSetErrorStatus(const SimStruct *S, DTypeId arg2)
{
  static char msg[256];
  if (strlen(ssGetModelName(S)) < 128) {
    sprintf(msg,
            "S-function %s does not have a tlc file. It cannot use macros that access regDataType field in simstruct.",
            ssGetModelName(S));
  } else {
    sprintf(msg,
            "A S-function does not have a tlc file. It cannot use macros that access regDataType field in simstruct.");
  }

  ssSetErrorStatus(S, msg);
  UNUSED_PARAMETER(arg2);
  return 0;
}

#endif

/* Instance data for model: DOF */
void *DOF_malloc(SimStruct *rts)
{
  /* Local SimStruct for the generated S-Function */
  LocalS *lS = (LocalS *) malloc(sizeof(LocalS));
  ss_VALIDATE_MEMORY(rts,lS);
  (void) memset((char *) lS, 0,
                sizeof(LocalS));
  ssSetUserData(rts, lS);

  /* block I/O */
  {
    void *b = malloc(sizeof(B_DOF_T));
    ss_VALIDATE_MEMORY(rts,b);
    ssSetLocalBlockIO(rts, b);

    {
      int_T i;
      for (i = 0; i < 9; i++) {
        ((B_DOF_T *) ssGetLocalBlockIO(rts))->X_dot_ext[i] = 0.0;
      }
    }
  }

  /* model checksums */
  ssSetChecksumVal(rts, 0, 1424310571U);
  ssSetChecksumVal(rts, 1, 1539951798U);
  ssSetChecksumVal(rts, 2, 1527948562U);
  ssSetChecksumVal(rts, 3, 2581538606U);
  return (NULL);
}
