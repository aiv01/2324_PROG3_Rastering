#define CLOVE_SUITE_NAME ObjParserTest
#include "clove-unit.h"
#include "obj_parser.h"

CLOVE_TEST(FileOpenNotSuccesfully)
{
   FILE* file = obj_file_open("test.txt");
   CLOVE_NULL(file);
}

CLOVE_TEST(FileOpenSuccesfully)
{
   FILE* file = obj_file_open("bin\\test\\resources\\quad.obj");
   CLOVE_NOT_NULL(file);

   obj_file_close(file);
}

CLOVE_TEST(ObjNew)
{
   obj_t* obj = obj_new();
   CLOVE_NOT_NULL(obj);

   CLOVE_NULL(obj->vertex_dynamic_array);
   CLOVE_NULL(obj->triangle_dynamic_array);

   CLOVE_INT_EQ(0, obj->vertex_amount);
   CLOVE_INT_EQ(0, obj->triangle_amount);

   obj_free(obj);
}

CLOVE_TEST(AllVertexInfoNew)
{
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();
   CLOVE_NOT_NULL(all_vertex_info);

   CLOVE_NULL(all_vertex_info->position_dynamic_array);
   CLOVE_NULL(all_vertex_info->normal_dynamic_array);
   CLOVE_NULL(all_vertex_info->uv_dynamic_array);

   CLOVE_INT_EQ(0, all_vertex_info->position_amount);
   CLOVE_INT_EQ(0, all_vertex_info->normal_amount);
   CLOVE_INT_EQ(0, all_vertex_info->uv_amount);

   obj_all_vertex_info_free(all_vertex_info);
}

CLOVE_TEST(AddOnePosition)
{
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();

   const float x = 15.234f;
   const float y = 125.234f;
   const float z = 5.0f;

   const obj_float3_t position = (obj_float3_t){x, y, z};
   int error = obj_add_position(all_vertex_info, position);
   CLOVE_INT_EQ(0, error);

   CLOVE_FLOAT_EQ(x, all_vertex_info->position_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(y, all_vertex_info->position_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(z, all_vertex_info->position_dynamic_array[0].z);
   CLOVE_INT_EQ(all_vertex_info->position_amount, 1);

   CLOVE_NULL(all_vertex_info->normal_dynamic_array);
   CLOVE_NULL(all_vertex_info->uv_dynamic_array);

   CLOVE_INT_EQ(0, all_vertex_info->normal_amount);
   CLOVE_INT_EQ(0, all_vertex_info->uv_amount);

   obj_all_vertex_info_free(all_vertex_info);
}

CLOVE_TEST(AddThreePositions)
{
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();

   const float x1 = 15.234f;
   const float y1 = 125.234f;
   const float z1 = 5.0f;

   const float x2 = 0.0f;
   const float y2 = 2.123f;
   const float z2 = 74.125f;

   const float x3 = 123.124f;
   const float y3 = 234.312f;
   const float z3 = 194.8942f;

   const obj_float3_t position1 = (obj_float3_t){x1, y1, z1};
   int error1 = obj_add_position(all_vertex_info, position1);
   CLOVE_INT_EQ(0, error1);

   CLOVE_INT_EQ(1, all_vertex_info->position_amount);

   const obj_float3_t position2 = (obj_float3_t){x2, y2, z2};
   int error2 = obj_add_position(all_vertex_info, position2);
   CLOVE_INT_EQ(0, error2);

   CLOVE_INT_EQ(2, all_vertex_info->position_amount);

   const obj_float3_t position3 = (obj_float3_t){x3, y3, z3};
   int error3 = obj_add_position(all_vertex_info, position3);
   CLOVE_INT_EQ(0, error3);

   CLOVE_INT_EQ(3, all_vertex_info->position_amount);
   
   CLOVE_FLOAT_EQ(x1, all_vertex_info->position_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(y1, all_vertex_info->position_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(z1, all_vertex_info->position_dynamic_array[0].z);

   CLOVE_FLOAT_EQ(x2, all_vertex_info->position_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(y2, all_vertex_info->position_dynamic_array[1].y);
   CLOVE_FLOAT_EQ(z2, all_vertex_info->position_dynamic_array[1].z);

   CLOVE_FLOAT_EQ(x3, all_vertex_info->position_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(y3, all_vertex_info->position_dynamic_array[2].y);
   CLOVE_FLOAT_EQ(z3, all_vertex_info->position_dynamic_array[2].z);

   CLOVE_NULL(all_vertex_info->normal_dynamic_array);
   CLOVE_NULL(all_vertex_info->uv_dynamic_array);

   CLOVE_INT_EQ(0, all_vertex_info->normal_amount);
   CLOVE_INT_EQ(0, all_vertex_info->uv_amount);

   obj_all_vertex_info_free(all_vertex_info);
}

CLOVE_TEST(AddOneNormal)
{
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();

   const float x = 15.234f;
   const float y = 125.234f;
   const float z = 5.0f;

   const obj_float3_t normal = (obj_float3_t){x, y, z};
   int error = obj_add_normal(all_vertex_info, normal);
   CLOVE_INT_EQ(0, error);

   CLOVE_FLOAT_EQ(x, all_vertex_info->normal_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(y, all_vertex_info->normal_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(z, all_vertex_info->normal_dynamic_array[0].z);
   CLOVE_INT_EQ(all_vertex_info->normal_amount, 1);

   CLOVE_NULL(all_vertex_info->position_dynamic_array);
   CLOVE_NULL(all_vertex_info->uv_dynamic_array);

   CLOVE_INT_EQ(0, all_vertex_info->position_amount);
   CLOVE_INT_EQ(0, all_vertex_info->uv_amount);

   obj_all_vertex_info_free(all_vertex_info);
}

CLOVE_TEST(AddThreeNormals)
{
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();

   const float x1 = 15.234f;
   const float y1 = 125.234f;
   const float z1 = 5.0f;

   const float x2 = 0.0f;
   const float y2 = 2.123f;
   const float z2 = 74.125f;

   const float x3 = 123.124f;
   const float y3 = 234.312f;
   const float z3 = 194.8942f;

   const obj_float3_t normal1 = (obj_float3_t){x1, y1, z1};
   int error1 = obj_add_normal(all_vertex_info, normal1);
   CLOVE_INT_EQ(0, error1);

   CLOVE_INT_EQ(1, all_vertex_info->normal_amount);

   const obj_float3_t normal2 = (obj_float3_t){x2, y2, z2};
   int error2 = obj_add_normal(all_vertex_info, normal2);
   CLOVE_INT_EQ(0, error2);

   CLOVE_INT_EQ(2, all_vertex_info->normal_amount);

   const obj_float3_t normal3 = (obj_float3_t){x3, y3, z3};
   int error3 = obj_add_normal(all_vertex_info, normal3);
   CLOVE_INT_EQ(0, error3);

   CLOVE_INT_EQ(3, all_vertex_info->normal_amount);
   
   CLOVE_FLOAT_EQ(x1, all_vertex_info->normal_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(y1, all_vertex_info->normal_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(z1, all_vertex_info->normal_dynamic_array[0].z);

   CLOVE_FLOAT_EQ(x2, all_vertex_info->normal_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(y2, all_vertex_info->normal_dynamic_array[1].y);
   CLOVE_FLOAT_EQ(z2, all_vertex_info->normal_dynamic_array[1].z);

   CLOVE_FLOAT_EQ(x3, all_vertex_info->normal_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(y3, all_vertex_info->normal_dynamic_array[2].y);
   CLOVE_FLOAT_EQ(z3, all_vertex_info->normal_dynamic_array[2].z);

   CLOVE_NULL(all_vertex_info->position_dynamic_array);
   CLOVE_NULL(all_vertex_info->uv_dynamic_array);

   CLOVE_INT_EQ(0, all_vertex_info->position_amount);
   CLOVE_INT_EQ(0, all_vertex_info->uv_amount);

   obj_all_vertex_info_free(all_vertex_info);
}

CLOVE_TEST(AddOneUv)
{
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();

   const float x = 15.234f;
   const float y = 125.234f;

   const obj_float2_t uv = (obj_float2_t){x, y};
   int error = obj_add_uv(all_vertex_info, uv);
   CLOVE_INT_EQ(0, error);

   CLOVE_FLOAT_EQ(x, all_vertex_info->uv_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(y, all_vertex_info->uv_dynamic_array[0].y);
   CLOVE_INT_EQ(all_vertex_info->uv_amount, 1);

   CLOVE_NULL(all_vertex_info->position_dynamic_array);
   CLOVE_NULL(all_vertex_info->normal_dynamic_array);

   CLOVE_INT_EQ(0, all_vertex_info->position_amount);
   CLOVE_INT_EQ(0, all_vertex_info->normal_amount);

   obj_all_vertex_info_free(all_vertex_info);
}

CLOVE_TEST(AddThreeUvs)
{
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();

   const float x1 = 15.234f;
   const float y1 = 125.234f;

   const float x2 = 0.0f;
   const float y2 = 2.123f;

   const float x3 = 123.124f;
   const float y3 = 234.312f;

   const obj_float2_t uv1 = (obj_float2_t){x1, y1};
   int error1 = obj_add_uv(all_vertex_info, uv1);
   CLOVE_INT_EQ(0, error1);

   CLOVE_INT_EQ(1, all_vertex_info->uv_amount);

   const obj_float2_t uv2 = (obj_float2_t){x2, y2};
   int error2 = obj_add_uv(all_vertex_info, uv2);
   CLOVE_INT_EQ(0, error2);

   CLOVE_INT_EQ(2, all_vertex_info->uv_amount);

   const obj_float2_t uv3 = (obj_float2_t){x3, y3};
   int error3 = obj_add_uv(all_vertex_info, uv3);
   CLOVE_INT_EQ(0, error3);

   CLOVE_INT_EQ(3, all_vertex_info->uv_amount);
   
   CLOVE_FLOAT_EQ(x1, all_vertex_info->uv_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(y1, all_vertex_info->uv_dynamic_array[0].y);

   CLOVE_FLOAT_EQ(x2, all_vertex_info->uv_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(y2, all_vertex_info->uv_dynamic_array[1].y);

   CLOVE_FLOAT_EQ(x3, all_vertex_info->uv_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(y3, all_vertex_info->uv_dynamic_array[2].y);

   CLOVE_NULL(all_vertex_info->position_dynamic_array);
   CLOVE_NULL(all_vertex_info->normal_dynamic_array);

   CLOVE_INT_EQ(0, all_vertex_info->position_amount);
   CLOVE_INT_EQ(0, all_vertex_info->normal_amount);

   obj_all_vertex_info_free(all_vertex_info);
}

CLOVE_TEST(SavePositionInfo)
{
   FILE* file = obj_file_open("bin\\test\\resources\\quad.obj");
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();
   char buffer[1024];

   while(fgets(buffer, sizeof(buffer), file))
   {
      if (strncmp(buffer, "v ", 2) == 0)
      {
         int error = obj_save_position_info(all_vertex_info, buffer);
         CLOVE_INT_EQ(0, error);
      }
   }

   CLOVE_NOT_NULL(all_vertex_info->position_dynamic_array);
   CLOVE_NULL(all_vertex_info->normal_dynamic_array);
   CLOVE_NULL(all_vertex_info->uv_dynamic_array);

   CLOVE_INT_EQ(4, all_vertex_info->position_amount);
   CLOVE_INT_EQ(0, all_vertex_info->normal_amount);
   CLOVE_INT_EQ(0, all_vertex_info->uv_amount);

   CLOVE_FLOAT_EQ(-1.000000f, all_vertex_info->position_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(1.000000f, all_vertex_info->position_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->position_dynamic_array[0].z);

   CLOVE_FLOAT_EQ(1.000000f, all_vertex_info->position_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(1.000000f, all_vertex_info->position_dynamic_array[1].y);
   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->position_dynamic_array[1].z);

   CLOVE_FLOAT_EQ(-1.000000f, all_vertex_info->position_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(-1.000000f, all_vertex_info->position_dynamic_array[2].y);
   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->position_dynamic_array[2].z);

   CLOVE_FLOAT_EQ(1.000000f, all_vertex_info->position_dynamic_array[3].x);
   CLOVE_FLOAT_EQ(-1.000000f, all_vertex_info->position_dynamic_array[3].y);
   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->position_dynamic_array[3].z);

   obj_all_vertex_info_free(all_vertex_info);
}

CLOVE_TEST(SaveNormalInfo)
{
   FILE* file = obj_file_open("bin\\test\\resources\\quad.obj");
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();
   char buffer[1024];

   while(fgets(buffer, sizeof(buffer), file))
   {
      if (strncmp(buffer, "vn ", 3) == 0)
      {
         int error = obj_save_normal_info(all_vertex_info, buffer);
         CLOVE_INT_EQ(0, error);
      }
   }

   CLOVE_NULL(all_vertex_info->position_dynamic_array);
   CLOVE_NOT_NULL(all_vertex_info->normal_dynamic_array);
   CLOVE_NULL(all_vertex_info->uv_dynamic_array);

   CLOVE_INT_EQ(0, all_vertex_info->position_amount);
   CLOVE_INT_EQ(1, all_vertex_info->normal_amount);
   CLOVE_INT_EQ(0, all_vertex_info->uv_amount);

   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->normal_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->normal_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(1.000000f, all_vertex_info->normal_dynamic_array[0].z);

   obj_all_vertex_info_free(all_vertex_info);
}

CLOVE_TEST(SaveUvInfo)
{
   FILE* file = obj_file_open("bin\\test\\resources\\quad.obj");
   obj_info_t* all_vertex_info = obj_all_vertex_info_new();
   char buffer[1024];

   while(fgets(buffer, sizeof(buffer), file))
   {
      if (strncmp(buffer, "vt ", 3) == 0)
      {
         int error = obj_save_uv_info(all_vertex_info, buffer);
         CLOVE_INT_EQ(0, error);
      }
   }

   CLOVE_NULL(all_vertex_info->position_dynamic_array);
   CLOVE_NULL(all_vertex_info->normal_dynamic_array);
   CLOVE_NOT_NULL(all_vertex_info->uv_dynamic_array);

   CLOVE_INT_EQ(0, all_vertex_info->position_amount);
   CLOVE_INT_EQ(0, all_vertex_info->normal_amount);
   CLOVE_INT_EQ(4, all_vertex_info->uv_amount);

   CLOVE_FLOAT_EQ(1.000000f, all_vertex_info->uv_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(1.000000f, all_vertex_info->uv_dynamic_array[0].y);

   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->uv_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(1.000000f, all_vertex_info->uv_dynamic_array[1].y);

   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->uv_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->uv_dynamic_array[2].y);

   CLOVE_FLOAT_EQ(1.000000f, all_vertex_info->uv_dynamic_array[3].x);
   CLOVE_FLOAT_EQ(0.000000f, all_vertex_info->uv_dynamic_array[3].y);

   obj_all_vertex_info_free(all_vertex_info);
}

/*CLOVE_TEST(VertexNew)
{

}*/

/*CLOVE_TEST(AddOneVertex)
{
   obj_t* obj = obj_new();
   obj_vertex_t vertex = 

   int error = obj_add_vertex(obj, vertex);

}*/

/*CLOVE_TEST(ReadQuadObj)
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

CLOVE_TEST(CheckSuzanneCounts)
{
   char *file_name = "bin\\test\\resources\\suzanne.obj";
   obj_t *obj = obj_parse(file_name);

   CLOVE_NOT_NULL(obj);
   CLOVE_INT_EQ(511, obj->v_count);
   CLOVE_INT_EQ(590, obj->vt_count);
   CLOVE_INT_EQ(507, obj->vn_count);
   CLOVE_INT_EQ(968, obj->f_count);
}
*/