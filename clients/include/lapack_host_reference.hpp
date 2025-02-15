/* ************************************************************************
 * Copyright (c) 2020-2022 Advanced Micro Devices, Inc.
 * ************************************************************************/

#pragma once

#include "clientcommon.hpp"
#include "rocsolver_datatype2string.hpp"
#include <rocblas/rocblas.h>

/*!\file
 * \brief provide template functions interfaces to CBLAS and LAPACK interfaces,
 * it is only used for testing not part of the GPU library
 */

/*template <typename T>
void cblas_iamax(rocblas_int n, const T *x, rocblas_int incx,
                 rocblas_int *result);

template <typename T>
void cblas_iamin(rocblas_int n, const T *x, rocblas_int incx,
                 rocblas_int *result);

template <typename T1, typename T2>
void cblas_asum(rocblas_int n, const T1 *x, rocblas_int incx, T2 *result);

template <typename T>
void cblas_axpy(rocblas_int n, const T alpha, T *x, rocblas_int incx, T *y,
                rocblas_int incy);

template <typename T>
void cblas_copy(rocblas_int n, T *x, rocblas_int incx, T *y, rocblas_int incy);

template <typename T>
void cblas_dot(rocblas_int n, const T *x, rocblas_int incx, const T *y,
               rocblas_int incy, T *result);

template <typename T1, typename T2>
void cblas_nrm2(rocblas_int n, const T1 *x, rocblas_int incx, T2 *result);

template <typename T>
void cblas_scal(rocblas_int n, const T alpha, T *x, rocblas_int incx);

template <typename T>
void cblas_swap(rocblas_int n, T *x, rocblas_int incx, T *y, rocblas_int incy);

template <typename T>
void cblas_gemv(rocblas_operation transA, rocblas_int m, rocblas_int n, T alpha,
                T *A, rocblas_int lda, T *x, rocblas_int incx, T beta, T *y,
                rocblas_int incy);

template <typename T>
void cblas_ger(rocblas_int m, rocblas_int n, T alpha, T *x, rocblas_int incx,
               T *y, rocblas_int incy, T *A, rocblas_int lda);

template <typename T>
void cblas_syr(rocblas_fill uplo, rocblas_int n, T alpha, T *x,
               rocblas_int incx, T *A, rocblas_int lda);
*/
template <typename T>
void cblas_symv_hemv(rocblas_fill uplo,
                     rocblas_int n,
                     T alpha,
                     T* A,
                     rocblas_int lda,
                     T* x,
                     rocblas_int incx,
                     T beta,
                     T* y,
                     rocblas_int incy);

template <typename T>
void cblas_symm_hemm(rocblas_side side,
                     rocblas_fill uplo,
                     rocblas_int m,
                     rocblas_int n,
                     T alpha,
                     T* A,
                     rocblas_int lda,
                     T* B,
                     rocblas_int ldb,
                     T beta,
                     T* C,
                     rocblas_int ldc);

template <typename T>
void cblas_gemm(rocblas_operation transA,
                rocblas_operation transB,
                rocblas_int m,
                rocblas_int n,
                rocblas_int k,
                T alpha,
                T* A,
                rocblas_int lda,
                T* B,
                rocblas_int ldb,
                T beta,
                T* C,
                rocblas_int ldc);

template <typename T>
void cblas_trsm(rocblas_side side,
                rocblas_fill uplo,
                rocblas_operation transA,
                rocblas_diagonal diag,
                rocblas_int m,
                rocblas_int n,
                T alpha,
                T* A,
                rocblas_int lda,
                T* B,
                rocblas_int ldb);
/*
template <typename T>
void cblas_trsv(rocblas_fill uplo,
                rocblas_operation transA,
                rocblas_diagonal diag,
                rocblas_int n,
                T* A,
                rocblas_int lda,
                T* x,
                rocblas_int incx);
*/
template <typename T>
void cblas_trmm(rocblas_side side,
                rocblas_fill uplo,
                rocblas_operation transA,
                rocblas_diagonal diag,
                rocblas_int m,
                rocblas_int n,
                T alpha,
                T* A,
                rocblas_int lda,
                T* B,
                rocblas_int ldb);

template <typename T>
void cblas_potf2(rocblas_fill uplo, rocblas_int n, T* A, rocblas_int lda, rocblas_int* info);

template <typename T>
void cblas_potrf(rocblas_fill uplo, rocblas_int n, T* A, rocblas_int lda, rocblas_int* info);

template <typename T>
void cblas_potrs(rocblas_fill uplo,
                 rocblas_int n,
                 rocblas_int nrhs,
                 T* A,
                 rocblas_int lda,
                 T* B,
                 rocblas_int ldb);

template <typename T>
void cblas_posv(rocblas_fill uplo,
                rocblas_int n,
                rocblas_int nrhs,
                T* A,
                rocblas_int lda,
                T* B,
                rocblas_int ldb,
                rocblas_int* info);

template <typename T>
void cblas_potri(rocblas_fill uplo, rocblas_int n, T* A, rocblas_int lda, rocblas_int* info);

template <typename T>
void cblas_getf2(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, rocblas_int* ipiv, rocblas_int* info);

template <typename T>
void cblas_getrf(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, rocblas_int* ipiv, rocblas_int* info);

template <typename T>
void cblas_getrs(rocblas_operation trans,
                 rocblas_int n,
                 rocblas_int nrhs,
                 T* A,
                 rocblas_int lda,
                 rocblas_int* ipiv,
                 T* B,
                 rocblas_int ldb);

template <typename T>
void cblas_gesv(rocblas_int n,
                rocblas_int nrhs,
                T* A,
                rocblas_int lda,
                rocblas_int* ipiv,
                T* B,
                rocblas_int ldb,
                rocblas_int* info);

template <typename T>
void cblas_gels(rocblas_operation transR,
                rocblas_int m,
                rocblas_int n,
                rocblas_int nrhs,
                T* A,
                rocblas_int lda,
                T* B,
                rocblas_int ldb,
                T* work,
                rocblas_int lwork,
                rocblas_int* info);

template <typename T>
void cblas_getri(rocblas_int n,
                 T* A,
                 rocblas_int lda,
                 rocblas_int* ipiv,
                 T* work,
                 rocblas_int lwork,
                 rocblas_int* info);

template <typename T>
void cblas_trtri(rocblas_fill uplo,
                 rocblas_diagonal diag,
                 rocblas_int n,
                 T* A,
                 rocblas_int lda,
                 rocblas_int* info);

template <typename T>
void cblas_larfg(rocblas_int n, T* alpha, T* x, rocblas_int incx, T* tau);

template <typename T>
void cblas_larf(rocblas_side side,
                rocblas_int m,
                rocblas_int n,
                T* x,
                rocblas_int incx,
                T* alpha,
                T* A,
                rocblas_int lda,
                T* work);

template <typename T>
void cblas_larft(rocblas_direct direct,
                 rocblas_storev storev,
                 rocblas_int n,
                 rocblas_int k,
                 T* V,
                 rocblas_int ldv,
                 T* tau,
                 T* F,
                 rocblas_int ldt);

template <typename T>
void cblas_larfb(rocblas_side side,
                 rocblas_operation trans,
                 rocblas_direct direct,
                 rocblas_storev storev,
                 rocblas_int m,
                 rocblas_int n,
                 rocblas_int k,
                 T* V,
                 rocblas_int ldv,
                 T* F,
                 rocblas_int ldt,
                 T* A,
                 rocblas_int lda,
                 T* W,
                 rocblas_int ldw);

template <typename T, typename S>
void cblas_latrd(rocblas_fill uplo,
                 rocblas_int n,
                 rocblas_int k,
                 T* A,
                 rocblas_int lda,
                 S* E,
                 T* tau,
                 T* W,
                 rocblas_int ldw);

template <typename T, typename S>
void cblas_labrd(rocblas_int m,
                 rocblas_int n,
                 rocblas_int nb,
                 T* A,
                 rocblas_int lda,
                 S* D,
                 S* E,
                 T* tauq,
                 T* taup,
                 T* X,
                 rocblas_int ldx,
                 T* Y,
                 rocblas_int ldy);

template <typename T, typename W>
void cblas_bdsqr(rocblas_fill uplo,
                 rocblas_int n,
                 rocblas_int nv,
                 rocblas_int nu,
                 rocblas_int nc,
                 W* D,
                 W* E,
                 T* V,
                 rocblas_int ldv,
                 T* U,
                 rocblas_int ldu,
                 T* C,
                 rocblas_int ldc,
                 W* work,
                 rocblas_int* info);

template <typename T>
void cblas_geqr2(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, T* ipiv, T* work);

template <typename T>
void cblas_geqrf(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, T* ipiv, T* work, rocblas_int sizeW);

template <typename T>
void cblas_gerq2(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, T* ipiv, T* work);

template <typename T>
void cblas_gerqf(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, T* ipiv, T* work, rocblas_int sizeW);

template <typename T>
void cblas_geql2(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, T* ipiv, T* work);

template <typename T>
void cblas_geqlf(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, T* ipiv, T* work, rocblas_int sizeW);

template <typename T>
void cblas_gelq2(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, T* ipiv, T* work);

template <typename T>
void cblas_gelqf(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, T* ipiv, T* work, rocblas_int sizeW);

template <typename T>
void cblas_lacgv(rocblas_int n, T* x, rocblas_int incx);

template <typename T>
void cblas_laswp(rocblas_int n,
                 T* A,
                 rocblas_int lda,
                 rocblas_int k1,
                 rocblas_int k2,
                 rocblas_int* ipiv,
                 rocblas_int inc);

template <typename T>
void cblas_org2r_ung2r(rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* work);

template <typename T>
void cblas_orgqr_ungqr(rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* work,
                       rocblas_int sizeW);

template <typename T>
void cblas_orgl2_ungl2(rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* work);

template <typename T>
void cblas_orglq_unglq(rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* work,
                       rocblas_int sizeW);

template <typename T>
void cblas_org2l_ung2l(rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* work);

template <typename T>
void cblas_orgql_ungql(rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* work,
                       rocblas_int sizeW);

template <typename T>
void cblas_orgbr_ungbr(rocblas_storev storev,
                       rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* work,
                       rocblas_int size_w);

template <typename T>
void cblas_orgtr_ungtr(rocblas_fill uplo,
                       rocblas_int n,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* work,
                       rocblas_int size_w);

template <typename T>
void cblas_orm2r_unm2r(rocblas_side side,
                       rocblas_operation trans,
                       rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* C,
                       rocblas_int ldc,
                       T* work);

template <typename T>
void cblas_ormqr_unmqr(rocblas_side side,
                       rocblas_operation trans,
                       rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* C,
                       rocblas_int ldc,
                       T* work,
                       rocblas_int sizeW);

template <typename T>
void cblas_orml2_unml2(rocblas_side side,
                       rocblas_operation trans,
                       rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* C,
                       rocblas_int ldc,
                       T* work);

template <typename T>
void cblas_ormlq_unmlq(rocblas_side side,
                       rocblas_operation trans,
                       rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* C,
                       rocblas_int ldc,
                       T* work,
                       rocblas_int sizeW);

template <typename T>
void cblas_orm2l_unm2l(rocblas_side side,
                       rocblas_operation trans,
                       rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* C,
                       rocblas_int ldc,
                       T* work);

template <typename T>
void cblas_ormql_unmql(rocblas_side side,
                       rocblas_operation trans,
                       rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* C,
                       rocblas_int ldc,
                       T* work,
                       rocblas_int sizeW);

template <typename T>
void cblas_ormbr_unmbr(rocblas_storev storev,
                       rocblas_side side,
                       rocblas_operation trans,
                       rocblas_int m,
                       rocblas_int n,
                       rocblas_int k,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* C,
                       rocblas_int ldc,
                       T* work,
                       rocblas_int sizeW);

template <typename T>
void cblas_ormtr_unmtr(rocblas_side side,
                       rocblas_fill uplo,
                       rocblas_operation trans,
                       rocblas_int m,
                       rocblas_int n,
                       T* A,
                       rocblas_int lda,
                       T* Ipiv,
                       T* C,
                       rocblas_int ldc,
                       T* work,
                       rocblas_int sizeW);

template <typename T, typename S>
void cblas_gebd2(rocblas_int m, rocblas_int n, T* A, rocblas_int lda, S* D, S* E, T* tauq, T* taup, T* work);

template <typename T, typename S>
void cblas_gebrd(rocblas_int m,
                 rocblas_int n,
                 T* A,
                 rocblas_int lda,
                 S* D,
                 S* E,
                 T* tauq,
                 T* taup,
                 T* work,
                 rocblas_int size_w);

template <typename T, typename S>
void cblas_sytrd_hetrd(rocblas_fill uplo,
                       rocblas_int n,
                       T* A,
                       rocblas_int lda,
                       S* D,
                       S* E,
                       T* tau,
                       T* work,
                       rocblas_int size_w);

template <typename T, typename S>
void cblas_sytd2_hetd2(rocblas_fill uplo, rocblas_int n, T* A, rocblas_int lda, S* D, S* E, T* tau);

template <typename T, typename W>
void cblas_gesvd(rocblas_svect leftv,
                 rocblas_svect rightv,
                 rocblas_int m,
                 rocblas_int n,
                 T* A,
                 rocblas_int lda,
                 W* S,
                 T* U,
                 rocblas_int ldu,
                 T* V,
                 rocblas_int ldv,
                 T* work,
                 rocblas_int lwork,
                 W* E,
                 rocblas_int* info);

template <typename T>
void cblas_sterf(rocblas_int n, T* D, T* E);

template <typename T, typename S>
void cblas_steqr(rocblas_evect evect,
                 rocblas_int n,
                 S* D,
                 S* E,
                 T* C,
                 rocblas_int ldc,
                 S* work,
                 rocblas_int* info);

template <typename T, typename S>
void cblas_stedc(rocblas_evect evect,
                 rocblas_int n,
                 S* D,
                 S* E,
                 T* C,
                 rocblas_int ldc,
                 T* work,
                 rocblas_int lwork,
                 S* rwork,
                 rocblas_int lrwork,
                 rocblas_int* iwork,
                 rocblas_int liwork,
                 rocblas_int* info);

template <typename T>
void cblas_stebz(rocblas_erange erange,
                 rocblas_eorder eorder,
                 rocblas_int n,
                 T vl,
                 T vu,
                 rocblas_int il,
                 rocblas_int iu,
                 T abstol,
                 T* D,
                 T* E,
                 rocblas_int* nev,
                 rocblas_int* nsplit,
                 T* W,
                 rocblas_int* iblock,
                 rocblas_int* isplit,
                 T* work,
                 rocblas_int* iwork,
                 rocblas_int* info);

template <typename T, typename S>
void cblas_stein(rocblas_int n,
                 S* D,
                 S* E,
                 rocblas_int* nev,
                 S* W,
                 rocblas_int* iblock,
                 rocblas_int* isplit,
                 T* Z,
                 rocblas_int ldz,
                 S* work,
                 rocblas_int* iwork,
                 rocblas_int* ifail,
                 rocblas_int* info);

template <typename T>
void cblas_sygs2_hegs2(rocblas_eform itype,
                       rocblas_fill uplo,
                       rocblas_int n,
                       T* A,
                       rocblas_int lda,
                       T* B,
                       rocblas_int ldb);

template <typename T>
void cblas_sygst_hegst(rocblas_eform itype,
                       rocblas_fill uplo,
                       rocblas_int n,
                       T* A,
                       rocblas_int lda,
                       T* B,
                       rocblas_int ldb);

template <typename T, typename S>
void cblas_syev_heev(rocblas_evect evect,
                     rocblas_fill uplo,
                     rocblas_int n,
                     T* A,
                     rocblas_int lda,
                     S* W,
                     T* work,
                     rocblas_int lwork,
                     S* rwork,
                     rocblas_int lrwork,
                     rocblas_int* info);

template <typename T, typename S>
void cblas_syevd_heevd(rocblas_evect evect,
                       rocblas_fill uplo,
                       rocblas_int n,
                       T* A,
                       rocblas_int lda,
                       S* W,
                       T* work,
                       rocblas_int lwork,
                       S* rwork,
                       rocblas_int lrwork,
                       rocblas_int* iwork,
                       rocblas_int liwork,
                       rocblas_int* info);

template <typename T, typename S>
void cblas_syevx_heevx(rocblas_evect evect,
                       rocblas_erange erange,
                       rocblas_fill uplo,
                       rocblas_int n,
                       T* A,
                       rocblas_int lda,
                       S vl,
                       S vu,
                       rocblas_int il,
                       rocblas_int iu,
                       S abstol,
                       rocblas_int* nev,
                       S* W,
                       T* Z,
                       rocblas_int ldz,
                       T* work,
                       rocblas_int lwork,
                       S* rwork,
                       rocblas_int* iwork,
                       rocblas_int* ifail,
                       rocblas_int* info);

template <typename T, typename S>
void cblas_sygv_hegv(rocblas_eform itype,
                     rocblas_evect evect,
                     rocblas_fill uplo,
                     rocblas_int n,
                     T* A,
                     rocblas_int lda,
                     T* B,
                     rocblas_int ldb,
                     S* W,
                     T* work,
                     rocblas_int lwork,
                     S* rwork,
                     rocblas_int* info);

template <typename T, typename S>
void cblas_sygvd_hegvd(rocblas_eform itype,
                       rocblas_evect evect,
                       rocblas_fill uplo,
                       rocblas_int n,
                       T* A,
                       rocblas_int lda,
                       T* B,
                       rocblas_int ldb,
                       S* W,
                       T* work,
                       rocblas_int lwork,
                       S* rwork,
                       rocblas_int lrwork,
                       rocblas_int* iwork,
                       rocblas_int liwork,
                       rocblas_int* info);

template <typename T, typename S>
void cblas_sygvx_hegvx(rocblas_eform itype,
                       rocblas_evect evect,
                       rocblas_erange erange,
                       rocblas_fill uplo,
                       rocblas_int n,
                       T* A,
                       rocblas_int lda,
                       T* B,
                       rocblas_int ldb,
                       S vl,
                       S vu,
                       rocblas_int il,
                       rocblas_int iu,
                       S abstol,
                       rocblas_int* m,
                       S* W,
                       T* Z,
                       rocblas_int ldz,
                       T* work,
                       rocblas_int lwork,
                       S* rwork,
                       rocblas_int* iwork,
                       rocblas_int* ifail,
                       rocblas_int* info);

template <typename T>
void cblas_lasyf(rocblas_fill uplo,
                 rocblas_int n,
                 rocblas_int nb,
                 rocblas_int* kb,
                 T* A,
                 rocblas_int lda,
                 rocblas_int* ipiv,
                 T* W,
                 rocblas_int ldw,
                 rocblas_int* info);

template <typename T>
void cblas_sytf2(rocblas_fill uplo,
                 rocblas_int n,
                 T* A,
                 rocblas_int lda,
                 rocblas_int* ipiv,
                 rocblas_int* info);

template <typename T>
void cblas_sytrf(rocblas_fill uplo,
                 rocblas_int n,
                 T* A,
                 rocblas_int lda,
                 rocblas_int* ipiv,
                 T* work,
                 rocblas_int lwork,
                 rocblas_int* info);
