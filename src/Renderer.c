#include "Renderer.h"

renderer_s* renderer_create(int32_t width, int32_t height, int32_t bpp, char* title)
{
    renderer_s* renderer = malloc(sizeof(renderer_s));

    renderer->window = sfRenderWindow_create(
        (sfVideoMode){width, height, bpp},
        title,
        sfClose,
        NULL
    );
    sfRenderWindow_setFramerateLimit(renderer->window, 0);

    renderer->properties.width = width;
    renderer->properties.height = height;
    renderer->properties.title = strdup(title);
    renderer->properties.bpp = bpp;

    return renderer;
}

bool renderer_is_open(renderer_s* renderer)
{
    return sfRenderWindow_isOpen(renderer->window);
}

void renderer_clear(renderer_s* renderer, sfColor color)
{
    sfRenderWindow_clear(renderer->window, color);
}

void renderer_display(renderer_s* renderer)
{
    sfRenderWindow_display(renderer->window);
}

int32_t renderer_get_width(renderer_s* renderer)
{
    return renderer->properties.width;
}

int32_t renderer_get_height(renderer_s* renderer)
{
    return renderer->properties.height;
}

int32_t renderer_get_bpp(renderer_s* renderer)
{
    return renderer->properties.bpp;
}

char* renderer_get_title(renderer_s* renderer)
{
    return renderer->properties.title;
}

void renderer_destroy(renderer_s* renderer)
{
    free(renderer->properties.title);
    sfRenderWindow_destroy(renderer->window);
    free(renderer);
}
