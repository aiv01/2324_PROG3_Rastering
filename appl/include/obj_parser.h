#ifndef OBJ_PARSER
#define OBJ_PARSER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct obj_float3_t{
    float x;
    float y;
    float z;
}obj_float3_t;

typedef struct obj_float2_t{
    float x;
    float y;
}obj_float2_t;

typedef struct obj_t{

    int v_count;
    int vt_count;
    int vn_count;
    int f_count;
    obj_float3_t* v;
    obj_float2_t* vt;
    obj_float3_t* vn;
}obj_t;

obj_t* obj_parse(const char* file_name){

    obj_t *obj = (obj_t*)malloc(sizeof(obj_t));
    obj->v_count = 0;
    obj->vt_count = 0;
    obj->vn_count = 0;
    obj->f_count = 0;

    FILE *file;
    fopen_s(&file, file_name, "r");

    if(file == NULL)
    {
        printf("ERROR READ FILE: %s\n", file_name);
        return NULL;
    }

    char buffer[1024];

    while(fgets(buffer,sizeof(buffer), file))
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

    fclose(file);

    return obj;
}




#endif // end define OBJ_PARSER