#ifndef WINDOW_H
#define WINDOW_H

#include "main.h"

typedef struct {
    sfRenderWindow* window;
    sfEvent event;
    uint32_t width;
    uint32_t height;
    uint8_t bpp;
    char *title;
    bool is_open;
} window_t;

window_t *create_window(uint32_t width, uint32_t height, uint8_t bpp, char *title);
void destroy_window(window_t *window);
void clear(window_t *window, sfColor color);
void display(window_t *window);

#endif /* WINDOW_H */
