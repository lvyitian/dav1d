/*
 * ..
 */

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "output/output.h"
#include "output/muxer.h"

struct MuxerContext {
    MuxerPriv *data;
    const Muxer *impl;
};

#define MAX_NUM_MUXERS 3
static const Muxer *muxers[MAX_NUM_MUXERS];
static int num_muxers = 0;

#define register_muxer(impl) { \
    extern const Muxer impl; \
    assert(num_muxers < MAX_NUM_MUXERS); \
    muxers[num_muxers++] = &impl; \
}

void init_muxers(void) {
    register_muxer(md5_muxer);
    register_muxer(yuv_muxer);
    register_muxer(y4m2_muxer);
}

static const char *find_extension(const char *const f) {
    const int l = strlen(f);

    if (l == 0) return NULL;

    const char *const end = &f[l - 1], *step = end;
    while ((*step >= 'a' && *step <= 'z') ||
           (*step >= 'A' && *step <= 'Z') ||
           (*step >= '0' && *step <= '9'))
    {
        step--;
    }

    return (step < end && step > f && *step == '.' && step[-1] != '/') ?
           &step[1] : NULL;
}

int output_open(MuxerContext **const c_out,
                const char *const name, const char *const filename,
                const Dav1dPictureParameters *const p, const unsigned fps[2])
{
    const Muxer *impl;
    MuxerContext *c;
    int res, i;

    if (name) {
        for (i = 0; i < num_muxers; i++) {
            if (!strcmp(muxers[i]->name, name)) {
                impl = muxers[i];
                break;
            }
        }
        if (i == num_muxers) {
            fprintf(stderr, "Failed to find muxer named \"%s\"\n", name);
            return -ENOPROTOOPT;
        }
    } else {
        const char *ext = find_extension(filename);
        if (!ext) {
            fprintf(stderr, "No extension found for file %s\n", filename);
            return -1;
        }
        for (i = 0; i < num_muxers; i++) {
            if (!strcmp(muxers[i]->extension, ext)) {
                impl = muxers[i];
                break;
            }
        }
        if (i == num_muxers) {
            fprintf(stderr, "Failed to find muxer for extension \"%s\"\n", ext);
            return -ENOPROTOOPT;
        }
    }

    if (!(c = malloc(sizeof(MuxerContext) + impl->priv_data_size))) {
        fprintf(stderr, "Failed to allocate memory\n");
        return -ENOMEM;
    }
    c->impl = impl;
    c->data = (MuxerPriv *) &c[1];
    if ((res = impl->write_header(c->data, filename, p, fps)) < 0) {
        free(c);
        return res;
    }
    *c_out = c;

    return 0;
}

int output_write(MuxerContext *const ctx, Dav1dPicture *const p) {
    int res;

    if ((res = ctx->impl->write_picture(ctx->data, p)) < 0)
        return res;

    return 0;
}

void output_close(MuxerContext *const ctx) {
    ctx->impl->write_trailer(ctx->data);
    free(ctx);
}
