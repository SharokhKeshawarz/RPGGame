#include "main.h"
#include "Renderer.h"
#include "Time.h"
#include "Events.h"

typedef struct game_s {

    renderer_s* renderer;
    events_s* events;
    global_time_s* globalTime;

} game_s;

int main(void)
{
    game_s* game = malloc(sizeof(game_s));

    game->renderer = renderer_create(800, 600, 32, "Game");
    game->globalTime = global_time_init();
    game->events = events_init();

    while (renderer_is_open(game->renderer)) {
        global_time_update(game->globalTime);

        while (sfRenderWindow_pollEvent(game->renderer->window, &game->events->event)) {
            if (game->events->event.type == sfEvtClosed)
                sfRenderWindow_close(game->renderer->window);
        }

        renderer_clear(game->renderer, sfBlack);


        renderer_display(game->renderer);
    }

    events_destroy(game->events);
    global_time_destroy(game->globalTime);
    renderer_destroy(game->renderer);
    free(game);

    return 0;
}
