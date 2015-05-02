/*
 * DOF_sid.h
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

/* statically allocated instance data for model: DOF */
{
  {
    /* Local SimStruct for the generated S-Function */
    static LocalS slS;
    LocalS *lS = &slS;
    ssSetUserData(rts, lS);

    /* block I/O */
    {
      static B_DOF_T sfcnB;
      void *b = (real_T *) &sfcnB;
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
  }
}
