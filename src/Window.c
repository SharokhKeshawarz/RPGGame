#include "Window.h"

window_t *create_window(uint32_t width, uint32_t height, uint8_t bpp, char *title)
{
    window_t *window = malloc(sizeof(window_t));
    if (window == NULL) {
        PRINT_ERROR("Failed To Create Window Struct\n");
        exit(EXIT_FAILURE);
    }

    window->window = sfRenderWindow_create(
        (sfVideoMode){width, height, bpp},
        title,
        sfDefaultStyle,
        sfContextDefault
    );
    if (window->window == NULL) {
        PRINT_ERROR("Failed To Create Window\n");
        exit(EXIT_FAILURE);
    }

    window->width = width;
    window->height = height;
    window->bpp = bpp;
    window->is_open = true;
    window->title = (char *)malloc(strlen(title) * sizeof(char) + 1);
    if (title == NULL) {
        PRINT_ERROR("Failed To Malloc For Title\n");
        exit(EXIT_FAILURE);
    }
    strcpy(window->title, title);
    PRINT_SUCCESS("Created Window");
    return window;
}

void destroy_window(window_t *window)
{
    if (window == NULL) {
        PRINT_ERROR("Cannot Free A NULL Object: Window Struct");
        exit(EXIT_FAILURE);
    }
    if (window->title != NULL)
        free(window->title);
    if (window->window != NULL)
        sfRenderWindow_destroy(window->window);
    free(window);
    PRINT_SUCCESS("Freed Window");
}

void clear(window_t *window, sfColor color)
{
    sfRenderWindow_clear(window->window, color);
}

void display(window_t *window)
{
    sfRenderWindow_display(window->window);
}
