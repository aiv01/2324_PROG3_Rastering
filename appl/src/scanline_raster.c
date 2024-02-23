#include "scanline_raster.h"
#include "color.h"
#include <float.h>

static void _sort_by_y(vertex_t** op1, vertex_t** op2, vertex_t** op3) 
{   
    vertex_t* temp;
    if ( (*op1)->screen_pos->y > (*op2)->screen_pos->y) {
        temp = *op1;
        *op1 = *op2;
        *op2 = temp;
    }

    if ( (*op2)->screen_pos->y > (*op3)->screen_pos->y) {
        temp = *op2;
        *op2 = *op3;
        *op3 = temp;
    }

    if ( (*op1)->screen_pos->y > (*op2)->screen_pos->y) {
        temp = *op1;
        *op1 = *op2;
        *op2 = temp;
    }
}


static float _interpolate_scalar(float value_a, float value_b, float gradient) {
    return  value_a + (value_b - value_a) * gradient;         
}

static color_t _interpolate_color(color_t* color_a, color_t* color_b, float gradient) {
    color_t result;
    result.r = (unsigned char)_interpolate_scalar((float)color_a->r, (float)color_b->r, gradient);
    result.g = (unsigned char)_interpolate_scalar((float)color_a->g, (float)color_b->g, gradient);
    result.b = (unsigned char)_interpolate_scalar((float)color_a->b, (float)color_b->b, gradient);
    result.a = (unsigned char)_interpolate_scalar((float)color_a->a, (float)color_b->a, gradient);
    return result;
}

static void _interpolate_row(screen_t* screen, int y, vertex_t* left_edge_v1, vertex_t* left_edge_v2, vertex_t* right_edge_v1, vertex_t* right_edge_v2)
{
    vector2i_t* left_edge_p1 = left_edge_v1->screen_pos;
    vector2i_t* left_edge_p2 = left_edge_v2->screen_pos;

    vector2i_t* right_edge_p1 = right_edge_v1->screen_pos;
    vector2i_t* right_edge_p2 = right_edge_v2->screen_pos;

    float left_gradient_y = 1.f;
    if (left_edge_p1->y != left_edge_p2->y) 
    {
        left_gradient_y = (float)(y - left_edge_p1->y) / (float)(left_edge_p2->y - left_edge_p1->y);
    }

    float right_gradient_y = 1.f;
    if (right_edge_p1->y != right_edge_p2->y) 
    {
        right_gradient_y = (float)(y - right_edge_p1->y) / (float)(right_edge_p2->y - right_edge_p1->y);
    }

    int left_x = (int)_interpolate_scalar( (float)left_edge_p1->x, (float)left_edge_p2->x, left_gradient_y);
    int right_x = (int)_interpolate_scalar( (float)right_edge_p1->x, (float)right_edge_p2->x, right_gradient_y);

    float left_z = _interpolate_scalar(left_edge_v1->z_pos, left_edge_v2->z_pos, left_gradient_y);
    float right_z = _interpolate_scalar(right_edge_v1->z_pos, right_edge_v2->z_pos, right_gradient_y);

    color_t left_color = _interpolate_color(left_edge_v1->color, left_edge_v2->color, left_gradient_y);
    color_t right_color = _interpolate_color(right_edge_v1->color, right_edge_v2->color, right_gradient_y);

    for(int x = left_x; x <= right_x; ++x) 
    {
        float gradient_x = 1.f;
        if (left_x < right_x) 
        {
            gradient_x = (float)(x - left_x)/ (float)(right_x - left_x);
        }

        float sample_z = _interpolate_scalar(left_z, right_z, gradient_x);

        color_t sampled_color = _interpolate_color(&left_color, &right_color, gradient_x);

        screen_put_pixel_with_depth(screen, x, y, sample_z, sampled_color);
    }
}

void scanline_raster(screen_t* screen, vertex_t* v1, vertex_t* v2, vertex_t* v3) 
{
   
    _sort_by_y(&v1, &v2, &v3);

    vector2i_t* op1 = v1->screen_pos;
    vector2i_t* op2 = v2->screen_pos;
    vector2i_t* op3 = v3->screen_pos;

    //TODO: Understand default value to assign when Y on the divider are equal
    float inv_slope_p1p2 = (float)(op2->x - op1->x) / (float)(op2->y - op1->y);
    float inv_slope_p1p3 = (float)(op3->x - op1->x) / (float)(op3->y - op1->y);

    // <|
    if (inv_slope_p1p2 < inv_slope_p1p3) 
    {
        for(int y = op1->y; y <= op3->y; ++y) 
        {
            if (y < op2->y) //phase1: upper triangle: left: p1p2 right: p1p3
            {
                _interpolate_row(screen, y, v1, v2, v1, v3);
            } 
            else //phase2: lower triangle: left: p2p3 right: p1p3
            {
                _interpolate_row(screen, y, v2, v3, v1, v3);
            }
        }
    } 
    else // |>
    {
        for(int y = op1->y; y <= op3->y; ++y) 
        {
            if (y < op2->y) //phase1: upper triangle: left: p1p3 right: p1p2
            {
                _interpolate_row(screen, y, v1, v3, v1, v2);
            } 
            else //phase2: lower triangle: left: p1p3 right: p2p3
            {
                _interpolate_row(screen, y, v1, v3, v2, v3);
            }
        }
    }
}