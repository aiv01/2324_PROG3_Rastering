#ifndef OBJ_PARSER
#define OBJ_PARSER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int v_index;
    int vt_index;
    int vn_index;
} obj_vertex_info_t;

typedef struct 
{
    float x;
    float y;
    float z;
} obj_float3_t;

typedef struct 
{
    float x;
    float y;
} obj_float2_t;

typedef struct
{
    obj_float3_t position; // alias 'v'
    obj_float3_t normal;   // alias 'vn'
    obj_float2_t uv;       // alias 'vt'
} obj_vertex_t;

typedef struct
{
    obj_vertex_t v1;
    obj_vertex_t v2;
    obj_vertex_t v3;
} obj_triangle_t;

typedef struct 
{
    int v_count;
    int vt_count;
    int vn_count;
    int f_count;
    size_t triangle_count;
    obj_float3_t *v;
    obj_float2_t *vt;
    obj_float3_t *vn;
    obj_vertex_info_t *v_info;
    obj_triangle_t *triangles;

} obj_t;

obj_t *obj_parser(const char *file_name)
{
    obj_t *obj_parse = (obj_t *)malloc(sizeof(obj_t));
    obj_parse->v_count = 0;
    obj_parse->vt_count = 0;
    obj_parse->vn_count = 0;
    obj_parse->f_count = 0;

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
            obj_parse->v_count++;
        }

        if (strncmp(buffer, "vt ", 3) == 0)
        {
            obj_parse->vt_count++;
        }

        if (strncmp(buffer, "vn ", 3) == 0)
        {
            obj_parse->vn_count++;
        }

        if (strncmp(buffer, "f ", 2) == 0)
        {
            obj_parse->f_count++;
        }
    }

    obj_parse->v = (obj_float3_t *)malloc(obj_parse->v_count * sizeof(obj_float3_t));
    obj_parse->vt = (obj_float2_t *)malloc(obj_parse->vt_count * sizeof(obj_float2_t));
    obj_parse->vn = (obj_float3_t *)malloc(obj_parse->vn_count * sizeof(obj_float3_t));
    obj_parse->v_info = (obj_vertex_info_t *)malloc(obj_parse->f_count * sizeof(obj_vertex_info_t) * 3);

    rewind(file); // seeks file at start

    int v_index = 0;
    int vt_index = 0;
    int vn_index = 0;
    int f_index = 0;
    size_t triangle_count = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (strncmp(buffer, "v ", 2) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // v token

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parse->v[v_index].x = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parse->v[v_index].y = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parse->v[v_index].z = atof(token);

            v_index++;
        }

        if (strncmp(buffer, "vt ", 3) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // vt token

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parse->vt[vt_index].x = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parse->vt[vt_index].y = atof(token);

            vt_index++;
        }

        if (strncmp(buffer, "vn ", 3) == 0)
        {
            char *remaining_tokens;
            char *token;

            strtok_s(buffer, " ", &remaining_tokens); // vt token

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parse->vn[vn_index].x = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parse->vn[vn_index].y = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens);
            obj_parse->vn[vn_index].z = atof(token);

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

                obj_parse->v_info[f_index + i].v_index = atoi(token);

                token = strtok_s(NULL, "/", &remaining_tokens);
                obj_parse->v_info[f_index + i].vt_index = atoi(token);

                token = strtok_s(NULL, " ", &remaining_tokens);
                obj_parse->v_info[f_index + i].vn_index = atoi(token);
            }

            f_index += 3;
        }
    }

    fclose(file);

    // Set triangle count
    obj_parse->triangle_count = obj_parse->f_count;

    // Allocate triangles struct
    obj_parse->triangles = (obj_triangle_t *)malloc(sizeof(obj_triangle_t) * obj_parse->triangle_count);

    // Loop faces
    for (size_t i = 0; i < obj_parse->triangle_count; i++)
    {
        // Set current face index for v_info
        int f_index = i * 3;

        // Set indexes for vertex 1
        int index_v1 = obj_parse->v_info[f_index + 0].v_index - 1;
        int index_vt1 = obj_parse->v_info[f_index + 0].vt_index - 1;
        int index_vn1 = obj_parse->v_info[f_index + 0].vn_index - 1;

        // Set position info for vertex 1
        obj_parse->triangles[i].v1.position = obj_parse->v[index_v1];

        // Set uv info for vertex 1
        obj_parse->triangles[i].v1.uv = obj_parse->vt[index_vt1];

        // Set normals info for vertex 1
        obj_parse->triangles[i].v1.normal = obj_parse->vn[index_vn1];

        // Set indexes for vertex 2
        int index_v2 = obj_parse->v_info[f_index + 1].v_index - 1;
        int index_vt2 = obj_parse->v_info[f_index + 1].vt_index - 1;
        int index_vn2 = obj_parse->v_info[f_index + 1].vn_index - 1;

        // Set position info for vertex 2
        obj_parse->triangles[i].v2.position = obj_parse->v[index_v2];

        // Set uv info for vertex 2
        obj_parse->triangles[i].v2.uv = obj_parse->vt[index_vt2];

        // Set normals info for vertex 2
        obj_parse->triangles[i].v2.normal = obj_parse->vn[index_vn2];

        // Set indexes for vertex 3
        int index_v3 = obj_parse->v_info[f_index + 2].v_index - 1;
        int index_vt3 = obj_parse->v_info[f_index + 2].vt_index - 1;
        int index_vn3 = obj_parse->v_info[f_index + 2].vn_index - 1;

        // Set position info for vertex 3
        obj_parse->triangles[i].v3.position = obj_parse->v[index_v3];

        // Set uv info for vertex 3
        obj_parse->triangles[i].v3.uv = obj_parse->vt[index_vt3];

        // Set normals info for vertex 3
        obj_parse->triangles[i].v3.normal = obj_parse->vn[index_vn3];
    }

    return obj_parse;
}

void obj_parser_destroy(obj_t *obj_parse)
{
    free(obj_parse->v);
    free(obj_parse->vt);
    free(obj_parse->vn);
    free(obj_parse->v_info);
    free(obj_parse->triangles);
    free(obj_parse);
}

#endif // end define OBJ_PARSER