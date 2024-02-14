#define CLOVE_SUITE_NAME ObjParserTest
#define OBJ_IMPLEMENTATION
#include "clove-unit.h"
#include "obj_parser.h"

CLOVE_TEST(ObjNew)
{
   obj_t* obj = _obj_new();
   CLOVE_NOT_NULL(obj);

   CLOVE_NULL(obj->triangles);

   CLOVE_SIZET_EQ(0, obj->triangle_amount);
   CLOVE_SIZET_EQ(0, obj->vertex_amount);
   CLOVE_SIZET_EQ(0, obj->position_amount);
   CLOVE_SIZET_EQ(0, obj->uv_amount);
   CLOVE_SIZET_EQ(0, obj->normal_amount);

   _obj_free(obj);
}

CLOVE_TEST(AddOneTriangle)
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

   obj_triangle_t triangle = _obj_triangle_new(vertex1, vertex2, vertex3);

   obj_t* obj = _obj_new();

   int error = _obj_add_triangle(obj, triangle);
   CLOVE_NOT_NULL(obj->triangles);
   CLOVE_SIZET_EQ(0, error);

   CLOVE_SIZET_EQ(1, obj->triangle_amount);

   CLOVE_FLOAT_EQ(position1.x, obj->triangles[0].v1.position.x);
   CLOVE_FLOAT_EQ(position2.y, obj->triangles[0].v2.position.y);
   CLOVE_FLOAT_EQ(position3.z, obj->triangles[0].v3.position.z);

   CLOVE_FLOAT_EQ(uv1.x, obj->triangles[0].v1.uv.x);
   CLOVE_FLOAT_EQ(uv2.y, obj->triangles[0].v2.uv.y);

   CLOVE_FLOAT_EQ(normal1.x, obj->triangles[0].v1.normal.x);
   CLOVE_FLOAT_EQ(normal2.y, obj->triangles[0].v2.normal.y);
   CLOVE_FLOAT_EQ(normal3.z, obj->triangles[0].v3.normal.z);

   _obj_free(obj);
}

CLOVE_TEST(ReadQuadObj)
{
   obj_t* obj = obj_parse("bin\\test\\resources\\quad.obj");
   CLOVE_NOT_NULL(obj);

   CLOVE_NOT_NULL(obj->triangles);
   CLOVE_SIZET_EQ(2, obj->triangle_amount);

   /********** FIRST TRIANGLE **********/

   //First triangle, first vertex, positions
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[0].v1.position.x);
   CLOVE_FLOAT_EQ(-1.0f, obj->triangles[0].v1.position.y);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v1.position.z);

   //First triangle, second vertex, positions
   CLOVE_FLOAT_EQ(-1.0f, obj->triangles[0].v2.position.x);
   CLOVE_FLOAT_EQ(-1.0f, obj->triangles[0].v2.position.y);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v2.position.z);

   //First triangle, third vertex, positions
   CLOVE_FLOAT_EQ(-1.0f, obj->triangles[0].v3.position.x);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[0].v3.position.y);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v3.position.z);

   //First triangle, first vertex, uvs
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[0].v1.uv.x);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v1.uv.y);

   //First triangle, second vertex, uvs
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v2.uv.x);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v2.uv.y);

   //First triangle, third vertex, uvs
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v3.uv.x);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[0].v3.uv.y);

   //First triangle, first vertex, normals
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v1.normal.x);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v1.normal.y);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[0].v1.normal.z);

   //First triangle, second vertex, normals
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v2.normal.x);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v2.normal.y);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[0].v2.normal.z);

   //First triangle, third vertex, normals
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v3.normal.x);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[0].v3.normal.y);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[0].v3.normal.z);

   /********** SECOND TRIANGLE **********/

   //Second triangle, first vertex, positions
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v1.position.x);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v1.position.y);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v1.position.z);

   //Second triangle, second vertex, positions
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v2.position.x);
   CLOVE_FLOAT_EQ(-1.0f, obj->triangles[1].v2.position.y);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v2.position.z);

   //Second triangle, third vertex, positions
   CLOVE_FLOAT_EQ(-1.0f, obj->triangles[1].v3.position.x);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v3.position.y);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v3.position.z);

   //Second triangle, first vertex, uvs
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v1.uv.x);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v1.uv.y);

   //Second triangle, second vertex, uvs
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v2.uv.x);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v2.uv.y);

   //Second triangle, third vertex, uvs
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v3.uv.x);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v3.uv.y);

   //Second triangle, first vertex, normals
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v1.normal.x);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v1.normal.y);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v1.normal.z);

   //Second triangle, second vertex, normals
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v2.normal.x);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v2.normal.y);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v2.normal.z);

   //Second triangle, third vertex, normals
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v3.normal.x);
   CLOVE_FLOAT_EQ(0.0f, obj->triangles[1].v3.normal.y);
   CLOVE_FLOAT_EQ(1.0f, obj->triangles[1].v3.normal.z);

   _obj_free(obj);
}

CLOVE_TEST(UpdateOtherCounters)
{
   const size_t vertex_amount = 13;
   const size_t position_amount = 5;
   const size_t uv_amount = 65;
   const size_t normal_amount = 12;

   obj_info_t* obj_info = _obj_info_new();
   obj_t* obj = _obj_new();

   obj_info->vertex_amount = vertex_amount;
   obj_info->position_amount = position_amount;
   obj_info->uv_amount = uv_amount;
   obj_info->normal_amount = normal_amount;

   _obj_update_other_counters(obj, obj_info);

   CLOVE_SIZET_EQ(vertex_amount, obj->vertex_amount);
   CLOVE_SIZET_EQ(position_amount, obj->position_amount);
   CLOVE_SIZET_EQ(uv_amount, obj->uv_amount);
   CLOVE_SIZET_EQ(normal_amount, obj->normal_amount);

   _obj_info_free(obj_info);
   _obj_free(obj);
}

CLOVE_TEST(CheckSuzanneCounters)
{
   obj_t* obj = obj_parse("bin\\test\\resources\\suzanne.obj");
   CLOVE_NOT_NULL(obj);

   CLOVE_NOT_NULL(obj->triangles);
   CLOVE_SIZET_EQ(968, obj->triangle_amount);

   CLOVE_SIZET_EQ(2904, obj->vertex_amount);
   CLOVE_SIZET_EQ(511, obj->position_amount);
   CLOVE_SIZET_EQ(590, obj->uv_amount);
   CLOVE_SIZET_EQ(507, obj->normal_amount);

   _obj_free(obj);
}

CLOVE_TEST(CheckStormtrooperCounters)
{
   obj_t* obj = obj_parse("bin\\test\\resources\\stormtrooper.obj");
   CLOVE_NOT_NULL(obj);

   CLOVE_NOT_NULL(obj->triangles);
   CLOVE_SIZET_EQ(6518, obj->triangle_amount);

   CLOVE_SIZET_EQ(19554, obj->vertex_amount);
   CLOVE_SIZET_EQ(3275, obj->position_amount);
   CLOVE_SIZET_EQ(4653, obj->uv_amount);
   CLOVE_SIZET_EQ(3275, obj->normal_amount);

   _obj_free(obj);
}