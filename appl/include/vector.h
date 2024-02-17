#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector2i_t 
{
    int x;
    int y;
} vector2i_t;

typedef struct vector3f_t 
{
    float x;
    float y;
    float z;
} vector3f_t;

vector3f_t vector3f_sub(vector3f_t v1, vector3f_t v2);

vector3f_t vector3f_rotate_y(vector3f_t v1, float angle_degrees);

vector3f_t vector3f_mult(vector3f_t v1, float scalar);

#endif //VECTOR_H