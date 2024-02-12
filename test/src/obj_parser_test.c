#define CLOVE_SUITE_NAME ObjParserTest
#include "clove-unit.h"
#include "obj_parser.h"

CLOVE_TEST(ReadQuadObj)
{
   char *file_name = "bin\\test\\resources\\quad.obj";
   obj_t *obj_parse = obj_parser(file_name);

   CLOVE_NOT_NULL(obj_parse);
   CLOVE_INT_EQ(4, obj_parse->v_count);
   CLOVE_INT_EQ(4, obj_parse->vt_count);
   CLOVE_INT_EQ(1, obj_parse->vn_count);
   CLOVE_INT_EQ(2, obj_parse->f_count);

   // vertex tests
   CLOVE_FLOAT_EQ(-1.f, obj_parse->v[0].x);
   CLOVE_FLOAT_EQ(1.f, obj_parse->v[0].y);
   CLOVE_FLOAT_EQ(0.f, obj_parse->v[0].z);

   CLOVE_FLOAT_EQ(1.f, obj_parse->v[1].x);
   CLOVE_FLOAT_EQ(1.f, obj_parse->v[1].y);
   CLOVE_FLOAT_EQ(0.f, obj_parse->v[1].z);

   CLOVE_FLOAT_EQ(-1.f, obj_parse->v[2].x);
   CLOVE_FLOAT_EQ(-1.f, obj_parse->v[2].y);
   CLOVE_FLOAT_EQ(0.f, obj_parse->v[2].z);

   CLOVE_FLOAT_EQ(1.f, obj_parse->v[3].x);
   CLOVE_FLOAT_EQ(-1.f, obj_parse->v[3].y);
   CLOVE_FLOAT_EQ(0.f, obj_parse->v[3].z);

   // uv tests
   CLOVE_FLOAT_EQ(1.f, obj_parse->vt[0].x);
   CLOVE_FLOAT_EQ(1.f, obj_parse->vt[0].y);

   CLOVE_FLOAT_EQ(0.f, obj_parse->vt[1].x);
   CLOVE_FLOAT_EQ(1.f, obj_parse->vt[1].y);

   CLOVE_FLOAT_EQ(0.f, obj_parse->vt[2].x);
   CLOVE_FLOAT_EQ(0.f, obj_parse->vt[2].y);

   CLOVE_FLOAT_EQ(1.f, obj_parse->vt[3].x);
   CLOVE_FLOAT_EQ(0.f, obj_parse->vt[3].y);

   // normals tests
   CLOVE_FLOAT_EQ(0.f, obj_parse->vn[0].x);
   CLOVE_FLOAT_EQ(0.f, obj_parse->vn[0].y);
   CLOVE_FLOAT_EQ(1.f, obj_parse->vn[0].z);

   // info test
   CLOVE_NOT_NULL(obj_parse);
   CLOVE_INT_EQ(4, obj_parse->v_count);
   CLOVE_INT_EQ(4, obj_parse->vt_count);
   CLOVE_INT_EQ(1, obj_parse->vn_count);
   CLOVE_INT_EQ(2, obj_parse->f_count);

   // faces test

   // face 1
   CLOVE_INT_EQ(4, obj_parse->v_info[0].v_index);
   CLOVE_INT_EQ(4, obj_parse->v_info[0].vt_index);
   CLOVE_INT_EQ(1, obj_parse->v_info[0].vn_index);

   CLOVE_INT_EQ(3, obj_parse->v_info[1].v_index);
   CLOVE_INT_EQ(3, obj_parse->v_info[1].vt_index);
   CLOVE_INT_EQ(1, obj_parse->v_info[1].vn_index);

   CLOVE_INT_EQ(1, obj_parse->v_info[2].v_index);
   CLOVE_INT_EQ(2, obj_parse->v_info[2].vt_index);
   CLOVE_INT_EQ(1, obj_parse->v_info[2].vn_index);

   // face 2
   CLOVE_INT_EQ(2, obj_parse->v_info[3].v_index);
   CLOVE_INT_EQ(1, obj_parse->v_info[3].vt_index);
   CLOVE_INT_EQ(1, obj_parse->v_info[3].vn_index);

   CLOVE_INT_EQ(4, obj_parse->v_info[4].v_index);
   CLOVE_INT_EQ(4, obj_parse->v_info[4].vt_index);
   CLOVE_INT_EQ(1, obj_parse->v_info[4].vn_index);

   CLOVE_INT_EQ(1, obj_parse->v_info[5].v_index);
   CLOVE_INT_EQ(2, obj_parse->v_info[5].vt_index);
   CLOVE_INT_EQ(1, obj_parse->v_info[5].vn_index);
}

CLOVE_TEST(CheckSuzanneCounts)
{
   char *file_name = "bin\\test\\resources\\suzanne.obj";
   obj_t *obj_parse = obj_parser(file_name);

   CLOVE_NOT_NULL(obj_parse);
   CLOVE_INT_EQ(511, obj_parse->v_count);
   CLOVE_INT_EQ(590, obj_parse->vt_count);
   CLOVE_INT_EQ(507, obj_parse->vn_count);
   CLOVE_INT_EQ(968, obj_parse->f_count);
}

CLOVE_TEST(CheckObjCtor)
{
   char *file_name = "bin\\test\\resources\\quad.obj";
   obj_t *obj_quad = obj_parser(file_name);
   
   CLOVE_NOT_NULL(obj_quad);

   // Test: FACE 1
   // Test: Vertex 1
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[0].v1.position.x);
   CLOVE_FLOAT_EQ(-1, obj_quad->triangles[0].v1.position.y);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v1.position.z);

   CLOVE_FLOAT_EQ(1, obj_quad->triangles[0].v1.uv.x);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v1.uv.y);

   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v1.normal.x);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v1.normal.y);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[0].v1.normal.z);

   // Test: Vertex 2
   CLOVE_FLOAT_EQ(-1, obj_quad->triangles[0].v2.position.x);
   CLOVE_FLOAT_EQ(-1, obj_quad->triangles[0].v2.position.y);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v2.position.z);

   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v2.uv.x);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v2.uv.y);

   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v2.normal.x);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v2.normal.y);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[0].v2.normal.z);

   // Test: Vertex 3
   CLOVE_FLOAT_EQ(-1, obj_quad->triangles[0].v3.position.x);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[0].v3.position.y);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v3.position.z);

   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v3.uv.x);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[0].v3.uv.y);

   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v3.normal.x);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[0].v3.normal.y);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[0].v3.normal.z);

   // Test FACE 2
   // Test: Verte 1
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v1.position.x);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v1.position.y);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v1.position.z);

   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v1.uv.x);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v1.uv.y);

   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v1.normal.x);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v1.normal.y);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v1.normal.z);

   // Test: Vertex 2
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v2.position.x);
   CLOVE_FLOAT_EQ(-1, obj_quad->triangles[1].v2.position.y);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v2.position.z);

   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v2.uv.x);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v2.uv.y);

   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v2.normal.x);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v2.normal.y);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v2.normal.z);

   // Test: Vertex 3
   CLOVE_FLOAT_EQ(-1, obj_quad->triangles[1].v3.position.x);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v3.position.y);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v3.position.z);

   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v3.uv.x);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v3.uv.y);

   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v3.normal.x);
   CLOVE_FLOAT_EQ(0, obj_quad->triangles[1].v3.normal.y);
   CLOVE_FLOAT_EQ(1, obj_quad->triangles[1].v3.normal.z);

   obj_parser_destroy(obj_quad);
}
