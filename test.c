#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "console.h"
#include "raster.h"
#include "ki25.h"

#define FONT_ASPECT 0.5

si f32 bound(f32 x, f32 y, f32 a, f32 r) {
    return sin(a) * x + cos(a) * y - r;
}

si f32 triangle(f32 x, f32 y, f32 r) {
    f32 d = r * cos(M_PI/3);
    return fmax
    ( fmax
      ( bound(x, y, M_PI, d)
      , bound(x, y, M_PI / 3, d)
      )
    , bound(x, y, -M_PI / 3, d)
    );
}

si f32 circle(f32 x, f32 y, f32 r) {
    return sqrt(x * x + y * y) - r;
}

si u8 raster(u32 i, u16 w, u16 h, float a) {
    f32 x = rasterx(i, w, h, a);
    f32 y = rastery(i, w, h, a);
    f32 d = fmax(triangle(x, y, 1/4.0), -circle(x, y + 1/4.0 * cos(M_PI/3), 1/16.0));
    return d <= 0 ? 'Q' : ' ';
}

int main() {
    u16 cols = ws_col();
    u16 rows = ws_row();
    float aspect = FONT_ASPECT * cols / rows;
    u32 n = cols * rows;
    u8 *xs = alloca(n);
    for (u32 i = 0; i < n; i++) {
        xs[i] = raster(i, cols, rows, aspect);
    }
    printf("\n%dx%d (%f)\n", cols, rows, aspect);
    write(1, xs + cols, n - cols);
}
