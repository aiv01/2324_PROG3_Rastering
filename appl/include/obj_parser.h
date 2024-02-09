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

typedef struct obj_t
{
    int v_count;
    int vt_count;
    int vn_count;
    int f_count;
    obj_float3_t *v;
    obj_float2_t *vt;
    obj_float3_t *vn;
    obj_vertex_info_t *v_info;

} obj_t;

obj_t *obj_parse(const char *file_name)
{

    obj_t *obj = (obj_t *)malloc(sizeof(obj_t));
    obj->v_count = 0;
    obj->vt_count = 0;
    obj->vn_count = 0;
    obj->f_count = 0;

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
            obj->v_count++;
        }

        if (strncmp(buffer, "vt ", 3) == 0)
        {
            obj->vt_count++;
        }

        if (strncmp(buffer, "vn ", 3) == 0)
        {
            obj->vn_count++;
        }

        if (strncmp(buffer, "f ", 2) == 0)
        {
            obj->f_count++;
        }
    }

    obj->v = (obj_float3_t *)malloc(obj->v_count * sizeof(obj_float3_t));
    obj->vt = (obj_float2_t *)malloc(obj->vt_count * sizeof(obj_float2_t));
    obj->vn = (obj_float3_t *)malloc(obj->vn_count * sizeof(obj_float3_t));
    obj->v_info = (obj_vertex_info_t *)malloc(obj->f_count * sizeof(obj_vertex_info_t) * 3);

    rewind(file); // seeks file at start

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
            obj->v[v_index].x = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj->v[v_index].y = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj->v[v_index].z = atof(token);

            v_index++;
        }

        if (strncmp(buffer, "vt ", 3) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // vt token

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj->vt[vt_index].x = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj->vt[vt_index].y = atof(token);

            vt_index++;
        }

        if (strncmp(buffer, "vn ", 3) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // vt token

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj->vn[vn_index].x = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj->vn[vn_index].y = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj->vn[vn_index].z = atof(token);

            vn_index++;
        }

        if (strncmp(buffer, "f ", 2) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // f token

            for (int i = 0; i < 3; i++)
            {
                token = strtok_s(NULL, "/", &remaining_tokens);

                obj->v_info[f_index + i].v_index = atoi(token);

                token = strtok_s(NULL, "/", &remaining_tokens);
                obj->v_info[f_index + i].vt_index = atoi(token);

                token = strtok_s(NULL, " ", &remaining_tokens);
                obj->v_info[f_index + i].vn_index = atoi(token);
            }

            f_index += 3;
        }
    }

    fclose(file);

    return obj;
}

#endif // end define OBJ_PARSER