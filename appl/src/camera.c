#include "camera.h"
#include <stdlib.h>
#include <math.h>

#define M_PI 3.141592

camera_t* camera_new(float vertical_fov, int width, int height)
{
    camera_t* camera = (camera_t*)malloc(sizeof(camera_t));
    camera->position = (vector3f_t){0, 0, 0};
    camera->vertical_fov = vertical_fov;
    camera->width = width;
    camera->height = height;
    return camera;
}

void camera_free(camera_t* camera)
{
    free(camera);
}

vector2i_t camera_world_to_screen_point(camera_t* camera, vector3f_t wp)
{
    vector3f_t camera_point = vector3f_sub(wp, camera->position);
    
    float plane_x = camera_point.x / -camera_point.z;
    float plane_y = camera_point.y / -camera_point.z;

    float half_fov = camera->vertical_fov * 0.5f;
    float half_fov_rads = half_fov * M_PI / 180.f;
    float tan_fov = tanf(half_fov_rads);

    plane_x /= tan_fov;
    plane_y /= tan_fov;

    float aspect = (float)camera->width / (float)camera->height;
    plane_x /= aspect;

    int screen_x = (plane_x + 1.f) * 0.5f * (float)camera->width;
    int screen_y = (1.f - (plane_y + 1.f) * 0.5f) * (float)camera->height;

    return (vector2i_t){screen_x, screen_y};
}