#define CLOVE_SUITE_NAME TestTry
#include "clove-unit.h"
#include "obj_parser.h"

CLOVE_TEST(ReadQuadObj)
{

   char *file_name = "bin\\test\\resources\\quad.obj";
   obj_t *obj = obj_parse(file_name);

   CLOVE_NOT_NULL(obj);
   CLOVE_INT_EQ(4, obj->v_count);
   CLOVE_INT_EQ(4, obj->vt_count);
   CLOVE_INT_EQ(1, obj->vn_count);
   CLOVE_INT_EQ(2, obj->f_count);

   // vertex tests
   CLOVE_FLOAT_EQ(-1.f, obj->v[0].x);
   CLOVE_FLOAT_EQ(1.f, obj->v[0].y);
   CLOVE_FLOAT_EQ(0.f, obj->v[0].z);

   CLOVE_FLOAT_EQ(1.f, obj->v[1].x);
   CLOVE_FLOAT_EQ(1.f, obj->v[1].y);
   CLOVE_FLOAT_EQ(0.f, obj->v[1].z);

   CLOVE_FLOAT_EQ(-1.f, obj->v[2].x);
   CLOVE_FLOAT_EQ(-1.f, obj->v[2].y);
   CLOVE_FLOAT_EQ(0.f, obj->v[2].z);

   CLOVE_FLOAT_EQ(1.f, obj->v[3].x);
   CLOVE_FLOAT_EQ(-1.f, obj->v[3].y);
   CLOVE_FLOAT_EQ(0.f, obj->v[3].z);

   // uv tests
   CLOVE_FLOAT_EQ(1.f, obj->vt[0].x);
   CLOVE_FLOAT_EQ(1.f, obj->vt[0].y);

   CLOVE_FLOAT_EQ(0.f, obj->vt[1].x);
   CLOVE_FLOAT_EQ(1.f, obj->vt[1].y);

   CLOVE_FLOAT_EQ(0.f, obj->vt[2].x);
   CLOVE_FLOAT_EQ(0.f, obj->vt[2].y);

   CLOVE_FLOAT_EQ(1.f, obj->vt[3].x);
   CLOVE_FLOAT_EQ(0.f, obj->vt[3].y);

   // normals tests
   CLOVE_FLOAT_EQ(0.f, obj->vn[0].x);
   CLOVE_FLOAT_EQ(0.f, obj->vn[0].y);
   CLOVE_FLOAT_EQ(1.f, obj->vn[0].z);

   // faces tests

   //face 1
   CLOVE_INT_EQ(4, obj->v_info[0].v_index);
   CLOVE_INT_EQ(4, obj->v_info[0].vt_index);
   CLOVE_INT_EQ(1, obj->v_info[0].vn_index);

   CLOVE_INT_EQ(3, obj->v_info[1].v_index);
   CLOVE_INT_EQ(3, obj->v_info[1].vt_index);
   CLOVE_INT_EQ(1, obj->v_info[1].vn_index);

   CLOVE_INT_EQ(1, obj->v_info[2].v_index);
   CLOVE_INT_EQ(2, obj->v_info[2].vt_index);
   CLOVE_INT_EQ(1, obj->v_info[2].vn_index);

   //face 2
   CLOVE_INT_EQ(2, obj->v_info[3].v_index);
   CLOVE_INT_EQ(1, obj->v_info[3].vt_index);
   CLOVE_INT_EQ(1, obj->v_info[3].vn_index);

   CLOVE_INT_EQ(4, obj->v_info[4].v_index);
   CLOVE_INT_EQ(4, obj->v_info[4].vt_index);
   CLOVE_INT_EQ(1, obj->v_info[4].vn_index);

   CLOVE_INT_EQ(1, obj->v_info[5].v_index);
   CLOVE_INT_EQ(2, obj->v_info[5].vt_index);
   CLOVE_INT_EQ(1, obj->v_info[5].vn_index);
}
