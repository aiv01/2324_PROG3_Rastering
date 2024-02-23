#include "scene.h"
#include "SDL.h"
#include <math.h>
#include <stdlib.h>
#include "color.h"
#include "line_raster.h"
#include "vector.h"
#include "triangle_raster.h"
#include "camera.h"
#include "scanline_raster.h"

scene_t* scene_create(int screen_width, int screen_height, SDL_Renderer* r) {
    scene_t* scene = (scene_t*)malloc(sizeof(scene_t));
    scene->screen = screen_new(screen_width, screen_height, r);
    scene->camera = camera_new(60.f, screen_width, screen_height);
    scene->camera->position = (vector3f_t){0, 0, 0};

    scene->quad = obj_parse("bin\\appl\\resources\\quad.obj");
    scene->suzanne = obj_parse("bin\\appl\\resources\\suzanne.obj");
    return scene;
}

static void draw_two_triangles(scene_t* s) {
        // World to Screen
    vector3f_t wp1 = {  0,  0, -10 }; //Top
    vector3f_t wp2 = { -4, -4, -10 }; //Left
    vector3f_t wp3 = { +4, -4, -10 }; //Right

    vector2i_t sp1 = camera_world_to_screen_point(s->camera, wp1);
    vector2i_t sp2 = camera_world_to_screen_point(s->camera, wp2);
    vector2i_t sp3 = camera_world_to_screen_point(s->camera, wp3);

    color_t green = {0, 255, 0, 255};
    bbox_triangle_raster(s->screen, sp1, sp2, sp3, green);

    vector3f_t t2_wp1 = {  2,  0, -15 }; //Top
    vector3f_t t2_wp2 = { -2, -4, -15 }; //Left
    vector3f_t t2_wp3 = { +6, -4, -15 }; //Right

    vector2i_t t2_sp1 = camera_world_to_screen_point(s->camera, t2_wp1);
    vector2i_t t2_sp2 = camera_world_to_screen_point(s->camera, t2_wp2);
    vector2i_t t2_sp3 = camera_world_to_screen_point(s->camera, t2_wp3);

    color_t red = {255, 0, 0, 255};
    bbox_triangle_raster(s->screen, t2_sp1, t2_sp2, t2_sp3, red);
}

static void draw_quad_obj(scene_t* scene) {

    obj_t* obj = scene->quad;

    for(size_t i=0; i < obj->triangle_count; ++i) { 
        /*
        obj_float3_t* f1 = &obj->triangles[i].v1.position;
        vector3f_t* v1 = (vector3f_t*)f1;
        vector3f_t wp1 = *v1;
        */ 

        vector3f_t wp1 = *(vector3f_t*)&(obj->triangles[i].v1.position);
        vector3f_t wp2 = *(vector3f_t*)&(obj->triangles[i].v2.position);
        vector3f_t wp3 = *(vector3f_t*)&(obj->triangles[i].v3.position);

        wp1.z -= 4;
        wp2.z -= 4;
        wp3.z -= 4;

        vector2i_t sp1 = camera_world_to_screen_point(scene->camera, wp1);
        vector2i_t sp2 = camera_world_to_screen_point(scene->camera, wp2);
        vector2i_t sp3 = camera_world_to_screen_point(scene->camera, wp3);

        color_t red = {255, 0, 0, 255};
        bbox_triangle_raster(scene->screen, sp1, sp2, sp3, red);
    }
}

static void draw_suzanne_obj(scene_t* scene, float delta_time, bool is_wireframe) {

    obj_t* obj = scene->suzanne;

    vector3f_t transl = (vector3f_t){0, 0, 5};
    
    static float rotation = 0.f;

    rotation += 2.f * delta_time;

    for(size_t i=0; i < obj->triangle_count; ++i) { 
        vector3f_t wp1 = *(vector3f_t*)&(obj->triangles[i].v1.position);
        vector3f_t wp2 = *(vector3f_t*)&(obj->triangles[i].v2.position);
        vector3f_t wp3 = *(vector3f_t*)&(obj->triangles[i].v3.position);

        wp1 = vector3f_mult(wp1, 2);
        wp2 = vector3f_mult(wp2, 2);
        wp3 = vector3f_mult(wp3, 2);

        wp1 = vector3f_rotate_y(wp1, rotation);
        wp2 = vector3f_rotate_y(wp2, rotation);
        wp3 = vector3f_rotate_y(wp3, rotation);
        
        wp1 = vector3f_sub(wp1, transl);
        wp2 = vector3f_sub(wp2, transl);
        wp3 = vector3f_sub(wp3, transl);
        
        vector2i_t sp1 = camera_world_to_screen_point(scene->camera, wp1);
        vector2i_t sp2 = camera_world_to_screen_point(scene->camera, wp2);
        vector2i_t sp3 = camera_world_to_screen_point(scene->camera, wp3);

        color_t red = {255, 0, 0, 255};

        if (is_wireframe) 
        {
            dda_line_raster(scene->screen, sp1.x, sp1.y, sp2.x, sp2.y, red);
            dda_line_raster(scene->screen, sp1.x, sp1.y, sp3.x, sp3.y, red);
            dda_line_raster(scene->screen, sp2.x, sp2.y, sp3.x, sp3.y, red);
        } 
        else 
        {
            bbox_triangle_raster(scene->screen, sp1, sp2, sp3, red);
        }
    }

}

static void draw_suzanne_obj_scanline(scene_t* scene, float delta_time) {

    obj_t* obj = scene->suzanne;

    vector3f_t transl = (vector3f_t){0, 0, 5};
    
    static float rotation = 0.f;

    rotation += 2.f * delta_time;

    for(size_t i=0; i < obj->triangle_count; ++i) { 
        vector3f_t wp1 = *(vector3f_t*)&(obj->triangles[i].v1.position);
        vector3f_t wp2 = *(vector3f_t*)&(obj->triangles[i].v2.position);
        vector3f_t wp3 = *(vector3f_t*)&(obj->triangles[i].v3.position);

        wp1 = vector3f_mult(wp1, 2);
        wp2 = vector3f_mult(wp2, 2);
        wp3 = vector3f_mult(wp3, 2);

        wp1 = vector3f_rotate_y(wp1, rotation);
        wp2 = vector3f_rotate_y(wp2, rotation);
        wp3 = vector3f_rotate_y(wp3, rotation);
        
        wp1 = vector3f_sub(wp1, transl);
        wp2 = vector3f_sub(wp2, transl);
        wp3 = vector3f_sub(wp3, transl);
        
        vector2i_t sp1 = camera_world_to_screen_point(scene->camera, wp1);
        vector2i_t sp2 = camera_world_to_screen_point(scene->camera, wp2);
        vector2i_t sp3 = camera_world_to_screen_point(scene->camera, wp3);

        color_t red = {255, 0, 0, 255};
        color_t green = {0, 255, 0, 255};
        color_t blue = {0, 0, 255, 255};

        vector3f_t cp1 = camera_world_to_camera_space(scene->camera, wp1);
        vector3f_t cp2 = camera_world_to_camera_space(scene->camera, wp2);
        vector3f_t cp3 = camera_world_to_camera_space(scene->camera, wp3);

        vertex_t v1;
        v1.screen_pos = &sp1;
        v1.color = &red;
        v1.z_pos = cp1.z;

        vertex_t v2;
        v2.screen_pos = &sp2;
        v2.color = &green;
        v2.z_pos = cp2.z;

        vertex_t v3;
        v3.screen_pos = &sp3;
        v3.color = &blue;
        v3.z_pos = cp3.z;
       
        scanline_raster(scene->screen, &v1, &v2, &v3);
    }

}

void scene_update(scene_t* s, float delta_time) {

    screen_clear(s->screen);

    //Directly drawing pixels
    /*
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

    vector2i_t p1 = {100, 400}; //left
    vector2i_t p2 = {200, 100}; //top
    vector2i_t p3 = {300, 400}; //right

    color_t green = {0, 255, 0, 255};
    bbox_triangle_raster(s->screen, p1, p2, p3, green);
    */

    //draw_quad_obj(s);
    //draw_suzanne_obj(s, delta_time, true);

    draw_suzanne_obj_scanline(s, delta_time);

    screen_blit(s->screen);
}

void scene_destroy(scene_t* s) {
    screen_free(s->screen);
    obj_parse_destroy(s->quad);
    obj_parse_destroy(s->suzanne);
    free(s);
}