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
#define INFO_PER_TRIANGLE_AMOUNT 3
#define VERTEX_PER_TRIANGLE 3
#define STARTING_DYNAMIC_ARRAY_CAPACITY 10

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
    size_t position_dynamic_array_capacity;
    obj_float3_t* normal_dynamic_array;
    size_t normal_amount;
    size_t normal_dynamic_array_capacity;
    obj_float2_t* uv_dynamic_array;
    size_t uv_amount;
    size_t uv_dynamic_array_capacity;
    obj_vertex_t* vertex_dynamic_array;
    size_t vertex_amount;
    size_t vertex_dynamic_array_capacity;
} obj_info_t;

/// @brief Structure to hold dynamic arrays of triangles
typedef struct obj_t
{
    obj_triangle_t* triangles;
    size_t triangle_amount;
    size_t triangles_capacity;
    size_t vertex_amount;
    size_t position_amount;
    size_t uv_amount;
    size_t normal_amount;
} obj_t;

/// @brief Function to open an OBJ file for reading
/// @param file_name Complete path of the file to read
/// @return A pointer to the file
FILE* __obj_file_open(const char* file_name)
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
void __obj_file_close(FILE* file)
{
    fclose(file);
}

/// @brief Function to add a position to the dynamic array
/// @param obj_info Structure containig all the obj info
/// @param position Strcture containig the x, y, z component of the position to be added
/// @return An error number, 0 if everything have been completed succesfully
int __obj_add_position(obj_info_t* obj_info, const obj_float3_t position)
{
    if(obj_info->position_amount != 0)
    {
        if(obj_info->position_amount >= obj_info->position_dynamic_array_capacity)
        {
            obj_info->position_dynamic_array_capacity *= STARTING_DYNAMIC_ARRAY_CAPACITY;
            obj_info->position_dynamic_array = (obj_float3_t*)realloc(obj_info->position_dynamic_array, (obj_info->position_dynamic_array_capacity) * sizeof(obj_float3_t));
        }
    }
    else
    {
        obj_info->position_dynamic_array = (obj_float3_t*)calloc(STARTING_DYNAMIC_ARRAY_CAPACITY, sizeof(obj_float3_t));
    }

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
int __obj_add_uv(obj_info_t* obj_info, const obj_float2_t uv)
{
    if(obj_info->uv_amount != 0)
    {
        if(obj_info->uv_amount > obj_info->uv_dynamic_array_capacity)
        {
            obj_info->uv_dynamic_array_capacity *= STARTING_DYNAMIC_ARRAY_CAPACITY;
            obj_info->uv_dynamic_array = (obj_float2_t*)realloc(obj_info->uv_dynamic_array, (obj_info->uv_dynamic_array_capacity) * sizeof(obj_float2_t));
        }
    }
    else
    {
        obj_info->uv_dynamic_array = (obj_float2_t*)calloc(STARTING_DYNAMIC_ARRAY_CAPACITY, sizeof(obj_float2_t));
    }

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
int __obj_add_normal(obj_info_t* obj_info, const obj_float3_t normal)
{
    if(obj_info->normal_amount != 0)
    {
        if(obj_info->normal_amount >= obj_info->normal_dynamic_array_capacity)
        {
            obj_info->normal_dynamic_array_capacity *= STARTING_DYNAMIC_ARRAY_CAPACITY;
            obj_info->normal_dynamic_array = (obj_float3_t*)realloc(obj_info->normal_dynamic_array, (obj_info->normal_dynamic_array_capacity) * sizeof(obj_float3_t));
        }
    }
    else
    {
        obj_info->normal_dynamic_array = (obj_float3_t*)calloc(STARTING_DYNAMIC_ARRAY_CAPACITY, sizeof(obj_float3_t));
    }

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
int __obj_add_vertex(obj_info_t* obj_info, const obj_vertex_t vertex)
{
    if(obj_info->vertex_amount != 0)
    {
        if(obj_info->vertex_amount >= obj_info->vertex_dynamic_array_capacity)
        {
            obj_info->vertex_dynamic_array_capacity *= STARTING_DYNAMIC_ARRAY_CAPACITY;
            obj_info->vertex_dynamic_array = (obj_vertex_t*)realloc(obj_info->vertex_dynamic_array, (obj_info->vertex_dynamic_array_capacity) * sizeof(obj_vertex_t));
        }
    }
    else
    {
        obj_info->vertex_dynamic_array = (obj_vertex_t*)calloc(STARTING_DYNAMIC_ARRAY_CAPACITY, sizeof(obj_vertex_t));
    }
    
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
int __obj_save_position_info(obj_info_t* obj_info, char* buffer)
{
    char* remaining_tokens;
    char* token;
    obj_float3_t position;

    strtok_s(buffer, " ", &remaining_tokens); //v token

    token = strtok_s(NULL, " ", &remaining_tokens);
    position.x = strtof(token, NULL);

    token = strtok_s(NULL, " ", &remaining_tokens);
    position.y = strtof(token, NULL);

    token = strtok_s(NULL, " ", &remaining_tokens);
    position.z = strtof(token, NULL);

    return __obj_add_position(obj_info, position);
}

/// @brief Function to save uv information from a buffer into the obj_info structure
/// @param obj_info Structure containig all the obj info
/// @param buffer A buffer containing chars representing the obj file
/// @return An error number, 0 if everything have been completed succesfully
int __obj_save_uv_info(obj_info_t* obj_info, char* buffer)
{
    char* remaining_tokens;
    char* token;
    obj_float2_t uv;

    strtok_s(buffer, " ", &remaining_tokens); //vt token

    token = strtok_s(NULL, " ", &remaining_tokens);
    uv.x = strtof(token, NULL);

    token = strtok_s(NULL, " ", &remaining_tokens);
    uv.y = strtof(token, NULL);

    return __obj_add_uv(obj_info, uv);
}

/// @brief Function to save normal information from a buffer into the obj_info structure
/// @param obj_info Structure containig all the obj info
/// @param buffer A buffer containing chars representing the obj file
/// @return An error number, 0 if everything have been completed succesfully
int __obj_save_normal_info(obj_info_t* obj_info, char* buffer)
{
    char* remaining_tokens;
    char* token;
    obj_float3_t normal;

    strtok_s(buffer, " ", &remaining_tokens); //vn token

    token = strtok_s(NULL, " ", &remaining_tokens);
    normal.x = strtof(token, NULL);

    token = strtok_s(NULL, " ", &remaining_tokens);
    normal.y = strtof(token, NULL);

    token = strtok_s(NULL, " ", &remaining_tokens);
    normal.z = strtof(token, NULL);

    return __obj_add_normal(obj_info, normal);
}

/// @brief Function to save vertex information from a buffer into the obj_info structure
/// @param obj_info Structure containig all the obj info
/// @param buffer A buffer containing chars representing the obj file
/// @return An error number, 0 if everything have been completed succesfully
int __obj_save_vertex_info(obj_info_t* obj_info, char* buffer)
{
    char *remaining_tokens;
    char *token;

    strtok_s(buffer, " ", &remaining_tokens); //f token

    for (int i = 0; i < INFO_PER_TRIANGLE_AMOUNT; i++)
    {
        obj_vertex_t vertex;

        token = strtok_s(NULL, "/", &remaining_tokens);
        vertex.position = obj_info->position_dynamic_array[strtol(token, NULL, 0) - 1];

        token = strtok_s(NULL, "/", &remaining_tokens);
        vertex.uv = obj_info->uv_dynamic_array[strtol(token, NULL, 0) - 1];

        token = strtok_s(NULL, " ", &remaining_tokens);
        vertex.normal = obj_info->normal_dynamic_array[strtol(token, NULL, 0) - 1];

        if(__obj_add_vertex(obj_info, vertex))
        {
            return 1;
        }
    }

    return 0;
}

/// @brief Function to create a new obj_info and initialize its members
/// @return A pointer to the obj_info structure
obj_info_t* __obj_info_new()
{
    obj_info_t* obj_info = (obj_info_t*)malloc(sizeof(obj_info_t));

    if(!obj_info)
    {
        return NULL;
    }

    obj_info->position_dynamic_array = NULL;
    obj_info->position_amount = 0;
    obj_info->position_dynamic_array_capacity = STARTING_DYNAMIC_ARRAY_CAPACITY;
    obj_info->normal_dynamic_array = NULL;
    obj_info->normal_amount = 0;
    obj_info->normal_dynamic_array_capacity = STARTING_DYNAMIC_ARRAY_CAPACITY;
    obj_info->uv_dynamic_array = NULL;
    obj_info->uv_amount = 0;
    obj_info->uv_dynamic_array_capacity = STARTING_DYNAMIC_ARRAY_CAPACITY;
    obj_info->vertex_dynamic_array = NULL;
    obj_info->vertex_amount = 0;
    obj_info->vertex_dynamic_array_capacity = STARTING_DYNAMIC_ARRAY_CAPACITY;

    return obj_info;
}

/// @brief Function to free the memory allocated for an obj_info
/// @param obj_info The obj_info structure to free
void __obj_info_free(obj_info_t* obj_info)
{
    free(obj_info->position_dynamic_array);
    free(obj_info->normal_dynamic_array);
    free(obj_info->uv_dynamic_array);
    free(obj_info->vertex_dynamic_array);

    free(obj_info);
}

/// @brief Function to create a new obj and initialize its members
/// @return A pointer to the obj structure
obj_t* __obj_new()
{
    obj_t* obj = (obj_t*)malloc(sizeof(obj_t));
    if(!obj)
    {
        return NULL;
    }

    obj->triangles = NULL;
    obj->triangle_amount = 0;
    obj->triangles_capacity = STARTING_DYNAMIC_ARRAY_CAPACITY;
    obj->vertex_amount = 0;
    obj->position_amount = 0;
    obj->uv_amount = 0;
    obj->normal_amount = 0;

    return obj;
}

/// @brief Function to free the memory allocated for an obj
/// @param obj The obj structure to free
void __obj_free(obj_t* obj)
{
    free(obj->triangles);

    free(obj);
}

/// @brief Functiona to create a new triangle structure
/// @param vertex1 The first vertex od the triangle
/// @param vertex2 The second vertex od the triangle
/// @param vertex3 The third vertex od the triangle
/// @return A new triangle structure
obj_triangle_t __obj_triangle_new(obj_vertex_t vertex1, obj_vertex_t vertex2, obj_vertex_t vertex3)
{
    obj_triangle_t triangle;
    triangle.v1 = vertex1;
    triangle.v2 = vertex2;
    triangle.v3 = vertex3;

    return triangle;
}

/// @brief Function to add a triangle inside the obj triangle dynamic array
/// @param obj A pointer to the obj structure
/// @param triangle The triangle structure to be added
/// @return An error number, 0 if everything have been completed succesfully
int __obj_add_triangle(obj_t* obj, obj_triangle_t triangle)
{
    if(obj->triangle_amount != 0)
    {
        if(obj->triangle_amount >= obj->triangles_capacity)
        {
            obj->triangles_capacity *= STARTING_DYNAMIC_ARRAY_CAPACITY;
            obj->triangles = (obj_triangle_t*)realloc(obj->triangles, (obj->triangles_capacity) * sizeof(obj_triangle_t));
        }
    }
    else
    {
        obj->triangles = (obj_triangle_t*)calloc(STARTING_DYNAMIC_ARRAY_CAPACITY, sizeof(obj_triangle_t));
    }

    if(!obj->triangles)
    {
        return 1;
    }

    obj->triangles[obj->triangle_amount] = triangle;
    obj->triangle_amount++;

    return 0;
}

/// @brief Function to update all the counters but triangle_amount inside obj structure
/// @param obj A pointer to the obj structure to update
/// @param obj_info A pointer to the obj_info structure from which data will be retrieved
void __obj_update_other_counters(obj_t* obj, obj_info_t* obj_info)
{
    obj->vertex_amount = obj_info->vertex_amount;
    obj->position_amount = obj_info->position_amount;
    obj->uv_amount = obj_info->uv_amount;
    obj->normal_amount = obj_info->normal_amount;
}

/// @brief Function to parse an OBJ file and populate an obj structure with triangle data
/// @param file_name Complete path of the file to read
/// @return A pointer to the obj structure
obj_t* obj_parse(const char* file_name);

#ifdef OBJ_IMPLEMENTATION
obj_t* obj_parse(const char* file_name)
{
    FILE* file = __obj_file_open(file_name);
    if(!file)
    {
        fprintf(stderr, "Error: Trying to open the file %s!\n", file_name);
        return NULL;
    }

    obj_info_t* obj_info = __obj_info_new();
    if(!obj_info)
    {
        fprintf(stderr, "Error: Trying to allocate memory for obj_info!\n");
        __obj_file_close(file);
        return NULL;
    }

    obj_t* obj = __obj_new();
    if(!obj)
    {
        fprintf(stderr, "Error: Trying to allocate memory for obj!\n");
        __obj_file_close(file);
        __obj_info_free(obj_info);
        return NULL;
    }

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), file))
    {
        if(!strncmp(buffer, POSITION_LABEL, POSITION_LABEL_CHAR_AMOUNT))
        {
            if(__obj_save_position_info(obj_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save position inside obj_info!\n");
                __obj_file_close(file);
                __obj_info_free(obj_info);
                __obj_free(obj);
                return NULL;
            }
        }

        if(!strncmp(buffer, UV_LABEL, UV_LABEL_CHAR_AMOUNT))
        {
            if(__obj_save_uv_info(obj_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save uv inside obj_info!\n");
                __obj_file_close(file);
                __obj_info_free(obj_info);
                __obj_free(obj);
                return NULL;
            }
        }

        if(!strncmp(buffer, NORMAL_LABEL, NORMAL_LABEL_CHAR_AMOUNT))
        {
            if(__obj_save_normal_info(obj_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save normal inside obj_info!\n");
                __obj_file_close(file);
                __obj_info_free(obj_info);
                __obj_free(obj);
                return NULL;
            }
        }

        if(!strncmp(buffer, FACE_LABEL, FACE_LABEL_CHAR_AMOUNT))
        {
            if(__obj_save_vertex_info(obj_info, buffer))
            {
                fprintf(stderr, "Error: Trying to save vertex inside obj_info!\n");
                __obj_info_free(obj_info);
                __obj_free(obj);
                return NULL;
            }
        }
    }

    __obj_file_close(file);

    for(int i = 0; i < obj_info->vertex_amount; i += VERTEX_PER_TRIANGLE)
    {
        obj_triangle_t triangle = __obj_triangle_new(obj_info->vertex_dynamic_array[i], obj_info->vertex_dynamic_array[i + 1], obj_info->vertex_dynamic_array[i + 2]);
        if(__obj_add_triangle(obj, triangle))
        {
            fprintf(stderr, "Error: Trying to add triangle inside obj!\n");
            __obj_info_free(obj_info);
            __obj_free(obj);
            return NULL;
        }
    }

    __obj_update_other_counters(obj, obj_info);

    __obj_info_free(obj_info);

    return obj;
}
#endif //OBJ_IMPLEMENTATION

#endif //OBJ_PARSER