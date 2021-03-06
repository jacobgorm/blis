#include "blis.h"
#ifdef BLIS_ENABLE_CBLAS
/*
 *
 * cblas_dger.c
 * This program is a C interface to dger.
 * Written by Keita Teranishi
 * 4/6/1998
 *
 */

#include "cblas.h"
#include "cblas_f77.h"
void BLIS_EXPORT_BLAS cblas_dger(enum CBLAS_ORDER order, f77_int M, f77_int N,
                double alpha, const double  *X, f77_int incX,
                const double  *Y, f77_int incY, double  *A, f77_int lda)
{
#ifdef F77_INT
   F77_INT F77_M=M, F77_N=N, F77_lda=lda, F77_incX=incX, F77_incY=incY;
#else
   #define F77_M M
   #define F77_N N
   #define F77_incX incX
   #define F77_incY incY
   #define F77_lda lda
#endif

   extern int CBLAS_CallFromC;
   extern int RowMajorStrg;
   RowMajorStrg = 0;

   CBLAS_CallFromC = 1;
   if (order == CblasColMajor)
   {
      F77_dger( &F77_M, &F77_N, &alpha, X, &F77_incX, Y, &F77_incY, A, 
                      &F77_lda);
   }
   else if (order == CblasRowMajor)
   {
      RowMajorStrg = 1;
      F77_dger( &F77_N, &F77_M ,&alpha, Y, &F77_incY, X, &F77_incX, A, 
                      &F77_lda);

   }
   else cblas_xerbla(1, "cblas_dger", "Illegal Order setting, %d\n", order);
   CBLAS_CallFromC = 0;
   RowMajorStrg = 0;
   return;
}
#endif
