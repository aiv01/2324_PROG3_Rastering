#ifndef OBJ_PARSER
#define OBJ_PARSER

#define POSITION_LABEL "v "
#define NORMAL_LABEL "vn "
#define UV_LABEL "vt "
#define FACE_LABEL "f "

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

typedef struct obj_info_t
{
    obj_float3_t* position_dynamic_array;
    size_t position_amount;
    obj_float3_t* normal_dynamic_array;
    size_t normal_amount;
    obj_float2_t* uv_dynamic_array;
    size_t uv_amount;
} obj_info_t;

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
    obj_float3_t* v;
    obj_float2_t* vt;
    obj_float3_t* vn;
    obj_vertex_t* vertex_dynamic_array;
    size_t vertex_amount;
    obj_vertex_info_t* v_info;
    obj_triangle_t* triangle_dynamic_array;
    size_t triangle_amount;
} obj_t;

int obj_add_uv(obj_info_t* all_vertex_info, const obj_float2_t uv)
{
    all_vertex_info->uv_dynamic_array = (obj_float2_t*)realloc(all_vertex_info->uv_dynamic_array, (all_vertex_info->uv_amount + 1) * sizeof(obj_float2_t));
    if(!all_vertex_info->uv_dynamic_array)
    {
        return 1;
    }

    all_vertex_info->uv_dynamic_array[all_vertex_info->uv_amount] = uv;
    all_vertex_info->uv_amount++;

    return 0;
}

int obj_add_normal(obj_info_t* all_vertex_info, const obj_float3_t normal)
{
    all_vertex_info->normal_dynamic_array = (obj_float3_t*)realloc(all_vertex_info->normal_dynamic_array, (all_vertex_info->normal_amount + 1) * sizeof(obj_float3_t));
    if(!all_vertex_info->normal_dynamic_array)
    {
        return 1;
    }

    all_vertex_info->normal_dynamic_array[all_vertex_info->normal_amount] = normal;
    all_vertex_info->normal_amount++;

    return 0;
}

int obj_add_position(obj_info_t* all_vertex_info, const obj_float3_t position)
{
    all_vertex_info->position_dynamic_array = (obj_float3_t*)realloc(all_vertex_info->position_dynamic_array, (all_vertex_info->position_amount + 1) * sizeof(obj_float3_t));
    if(!all_vertex_info->position_dynamic_array)
    {
        return 1;
    }

    all_vertex_info->position_dynamic_array[all_vertex_info->position_amount] = position;
    all_vertex_info->position_amount++;

    return 0;
}

int obj_save_position_info(obj_info_t* all_vertex_info, char* buffer)
{
    char* remaining_tokens;
    char* token;
    obj_float3_t position;

    strtok_s(buffer, " ", &remaining_tokens); //v token

    token = strtok_s(NULL, " ", &remaining_tokens);
    position.x = atof(token);

    token = strtok_s(NULL, " ", &remaining_tokens);
    position.y = atof(token);

    token = strtok_s(NULL, " ", &remaining_tokens);
    position.z = atof(token);

    return obj_add_position(all_vertex_info, position);
}

int obj_save_normal_info(obj_info_t* all_vertex_info, char* buffer)
{
    char* remaining_tokens;
    char* token;
    obj_float3_t normal;

    strtok_s(buffer, " ", &remaining_tokens); //vn token

    token = strtok_s(NULL, " ", &remaining_tokens);
    normal.x = atof(token);

    token = strtok_s(NULL, " ", &remaining_tokens);
    normal.y = atof(token);

    token = strtok_s(NULL, " ", &remaining_tokens);
    normal.z = atof(token);

    return obj_add_normal(all_vertex_info, normal);
}

int obj_save_uv_info(obj_info_t* all_vertex_info, char* buffer)
{
    char* remaining_tokens;
    char* token;
    obj_float2_t uv;

    strtok_s(buffer, " ", &remaining_tokens); //vt token

    token = strtok_s(NULL, " ", &remaining_tokens);
    uv.x = atof(token);

    token = strtok_s(NULL, " ", &remaining_tokens);
    uv.y = atof(token);

    return obj_add_uv(all_vertex_info, uv);
}

obj_info_t* obj_all_vertex_info_new()
{
    obj_info_t* all_vertex_info = (obj_info_t*)malloc(sizeof(obj_info_t));

    if(!all_vertex_info)
    {
        return NULL;
    }

    all_vertex_info->position_dynamic_array = NULL;
    all_vertex_info->position_amount = 0;
    all_vertex_info->normal_dynamic_array = NULL;
    all_vertex_info->normal_amount = 0;
    all_vertex_info->uv_dynamic_array = NULL;
    all_vertex_info->uv_amount = 0;

    return all_vertex_info;
}

void obj_all_vertex_info_free(obj_info_t* all_vertex_info)
{
    free(all_vertex_info->position_dynamic_array);
    free(all_vertex_info->normal_dynamic_array);
    free(all_vertex_info->uv_dynamic_array);

    free(all_vertex_info);
}

FILE* obj_file_open(const char* file_name)
{
    FILE* file;
    if(fopen_s(&file, file_name, "r"))
    {
        return NULL;
    }

    return file;
}

void obj_file_close(FILE* file)
{
    fclose(file);
}

int obj_add_vertex(obj_t* obj, const obj_vertex_t vertex)
{
    obj->vertex_dynamic_array = (obj_vertex_t*)realloc(obj->vertex_dynamic_array, (obj->vertex_amount + 1) * sizeof(obj_vertex_t));
    if(!obj->vertex_dynamic_array)
    {
        return 1;
    }

    obj->vertex_dynamic_array[obj->vertex_amount] = vertex;
    obj->vertex_amount++;

    return 0;
}

obj_t* obj_new()
{
    obj_t* obj = (obj_t*)malloc(sizeof(obj_t));
    if(!obj)
    {
        return NULL;
    }

    obj->vertex_dynamic_array = NULL;
    obj->vertex_amount = 0;
    obj->triangle_dynamic_array = NULL;
    obj->triangle_amount = 0;

    return obj;
}

void obj_free(obj_t* obj)
{
    free(obj->vertex_dynamic_array);
    free(obj->triangle_dynamic_array);

    free(obj);
}

obj_t* obj_parse(const char* file_name)
{
    obj_t* obj = obj_new(); //DEBUG

    FILE* file = obj_file_open(file_name);
    if(!file)
    {
        fprintf(stderr, "Error: Trying to open the file %s!\n", file_name);
        return NULL;
    }

    obj_info_t* all_vertex_info = obj_all_vertex_info_new();
    if(!all_vertex_info)
    {
        fprintf(stderr, "Error: Trying to allocate memory for all_vertex_info!\n");
        obj_file_close(file);
        return NULL;
    }

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), file))
    {
        if(strncmp(buffer, POSITION_LABEL, 2) == 0)
        {
            if(obj_save_position_info(all_vertex_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save position inside all_vertex_info!\n");
                obj_file_close(file);
                obj_all_vertex_info_free(all_vertex_info);
                return NULL;
            }
        }

        if(strncmp(buffer, UV_LABEL, 3) == 0)
        {
            if(obj_save_uv_info(all_vertex_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save uv inside all_vertex_info!\n");
                obj_file_close(file);
                obj_all_vertex_info_free(all_vertex_info);
                return NULL;
            }
        }

        if(strncmp(buffer, NORMAL_LABEL, 3) == 0)
        {
            if(obj_save_normal_info(all_vertex_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save normal inside all_vertex_info!\n");
                obj_file_close(file);
                obj_all_vertex_info_free(all_vertex_info);
                return NULL;
            }
        }

        if(strncmp(buffer, FACE_LABEL, 2) == 0)
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

#endif //OBJ_PARSER