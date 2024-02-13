#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRIANGLE_VERTECES 3

typedef struct obj_float3_t
{
    float x;
    float y;
    float z;
}obj_float3_t;

typedef struct obj_float2_t
{
    float x;
    float y;
}obj_float2_t;

typedef struct obj_vertex_info_t
{
    int v_index;
    int vt_index;
    int vn_index;
}obj_vertex_info_t;

typedef struct obj_vertex_t
{
    obj_float3_t position; // alias 'v'
    obj_float3_t normal;   // alias 'vn'
    obj_float2_t uv;       // alias 'vt'
} obj_vertex_t;

typedef struct obj_triangle_t
{
    obj_vertex_t v1;
    obj_vertex_t v2;
    obj_vertex_t v3;
} obj_triangle_t;

typedef struct obj_t
{
    int v_count;
    int vt_count;
    int vn_count;
    int f_count;
    size_t triangle_count;
    obj_float3_t* v;
    obj_float2_t* vt;
    obj_float3_t* vn; 
    obj_vertex_info_t* v_info;
    obj_triangle_t* triangles;
}obj_t;

obj_t* ObjParse(const char* file_name);
#endif //OBJ_PARSER_H
