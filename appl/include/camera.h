#ifndef CAMERA_H
#define CAMERA_H
#include "vector.h"

typedef struct camera_t 
{
    vector3f_t position;
    float vertical_fov;
    int width;
    int height;
} camera_t;

camera_t* camera_new(float vertical_fov, int width, int height);

void camera_free(camera_t* camera);

vector2i_t camera_world_to_screen_point(camera_t* camera, vector3f_t wp);

#endif //CAMERA_H