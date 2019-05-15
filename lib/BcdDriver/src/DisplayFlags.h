#ifndef _DISPLAYFLAGS_H_
#define _DISPLAYFLAGS_H_

enum DisplayFlags {
    DISPLAY_NONE = 0,
    DISPLAY_DP1 = 1 << 0,
    DISPLAY_DP2 = 1 << 1,
    DISPLAY_DP3 = 1 << 2,
    DISPLAY_DP4 = 1 << 3,
    DISPLAY_L1_L2 = 1 << 4
};

#endif