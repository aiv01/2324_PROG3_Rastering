#include "scene.h"
#include "SDL.h"
#include <math.h>


/// @brief rasterize a line from p1 (x1,y2) to p2 (x2,y2)
void dda_line_raster(SDL_Renderer* r, int x1, int y1, int x2, int y2) 
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int steps = (dx > dy) ? dx : dy;

    int sx = (x1 > x2) ? -1 : 1;
    int sy = (y1 > y2) ? -1 : 1;

    float step_x = (float)dx * (float)sx / (float)steps;
    float step_y = (float)dy * (float)sy / (float)steps;

    int x = x1;
    int y = y1;
    for (int i = 0; i < steps; i++)
    {
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        SDL_RenderDrawPoint(r, x, y);

        x += step_x;
        y += step_y;
    }
    
}

static SDL_Renderer* renderer;

scene_t* scene_create(int screen_width, int screen_height, SDL_Renderer* r) {
    renderer = r;
    return NULL;
}

void scene_update(scene_t* s, float delta_time) {
    dda_line_raster(renderer, 0, 0, 100, 100);
}

void scene_destroy(scene_t* s) {
    
}