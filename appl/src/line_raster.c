#include "line_raster.h"

void dda_line_raster(screen_t* screen, const int x1, const int y1, const int x2, const int y2, color_t* color)
{
    const unsigned int dx = abs(x2 - x1);
    const unsigned int dy = abs(y2 - y1);

    const unsigned int steps = (dx > dy) ? dx : dy;

    const int sign_of_x = (x1 > x2) ? -1 : 1;
    const int sign_of_y = (y1 > y2) ? -1 : 1;

    const float step_x = (float)dx / steps * sign_of_x;
    const float step_y = (float)dy / steps * sign_of_y;

    float x = x1;
    float y = y1;
    for (int i = 0; i < steps; i++)
    {
        screen_put_pixel(screen, x, y, color);

        x += step_x;
        y += step_y;
    }
}