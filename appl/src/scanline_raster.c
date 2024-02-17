#include "scanline_raster.h"
#include "color.h"

static void _sort_by_y(vector2i_t** op1, vector2i_t** op2, vector2i_t** op3) 
{   
    vector2i_t* temp;
    if ( (*op1)->y > (*op2)->y) {
        temp = *op1;
        *op1 = *op2;
        *op2 = temp;
    }

    if ( (*op2)->y > (*op3)->y) {
        temp = *op2;
        *op2 = *op3;
        *op3 = temp;
    }

    if ( (*op1)->y > (*op2)->y) {
        temp = *op1;
        *op1 = *op2;
        *op2 = temp;
    }
}

static float _interpolate_scalar(float value_a, float value_b, float gradient) {
    return  value_a + (value_b - value_a) * gradient;         
}

static void _interpolate_row(screen_t* screen, int y, vector2i_t* left_edge_p1, vector2i_t* left_edge_p2, vector2i_t* right_edge_p1, vector2i_t* right_edge_p2)
{
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

    for(int x = left_x; x <= right_x; ++x) 
    {
        color_t red = (color_t){(unsigned char)(255.f * left_gradient_y), (unsigned char)(255.f * right_gradient_y), 0, 255};
        screen_put_pixel(screen, x, y, red);
    }
}

void scanline_raster(screen_t* screen, vector2i_t p1, vector2i_t p2, vector2i_t p3) 
{
    vector2i_t* op1 = &p1;
    vector2i_t* op2 = &p2;
    vector2i_t* op3 = &p3;

    _sort_by_y(&op1, &op2, &op3);


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
                _interpolate_row(screen, y, op1, op2, op1, op3);
            } 
            else //phase1: lower triangle: left: p2p3 right: p1p3
            {
                _interpolate_row(screen, y, op2, op3, op1, op3);
            }
        }
    } 
    else // |>
    {
        for(int y = op1->y; y <= op3->y; ++y) 
        {
            if (y < op2->y) //phase1: upper triangle: left: p1p3 right: p1p2
            {
                _interpolate_row(screen, y, op1, op3, op1, op2);
            } 
            else //phase1: lower triangle: left: p1p3 right: p2p3
            {
                _interpolate_row(screen, y, op1, op3, op2, op3);
            }
        }
    }
}