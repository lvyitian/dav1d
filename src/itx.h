/*
 * ..
 */

#ifndef __DAV1D_SRC_ITX_H__
#define __DAV1D_SRC_ITX_H__

#include "common/bitdepth.h"

#include "src/levels.h"

#define decl_itx_fn(name) \
void (name)(pixel *dst, ptrdiff_t dst_stride, coef *coeff, int eob)
typedef decl_itx_fn(*itxfm_fn);

typedef struct Dav1dInvTxfmDSPContext {
    itxfm_fn itxfm_add[N_RECT_TX_SIZES][N_TX_TYPES_PLUS_LL];
} Dav1dInvTxfmDSPContext;

void dav1d_itx_dsp_init_8bpc(Dav1dInvTxfmDSPContext *c);
void dav1d_itx_dsp_init_10bpc(Dav1dInvTxfmDSPContext *c);

#endif /* __DAV1D_SRC_ITX_H__ */
