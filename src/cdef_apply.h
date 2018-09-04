/*
 * ..
 */

#ifndef __DAV1D_SRC_CDEF_APPLY_H__
#define __DAV1D_SRC_CDEF_APPLY_H__

#include "common/bitdepth.h"

#include "src/internal.h"

void bytefn(dav1d_cdef_brow)(const Dav1dFrameContext *f, pixel *const p[3],
                             const Av1Filter *lflvl, int by_start, int by_end);

#endif /* __DAV1D_SRC_CDEF_APPLY_H__ */
