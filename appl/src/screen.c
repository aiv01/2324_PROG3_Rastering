#include "screen.h"
#include <stdlib.h>
#include <string.h>

screen_t* screen_new(const unsigned int screen_width, const unsigned int screen_height, SDL_Renderer* renderer)
{
    screen_t* screen = (screen_t*)malloc(sizeof(screen_t));
    screen->width = screen_width;
    screen->height = screen_height;
    screen->channel_amount = 4;
    screen->color_buffer_size = screen->width * screen->height * screen->channel_amount;
    screen->color_buffer = (unsigned char*)malloc(screen->color_buffer_size);
    screen->renderer = renderer;
    screen->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, screen_width, screen_height);

    return screen;
}

void screen_free(screen_t* screen)
{
    SDL_DestroyTexture(screen->texture);
    free(screen->color_buffer);
    free(screen);
}

void screen_put_pixel(screen_t* screen, const unsigned int x, const unsigned int y, color_t* color)
{
    if(x < 0 || x >= screen->width) return;
    if(y < 0 || y >= screen->height) return;

    int index = (y * screen->width + x) * screen->channel_amount;
    screen->color_buffer[index + 0] = color->r;
    screen->color_buffer[index + 1] = color->g;
    screen->color_buffer[index + 2] = color->b;
    screen->color_buffer[index + 3] = color->a;
}

void screen_blit(screen_t* screen)
{
    SDL_UpdateTexture(screen->texture, NULL, screen->color_buffer, screen->width * screen->channel_amount);
    SDL_RenderCopy(screen->renderer, screen->texture, NULL, NULL);
}

void screen_clear(screen_t* screen)
{
    memset(screen->color_buffer, 0, screen->color_buffer_size);
}