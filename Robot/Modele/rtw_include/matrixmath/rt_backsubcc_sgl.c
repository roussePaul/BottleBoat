/* Copyright 1994-2010 The MathWorks, Inc.
 *
 * File: rt_backsubcc_dbl.c     $Revision: 1.1.6.2 $
 *
 * Abstract:
 *      Simulink Coder support routine which performs
 *      backward substitution: solving Ux=b for complex
 *      double precision float operands
 *
 */

#include <math.h>
#include "rt_matrixlib.h"

/* Function: rt_BackwardSubstitutionCC_Sgl =====================================
 * Abstract: Backward substitution: Solving Ux=b 
 *           U: complex, single
 *           b: complex, single
 *           U is an upper (or unit upper) triangular full matrix.
 *           The entries in the lower triangle are ignored.
 *           U is a NxN matrix
 *           X is a NxP matrix
 *           B is a NxP matrix
 */
#ifdef CREAL_T
void rt_BackwardSubstitutionCC_Sgl(creal32_T         *pU,
                                   const creal32_T   *pb,
                                   creal32_T         *x,
                                   int_T              N,
                                   int_T              P,
                                   boolean_T          unit_upper)
{
  int_T i, k;
  for(k=P; k>0; k--) {
    creal32_T *pUcol = pU;
    for(i=0; i<N; i++) {
      creal32_T *xj = x + k*N-1;
      creal32_T s = {0.0F, 0.0F};
      creal32_T *pUrow = pUcol--;
      creal32_T cb;

      {
        int_T j = i;
        while(j-- > 0) {
          /* Compute: s += L * xj, in complex */
          creal32_T cU = *pUrow;
          creal32_T c;
          rt_ComplexTimes_Sgl(&c, cU, *xj);

          s.re += c.re;
          s.im += c.im;
          xj--;
          pUrow -= N;
        }
      }

      cb = *pb--;
      if (unit_upper) {
        xj->re = cb.re - s.re;
        xj->im = cb.im - s.im;
      } else {
        /* Complex divide: *xj = cdiff / *cL */
        creal32_T cU = *pUrow;
        creal32_T cdiff;
        cdiff.re = cb.re - s.re;
        cdiff.im = cb.im - s.im;

        rt_ComplexRDivide_Sgl(xj, cdiff, cU);
      }
    }
  }
}
#endif
/* [EOF] rt_backsubcc_dbl.c */
