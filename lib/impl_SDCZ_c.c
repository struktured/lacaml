/* File: impl_SDCZ_c.c

   Copyright (C) 2001-

     Markus Mottl
     email: markus.mottl@gmail.com
     WWW: http://www.ocaml.info

     Christophe Troestler
     email: Christophe.Troestler@umh.ac.be
     WWW: http://math.umh.ac.be/an/

     Liam Stewart
     email: liam@cs.toronto.edu
     WWW: http://www.cs.toronto.edu/~liam

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "lacaml_macros.h"
#include "f2c.h"

/*** BLAS-1 */

/** SWAP */

extern void FUN(swap)(
  integer *N,
  NUMBER *X, integer *INCX,
  NUMBER *Y, integer *INCY);

CAMLprim value LFUN(swap_stub)(
  value vN,
  value vOFSX, value vINCX, value vX,
  value vOFSY, value vINCY, value vY)
{
  CAMLparam2(vX, vY);

  integer GET_INT(N),
          GET_INT(INCX),
          GET_INT(INCY);

  VEC_PARAMS(X);
  VEC_PARAMS(Y);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(swap)(
    &N,
    X_data, &INCX,
    Y_data, &INCY);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}

CAMLprim value LFUN(swap_stub_bc)(value *argv, int argn)
{
  return
    LFUN(swap_stub)(argv[0], argv[1], argv[2], argv[3],
                    argv[4], argv[5], argv[6]);
}


/** SCAL */

extern void FUN(scal)(
  integer *N,
  NUMBER *ALPHA,
  NUMBER *X, integer *INCX);

CAMLprim value LFUN(scal_stub)(
  value vN,
  value vALPHA,
  value vOFSX, value vINCX, value vX)
{
  CAMLparam1(vX);

  integer GET_INT(N),
          GET_INT(INCX);

  CREATE_NUMBERP(ALPHA);

  VEC_PARAMS(X);

  INIT_NUMBER(ALPHA);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(scal)(
    &N,
    pALPHA,
    X_data, &INCX);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}


/** COPY */

extern void FUN(copy)(
  integer *N,
  NUMBER *X, integer *INCX,
  NUMBER *Y, integer *INCY);

CAMLprim value LFUN(copy_stub)(
  value vN,
  value vOFSY, value vINCY, value vY,
  value vOFSX, value vINCX, value vX)
{
  CAMLparam2(vX, vY);

  integer GET_INT(N),
          GET_INT(INCX),
          GET_INT(INCY);

  VEC_PARAMS(X);
  VEC_PARAMS(Y);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(copy)(
    &N,
    X_data, &INCX,
    Y_data, &INCY);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}

CAMLprim value LFUN(copy_stub_bc)(value *argv, int argn)
{
  return LFUN(copy_stub)(
    argv[0], argv[1], argv[2], argv[3],
    argv[4], argv[5], argv[6]);
}


/** AXPY */

extern void FUN(axpy)(
  integer *N,
  NUMBER *ALPHA,
  NUMBER *X, integer *INCX,
  NUMBER *Y, integer *INCY);

CAMLprim value LFUN(axpy_stub)(
  value vN,
  value vOFSY, value vINCY, value vY,
  value vALPHA,
  value vOFSX, value vINCX, value vX)
{
  CAMLparam2(vX, vY);

  integer GET_INT(N),
          GET_INT(INCX),
          GET_INT(INCY);

  CREATE_NUMBERP(ALPHA);

  VEC_PARAMS(X);
  VEC_PARAMS(Y);

  INIT_NUMBER(ALPHA);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(axpy)(
    &N,
    pALPHA,
    X_data, &INCX,
    Y_data, &INCY);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}

CAMLprim value LFUN(axpy_stub_bc)(value *argv, int argn)
{
  return LFUN(axpy_stub)(
    argv[0], argv[1], argv[2], argv[3],
    argv[4], argv[5], argv[6], argv[7]);
}


/** AMAX */

extern integer FUN2(i,amax)(integer *N, NUMBER *X, integer *INCX);

CAMLprim value LFUN(iamax_stub)(value vN, value vOFSX, value vINCX, value vX)
{
  CAMLparam1(vX);

  integer GET_INT(N),
          GET_INT(INCX),
          index;

  VEC_PARAMS(X);

  caml_enter_blocking_section();  /* Allow other threads */
  index = FUN2(i,amax)(&N, X_data, &INCX);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(index));
}



/*** BLAS-2 */

/** GEMV */

extern void FUN(gemv)(
  char *TRANS,
  integer *M, integer *N,
  NUMBER *ALPHA,
  NUMBER *A, integer *LDA,
  NUMBER *X, integer *INCX,
  NUMBER *BETA,
  NUMBER *Y, integer *INCY);

CAMLprim value LFUN(gemv_stub)(
  value vOFSY, value vINCY, value vY,
  value vAR,
  value vAC,
  value vA,
  value vM,
  value vN,
  value vTRANS,
  value vALPHA,
  value vBETA,
  value vOFSX, value vINCX, value vX)
{
  CAMLparam3(vA, vX, vY);

  char GET_INT(TRANS);

  integer GET_INT(M),
          GET_INT(N),
          GET_INT(INCX),
          GET_INT(INCY);

  CREATE_NUMBERP(ALPHA);
  CREATE_NUMBERP(BETA);

  MAT_PARAMS(A);
  VEC_PARAMS(X);
  VEC_PARAMS(Y);

  INIT_NUMBER(ALPHA);
  INIT_NUMBER(BETA);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(gemv)(
    &TRANS,
    &M, &N,
    pALPHA,
    A_data, &rows_A,
    X_data, &INCX,
    pBETA,
    Y_data, &INCY);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}

CAMLprim value LFUN(gemv_stub_bc)(value *argv, int argn)
{
  return LFUN(gemv_stub)(
    argv[0], argv[1], argv[2], argv[3], argv[4],
    argv[5], argv[6], argv[7], argv[8], argv[9],
    argv[10], argv[11], argv[12], argv[13]);
}


/** GBMV */

extern void FUN(gbmv)(
  char *TRANS,
  integer *M, integer *N, integer *KL, integer *KU,
  NUMBER *ALPHA,
  NUMBER *A, integer *LDA,
  NUMBER *X, integer *INCX,
  NUMBER *BETA,
  NUMBER *Y, integer *INCY);

CAMLprim value LFUN(gbmv_stub)(
  value vOFSY, value vINCY, value vY,
  value vAR,
  value vAC,
  value vA,
  value vM, value vN, value vKL, value vKU,
  value vTRANS,
  value vALPHA,
  value vBETA,
  value vOFSX, value vINCX, value vX)
{
  CAMLparam3(vA, vX, vY);

  char GET_INT(TRANS);

  integer GET_INT(M),
          GET_INT(N),
          GET_INT(KL),
          GET_INT(KU),
          GET_INT(INCX),
          GET_INT(INCY);

  CREATE_NUMBERP(ALPHA);
  CREATE_NUMBERP(BETA);

  MAT_PARAMS(A);
  VEC_PARAMS(X);
  VEC_PARAMS(Y);

  INIT_NUMBER(ALPHA);
  INIT_NUMBER(BETA);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(gbmv)(
    &TRANS,
    &M, &N, &KL, &KU,
    pALPHA,
    A_data, &rows_A,
    X_data, &INCX,
    pBETA,
    Y_data, &INCY);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}

CAMLprim value LFUN(gbmv_stub_bc)(value *argv, int argn)
{
  return
    LFUN(gbmv_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6],
      argv[7], argv[8], argv[9], argv[10], argv[11], argv[12], argv[13],
      argv[14], argv[15]);
}


/** SYMV */

extern void FUN(symv)(
  char *UPLO,
  integer *N,
  NUMBER *ALPHA,
  NUMBER *A, integer *LDA,
  NUMBER *X, integer *INCX,
  NUMBER *BETA,
  NUMBER *Y, integer *INCY);

CAMLprim value LFUN(symv_stub)(
  value vOFSY, value vINCY, value vY,
  value vAR,
  value vAC,
  value vA,
  value vN,
  value vUPLO,
  value vALPHA,
  value vBETA,
  value vOFSX, value vINCX, value vX)
{
  CAMLparam3(vA, vX, vY);

  char GET_INT(UPLO);

  integer GET_INT(N),
          GET_INT(INCX),
          GET_INT(INCY);

  CREATE_NUMBERP(ALPHA);
  CREATE_NUMBERP(BETA);

  MAT_PARAMS(A);
  VEC_PARAMS(X);
  VEC_PARAMS(Y);

  INIT_NUMBER(ALPHA);
  INIT_NUMBER(BETA);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(symv)(
    &UPLO,
    &N,
    pALPHA,
    A_data, &rows_A,
    X_data, &INCX,
    pBETA,
    Y_data, &INCY);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}

CAMLprim value LFUN(symv_stub_bc)(value *argv, int argn)
{
  return
    LFUN(symv_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6],
      argv[7], argv[8], argv[9], argv[10], argv[11], argv[12]);
}


/** TODO: SPMV */

/** TODO: TRMV */

/** TODO: TBMV */

/** TODO: TPMV */

/** TODO: TRSV */

/** TODO: TBSV */

/** TODO: TPSV */


/*** BLAS-3 */

/** GEMM */

extern void FUN(gemm)(
  char *TRANSA, char *TRANSB,
  integer *M, integer *N, integer *K,
  NUMBER *ALPHA,
  NUMBER *A, integer *LDA,
  NUMBER *B, integer *LDB,
  NUMBER *BETA,
  NUMBER *C, integer *LDC);

CAMLprim value LFUN(gemm_stub)(
  value vTRANSA, value vTRANSB,
  value vM, value vN, value vK,
  value vAR, value vAC, value vA,
  value vBR, value vBC, value vB,
  value vCR, value vCC, value vC,
  value vALPHA, value vBETA)
{
  CAMLparam3(vA, vB, vC);

  char GET_INT(TRANSA), GET_INT(TRANSB);
  integer GET_INT(M), GET_INT(N), GET_INT(K);

  CREATE_NUMBERP(ALPHA);
  CREATE_NUMBERP(BETA);

  MAT_PARAMS(A);
  MAT_PARAMS(B);
  MAT_PARAMS(C);

  INIT_NUMBER(ALPHA);
  INIT_NUMBER(BETA);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(gemm)(
    &TRANSA, &TRANSB,
    &M, &N, &K,
    pALPHA,
    A_data, &rows_A,
    B_data, &rows_B,
    pBETA,
    C_data, &rows_C);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}

CAMLprim value LFUN(gemm_stub_bc)(value *argv, int argn)
{
  return
    LFUN(gemm_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6],
      argv[7], argv[8], argv[9], argv[10], argv[11], argv[12], argv[13],
      argv[14], argv[15]);
}

/** SYMM */

extern void FUN(symm)(
  char *SIDE, char *UPLO,
  integer *M, integer *N,
  NUMBER *ALPHA,
  NUMBER *A, integer *LDA,
  NUMBER *B, integer *LDB,
  NUMBER *BETA,
  NUMBER *C, integer *LDC);

CAMLprim value LFUN(symm_stub)(
  value vSIDE, value vUPLO,
  value vM, value vN,
  value vAR, value vAC, value vA,
  value vBR, value vBC, value vB,
  value vCR, value vCC, value vC,
  value vALPHA, value vBETA)
{
  CAMLparam3(vA, vB, vC);

  char GET_INT(SIDE), GET_INT(UPLO);
  integer GET_INT(M), GET_INT(N);

  CREATE_NUMBERP(ALPHA);
  CREATE_NUMBERP(BETA);

  MAT_PARAMS(A);
  MAT_PARAMS(B);
  MAT_PARAMS(C);

  INIT_NUMBER(ALPHA);
  INIT_NUMBER(BETA);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(symm)(
    &SIDE, &UPLO,
    &M, &N,
    pALPHA,
    A_data, &rows_A,
    B_data, &rows_B,
    pBETA,
    C_data, &rows_C);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}

CAMLprim value LFUN(symm_stub_bc)(value *argv, int argn)
{
  return
    LFUN(symm_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6],
      argv[7], argv[8], argv[9], argv[10], argv[11], argv[12], argv[13],
      argv[14]);
}

/** SYRK */

extern void FUN(syrk)(
  char *UPLO, char *TRANS,
  integer *N, integer *K,
  NUMBER *ALPHA,
  NUMBER *A, integer *LDA,
  NUMBER *BETA,
  NUMBER *C, integer *LDC);

CAMLprim value LFUN(syrk_stub)(
  value vUPLO, value vTRANS,
  value vN, value vK,
  value vAR, value vAC, value vA,
  value vCR, value vCC, value vC,
  value vALPHA, value vBETA)
{
  CAMLparam2(vA, vC);

  char GET_INT(UPLO), GET_INT(TRANS);
  integer GET_INT(N), GET_INT(K);

  CREATE_NUMBERP(ALPHA);
  CREATE_NUMBERP(BETA);

  MAT_PARAMS(A);
  MAT_PARAMS(C);

  INIT_NUMBER(ALPHA);
  INIT_NUMBER(BETA);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(syrk)(
    &UPLO, &TRANS,
    &N, &K,
    pALPHA,
    A_data, &rows_A,
    pBETA,
    C_data, &rows_C);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_unit);
}

CAMLprim value LFUN(syrk_stub_bc)(value *argv, int argn)
{
  return
    LFUN(syrk_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6],
      argv[7], argv[8], argv[9], argv[10], argv[11]);
}


/*** LAPACK */

/* Auxiliary Routines
************************************************************************/

/** LANGE */

extern REAL FUN(lange)(
  char *NORM,
  integer *M, integer *N,
  NUMBER *A, integer *LDA,
  REAL *WORK);

CAMLprim value LFUN(lange_stub)(
  value vNORM,
  value vM,
  value vN,
  value vAR,
  value vAC,
  value vA,
  value vWORK)
{
  CAMLparam2(vA, vWORK);

  char GET_INT(NORM);
  integer GET_INT(M), GET_INT(N);

  REAL res;

  MAT_PARAMS(A);
  RVEC_PARAMS1(WORK);

  caml_enter_blocking_section();  /* Allow other threads */
  res = FUN(lange)(
          &NORM, &M, &N,
          A_data, &rows_A,
          WORK_data);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(caml_copy_double(res));
}

CAMLprim value LFUN(lange_stub_bc)(value *argv, int argn)
{
  return
    LFUN(lange_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

/* Linear Equations (computational routines)
************************************************************************/

/** GETRF */

extern void FUN(getrf)(
  integer *M, integer *N,
  NUMBER *A, integer *LDA,
  integer *IPIV,
  integer *INFO);

CAMLprim value LFUN(getrf_stub)(
  value vM,
  value vN,
  value vAR,
  value vAC,
  value vA,
  value vIPIV)
{
  CAMLparam2(vA, vIPIV);

  integer GET_INT(M), GET_INT(N), INFO;

  MAT_PARAMS(A);
  INT_VEC_PARAMS(IPIV);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(getrf)(
    &M, &N,
    A_data, &rows_A,
    IPIV_data,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(getrf_stub_bc)(value *argv, int argn)
{
  return
    LFUN(getrf_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
}

/** GETRS */

extern void FUN(getrs)(
  char *TRANS,
  integer *N, integer *NRHS,
  NUMBER *A, integer *LDA,
  integer *IPIV,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(getrs_stub)(
  value vTRANS,
  value vN,
  value vNRHS,
  value vAR,
  value vAC,
  value vA,
  value vBR,
  value vBC,
  value vB,
  value vIPIV)
{
  CAMLparam3(vA, vB, vIPIV);

  char GET_INT(TRANS);
  integer GET_INT(N), GET_INT(NRHS), INFO;

  MAT_PARAMS(A);
  MAT_PARAMS(B);
  INT_VEC_PARAMS(IPIV);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(getrs)(
    &TRANS,
    &N, &NRHS,
    A_data, &rows_A,
    IPIV_data,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(getrs_stub_bc)(value *argv, int argn)
{
  return
    LFUN(getrs_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5],
      argv[6], argv[7], argv[8], argv[9]);
}

/** GETRI */

extern void FUN(getri)(
  integer *N,
  NUMBER *A, integer *LDA,
  integer *IPIV,
  NUMBER *WORK, integer *LWORK,
  integer *INFO);

CAMLprim value LFUN(getri_stub)(
  value vN,
  value vAR,
  value vAC,
  value vA,
  value vIPIV,
  value vWORK,
  value vLWORK)
{
  CAMLparam3(vA, vIPIV, vWORK);

  integer GET_INT(N), GET_INT(LWORK), INFO;

  MAT_PARAMS(A);
  INT_VEC_PARAMS(IPIV);
  VEC_PARAMS1(WORK);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(getri)(
    &N, A_data, &rows_A,
    IPIV_data,
    WORK_data, &LWORK,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(getri_stub_bc)(value *argv, int argn)
{
  return
    LFUN(getri_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

/** SYTRF */

extern void FUN(sytrf)(
  char *UPLO, integer *N,
  NUMBER *A, integer *LDA,
  integer *IPIV,
  NUMBER *WORK, integer *LWORK,
  integer *INFO);

CAMLprim value LFUN(sytrf_stub)(
  value vUPLO,
  value vN,
  value vAR,
  value vAC,
  value vA,
  value vIPIV,
  value vWORK,
  value vLWORK)
{
  CAMLparam3(vA, vIPIV, vWORK);

  char GET_INT(UPLO);
  integer GET_INT(N), GET_INT(LWORK), INFO;

  MAT_PARAMS(A);
  INT_VEC_PARAMS(IPIV);
  VEC_PARAMS1(WORK);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(sytrf)(
    &UPLO, &N,
    A_data, &rows_A,
    IPIV_data,
    WORK_data, &LWORK,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(sytrf_stub_bc)(value *argv, int argn)
{
  return
    LFUN(sytrf_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
}

/** SYTRS */

extern void FUN(sytrs)(
  char *UPLO,
  integer *N, integer *NRHS,
  NUMBER *A, integer *LDA,
  integer *IPIV,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(sytrs_stub)(
  value vUPLO,
  value vN,
  value vNRHS,
  value vAR,
  value vAC,
  value vA,
  value vBR,
  value vBC,
  value vB,
  value vIPIV)
{
  CAMLparam3(vA, vB, vIPIV);

  char GET_INT(UPLO);
  integer GET_INT(N), GET_INT(NRHS), INFO;

  MAT_PARAMS(A);
  MAT_PARAMS(B);
  INT_VEC_PARAMS(IPIV);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(sytrs)(
    &UPLO,
    &N, &NRHS,
    A_data, &rows_A,
    IPIV_data,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(sytrs_stub_bc)(value *argv, int argn)
{
  return
    LFUN(sytrs_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5],
      argv[6], argv[7], argv[8], argv[9]);
}

/** SYTRI */

extern void FUN(sytri)(
  char *UPLO,
  integer *N,
  NUMBER *A, integer *LDA,
  integer *IPIV,
  NUMBER *WORK,
  integer *INFO);

CAMLprim value LFUN(sytri_stub)(
  value vUPLO,
  value vN,
  value vAR,
  value vAC,
  value vA,
  value vIPIV,
  value vWORK)
{
  CAMLparam3(vA, vIPIV, vWORK);

  char GET_INT(UPLO);
  integer GET_INT(N), INFO;

  MAT_PARAMS(A);
  INT_VEC_PARAMS(IPIV);
  VEC_PARAMS1(WORK);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(sytri)(
    &UPLO,
    &N, A_data, &rows_A,
    IPIV_data,
    WORK_data,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(sytri_stub_bc)(value *argv, int argn)
{
  return
    LFUN(sytri_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

/** POTRF */

extern void FUN(potrf)(
  char *UPLO, integer *N,
  NUMBER *A, integer *LDA,
  integer *INFO);

CAMLprim value LFUN(potrf_stub)(
  value vUPLO,
  value vN,
  value vAR,
  value vAC,
  value vA)
{
  CAMLparam1(vA);

  char GET_INT(UPLO);
  integer GET_INT(N), INFO;

  MAT_PARAMS(A);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(potrf)(&UPLO, &N, A_data, &rows_A, &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

/** POTRS */

extern void FUN(potrs)(
  char *UPLO,
  integer *N, integer *NRHS,
  NUMBER *A, integer *LDA,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(potrs_stub)(
  value vUPLO,
  value vN,
  value vNRHS,
  value vAR,
  value vAC,
  value vA,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam2(vA, vB);

  char GET_INT(UPLO);
  integer GET_INT(N), GET_INT(NRHS), INFO;

  MAT_PARAMS(A);
  MAT_PARAMS(B);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(potrs)(
    &UPLO,
    &N, &NRHS,
    A_data, &rows_A,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(potrs_stub_bc)(value *argv, int argn)
{
  return
    LFUN(potrs_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5],
      argv[6], argv[7], argv[8]);
}

/** POTRI */

extern void FUN(potri)(
  char *UPLO, integer *N,
  NUMBER *A, integer *LDA,
  integer *INFO);

CAMLprim value LFUN(potri_stub)(
  value vUPLO,
  value vN,
  value vAR,
  value vAC,
  value vA)
{
  CAMLparam1(vA);

  char GET_INT(UPLO);
  integer GET_INT(N), INFO;

  MAT_PARAMS(A);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(potri)(&UPLO, &N, A_data, &rows_A, &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

/* Linear Equations (simple drivers)
************************************************************************/

/** GESV */

extern void FUN(gesv)(
  integer *N, integer *NRHS,
  NUMBER *A, integer *LDA,
  integer *IPIV,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(gesv_stub)(
  value vAR,
  value vAC,
  value vA,
  value vN,
  value vIPIV,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam3(vA, vB, vIPIV);

  integer GET_INT(N),
          GET_INT(NRHS),
          INFO;

  MAT_PARAMS(A);
  MAT_PARAMS(B);
  INT_VEC_PARAMS(IPIV);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(gesv)(
    &N, &NRHS,
    A_data, &rows_A,
    IPIV_data,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(gesv_stub_bc)(value *argv, int argn)
{
  return
    LFUN(gesv_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
      argv[8]);
}


/** GBSV */

extern void FUN(gbsv)(
  integer *N, integer *KL, integer *KU, integer *NRHS,
  NUMBER *AB, integer *LDAB,
  integer *IPIV,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(gbsv_stub)(
  value vABR,
  value vABC,
  value vAB,
  value vN,
  value vKL, value vKU,
  value vIPIV,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam3(vAB, vB, vIPIV);

  integer GET_INT(N),
          GET_INT(KL),
          GET_INT(KU),
          GET_INT(NRHS),
          INFO;

  MAT_PARAMS(AB);
  MAT_PARAMS(B);
  INT_VEC_PARAMS(IPIV);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(gbsv)(
    &N, &KL, &KU, &NRHS,
    AB_data, &rows_AB,
    IPIV_data,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(gbsv_stub_bc)(value *argv, int argn)
{
  return
    LFUN(gbsv_stub)(
     argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
     argv[8], argv[9], argv[10]);
}


/** GTSV */

extern void FUN(gtsv)(
  integer *N, integer *NRHS,
  NUMBER *DL, NUMBER *D, NUMBER *DU,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(gtsv_stub)(
  value vOFSDL, value vDL, value vOFSD, value vD, value vOFSDU, value vDU,
  value vN,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam4(vDL, vD, vDU, vB);

  integer GET_INT(N),
          GET_INT(NRHS),
          INFO;

  VEC_PARAMS(DL);
  VEC_PARAMS(D);
  VEC_PARAMS(DU);
  MAT_PARAMS(B);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(gtsv)(
    &N, &NRHS,
    DL_data, D_data, DU_data,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(gtsv_stub_bc)(value *argv, int argn)
{
  return
    LFUN(gtsv_stub)(
     argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
     argv[8], argv[9], argv[10]);
}


/** POSV */

extern void FUN(posv)(
  char *UPLO,
  integer *N, integer *NRHS,
  NUMBER *A, integer *LDA,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(posv_stub)(
  value vAR,
  value vAC,
  value vA,
  value vN,
  value vUPLO,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam2(vA, vB);

  char GET_INT(UPLO);

  integer GET_INT(N),
          GET_INT(NRHS),
          INFO;

  MAT_PARAMS(A);
  MAT_PARAMS(B);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(posv)(
    &UPLO,
    &N, &NRHS,
    A_data, &rows_A,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(posv_stub_bc)(value *argv, int argn)
{
  return
    LFUN(posv_stub)(
     argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
     argv[8]);
}


/** PPSV */

extern void FUN(ppsv)(
  char *UPLO,
  integer *N, integer *NRHS,
  NUMBER *AP,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(ppsv_stub)(
  value vOFSAP, value vAP,
  value vN,
  value vUPLO,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam2(vAP, vB);

  char GET_INT(UPLO);

  integer GET_INT(N),
          GET_INT(NRHS),
          INFO;

  VEC_PARAMS(AP);
  MAT_PARAMS(B);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(ppsv)(
    &UPLO,
    &N, &NRHS,
    AP_data,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(ppsv_stub_bc)(value *argv, int argn)
{
  return LFUN(ppsv_stub)(argv[0], argv[1], argv[2], argv[3],
                         argv[4], argv[5], argv[6], argv[7]);
}


/** PBSV */

extern void FUN(pbsv)(
  char *UPLO,
  integer *N, integer *KD, integer *NRHS,
  NUMBER *AB, integer *LDAB,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(pbsv_stub)(
  value vABR,
  value vABC,
  value vAB,
  value vN,
  value vKD,
  value vUPLO,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam2(vAB, vB);

  char GET_INT(UPLO);

  integer GET_INT(N),
          GET_INT(KD),
          GET_INT(NRHS),
          INFO;

  MAT_PARAMS(AB);
  MAT_PARAMS(B);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(pbsv)(
    &UPLO,
    &N, &KD, &NRHS,
    AB_data, &rows_AB,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(pbsv_stub_bc)(value *argv, int argn)
{
  return
    LFUN(pbsv_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
      argv[8], argv[9]);
}


/** PTSV */

extern void FUN(ptsv)(
  integer *N, integer *NRHS,
  REAL *D, NUMBER *E,
  NUMBER *B, integer *LDB,
  integer *INFO);

CAMLprim value LFUN(ptsv_stub)(
  value vOFSD, value vD, value vOFSE, value vE,
  value vN,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam3(vD, vE, vB);

  integer GET_INT(N),
          GET_INT(NRHS),
          INFO;

  RVEC_PARAMS(D);
  VEC_PARAMS(E);
  MAT_PARAMS(B);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(ptsv)(
    &N, &NRHS,
    D_data, E_data,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(ptsv_stub_bc)(value *argv, int argn)
{
  return LFUN(ptsv_stub)(argv[0], argv[1], argv[2], argv[3],
                         argv[4], argv[5], argv[6], argv[7], argv[8]);
}


/** SYSV */

extern void FUN(sysv)(
  char *UPLO,
  integer *N, integer *NRHS,
  NUMBER *A, integer *LDA,
  integer *IPIV,
  NUMBER *B, integer *LDB,
  NUMBER *WORK, integer *LWORK,
  integer *INFO);

CAMLprim value LFUN(sysv_stub)(
  value vAR,
  value vAC,
  value vA,
  value vN,
  value vUPLO,
  value vIPIV,
  value vWORK,
  value vLWORK,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam4(vA, vIPIV, vWORK, vB);

  char GET_INT(UPLO);

  integer GET_INT(N),
          GET_INT(LWORK),
          GET_INT(NRHS),
          INFO;

  MAT_PARAMS(A);
  INT_VEC_PARAMS(IPIV);
  VEC_PARAMS1(WORK);
  MAT_PARAMS(B);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(sysv)(
    &UPLO,
    &N, &NRHS,
    A_data, &rows_A,
    IPIV_data,
    B_data, &rows_B,
    WORK_data, &LWORK,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(sysv_stub_bc)(value *argv, int argn)
{
  return
    LFUN(sysv_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
      argv[8], argv[9], argv[10], argv[11]);
}


/** SPSV */

extern void FUN(spsv)(
  char *UPLO,
  integer *N, integer *NRHS,
  NUMBER *AP,
  integer *IPIV,
  NUMBER *B, integer *LDB,
  integer *INFO);


CAMLprim value LFUN(spsv_stub)(
  value vOFSAP, value vAP,
  value vN,
  value vUPLO,
  value vIPIV,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam3(vAP, vIPIV, vB);

  char GET_INT(UPLO);

  integer GET_INT(N),
          GET_INT(NRHS),
          INFO;

  VEC_PARAMS(AP);
  INT_VEC_PARAMS(IPIV);
  MAT_PARAMS(B);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(spsv)(
    &UPLO,
    &N, &NRHS,
    AP_data,
    IPIV_data,
    B_data, &rows_B,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(spsv_stub_bc)(value *argv, int argn)
{
  return LFUN(spsv_stub)(argv[0], argv[1], argv[2], argv[3],
                         argv[4], argv[5], argv[6], argv[7], argv[8]);
}


/* Linear Equations (expert drivers)
************************************************************************/

/** TODO: GESVX */

/** TODO: GBSVX */

/** TODO: GTSVX */

/** TODO: POSVX */

/** TODO: PPSVX */

/** TODO: PBSVX */

/** TODO: PTSVX */

/** TODO: SYSVX */

/** TODO: SPSVX */


/* Least squares (simple drivers)
************************************************************************/

/** GELS */

extern void FUN(gels)(
  char *TRANS,
  integer *M, integer *N, integer *NRHS,
  NUMBER *A, integer *LDA,
  NUMBER *B, integer *LDB,
  NUMBER *WORK, integer *LWORK,
  integer *INFO);

CAMLprim value LFUN(gels_stub)(
  value vAR,
  value vAC,
  value vA,
  value vM,
  value vN,
  value vTRANS,
  value vWORK,
  value vLWORK,
  value vNRHS,
  value vBR,
  value vBC,
  value vB)
{
  CAMLparam3(vA, vB, vWORK);

  char GET_INT(TRANS);

  integer GET_INT(M),
          GET_INT(N),
          GET_INT(LWORK),
          GET_INT(NRHS),
          INFO;

  MAT_PARAMS(A);
  MAT_PARAMS(B);

  VEC_PARAMS1(WORK);

  caml_enter_blocking_section();  /* Allow other threads */
  FUN(gels)(
    &TRANS,
    &M, &N, &NRHS,
    A_data, &rows_A,
    B_data, &rows_B,
    WORK_data, &LWORK,
    &INFO);
  caml_leave_blocking_section();  /* Disallow other threads */

  CAMLreturn(Val_int(INFO));
}

CAMLprim value LFUN(gels_stub_bc)(value *argv, int argn)
{
  return
    LFUN(gels_stub)(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
      argv[8], argv[9], argv[10], argv[11]);
}


/** GGLSE */


/* Standard eigenvalue and singular value problems (simple drivers)
************************************************************************/

/** TODO: GEES */


/* Generalized eigenvalue and singular value problems (simple drivers)
************************************************************************/

/** TODO: GGES */

/** TODO: GGEV */

/** TODO: GGSVD */


/* Generalized eigenvalue and singular value problems (expert drivers)
************************************************************************/

/** TODO: GEESX */

/** TODO: GGESX */

/** TODO: GEEVX */

/** TODO: GGEVX */