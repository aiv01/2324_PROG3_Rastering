#include "scene.h"
#include "SDL.h"
#include <math.h>
#include <stdlib.h>
#include "color.h"
#include "line_raster.h"

scene_t* scene_create(int screen_width, int screen_height, SDL_Renderer* r) {
    scene_t* scene = (scene_t*)malloc(sizeof(scene_t));
    scene->screen = screen_new(screen_width, screen_height, r);
    return scene;
}

void scene_update(scene_t* s, float delta_time) {

    screen_clear(s->screen);

    color_t yellow = {255, 255, 0, 255};

    dda_line_raster(s->screen, 0, 0, 100, 100, yellow);

    static float x1 = 0;
    static float y1 = 0;
    static float x2 = 100;
    static float y2 = 100;

    dda_line_raster(s->screen, (float)x1, (float)y1, (float)x2, (float)y2, yellow);

    x1 += delta_time * 10.f;
    y1 += delta_time * 10.f;
    x2 += delta_time * 10.f;
    y2 += delta_time * 10.f;


    //Draw Triangle Edges
    dda_line_raster(s->screen, 100, 400, 200, 100, yellow); //Left
    dda_line_raster(s->screen, 300, 400, 200, 100, yellow); //Right
    dda_line_raster(s->screen, 100, 400, 300, 400, yellow); //Base

    screen_blit(s->screen);
}

void scene_destroy(scene_t* s) {
    screen_free(s->screen);
    free(s);
}