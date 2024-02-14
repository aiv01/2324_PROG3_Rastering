#define CLOVE_SUITE_NAME ObjApiTest
#include "clove-unit.h"
#include "obj_parser.h"

CLOVE_TEST(FileOpenNotSuccesfully)
{
   FILE* file = __obj_file_open("test.txt");
   CLOVE_NULL(file);
}

CLOVE_TEST(FileOpenSuccesfully)
{
   FILE* file = __obj_file_open("bin\\test\\resources\\quad.obj");
   CLOVE_NOT_NULL(file);

   __obj_file_close(file);
}

CLOVE_TEST(AddThreePositions)
{
   obj_info_t* obj_info = __obj_info_new();

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
   int error1 = __obj_add_position(obj_info, position1);
   CLOVE_SIZET_EQ(0, error1);

   CLOVE_SIZET_EQ(1, obj_info->position_amount);

   const obj_float3_t position2 = (obj_float3_t){x2, y2, z2};
   int error2 = __obj_add_position(obj_info, position2);
   CLOVE_SIZET_EQ(0, error2);

   CLOVE_SIZET_EQ(2, obj_info->position_amount);

   const obj_float3_t position3 = (obj_float3_t){x3, y3, z3};
   int error3 = __obj_add_position(obj_info, position3);
   CLOVE_SIZET_EQ(0, error3);

   CLOVE_SIZET_EQ(3, obj_info->position_amount);
   
   CLOVE_FLOAT_EQ(x1, obj_info->position_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(y1, obj_info->position_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(z1, obj_info->position_dynamic_array[0].z);

   CLOVE_FLOAT_EQ(x2, obj_info->position_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(y2, obj_info->position_dynamic_array[1].y);
   CLOVE_FLOAT_EQ(z2, obj_info->position_dynamic_array[1].z);

   CLOVE_FLOAT_EQ(x3, obj_info->position_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(y3, obj_info->position_dynamic_array[2].y);
   CLOVE_FLOAT_EQ(z3, obj_info->position_dynamic_array[2].z);

   CLOVE_NULL(obj_info->normal_dynamic_array);
   CLOVE_NULL(obj_info->uv_dynamic_array);
   CLOVE_NULL(obj_info->vertex_dynamic_array);

   CLOVE_SIZET_EQ(0, obj_info->normal_amount);
   CLOVE_SIZET_EQ(0, obj_info->uv_amount);
   CLOVE_SIZET_EQ(0, obj_info->vertex_amount);

   __obj_info_free(obj_info);
}

CLOVE_TEST(AddThreeNormals)
{
   obj_info_t* obj_info = __obj_info_new();

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
   int error1 = __obj_add_normal(obj_info, normal1);
   CLOVE_SIZET_EQ(0, error1);

   CLOVE_SIZET_EQ(1, obj_info->normal_amount);

   const obj_float3_t normal2 = (obj_float3_t){x2, y2, z2};
   int error2 = __obj_add_normal(obj_info, normal2);
   CLOVE_SIZET_EQ(0, error2);

   CLOVE_SIZET_EQ(2, obj_info->normal_amount);

   const obj_float3_t normal3 = (obj_float3_t){x3, y3, z3};
   int error3 = __obj_add_normal(obj_info, normal3);
   CLOVE_SIZET_EQ(0, error3);

   CLOVE_SIZET_EQ(3, obj_info->normal_amount);
   
   CLOVE_FLOAT_EQ(x1, obj_info->normal_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(y1, obj_info->normal_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(z1, obj_info->normal_dynamic_array[0].z);

   CLOVE_FLOAT_EQ(x2, obj_info->normal_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(y2, obj_info->normal_dynamic_array[1].y);
   CLOVE_FLOAT_EQ(z2, obj_info->normal_dynamic_array[1].z);

   CLOVE_FLOAT_EQ(x3, obj_info->normal_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(y3, obj_info->normal_dynamic_array[2].y);
   CLOVE_FLOAT_EQ(z3, obj_info->normal_dynamic_array[2].z);

   CLOVE_NULL(obj_info->position_dynamic_array);
   CLOVE_NULL(obj_info->uv_dynamic_array);
   CLOVE_NULL(obj_info->vertex_dynamic_array);

   CLOVE_SIZET_EQ(0, obj_info->position_amount);
   CLOVE_SIZET_EQ(0, obj_info->uv_amount);
   CLOVE_SIZET_EQ(0, obj_info->vertex_amount);

   __obj_info_free(obj_info);
}

CLOVE_TEST(AddThreeUvs)
{
   obj_info_t* obj_info = __obj_info_new();

   const float x1 = 15.234f;
   const float y1 = 125.234f;

   const float x2 = 0.0f;
   const float y2 = 2.123f;

   const float x3 = 123.124f;
   const float y3 = 234.312f;

   const obj_float2_t uv1 = (obj_float2_t){x1, y1};
   int error1 = __obj_add_uv(obj_info, uv1);
   CLOVE_SIZET_EQ(0, error1);

   CLOVE_SIZET_EQ(1, obj_info->uv_amount);

   const obj_float2_t uv2 = (obj_float2_t){x2, y2};
   int error2 = __obj_add_uv(obj_info, uv2);
   CLOVE_SIZET_EQ(0, error2);

   CLOVE_SIZET_EQ(2, obj_info->uv_amount);

   const obj_float2_t uv3 = (obj_float2_t){x3, y3};
   int error3 = __obj_add_uv(obj_info, uv3);
   CLOVE_SIZET_EQ(0, error3);

   CLOVE_SIZET_EQ(3, obj_info->uv_amount);
   
   CLOVE_FLOAT_EQ(x1, obj_info->uv_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(y1, obj_info->uv_dynamic_array[0].y);

   CLOVE_FLOAT_EQ(x2, obj_info->uv_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(y2, obj_info->uv_dynamic_array[1].y);

   CLOVE_FLOAT_EQ(x3, obj_info->uv_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(y3, obj_info->uv_dynamic_array[2].y);

   CLOVE_NULL(obj_info->position_dynamic_array);
   CLOVE_NULL(obj_info->normal_dynamic_array);
   CLOVE_NULL(obj_info->vertex_dynamic_array);

   CLOVE_SIZET_EQ(0, obj_info->position_amount);
   CLOVE_SIZET_EQ(0, obj_info->normal_amount);
   CLOVE_SIZET_EQ(0, obj_info->vertex_amount);

   __obj_info_free(obj_info);
}

CLOVE_TEST(SavePositionInfo)
{
   FILE* file = __obj_file_open("bin\\test\\resources\\quad.obj");
   obj_info_t* obj_info = __obj_info_new();
   char buffer[1024];

   while(fgets(buffer, sizeof(buffer), file))
   {
      if (strncmp(buffer, "v ", 2) == 0)
      {
         int error = __obj_save_position_info(obj_info, buffer);
         CLOVE_SIZET_EQ(0, error);
      }
   }

   CLOVE_NOT_NULL(obj_info->position_dynamic_array);
   CLOVE_NULL(obj_info->normal_dynamic_array);
   CLOVE_NULL(obj_info->uv_dynamic_array);
   CLOVE_NULL(obj_info->vertex_dynamic_array);

   CLOVE_SIZET_EQ(4, obj_info->position_amount);
   CLOVE_SIZET_EQ(0, obj_info->normal_amount);
   CLOVE_SIZET_EQ(0, obj_info->uv_amount);
   CLOVE_SIZET_EQ(0, obj_info->vertex_amount);

   CLOVE_FLOAT_EQ(-1.000000f, obj_info->position_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(1.000000f, obj_info->position_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(0.000000f, obj_info->position_dynamic_array[0].z);

   CLOVE_FLOAT_EQ(1.000000f, obj_info->position_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(1.000000f, obj_info->position_dynamic_array[1].y);
   CLOVE_FLOAT_EQ(0.000000f, obj_info->position_dynamic_array[1].z);

   CLOVE_FLOAT_EQ(-1.000000f, obj_info->position_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(-1.000000f, obj_info->position_dynamic_array[2].y);
   CLOVE_FLOAT_EQ(0.000000f, obj_info->position_dynamic_array[2].z);

   CLOVE_FLOAT_EQ(1.000000f, obj_info->position_dynamic_array[3].x);
   CLOVE_FLOAT_EQ(-1.000000f, obj_info->position_dynamic_array[3].y);
   CLOVE_FLOAT_EQ(0.000000f, obj_info->position_dynamic_array[3].z);

   __obj_info_free(obj_info);

   __obj_file_close(file);
}

CLOVE_TEST(SaveNormalInfo)
{
   FILE* file = __obj_file_open("bin\\test\\resources\\quad.obj");
   obj_info_t* obj_info = __obj_info_new();
   char buffer[1024];

   while(fgets(buffer, sizeof(buffer), file))
   {
      if (strncmp(buffer, "vn ", 3) == 0)
      {
         int error = __obj_save_normal_info(obj_info, buffer);
         CLOVE_SIZET_EQ(0, error);
      }
   }

   CLOVE_NULL(obj_info->position_dynamic_array);
   CLOVE_NOT_NULL(obj_info->normal_dynamic_array);
   CLOVE_NULL(obj_info->uv_dynamic_array);
   CLOVE_NULL(obj_info->vertex_dynamic_array);

   CLOVE_SIZET_EQ(0, obj_info->position_amount);
   CLOVE_SIZET_EQ(1, obj_info->normal_amount);
   CLOVE_SIZET_EQ(0, obj_info->uv_amount);
   CLOVE_SIZET_EQ(0, obj_info->vertex_amount);

   CLOVE_FLOAT_EQ(0.000000f, obj_info->normal_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(0.000000f, obj_info->normal_dynamic_array[0].y);
   CLOVE_FLOAT_EQ(1.000000f, obj_info->normal_dynamic_array[0].z);

   __obj_info_free(obj_info);

   __obj_file_close(file);
}

CLOVE_TEST(SaveUvInfo)
{
   FILE* file = __obj_file_open("bin\\test\\resources\\quad.obj");
   obj_info_t* obj_info = __obj_info_new();
   char buffer[1024];

   while(fgets(buffer, sizeof(buffer), file))
   {
      if (strncmp(buffer, "vt ", 3) == 0)
      {
         int error = __obj_save_uv_info(obj_info, buffer);
         CLOVE_SIZET_EQ(0, error);
      }
   }

   CLOVE_NULL(obj_info->position_dynamic_array);
   CLOVE_NULL(obj_info->normal_dynamic_array);
   CLOVE_NOT_NULL(obj_info->uv_dynamic_array);
   CLOVE_NULL(obj_info->vertex_dynamic_array);

   CLOVE_SIZET_EQ(0, obj_info->position_amount);
   CLOVE_SIZET_EQ(0, obj_info->normal_amount);
   CLOVE_SIZET_EQ(4, obj_info->uv_amount);
   CLOVE_SIZET_EQ(0, obj_info->vertex_amount);

   CLOVE_FLOAT_EQ(1.000000f, obj_info->uv_dynamic_array[0].x);
   CLOVE_FLOAT_EQ(1.000000f, obj_info->uv_dynamic_array[0].y);

   CLOVE_FLOAT_EQ(0.000000f, obj_info->uv_dynamic_array[1].x);
   CLOVE_FLOAT_EQ(1.000000f, obj_info->uv_dynamic_array[1].y);

   CLOVE_FLOAT_EQ(0.000000f, obj_info->uv_dynamic_array[2].x);
   CLOVE_FLOAT_EQ(0.000000f, obj_info->uv_dynamic_array[2].y);

   CLOVE_FLOAT_EQ(1.000000f, obj_info->uv_dynamic_array[3].x);
   CLOVE_FLOAT_EQ(0.000000f, obj_info->uv_dynamic_array[3].y);

   __obj_info_free(obj_info);

   __obj_file_close(file);
}

CLOVE_TEST(AddTwoVertices)
{
   obj_info_t* obj_info = __obj_info_new();

   const float position_x1 = 15.234f;
   const float position_y1 = 125.234f;
   const float position_z1 = 5.0f;

   const float position_x2 = 0.234f;
   const float position_y2 = 5.234f;
   const float position_z2 = 142.0f;

   const float normal_x1 = 0.0f;
   const float normal_y1 = 2.123f;
   const float normal_z1 = 74.125f;

   const float normal_x2 = 7343.0f;
   const float normal_y2 = 0.1353f;
   const float normal_z2 = 7.1225f;

   const float uv_x1 = 123.124f;
   const float uv_y1 = 234.312f;
   const float uv_z1 = 194.8942f;

   const float uv_x2 = 452.134f;
   const float uv_y2 = 4.2f;
   const float uv_z2 = 1.0f;

   const obj_float3_t position1 = (obj_float3_t){position_x1, position_y1, position_z1};
   const obj_float3_t position2 = (obj_float3_t){position_x2, position_y2, position_z2};
   const obj_float3_t normal1 = (obj_float3_t){normal_x1, normal_y1, normal_z1};
   const obj_float3_t normal2 = (obj_float3_t){normal_x2, normal_y2, normal_z2};
   const obj_float2_t uv1 = (obj_float2_t){uv_x1, uv_y1};
   const obj_float2_t uv2 = (obj_float2_t){uv_x2, uv_y2};

   obj_vertex_t vertex1;
   vertex1.position = position1;
   vertex1.normal = normal1;
   vertex1.uv = uv1;

   obj_vertex_t vertex2;
   vertex2.position = position2;
   vertex2.normal = normal2;
   vertex2.uv = uv2;

   int error1 = __obj_add_vertex(obj_info, vertex1);
   CLOVE_SIZET_EQ(0, error1);

   int error2 = __obj_add_vertex(obj_info, vertex2);
   CLOVE_SIZET_EQ(0, error2);

   CLOVE_SIZET_EQ(2, obj_info->vertex_amount);

   CLOVE_FLOAT_EQ(vertex1.position.x, obj_info->vertex_dynamic_array[0].position.x);
   CLOVE_FLOAT_EQ(vertex1.position.y, obj_info->vertex_dynamic_array[0].position.y);
   CLOVE_FLOAT_EQ(vertex1.position.z, obj_info->vertex_dynamic_array[0].position.z);
   CLOVE_FLOAT_EQ(vertex1.normal.x, obj_info->vertex_dynamic_array[0].normal.x);
   CLOVE_FLOAT_EQ(vertex1.normal.y, obj_info->vertex_dynamic_array[0].normal.y);
   CLOVE_FLOAT_EQ(vertex1.normal.z, obj_info->vertex_dynamic_array[0].normal.z);
   CLOVE_FLOAT_EQ(vertex1.uv.x, obj_info->vertex_dynamic_array[0].uv.x);
   CLOVE_FLOAT_EQ(vertex1.uv.y, obj_info->vertex_dynamic_array[0].uv.y);

   CLOVE_FLOAT_EQ(vertex2.position.x, obj_info->vertex_dynamic_array[1].position.x);
   CLOVE_FLOAT_EQ(vertex2.position.y, obj_info->vertex_dynamic_array[1].position.y);
   CLOVE_FLOAT_EQ(vertex2.position.z, obj_info->vertex_dynamic_array[1].position.z);
   CLOVE_FLOAT_EQ(vertex2.normal.x, obj_info->vertex_dynamic_array[1].normal.x);
   CLOVE_FLOAT_EQ(vertex2.normal.y, obj_info->vertex_dynamic_array[1].normal.y);
   CLOVE_FLOAT_EQ(vertex2.normal.z, obj_info->vertex_dynamic_array[1].normal.z);
   CLOVE_FLOAT_EQ(vertex2.uv.x, obj_info->vertex_dynamic_array[1].uv.x);
   CLOVE_FLOAT_EQ(vertex2.uv.y, obj_info->vertex_dynamic_array[1].uv.y);

   CLOVE_NULL(obj_info->position_dynamic_array);
   CLOVE_NULL(obj_info->normal_dynamic_array);
   CLOVE_NULL(obj_info->uv_dynamic_array);

   CLOVE_SIZET_EQ(0, obj_info->position_amount);
   CLOVE_SIZET_EQ(0, obj_info->normal_amount);
   CLOVE_SIZET_EQ(0, obj_info->uv_amount);

   __obj_info_free(obj_info);
}

CLOVE_TEST(SaveAllInfo)
{
   FILE* file = __obj_file_open("bin\\test\\resources\\quad.obj");
   obj_info_t* obj_info = __obj_info_new();
   char buffer[1024];

   while(fgets(buffer, sizeof(buffer), file))
   {
      if(!strncmp(buffer, "v ", 2))
      {
         int error = __obj_save_position_info(obj_info, buffer);
         CLOVE_SIZET_EQ(0, error);
      }

      if(!strncmp(buffer, "vt ", 3))
      {
         int error = __obj_save_uv_info(obj_info, buffer);
         CLOVE_SIZET_EQ(0, error);
      }

      if(!strncmp(buffer, "vn ", 3))
      {
         int error = __obj_save_normal_info(obj_info, buffer);
         CLOVE_SIZET_EQ(0, error);
      }

      if(!strncmp(buffer, "f ", 2))
      {
         int error = __obj_save_vertex_info(obj_info, buffer);
         CLOVE_SIZET_EQ(0, error);
      }
   }

   CLOVE_NOT_NULL(obj_info->position_dynamic_array);
   CLOVE_NOT_NULL(obj_info->normal_dynamic_array);
   CLOVE_NOT_NULL(obj_info->uv_dynamic_array);
   CLOVE_NOT_NULL(obj_info->vertex_dynamic_array);

   CLOVE_SIZET_EQ(4, obj_info->position_amount);
   CLOVE_SIZET_EQ(1, obj_info->normal_amount);
   CLOVE_SIZET_EQ(4, obj_info->uv_amount);
   CLOVE_SIZET_EQ(6, obj_info->vertex_amount);

   CLOVE_FLOAT_EQ(1.000000f, obj_info->vertex_dynamic_array[0].position.x);
   CLOVE_FLOAT_EQ(-1.000000f, obj_info->vertex_dynamic_array[0].position.y);
   CLOVE_FLOAT_EQ(0.000000f, obj_info->vertex_dynamic_array[0].position.z);

   CLOVE_FLOAT_EQ(0.000000f, obj_info->vertex_dynamic_array[5].normal.x);
   CLOVE_FLOAT_EQ(0.000000f, obj_info->vertex_dynamic_array[5].normal.y);
   CLOVE_FLOAT_EQ(1.000000f, obj_info->vertex_dynamic_array[5].normal.z);

   CLOVE_FLOAT_EQ(1.000000f, obj_info->vertex_dynamic_array[3].uv.x);
   CLOVE_FLOAT_EQ(1.000000f, obj_info->vertex_dynamic_array[3].uv.y);

   __obj_info_free(obj_info);

   __obj_file_close(file);
}

CLOVE_TEST(ObjInfoNew)
{
   obj_info_t* obj_info = __obj_info_new();
   CLOVE_NOT_NULL(obj_info);

   CLOVE_NULL(obj_info->position_dynamic_array);
   CLOVE_NULL(obj_info->normal_dynamic_array);
   CLOVE_NULL(obj_info->uv_dynamic_array);
   CLOVE_NULL(obj_info->vertex_dynamic_array);

   CLOVE_SIZET_EQ(0, obj_info->position_amount);
   CLOVE_SIZET_EQ(0, obj_info->normal_amount);
   CLOVE_SIZET_EQ(0, obj_info->uv_amount);
   CLOVE_SIZET_EQ(0, obj_info->vertex_amount);

   CLOVE_SIZET_EQ(10, obj_info->position_dynamic_array_capacity);
   CLOVE_SIZET_EQ(10, obj_info->normal_dynamic_array_capacity);
   CLOVE_SIZET_EQ(10, obj_info->uv_dynamic_array_capacity);
   CLOVE_SIZET_EQ(10, obj_info->vertex_dynamic_array_capacity);

   __obj_info_free(obj_info);
}

CLOVE_TEST(TriangleNew)
{
   const float position_x1 = 15.234f;
   const float position_y1 = 125.234f;
   const float position_z1 = 5.0f;

   const float position_x2 = 0.234f;
   const float position_y2 = 5.234f;
   const float position_z2 = 142.0f;

   const float position_x3 = 065.234f;
   const float position_y3 = 3565.234f;
   const float position_z3 = 1642.0645f;

   const float normal_x1 = 0.0f;
   const float normal_y1 = 2.123f;
   const float normal_z1 = 74.125f;

   const float normal_x2 = 7343.0f;
   const float normal_y2 = 0.1353f;
   const float normal_z2 = 7.1225f;

   const float normal_x3 = 3467343.0f;
   const float normal_y3 = 0.136453f;
   const float normal_z3 = 75437.1225f;

   const float uv_x1 = 123.124f;
   const float uv_y1 = 234.312f;
   const float uv_z1 = 194.8942f;

   const float uv_x2 = 452.134f;
   const float uv_y2 = 4.2f;
   const float uv_z2 = 1.0f;

   const float uv_x3 = 452.13434f;
   const float uv_y3 = 465.2352f;
   const float uv_z3 = 16.4620f;

   const obj_float3_t position1 = (obj_float3_t){position_x1, position_y1, position_z1};
   const obj_float3_t position2 = (obj_float3_t){position_x2, position_y2, position_z2};
   const obj_float3_t position3 = (obj_float3_t){position_x3, position_y3, position_z3};
   const obj_float3_t normal1 = (obj_float3_t){normal_x1, normal_y1, normal_z1};
   const obj_float3_t normal2 = (obj_float3_t){normal_x2, normal_y2, normal_z2};
   const obj_float3_t normal3 = (obj_float3_t){normal_x3, normal_y3, normal_z3};
   const obj_float2_t uv1 = (obj_float2_t){uv_x1, uv_y1};
   const obj_float2_t uv2 = (obj_float2_t){uv_x2, uv_y2};
   const obj_float2_t uv3 = (obj_float2_t){uv_x3, uv_y3};

   obj_vertex_t vertex1;
   vertex1.position = position1;
   vertex1.normal = normal1;
   vertex1.uv = uv1;

   obj_vertex_t vertex2;
   vertex2.position = position2;
   vertex2.normal = normal2;
   vertex2.uv = uv2;

   obj_vertex_t vertex3;
   vertex3.position = position3;
   vertex3.normal = normal3;
   vertex3.uv = uv3;

   obj_triangle_t triangle = (obj_triangle_t){vertex1, vertex2, vertex3};
   
   CLOVE_FLOAT_EQ(position1.x, triangle.v1.position.x);
   CLOVE_FLOAT_EQ(position2.y, triangle.v2.position.y);
   CLOVE_FLOAT_EQ(position3.z, triangle.v3.position.z);

   CLOVE_FLOAT_EQ(uv1.x, triangle.v1.uv.x);
   CLOVE_FLOAT_EQ(uv2.y, triangle.v2.uv.y);

   CLOVE_FLOAT_EQ(normal1.x, triangle.v1.normal.x);
   CLOVE_FLOAT_EQ(normal2.y, triangle.v2.normal.y);
   CLOVE_FLOAT_EQ(normal3.z, triangle.v3.normal.z);
}