/*
 * ..
 */

#ifndef __DAV1D_SRC_LF_MASK_H__
#define __DAV1D_SRC_LF_MASK_H__

#include <stddef.h>
#include <stdint.h>

#include "src/levels.h"

typedef struct Av1FilterLUT {
    uint8_t e[64];
    uint8_t i[64];
} Av1FilterLUT;

typedef struct Av1RestorationUnit {
    enum RestorationType type;
    int16_t filter_h[3];
    int16_t filter_v[3];
    uint8_t sgr_idx;
    int16_t sgr_weights[2];
} Av1RestorationUnit;

// each struct describes one 128x128 area (1 or 4 SBs)
typedef struct Av1Filter {
    // each bit is 1 col
    uint32_t filter_y[2 /* 0=col, 1=row */][32][3];
    uint32_t filter_uv[2 /* 0=col, 1=row */][32][2];
    int8_t cdef_idx[4]; // -1 means "unset"
    uint32_t noskip_mask[32];
    Av1RestorationUnit lr[3][4];
} Av1Filter;

void dav1d_create_lf_mask_intra(Av1Filter *lflvl, uint8_t (*level_cache)[4],
                                const ptrdiff_t b4_stride,
                                const Av1FrameHeader *hdr,
                                const uint8_t (*level)[8][2], int bx, int by,
                                int iw, int ih, enum BlockSize bs,
                                enum RectTxfmSize ytx, enum RectTxfmSize uvtx,
                                enum Dav1dPixelLayout layout, uint8_t *ay,
                                uint8_t *ly, uint8_t *auv, uint8_t *luv);
void dav1d_create_lf_mask_inter(Av1Filter *lflvl, uint8_t (*level_cache)[4],
                                const ptrdiff_t b4_stride,
                                const Av1FrameHeader *hdr,
                                const uint8_t (*level)[8][2], int bx, int by,
                                int iw, int ih, int skip_inter,
                                enum BlockSize bs, const uint16_t *tx_mask,
                                enum RectTxfmSize uvtx,
                                enum Dav1dPixelLayout layout, uint8_t *ay,
                                uint8_t *ly, uint8_t *auv, uint8_t *luv);
void dav1d_calc_eih(Av1FilterLUT *lim_lut, int filter_sharpness);
void dav1d_calc_lf_values(uint8_t (*values)[4][8][2], const Av1FrameHeader *hdr,
                          const int8_t lf_delta[4]);

#endif /* __DAV1D_SRC_LF_MASK_H__ */
