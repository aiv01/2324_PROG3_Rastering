#ifndef SCANLINE_RASTER_H
#define SCANLINE_RASTER_H
#include "vector.h"
#include "screen.h"
#include <stdbool.h>

typedef struct {
    vector2i_t* screen_pos;
    color_t* color;
    float z_pos;
} vertex_t;

void scanline_raster(screen_t* screen, vertex_t* v1, vertex_t* v2, vertex_t* v3);

#endif //SCANLINE_RASTER_H

