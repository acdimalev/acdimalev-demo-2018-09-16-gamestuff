#include <math.h>

#include "ki25.h"

// convert an index into a coordinate,
// given a width `w` and height `h`
si u16 xcoord(u32 i, u16 w, u16 h) { return i % w; }
si u16 ycoord(u32 i, u16 w, u16 h) { return i / w; }

// normalize value on a scale from `0` to `s`
si f32 fnorm(u16 x, u16 s) { return (f32)x / s; }

// project normalized `(x, y)` coordinates
// to unit rectangle coordinate space
// given a visual width-to-height ratio `a`
si f32 xproj(f32 x, f32 a) { return (x - 0.5) * a * sqrt(1 / a); }
si f32 yproj(f32 y, f32 a) { return (0.5 - y) * sqrt(1 / a); }


// convert raster index to unit rectangle coordinate space
// given...
//   w: width
//   h: height
//   a: visual width-to-height ratio

si f32 rasterx(u32 i, u16 w, u16 h, f32 a)
{ return xproj(fnorm(xcoord(i, w, h), w), a); }

si f32 rastery(u32 i, u16 w, u16 h, f32 a)
{ return yproj(fnorm(ycoord(i, w, h), h), a); }
