#include <sys/ioctl.h>

#include "ki25.h"

si u32 winsz() {
    struct winsize x;
    ioctl(1, TIOCGWINSZ, &x);
    return x.ws_row << 16 | x.ws_col;
}

si u16 ws_col() {
    return winsz();
}

si u16 ws_row() {
    return winsz() >> 16;
}
