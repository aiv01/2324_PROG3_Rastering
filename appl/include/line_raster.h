#ifndef LINE_RASTER_H
#define LINE_RASTER_H
#include "screen.h"
#include "color.h"

/// @brief Rasterizes a line from p1 (x1,x2) to p2 (x2,y2)
void dda_line_raster(screen_t* screen, const int x1, const int y1, const int x2, const int y2, color_t* color);

#endif //LINE_RASTER_H