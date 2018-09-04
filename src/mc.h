/*
 * ..
 */

#ifndef __DAV1D_SRC_MC_H__
#define __DAV1D_SRC_MC_H__

#include <stdint.h>
#include <stddef.h>

#include "common/bitdepth.h"

#include "src/levels.h"

#define decl_mc_fn(name) \
void (name)(pixel *dst, ptrdiff_t dst_stride, \
            const pixel *src, ptrdiff_t src_stride, \
            int w, int h, int mx, int my)
typedef decl_mc_fn(*mc_fn);

#define decl_warp8x8_fn(name) \
void (name)(pixel *dst, ptrdiff_t dst_stride, \
            const pixel *src, ptrdiff_t src_stride, \
            const int16_t *abcd, int mx, int my)
typedef decl_warp8x8_fn(*warp8x8_fn);

#define decl_mct_fn(name) \
void (name)(coef *tmp, const pixel *src, ptrdiff_t src_stride, \
            int w, int h, int mx, int my)
typedef decl_mct_fn(*mct_fn);

#define decl_warp8x8t_fn(name) \
void (name)(coef *tmp, const ptrdiff_t tmp_stride, \
            const pixel *src, ptrdiff_t src_stride, \
            const int16_t *abcd, int mx, int my)
typedef decl_warp8x8t_fn(*warp8x8t_fn);

#define decl_avg_fn(name) \
void (name)(pixel *dst, ptrdiff_t dst_stride, \
            const coef *tmp1, const coef *tmp2, int w, int h)
typedef decl_avg_fn(*avg_fn);

#define decl_w_avg_fn(name) \
void (name)(pixel *dst, ptrdiff_t dst_stride, \
            const coef *tmp1, const coef *tmp2, int w, int h, int weight)
typedef decl_w_avg_fn(*w_avg_fn);

#define decl_mask_fn(name) \
void (name)(pixel *dst, ptrdiff_t dst_stride, \
            const coef *tmp1, const coef *tmp2, int w, int h, \
            const uint8_t *mask)
typedef decl_mask_fn(*mask_fn);

#define decl_w_mask_fn(name) \
void (name)(pixel *dst, ptrdiff_t dst_stride, \
            const coef *tmp1, const coef *tmp2, int w, int h, \
            uint8_t *mask, int sign)
typedef decl_w_mask_fn(*w_mask_fn);

#define decl_blend_fn(name) \
void (name)(pixel *dst, ptrdiff_t dst_stride, \
            const pixel *tmp, ptrdiff_t tmp_stride, int w, int h, \
            const uint8_t *mask, ptrdiff_t mstride)
typedef decl_blend_fn(*blend_fn);

typedef struct Dav1dMCDSPContext {
    mc_fn mc[N_2D_FILTERS];
    mct_fn mct[N_2D_FILTERS];
    avg_fn avg;
    w_avg_fn w_avg;
    mask_fn mask;
    w_mask_fn w_mask[3 /* 444, 422, 420 */];
    blend_fn blend;
    warp8x8_fn warp8x8;
    warp8x8t_fn warp8x8t;
} Dav1dMCDSPContext;

void dav1d_mc_dsp_init_8bpc(Dav1dMCDSPContext *c);
void dav1d_mc_dsp_init_10bpc(Dav1dMCDSPContext *c);

#endif /* __DAV1D_SRC_MC_H__ */
