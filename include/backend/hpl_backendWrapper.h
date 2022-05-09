#pragma once

#include <stdint.h>
#include <stddef.h>

#define DO_NOTHING()

#ifdef __cplusplus
extern "C" {
#endif


#include "hpl_grid.h"
#include "hpl_blas.h"
#include "hpl_panel.h"

enum HPL_TARGET {T_DEFAULT, T_CPU, T_HIP, T_TEMPO};
enum HPL_MOVE_DIRECTION {M_H2H = 0,
                         M_H2D = 1,
                         M_D2H = 2,
                         M_D2D = 3,
                         M_DEFAULT = 4};
enum HPL_EVENT {HPL_PANEL_COPY, HPL_PANEL_UPDATE, HPL_RS_1, HPL_RS_2, HPL_RS_3};
enum HPL_STREAM {HPL_COMPUTESTREAM, HPL_DATASTREAM, HPL_PDLASWPSTREAM};


void HPL_BE_init(size_t, enum HPL_TARGET);

void HPL_BE_malloc(void**, size_t, enum HPL_TARGET);

void HPL_BE_free(void **, enum HPL_TARGET);

void HPL_BE_panel_new(HPL_T_grid *, HPL_T_palg *, const int, const int, const int,
                        HPL_T_pmat *, const int, const int, const int, HPL_T_panel * *, enum HPL_TARGET);
void HPL_BE_panel_init(HPL_T_grid *, HPL_T_palg *, const int,
                    const int, const int, HPL_T_pmat *,
                    const int, const int, const int, HPL_T_panel *, enum HPL_TARGET);
void HPL_BE_panel_free(HPL_T_panel *, enum HPL_TARGET);
void HPL_BE_panel_disp(HPL_T_panel**, enum HPL_TARGET);

void HPL_BE_panel_send_to_device(HPL_T_panel*, enum HPL_TARGET);
void HPL_BE_panel_send_to_host(HPL_T_panel*, enum HPL_TARGET);

void HPL_BE_dmatgen(const HPL_T_grid *, const int, const int,
                 const int, double *, const int,
                 const int, enum HPL_TARGET);

void HPL_BE_device_sync(enum HPL_TARGET);
void HPL_BE_event_record(enum HPL_EVENT, enum HPL_TARGET);
void HPL_BE_event_synchronize(enum HPL_EVENT, enum HPL_TARGET);
void HPL_BE_stream_synchronize(enum HPL_STREAM, enum HPL_TARGET);
void HPL_BE_stream_wait_event(enum HPL_STREAM, enum HPL_EVENT, enum HPL_TARGET);

void HPL_BE_stream_sync(enum HPL_STREAM, enum HPL_TARGET);

/*
    Broadcast routine
*/
void HPL_BE_binit_ibcast(HPL_T_panel*, int&, HPL_TARGET);
void HPL_BE_bcast_ibcast(HPL_T_panel*, int*, int&, HPL_TARGET);
void HPL_BE_bwait_ibcast(HPL_T_panel*, int&, HPL_TARGET);
/*
*  ----------------------------------------------------------------------
*  - BLAS ---------------------------------------------------------------
*  ----------------------------------------------------------------------
*/ 

int  HPL_BE_idamax(const int, const double *, const int, enum HPL_TARGET);
void HPL_BE_daxpy(const int, const double, const double *, const int, double *, 
                const int, enum HPL_TARGET);
void HPL_BE_dscal(const int, const double, double *, const int, enum HPL_TARGET);
void HPL_BE_dswap(const int, double *, const int, double *, const int, enum HPL_TARGET);

void HPL_BE_dger( const enum HPL_ORDER, const int, const int, const double, const double *,
               const int, double *, const int, double *, const int, enum HPL_TARGET);







void HPL_BE_dtrsm(const enum HPL_ORDER, const enum HPL_SIDE, 
                const enum HPL_UPLO, const enum HPL_TRANS, 
                const enum HPL_DIAG, const int, const int, 
                const double, const double *, const int, double *, 
                const int, enum HPL_TARGET);

void HPL_BE_dtrsv(const enum HPL_ORDER, const enum HPL_UPLO,
                const enum HPL_TRANS, const enum HPL_DIAG,
                const int, const double *, const int,
                double *, const int, enum HPL_TARGET);                

void HPL_BE_dgemm(const enum HPL_ORDER, const enum HPL_TRANS, const enum HPL_TRANS,
                const int, const int, const int, const double, const double *,
                const int, const double *, const int, const double, double *, 
                const int, enum HPL_TARGET);

void HPL_BE_dgemv(const enum HPL_ORDER, const enum HPL_TRANS, const int, const int,
                const double, const double *, const int, const double *, const int,
                const double, double *, const int, enum HPL_TARGET);

void HPL_BE_dcopy(const int, const double *, const int, double *, const int, enum HPL_TARGET);

void HPL_BE_dlacpy(const int, const int, const double *, const int, double *, const int, enum HPL_TARGET);

void HPL_BE_dlatcpy(const int, const int, const double *, const int,
                double *, const int, enum HPL_TARGET);

void HPL_BE_move_data(double *, const double *, const size_t, enum HPL_MOVE_DIRECTION, enum HPL_TARGET);                

void HPL_BE_dlaswp00N(const int, const int, double *, const int, const int *, enum HPL_TARGET);
void HPL_BE_pdlaswp(HPL_T_panel*, const int, enum HPL_TARGET);

#ifdef __cplusplus
}
#endif