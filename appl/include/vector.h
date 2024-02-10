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

#endif //VECTOR_H