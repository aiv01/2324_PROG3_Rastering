#define CLOVE_SUITE_NAME TestTry
#include "clove-unit.h"
#include "obj_parser.h"

CLOVE_TEST(ReadQuadObj) {
   
   char* file_name = "bin\\test\\resources\\quad.obj";
   obj_t *obj = obj_parse(file_name);

   CLOVE_NOT_NULL(obj);
   CLOVE_INT_EQ(4, obj->v_count);
   CLOVE_INT_EQ(4, obj->vt_count);
   CLOVE_INT_EQ(1, obj->vn_count);
   CLOVE_INT_EQ(2, obj->f_count);


   // CLOVE_FLOAT_EQ(-1.f,obj->v[0].x);
   // CLOVE_FLOAT_EQ(1.f,obj->v[0].y);
   // CLOVE_FLOAT_EQ(0.f,obj->v[0].z);

   // CLOVE_FLOAT_EQ(1.f,obj->v[1].x);
   // CLOVE_FLOAT_EQ(1.f,obj->v[1].y);
   // CLOVE_FLOAT_EQ(0.f,obj->v[1].z);

   // CLOVE_FLOAT_EQ(-1.f,obj->v[2].x);
   // CLOVE_FLOAT_EQ(-1.f,obj->v[2].y);
   // CLOVE_FLOAT_EQ(0.f,obj->v[2].z);

   // CLOVE_FLOAT_EQ(1.f,obj->v[3].x);
   // CLOVE_FLOAT_EQ(-1.f,obj->v[3].y);
   // CLOVE_FLOAT_EQ(0.f,obj->v[3].z);

}


