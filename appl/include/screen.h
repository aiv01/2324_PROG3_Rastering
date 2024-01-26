#ifndef SCREEN_H
#define SCREEN_H
#include "SDL.h"
#include "color.h"

typedef struct screen_t
{
    unsigned int width;
    unsigned int height;
    unsigned int channel_amount;
    unsigned int color_buffer_size;
    unsigned char* color_buffer;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} screen_t;

screen_t* screen_new(const unsigned int screen_width, const unsigned int screen_height, SDL_Renderer* renderer);
void screen_free(screen_t* screen);
void screen_put_pixel(screen_t* screen, const unsigned int x, const unsigned int y, color_t* color);
void screen_blit(screen_t* screen);
void screen_clear(screen_t* screen);

#endif //SCREEN_H