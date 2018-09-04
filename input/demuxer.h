/*
 * ..
 */

#ifndef __DAV1D_INPUT_DEMUXER_H__
#define __DAV1D_INPUT_DEMUXER_H__

#include "data.h"

typedef struct DemuxerPriv DemuxerPriv;
typedef struct Demuxer {
    int priv_data_size;
    const char *name;
    const char *extension;
    int (*open)(DemuxerPriv *ctx, const char *filename,
                unsigned fps[2], unsigned *num_frames);
    int (*read)(DemuxerPriv *ctx, Dav1dData *data);
    void (*close)(DemuxerPriv *ctx);
} Demuxer;

#endif /* __DAV1D_INPUT_DEMUXER_H__ */
