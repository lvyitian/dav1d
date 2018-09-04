/*
 * ..
 */

#ifndef __DAV1D_SRC_LF_APPLY_H__
#define __DAV1D_SRC_LF_APPLY_H__

#include <stdint.h>

#include "common/bitdepth.h"

#include "src/internal.h"
#include "src/levels.h"

void bytefn(dav1d_loopfilter_sbrow)(const Dav1dFrameContext *f,
                                    pixel *const p[3], Av1Filter *lflvl, int sby);

#endif /* __DAV1D_SRC_LF_APPLY_H__ */
