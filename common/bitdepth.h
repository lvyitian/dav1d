/*
 * ..
 */

#ifndef __DAV1D_COMMON_BITDEPTH_H__
#define __DAV1D_COMMON_BITDEPTH_H__ 1

#include <stdint.h>
#include <string.h>

#if !defined(BITDEPTH)
typedef void pixel;
typedef void coef;
#elif BITDEPTH == 8
typedef uint8_t pixel;
typedef int16_t coef;
#define pixel_copy memcpy
#define pixel_set memset
#define iclip_pixel iclip_u8
#define PIX_HEX_FMT "%02x"
#define bytefn(x) x##_8bpc
#define bitfn(x) x##_8bpc
#define PXSTRIDE(x) x
#elif BITDEPTH == 10 || BITDEPTH == 12
typedef uint16_t pixel;
typedef int32_t coef;
#define pixel_copy(a, b, c) memcpy(a, b, (c) << 1)
#define iclip_pixel(x) iclip(x, 0, ((1 << BITDEPTH) - 1))
static inline void pixel_set(pixel *const dst, const int val, const int num) {
    for (int n = 0; n < num; n++)
        dst[n] = val;
}
#define PIX_HEX_FMT "%03x"
#define bytefn(x) x##_16bpc
#if BITDEPTH == 10
#define bitfn(x) x##_10bpc
#else
#define bitfn(x) x##_12bpc
#endif
#define PXSTRIDE(x) (x >> 1)
#else
#error invalid value for bitdepth
#endif

#endif /* __DAV1D_COMMON_BITDEPTH_H__ */
