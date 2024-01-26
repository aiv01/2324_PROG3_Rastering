#include <stdlib.h>
#include "scene.h"
#include "SDL.h"
#include "color.h"
#include "line_raster.h"

scene_t* scene_create(int screen_width, int screen_height, SDL_Renderer* r)
{
    scene_t* scene = (scene_t*)malloc(sizeof(scene_t));
    scene->screen = screen_new(screen_width, screen_height, r);

    return scene;
}

void scene_update(scene_t* s, float delta_time)
{
    color_t yellow = {255, 255, 0, 255};
    dda_line_raster(s->screen, 0, 0, 100, 100, &yellow);
    screen_blit(s->screen);
    screen_clear(s->screen);
}

void scene_destroy(scene_t* s)
{
    screen_free(s->screen);
    free(s);
}