#ifndef OBJ_PARSER
#define OBJ_PARSER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct obj_vertex_info_t
{
    int v_index;
    int vt_index;
    int vn_index;
} obj_vertex_info_t;

typedef struct obj_float3_t
{
    float x;
    float y;
    float z;
} obj_float3_t;

typedef struct obj_float2_t
{
    float x;
    float y;
} obj_float2_t;

typedef struct obj_parsed_t
{
    int v_count;
    int vt_count;
    int vn_count;
    int f_count;
    obj_float3_t *v;
    obj_float2_t *vt;
    obj_float3_t *vn;
    obj_vertex_info_t *v_info;
} obj_parsed_t;

typedef struct obj_vertex_t
{
    obj_float3_t position;
    obj_float2_t uv;      
    obj_float3_t normal;  
} obj_vertex_t;

typedef struct obj_triangle_t{
    obj_vertex_t v1;
    obj_vertex_t v2;
    obj_vertex_t v3;
} obj_triangle_t;

typedef struct obj_t
{
    obj_parsed_t* parsed_obj;
    obj_triangle_t* triangles;
    size_t triangle_count;
} obj_t;

#ifndef OBJ_IMPLEMENTATION
obj_t *obj_create(obj_parsed_t* obj_parsed);
obj_parsed_t *obj_parse(const char *file_name);
int obj_free(obj_t* obj);
#else
obj_parsed_t *obj_parse(const char *file_name)
{
    obj_parsed_t *obj_parsed = (obj_parsed_t *)malloc(sizeof(obj_parsed_t));
    obj_parsed->v_count = 0;
    obj_parsed->vt_count = 0;
    obj_parsed->vn_count = 0;
    obj_parsed->f_count = 0;

    FILE *file;
    fopen_s(&file, file_name, "r");

    if (file == NULL)
    {
        printf("ERROR READ FILE: %s\n", file_name);
        return NULL;
    }

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strncmp(buffer, "v ", 2) == 0)
        {
            obj_parsed->v_count++;
        }

        else if (strncmp(buffer, "vt ", 3) == 0)
        {
            obj_parsed->vt_count++;
        }

        else if (strncmp(buffer, "vn ", 3) == 0)
        {
            obj_parsed->vn_count++;
        }

        else if (strncmp(buffer, "f ", 2) == 0)
        {
            obj_parsed->f_count++;
        }
    }

    obj_parsed->v = (obj_float3_t *)malloc(obj_parsed->v_count * sizeof(obj_float3_t));
    obj_parsed->vt = (obj_float2_t *)malloc(obj_parsed->vt_count * sizeof(obj_float2_t));
    obj_parsed->vn = (obj_float3_t *)malloc(obj_parsed->vn_count * sizeof(obj_float3_t));
    obj_parsed->v_info = (obj_vertex_info_t *)malloc(obj_parsed->f_count * sizeof(obj_vertex_info_t) * 3);

    fseek(file,0,0);

    int v_index = 0;
    int vt_index = 0;
    int vn_index = 0;
    int f_index = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strncmp(buffer, "v ", 2) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // v token

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parsed->v[v_index].x = strtof(token,NULL);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parsed->v[v_index].y = strtof(token,NULL);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parsed->v[v_index].z = strtof(token,NULL);

            v_index++;
        }

        else if (strncmp(buffer, "vt ", 3) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // vt token

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parsed->vt[vt_index].x = strtof(token,NULL);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parsed->vt[vt_index].y = strtof(token,NULL);

            vt_index++;
        }

        else if (strncmp(buffer, "vn ", 3) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // vt token

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parsed->vn[vn_index].x = strtof(token,NULL);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parsed->vn[vn_index].y = strtof(token,NULL);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parsed->vn[vn_index].z = strtof(token,NULL);

            vn_index++;
        }

        else if (strncmp(buffer, "f ", 2) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // f token

            for (int i = 0; i < 3; i++)
            {
                token = strtok_s(NULL, "/", &remaining_tokens);
                obj_parsed->v_info[f_index + i].v_index = strtol(token,NULL,10); // x

                token = strtok_s(NULL, "/", &remaining_tokens);
                obj_parsed->v_info[f_index + i].vt_index = strtol(token,NULL,10); // y

                token = strtok_s(NULL, " ", &remaining_tokens);
                obj_parsed->v_info[f_index + i].vn_index = strtol(token,NULL,10); // z
            }

            f_index += 3;
        }
    }

    fclose(file);

    return obj_parsed;
}

obj_t *obj_create(obj_parsed_t* obj_parsed)
{
    if(!obj_parsed) return NULL;

    obj_t *obj = (obj_t*)malloc(sizeof(obj_t));

    obj->triangle_count = obj_parsed->f_count;
    obj->triangles = (obj_triangle_t*)malloc(sizeof(obj_triangle_t)*obj->triangle_count);
    obj->parsed_obj = obj_parsed;

    obj_vertex_info_t v_info;

    for (size_t i = 0; i < obj->triangle_count; i++)
    {
        v_info = obj_parsed->v_info[i*3]; //vertex 1
        obj->triangles[i].v1.position = obj_parsed->v[v_info.v_index-1];
        obj->triangles[i].v1.uv = obj_parsed->vt[v_info.vt_index-1];
        obj->triangles[i].v1.normal = obj_parsed->vn[v_info.vn_index-1];

        v_info = obj_parsed->v_info[i*3+1]; //vertex 2
        obj->triangles[i].v2.position = obj_parsed->v[v_info.v_index-1];
        obj->triangles[i].v2.uv = obj_parsed->vt[v_info.vt_index-1];
        obj->triangles[i].v2.normal = obj_parsed->vn[v_info.vn_index-1];

        v_info = obj_parsed->v_info[i*3+2]; //vertex 3
        obj->triangles[i].v3.position = obj_parsed->v[v_info.v_index-1];
        obj->triangles[i].v3.uv = obj_parsed->vt[v_info.vt_index-1];
        obj->triangles[i].v3.normal = obj_parsed->vn[v_info.vn_index-1];
    }    

    return obj;
}

int obj_free(obj_t* obj)
{
    free(obj->parsed_obj->v);
    free(obj->parsed_obj->vn);
    free(obj->parsed_obj->vt);
    free(obj->parsed_obj->v_info);
    free(obj->parsed_obj);
    free(obj->triangles);
    free(obj);

    return 0;
}
#endif // OBJ_IMPLEMENTATION 

#endif // end define OBJ_PARSER