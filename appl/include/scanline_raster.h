#ifndef SCANLINE_RASTER_H
#define SCANLINE_RASTER_H
#include "vector.h"
#include "screen.h"
#include <stdbool.h>

void scanline_raster(screen_t* screen, vector2i_t p1, vector2i_t p2, vector2i_t p3);

#endif //SCANLINE_RASTER_H

