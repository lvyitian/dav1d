/*
 * ..
 */

#ifndef __DAV1D_SRC_CDEF_H__
#define __DAV1D_SRC_CDEF_H__

#include <stddef.h>
#include <stdint.h>

#include "common/bitdepth.h"

enum CdefEdgeFlags {
    HAVE_LEFT = 1 << 0,
    HAVE_RIGHT = 1 << 1,
    HAVE_TOP = 1 << 2,
    HAVE_BOTTOM = 1 << 3,
};

typedef void (*cdef_fn)(pixel *dst, ptrdiff_t stride,
                        int pri_strength, int sec_strength,
                        int dir, int damping, enum CdefEdgeFlags edges);
typedef int (*cdef_dir_fn)(const pixel *dst, ptrdiff_t stride,
                           unsigned *var);

typedef struct Dav1dCdefDSPContext {
    cdef_dir_fn dir;
    cdef_fn fb[3 /* 444/luma, 422, 420 */];
} Dav1dCdefDSPContext;

void dav1d_cdef_dsp_init_8bpc(Dav1dCdefDSPContext *c);
void dav1d_cdef_dsp_init_10bpc(Dav1dCdefDSPContext *c);

#endif /* __DAV1D_SRC_CDEF_H__ */
