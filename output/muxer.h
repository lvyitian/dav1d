/*
 * ..
 */

#ifndef __DAV1D_OUTPUT_MUXER_H__
#define __DAV1D_OUTPUT_MUXER_H__

#include "picture.h"

typedef struct MuxerPriv MuxerPriv;
typedef struct Muxer {
    int priv_data_size;
    const char *name;
    const char *extension;
    int (*write_header)(MuxerPriv *ctx, const char *filename,
                        const Dav1dPictureParameters *p, const unsigned fps[2]);
    int (*write_picture)(MuxerPriv *ctx, Dav1dPicture *p);
    void (*write_trailer)(MuxerPriv *ctx);
} Muxer;

#endif /* __DAV1D_OUTPUT_MUXER_H__ */
