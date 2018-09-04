/*
 * ..
 */

#ifndef __DAV1D_SRC_INTRA_EDGE_H__
#define __DAV1D_SRC_INTRA_EDGE_H__

enum EdgeFlags {
    EDGE_I444_TOP_HAS_RIGHT = 1 << 0,
    EDGE_I422_TOP_HAS_RIGHT = 1 << 1,
    EDGE_I420_TOP_HAS_RIGHT = 1 << 2,
    EDGE_I444_LEFT_HAS_BOTTOM = 1 << 3,
    EDGE_I422_LEFT_HAS_BOTTOM = 1 << 4,
    EDGE_I420_LEFT_HAS_BOTTOM = 1 << 5,
};

typedef struct EdgeNode EdgeNode;
struct EdgeNode {
    enum EdgeFlags o, h[2], v[2];
};
typedef struct EdgeTip {
    EdgeNode node;
    enum EdgeFlags split[4];
} EdgeTip;
typedef struct EdgeBranch {
    EdgeNode node;
    enum EdgeFlags tts[3], tbs[3], tls[3], trs[3], h4[4], v4[4];
    EdgeNode *split[4];
} EdgeBranch;

void init_mode_tree(EdgeNode *const root, EdgeTip *const nt,
                    const int allow_sb128);

#endif /* __DAV1D_SRC_INTRA_EDGE_H__ */
