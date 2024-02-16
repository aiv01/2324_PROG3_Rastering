#include "vector.h"
#include <math.h>
#include "common.h"

vector3f_t vector3f_sub(vector3f_t v1, vector3f_t v2)
{
    vector3f_t r;
    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    r.z = v1.z - v2.z;
    return r;
}

/*
  x2 = cosA*x1 - sinA*y1
  y2 = sinA*x1 + cosA*y1
*/
vector3f_t vector3f_rotate_y(vector3f_t v1, float angle_degrees) 
{
    float rads = angle_degrees * M_PI / 180.f;

    vector3f_t r;
    r.x = cosf(rads) * v1.x - sinf(rads) * v1.z;
    r.y = v1.y;
    r.z = sinf(rads) * v1.x + cosf(rads) * v1.z;
    return r;
}

vector3f_t vector3f_mult(vector3f_t v1, float scalar) 
{
    vector3f_t r;
    r.x = v1.x * scalar;
    r.y = v1.y * scalar;
    r.z = v1.z * scalar;
    return r;
}