#ifndef SCANLINE_RASTER_H
#define SCANLINE_RASTER_H
#include "vector.h"
#include "screen.h"
#include <stdbool.h>
#include "texture.h"

typedef struct {
    vector2i_t* screen_pos;
    color_t* color;
    float z_pos;
    vector2f_t* text_coord;
} vertex_t;

typedef enum {
    GPU_FLAG_NONE = 0,
    GPU_FLAG_COLOR_MODE =   1 << 0,
    GPU_FLAG_TEXTURE_MODE = 1 << 1, //2,
} gpu_flags_e;
 
typedef struct {
    screen_t* screen;
    texture_t* texture;
    gpu_flags_e flags;
} gpu_t;

void scanline_raster(gpu_t* gpu, vertex_t* v1, vertex_t* v2, vertex_t* v3);

#endif //SCANLINE_RASTER_H

