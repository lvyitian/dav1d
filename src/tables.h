/*
 * ..
 */

#ifndef __DAV1D_SRC_TABLES_H__
#define __DAV1D_SRC_TABLES_H__

#include <stdint.h>

#include "common/intops.h"

#include "src/levels.h"

extern const uint8_t av1_al_part_ctx[2][N_BL_LEVELS][N_PARTITIONS];
extern const uint8_t /* enum BlockSize */
                     av1_block_sizes[N_BL_LEVELS][N_PARTITIONS][2];
// width, height (in 4px blocks), log2 versions of these two
extern const uint8_t av1_block_dimensions[N_BS_SIZES][4];
typedef struct TxfmInfo {
    // width, height (in 4px blocks), log2 of them, min/max of log2, sub, pad
    uint8_t w, h, lw, lh, min, max, sub, ctx;
} TxfmInfo;
extern const TxfmInfo av1_txfm_dimensions[N_RECT_TX_SIZES];
extern const uint8_t /* enum (Rect)TxfmSize */
                     av1_max_txfm_size_for_bs[N_BS_SIZES][4 /* y, 420, 422, 444 */];
extern const uint8_t /* enum TxfmType */
                     av1_txtp_from_uvmode[N_UV_INTRA_PRED_MODES];

extern const uint8_t /* enum InterPredMode */
                     av1_comp_inter_pred_modes[N_COMP_INTER_PRED_MODES][2];

extern const uint8_t av1_tx_type_count[N_TXTP_SETS];
extern const uint8_t /* enum TxfmType */
                     av1_tx_types_per_set[N_TXTP_SETS][N_TX_TYPES];
extern const uint8_t av1_tx_type_set_index[2][N_TXTP_SETS];

extern const uint8_t av1_filter_mode_to_y_mode[5];
extern const uint8_t av1_ymode_size_context[N_BS_SIZES];
extern const uint8_t av1_nz_map_ctx_offset[N_RECT_TX_SIZES][5][5];
extern const uint8_t /* enum TxClass */
                     av1_tx_type_class[N_TX_TYPES_PLUS_LL];
extern const uint8_t /* enum Filter2d */
                     av1_filter_2d[N_FILTERS /* h */][N_FILTERS /* v */];
extern const uint8_t intra_mode_context[N_INTRA_PRED_MODES];
extern const uint8_t av1_wedge_ctx_lut[N_BS_SIZES];

extern const unsigned cfl_allowed_mask;
extern const unsigned wedge_allowed_mask;
extern const unsigned interintra_allowed_mask;

extern const WarpedMotionParams default_wm_params;

extern const int16_t av1_sgr_params[16][4];

extern const int8_t dav1d_mc_subpel_filters[5][15][8];
extern const int8_t dav1d_mc_warp_filter[][8];

#endif /* __DAV1D_SRC_TABLES_H__ */
