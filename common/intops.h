/*
 * ..
 */

#ifndef __DAV1D_COMMON_INTOPS_H__
#define __DAV1D_COMMON_INTOPS_H__

#include <stdint.h>

static inline int imax(const int a, const int b) {
    return a > b ? a : b;
}

static inline int imin(const int a, const int b) {
    return a < b ? a : b;
}

static inline int iclip(const int v, const int min, const int max) {
    return v < min ? min : v > max ? max : v;
}

static inline int iclip_u8(const int v) {
    return iclip(v, 0, 255);
}

static inline int apply_sign(const int v, const int s) {
    return s < 0 ? -v : v;
}

static inline int ulog2(const unsigned v) {
    return 31 - __builtin_clz(v);
}

static inline unsigned rl16(const uint8_t *const ptr) {
    return (ptr[1] << 8) | ptr[0];
}

static inline unsigned rl32(const uint8_t *const ptr) {
    return (rl16(&ptr[2]) << 16) | rl16(ptr);
}

static inline unsigned inv_recenter(const unsigned r, const unsigned v) {
    if (v > (r << 1))
        return v;
    else if ((v & 1) == 0)
        return (v >> 1) + r;
    else
        return r - ((v + 1) >> 1);
}

#endif /* __DAV1D_COMMON_INTOPS_H__ */
