/*
 * ..
 */

#ifndef __DAV1D_COMMON_DUMP_H__
#define __DAV1D_COMMON_DUMP_H__

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "common/bitdepth.h"

static inline void append_plane_to_file(const pixel *buf, ptrdiff_t stride,
                                        int w, int h, const char *const file)
{
    FILE *const f = fopen(file, "ab");
    while (h--) {
        fwrite(buf, w * sizeof(pixel), 1, f);
        buf += PXSTRIDE(stride);
    }
    fclose(f);
}

static inline void hex_dump(const pixel *buf, ptrdiff_t stride,
                            int w, int h, const char *what)
{
    printf("%s\n", what);
    while (h--) {
        int x;
        for (x = 0; x < w; x++)
            printf(" " PIX_HEX_FMT, buf[x]);
        buf += PXSTRIDE(stride);
        printf("\n");
    }
}

static inline void coef_dump(const coef *buf, const int w, const int h,
                             const int len, const char *what)
{
    int y;
    printf("%s\n", what);
    for (y = 0; y < h; y++) {
        int x;
        for (x = 0; x < w; x++)
            printf(" %*d", len, buf[x]);
        buf += w;
        printf("\n");
    }
}

#endif /* __DAV1D_COMMON_DUMP_H__ */
