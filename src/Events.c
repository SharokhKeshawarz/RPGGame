#include "Events.h"

void close_event(window_t *window)
{
    if (window->event.key.code == sfKeyEscape) {
        if (window->is_open == true) {
            sfRenderWindow_close(window->window);
            window->is_open = !window->is_open;
        }
    }
}

void poll_events(window_t *window)
{
    while (sfRenderWindow_pollEvent(window->window, &window->event)) {
        close_event(window);
    }
}
