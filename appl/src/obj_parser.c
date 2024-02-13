#include "obj_parser.h"

obj_t* ObjParse(const char* file_name)
{
    obj_t* obj = (obj_t*)malloc(sizeof(obj_t));
    obj->v_count = 0;
    obj->vt_count = 0;
    obj->vn_count = 0;
    obj->f_count = 0;

    FILE* file; 
    errno_t err = fopen_s(&file, file_name, "r");
    if(err)
    {
        printf("ERROR TO READ FILE: %s\n", file_name);
        return NULL;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file))
    {
        if(strncmp(buffer, "v ", 2) == 0)
        {
            obj->v_count++;
        }
        if(strncmp(buffer, "vt ", 3) == 0)
        {
            obj->vt_count++;
        }
        if(strncmp(buffer, "vn ", 3) == 0)
        {
            obj->vn_count++;
        }
        if(strncmp(buffer, "f ", 2) == 0)
        {
            obj->f_count++;
        }

    }
    
    obj->v = (obj_float3_t*)malloc(obj->v_count * sizeof(obj_float3_t));
    obj->vt = (obj_float2_t*)malloc(obj->vt_count * sizeof(obj_float3_t));
    obj->vn = (obj_float3_t*)malloc(obj->vn_count * sizeof(obj_float3_t));
    obj->v_info = (obj_vertex_info_t*)malloc(obj->f_count * 3 * sizeof(obj_vertex_info_t));

    rewind(file);

    int v_index = 0;
    int vt_index = 0;
    int vn_index = 0;
    int f_index = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        if(strncmp(buffer, "v ", 2) == 0)
        {
            char* remaining_tokens;
            char* token;

            strtok_s(buffer, " ", &remaining_tokens); //v token

            token = strtok_s(NULL, " ", &remaining_tokens); //v.x token
            obj->v[v_index].x = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens); //v.y token
            obj->v[v_index].y = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens); //v.z token
            obj->v[v_index].z = atof(token);

            v_index++;
        }

        if(strncmp(buffer, "vt ", 3) == 0)
        {
            char* remaining_tokens;
            char* token;

            strtok_s(buffer, " ", &remaining_tokens); //vt token

            token = strtok_s(NULL, " ", &remaining_tokens); //vt.x token
            obj->vt[vt_index].x = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens); //vt.y token
            obj->vt[vt_index].y = atof(token);

            vt_index++;
        }

        if(strncmp(buffer, "vn ", 3) == 0)
        {
            char* remaining_tokens;
            char* token;

            strtok_s(buffer, " ", &remaining_tokens); //vn token

            token = strtok_s(NULL, " ", &remaining_tokens); //vn.x token
            obj->vn[vn_index].x = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens); //vn.y token
            obj->vn[vn_index].y = atof(token);

            token = strtok_s(NULL, " ", &remaining_tokens); //vn.z token
            obj->vn[vn_index].z = atof(token);

            vn_index++;
        }

        if(strncmp(buffer, "f ", 2) == 0)
        {
            char* remaining_tokens;
            char* token;

            strtok_s(buffer, " ", &remaining_tokens); //vn token

            for (int i = 0; i < 3; i++)
            {
                token = strtok_s(NULL, "/", &remaining_tokens); //vn.x token
                obj->v_info[f_index + i].v_index = atoi(token);
    
                token = strtok_s(NULL, "/", &remaining_tokens); //vn.y token
                obj->v_info[f_index + i].vt_index = atoi(token);
    
                token = strtok_s(NULL, " ", &remaining_tokens); //vn.z token
                obj->v_info[f_index + i].vn_index = atoi(token);
                
            }
    
            f_index+= 3;
        }
    }

    fclose(file);

    obj->triangle_count = f_index / TRIANGLE_VERTECES;
    obj->triangles = (obj_triangle_t*)malloc(obj->triangle_count * sizeof(obj_triangle_t));

    for (int i = 0; i < obj->triangle_count; i++)
    {
        obj_vertex_info_t v_info1 = obj->v_info[i * 3 + 0];
        obj_vertex_info_t v_info2 = obj->v_info[i * 3 + 1];
        obj_vertex_info_t v_info3 = obj->v_info[i * 3 + 2];

        obj->triangles[i].v1.position = obj->v[v_info1.v_index - 1];
        obj->triangles[i].v1.uv = obj->vt[v_info1.vt_index - 1];
        obj->triangles[i].v1.normal = obj->vn[v_info1.vn_index - 1];

        obj->triangles[i].v2.position = obj->v[v_info2.v_index - 1];
        obj->triangles[i].v2.uv = obj->vt[v_info2.vt_index - 1];
        obj->triangles[i].v2.normal = obj->vn[v_info2.vn_index - 1];

        obj->triangles[i].v3.position = obj->v[v_info3.v_index - 1];
        obj->triangles[i].v3.uv = obj->vt[v_info3.vt_index - 1];
        obj->triangles[i].v3.normal = obj->vn[v_info3.vn_index - 1];
    }
    
    return obj;
}