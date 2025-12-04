#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

typedef struct renderer_s {
    
    sfRenderWindow* window;

    struct properties {
        char* title;
        int width;
        int height;
        int bpp;
    } properties;

} renderer_s;

renderer_s* renderer_create(int32_t width, int32_t height, int32_t bpp, char* title);
bool renderer_is_open(renderer_s* renderer);
void renderer_clear(renderer_s* renderer, sfColor color);
void renderer_display(renderer_s* renderer);
int32_t renderer_get_width(renderer_s* renderer);
int32_t renderer_get_height(renderer_s* renderer);
int32_t renderer_get_bpp(renderer_s* renderer);
char* renderer_get_title(renderer_s* renderer);
void renderer_destroy(renderer_s* renderer);

#endif
