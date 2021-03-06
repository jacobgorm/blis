#include "blis.h"
#ifdef BLIS_ENABLE_CBLAS
/*
 *
 * cblas_ssymm.c
 * This program is a C interface to ssymm.
 * Written by Keita Teranishi
 * 4/8/1998
 *
 */

#include "cblas.h"
#include "cblas_f77.h"
void BLIS_EXPORT_BLAS cblas_ssymm(enum CBLAS_ORDER Order, enum CBLAS_SIDE Side,
                 enum CBLAS_UPLO Uplo, f77_int M, f77_int N,
                 float alpha, const float  *A, f77_int lda,
                 const float  *B, f77_int ldb, float beta,
                 float  *C, f77_int ldc)
{
   char SD, UL;   
#ifdef F77_CHAR
   F77_CHAR F77_SD, F77_UL;
#else
   #define F77_SD &SD  
   #define F77_UL &UL  
#endif

#ifdef F77_INT
   F77_INT F77_M=M, F77_N=N, F77_lda=lda, F77_ldb=ldb;
   F77_INT F77_ldc=ldc;
#else
   #define F77_M M
   #define F77_N N
   #define F77_lda lda
   #define F77_ldb ldb
   #define F77_ldc ldc
#endif

   extern int CBLAS_CallFromC;
   extern int RowMajorStrg;
   RowMajorStrg = 0;
   CBLAS_CallFromC = 1;

   if( Order == CblasColMajor )
   {
      if( Side == CblasRight) SD='R';
      else if ( Side == CblasLeft ) SD='L';
      else 
      {
         cblas_xerbla(2, "cblas_ssymm", 
                       "Illegal Side setting, %d\n", Side);
         CBLAS_CallFromC = 0;
         RowMajorStrg = 0;
         return;
      }

      if( Uplo == CblasUpper) UL='U';
      else if ( Uplo == CblasLower ) UL='L';
      else 
      {
         cblas_xerbla(3, "cblas_ssymm", 
                       "Illegal Uplo setting, %d\n", Uplo);
         CBLAS_CallFromC = 0;
         RowMajorStrg = 0;
         return;
      }

      #ifdef F77_CHAR
         F77_UL = C2F_CHAR(&UL);
         F77_SD = C2F_CHAR(&SD);
      #endif

      F77_ssymm(F77_SD, F77_UL, &F77_M, &F77_N, &alpha, A, &F77_lda, B, &F77_ldb, &beta, C, &F77_ldc);
   } else if (Order == CblasRowMajor)
   {
      RowMajorStrg = 1;
      if( Side == CblasRight) SD='L';
      else if ( Side == CblasLeft ) SD='R';
      else 
      {
         cblas_xerbla(2, "cblas_ssymm", 
                       "Illegal Side setting, %d\n", Side);
         CBLAS_CallFromC = 0;
         RowMajorStrg = 0;
         return;
      }

      if( Uplo == CblasUpper) UL='L';
      else if ( Uplo == CblasLower ) UL='U';
      else 
      {
         cblas_xerbla(3, "cblas_ssymm", 
                       "Illegal Uplo setting, %d\n", Uplo);
         CBLAS_CallFromC = 0;
         RowMajorStrg = 0;
         return;
      }

      #ifdef F77_CHAR
         F77_UL = C2F_CHAR(&UL);
         F77_SD = C2F_CHAR(&SD);
      #endif

      F77_ssymm(F77_SD, F77_UL, &F77_N, &F77_M, &alpha, A, &F77_lda, B, &F77_ldb, &beta, C, &F77_ldc);
   } else  cblas_xerbla(1, "cblas_ssymm",
                     "Illegal Order setting, %d\n", Order);
   CBLAS_CallFromC = 0;
   RowMajorStrg = 0;
   return;
} 
#endif
