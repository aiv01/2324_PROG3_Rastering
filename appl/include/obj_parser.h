#ifndef OBJ_PARSER
#define OBJ_PARSER

#define POSITION_LABEL "v "
#define POSITION_LABEL_CHAR_AMOUNT 2
#define NORMAL_LABEL "vn "
#define NORMAL_LABEL_CHAR_AMOUNT 3
#define UV_LABEL "vt "
#define UV_LABEL_CHAR_AMOUNT 3
#define FACE_LABEL "f "
#define FACE_LABEL_CHAR_AMOUNT 2
#define INFO_PER_FACE_AMOUNT 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Structure to represent a 3D floating-point vector
typedef struct obj_float3_t
{
    float x;
    float y;
    float z;
} obj_float3_t;

/// @brief Structure to represent a 2D floating-point vector
typedef struct obj_float2_t
{
    float x;
    float y;
} obj_float2_t;

/// @brief Structure to represent a vertex with position, normal, and texture coordinates
typedef struct obj_vertex_t
{
  obj_float3_t position;
  obj_float3_t normal;
  obj_float2_t uv;
} obj_vertex_t;

/// @brief Structure to represent a triangle composed of three vertices
typedef struct obj_triangle_t
{
  obj_vertex_t v1;
  obj_vertex_t v2;
  obj_vertex_t v3;
} obj_triangle_t;

/// @brief Structure to hold dynamic arrays of position, normal, texture coordinates, and vertex information
typedef struct obj_info_t
{
    obj_float3_t* position_dynamic_array;
    size_t position_amount;
    obj_float3_t* normal_dynamic_array;
    size_t normal_amount;
    obj_float2_t* uv_dynamic_array;
    size_t uv_amount;
    obj_vertex_t* vertex_dynamic_array;
    size_t vertex_amount;
} obj_info_t;

/// @brief Structure to hold dynamic arrays of triangles
typedef struct obj_t
{
    obj_triangle_t* triangle_dynamic_array;
    size_t triangle_amount;
} obj_t;

/// @brief Function to open an OBJ file for reading
/// @param file_name Complete path of the file to read
/// @return A pointer to the file
FILE* obj_file_open(const char* file_name)
{
    FILE* file;
    if(fopen_s(&file, file_name, "r"))
    {
        return NULL;
    }

    return file;
}

/// @brief Function to close an open file
/// @param file The file to be closed
void obj_file_close(FILE* file)
{
    fclose(file);
}

/// @brief Function to add a position to the dynamic array
/// @param obj_info Structure containig all the obj info
/// @param position Strcture containig the x, y, z component of the position to be added
/// @return An error number, 0 if everything have been completed succesfully
int obj_add_position(obj_info_t* obj_info, const obj_float3_t position)
{
    obj_info->position_dynamic_array = (obj_float3_t*)realloc(obj_info->position_dynamic_array, (obj_info->position_amount + 1) * sizeof(obj_float3_t));
    if(!obj_info->position_dynamic_array)
    {
        return 1;
    }

    obj_info->position_dynamic_array[obj_info->position_amount] = position;
    obj_info->position_amount++;

    return 0;
}

/// @brief Function to add a UV coordinate to the dynamic array
/// @param obj_info Structure containig all the obj info
/// @param uv Strcture containig the x, y component of the uv to be added
/// @return An error number, 0 if everything have been completed succesfully
int obj_add_uv(obj_info_t* obj_info, const obj_float2_t uv)
{
    obj_info->uv_dynamic_array = (obj_float2_t*)realloc(obj_info->uv_dynamic_array, (obj_info->uv_amount + 1) * sizeof(obj_float2_t));
    if(!obj_info->uv_dynamic_array)
    {
        return 1;
    }

    obj_info->uv_dynamic_array[obj_info->uv_amount] = uv;
    obj_info->uv_amount++;

    return 0;
}

/// @brief Function to add a normal to the dynamic array
/// @param obj_info Structure containig all the obj info
/// @param normal Strcture containig the x, y, z component of the normal to be added
/// @return An error number, 0 if everything have been completed succesfully
int obj_add_normal(obj_info_t* obj_info, const obj_float3_t normal)
{
    obj_info->normal_dynamic_array = (obj_float3_t*)realloc(obj_info->normal_dynamic_array, (obj_info->normal_amount + 1) * sizeof(obj_float3_t));
    if(!obj_info->normal_dynamic_array)
    {
        return 1;
    }

    obj_info->normal_dynamic_array[obj_info->normal_amount] = normal;
    obj_info->normal_amount++;

    return 0;
}

/// @brief Function to add a vertex to the dynamic array
/// @param obj_info Structure containig all the obj info
/// @param vertex Structure to represent a vertex with position, normal, and texture coordinates to be added
/// @return An error number, 0 if everything have been completed succesfully
int obj_add_vertex(obj_info_t* obj_info, const obj_vertex_t vertex)
{
    obj_info->vertex_dynamic_array = (obj_vertex_t*)realloc(obj_info->vertex_dynamic_array, (obj_info->vertex_amount + 1) * sizeof(obj_vertex_t));
    if(!obj_info->vertex_dynamic_array)
    {
        return 1;
    }

    obj_info->vertex_dynamic_array[obj_info->vertex_amount] = vertex;
    obj_info->vertex_amount++;

    return 0;
}

/// @brief Function to save position information from a buffer into the obj_info structure
/// @param obj_info Structure containig all the obj info
/// @param buffer A buffer containing chars representing the obj file
/// @return An error number, 0 if everything have been completed succesfully
int obj_save_position_info(obj_info_t* obj_info, char* buffer)
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

    return obj_add_position(obj_info, position);
}

/// @brief Function to save uv information from a buffer into the obj_info structure
/// @param obj_info Structure containig all the obj info
/// @param buffer A buffer containing chars representing the obj file
/// @return An error number, 0 if everything have been completed succesfully
int obj_save_uv_info(obj_info_t* obj_info, char* buffer)
{
    char* remaining_tokens;
    char* token;
    obj_float2_t uv;

    strtok_s(buffer, " ", &remaining_tokens); //vt token

    token = strtok_s(NULL, " ", &remaining_tokens);
    uv.x = atof(token);

    token = strtok_s(NULL, " ", &remaining_tokens);
    uv.y = atof(token);

    return obj_add_uv(obj_info, uv);
}

/// @brief Function to save normal information from a buffer into the obj_info structure
/// @param obj_info Structure containig all the obj info
/// @param buffer A buffer containing chars representing the obj file
/// @return An error number, 0 if everything have been completed succesfully
int obj_save_normal_info(obj_info_t* obj_info, char* buffer)
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

    return obj_add_normal(obj_info, normal);
}

/// @brief Function to save vertex information from a buffer into the obj_info structure
/// @param obj_info Structure containig all the obj info
/// @param buffer A buffer containing chars representing the obj file
/// @return An error number, 0 if everything have been completed succesfully
int obj_save_vertex_info(obj_info_t* obj_info, char* buffer)
{
    char *remaining_tokens;
    char *token;

    strtok_s(buffer, " ", &remaining_tokens); //f token

    for (int i = 0; i < INFO_PER_FACE_AMOUNT; i++)
    {
        obj_vertex_t vertex;

        token = strtok_s(NULL, "/", &remaining_tokens);
        vertex.position = obj_info->position_dynamic_array[atoi(token) - 1];

        token = strtok_s(NULL, "/", &remaining_tokens);
        vertex.uv = obj_info->uv_dynamic_array[atoi(token) - 1];

        token = strtok_s(NULL, " ", &remaining_tokens);
        vertex.normal = obj_info->normal_dynamic_array[atoi(token) - 1];

        if(obj_add_vertex(obj_info, vertex))
        {
            return 1;
        }
    }

    return 0;
}

/// @brief Function to create a new obj_info and initialize its members
/// @return A pointer to the obj_info structure
obj_info_t* obj_info_new()
{
    obj_info_t* obj_info = (obj_info_t*)malloc(sizeof(obj_info_t));

    if(!obj_info)
    {
        return NULL;
    }

    obj_info->position_dynamic_array = NULL;
    obj_info->position_amount = 0;
    obj_info->normal_dynamic_array = NULL;
    obj_info->normal_amount = 0;
    obj_info->uv_dynamic_array = NULL;
    obj_info->uv_amount = 0;
    obj_info->vertex_dynamic_array = NULL;
    obj_info->vertex_amount = 0;

    return obj_info;
}

/// @brief Function to free the memory allocated for an obj_info
/// @param obj_info The obj_info structure to free
void obj_info_free(obj_info_t* obj_info)
{
    free(obj_info->position_dynamic_array);
    free(obj_info->normal_dynamic_array);
    free(obj_info->uv_dynamic_array);
    free(obj_info->vertex_dynamic_array);

    free(obj_info);
}

/// @brief Function to create a new obj and initialize its members
/// @return A pointer to the obj structure
obj_t* obj_new()
{
    obj_t* obj = (obj_t*)malloc(sizeof(obj_t));
    if(!obj)
    {
        return NULL;
    }

    obj->triangle_dynamic_array = NULL;
    obj->triangle_amount = 0;

    return obj;
}

/// @brief Function to free the memory allocated for an obj
/// @param obj The obj structure to free
void obj_free(obj_t* obj)
{
    free(obj->triangle_dynamic_array);

    free(obj);
}

/// @brief Function to parse an OBJ file and populate an obj structure with triangle data
/// @param file_name Complete path of the file to read
/// @return A pointer to the obj structure
obj_t* obj_parse(const char* file_name)
{
    FILE* file = obj_file_open(file_name);
    if(!file)
    {
        fprintf(stderr, "Error: Trying to open the file %s!\n", file_name);
        return NULL;
    }

    obj_info_t* obj_info = obj_info_new();
    if(!obj_info)
    {
        fprintf(stderr, "Error: Trying to allocate memory for obj_info!\n");
        obj_file_close(file);
        return NULL;
    }

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), file))
    {
        if(!strncmp(buffer, POSITION_LABEL, POSITION_LABEL_CHAR_AMOUNT))
        {
            if(obj_save_position_info(obj_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save position inside obj_info!\n");
                obj_file_close(file);
                obj_info_free(obj_info);
                return NULL;
            }
        }

        if(!strncmp(buffer, UV_LABEL, UV_LABEL_CHAR_AMOUNT))
        {
            if(obj_save_uv_info(obj_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save uv inside obj_info!\n");
                obj_file_close(file);
                obj_info_free(obj_info);
                return NULL;
            }
        }

        if(!strncmp(buffer, NORMAL_LABEL, NORMAL_LABEL_CHAR_AMOUNT))
        {
            if(obj_save_normal_info(obj_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save normal inside obj_info!\n");
                obj_file_close(file);
                obj_info_free(obj_info);
                return NULL;
            }
        }

        if(!strncmp(buffer, FACE_LABEL, FACE_LABEL_CHAR_AMOUNT))
        {
            if(obj_save_vertex_info(obj_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save vertex inside obj_info!\n");
                obj_info_free(obj_info);
                return NULL;
            }
        }
    }

    obj_file_close(file);

    obj_t* obj = obj_new();
    if(!obj)
    {
        fprintf(stderr, "Error: Trying to allocate memory for obj!\n");
        obj_info_free(obj_info);
        return NULL;
    }

    

    return obj;
}

#endif //OBJ_PARSER