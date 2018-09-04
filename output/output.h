/*
 * ..
 */

#ifndef __DAV1D_OUTPUT_OUTPUT_H__
#define __DAV1D_OUTPUT_OUTPUT_H__

#include "picture.h"

typedef struct MuxerContext MuxerContext;

void init_muxers(void);
int output_open(MuxerContext **c, const char *name, const char *filename,
                const Dav1dPictureParameters *p, const unsigned fps[2]);
int output_write(MuxerContext *ctx, Dav1dPicture *pic);
void output_close(MuxerContext *ctx);

#endif /* __DAV1D_OUTPUT_OUTPUT_H__ */
