/*
 * ..
 */

#include "config.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input/input.h"
#include "input/demuxer.h"

struct DemuxerContext {
    DemuxerPriv *data;
    const Demuxer *impl;
};

#define MAX_NUM_DEMUXERS 1
static const Demuxer *demuxers[MAX_NUM_DEMUXERS];
static int num_demuxers = 0;

#define register_demuxer(impl) { \
    extern const Demuxer impl; \
    assert(num_demuxers < MAX_NUM_DEMUXERS); \
    demuxers[num_demuxers++] = &impl; \
}

void init_demuxers(void) {
    register_demuxer(ivf_demuxer);
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

int input_open(DemuxerContext **const c_out, const char *const filename,
               unsigned fps[2], unsigned *const num_frames)
{
    const Demuxer *impl;
    DemuxerContext *c;
    int res, i;

    const char *const ext = find_extension(filename);
    if (!ext) {
        fprintf(stderr, "No extension found for file %s\n", filename);
        return -1;
    }

    for (i = 0; i < num_demuxers; i++) {
        if (!strcmp(demuxers[i]->extension, ext)) {
            impl = demuxers[i];
            break;
        }
    }
    if (i == num_demuxers) {
        fprintf(stderr,
                "Failed to find demuxer for file %s (\"%s\")\n",
                filename, ext);
        return -ENOPROTOOPT;
    }

    if (!(c = malloc(sizeof(DemuxerContext) + impl->priv_data_size))) {
        fprintf(stderr, "Failed to allocate memory\n");
        return -ENOMEM;
    }
    memset(c, 0, sizeof(DemuxerContext) + impl->priv_data_size);
    c->impl = impl;
    c->data = (DemuxerPriv *) &c[1];
    if ((res = impl->open(c->data, filename, fps, num_frames)) < 0) {
        free(c);
        return res;
    }
    *c_out = c;

    return 0;
}

int input_read(DemuxerContext *const ctx, Dav1dData *const data) {
    return ctx->impl->read(ctx->data, data);
}

void input_close(DemuxerContext *const ctx) {
    ctx->impl->close(ctx->data);
    free(ctx);
}
