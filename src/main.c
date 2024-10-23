#include "main.h"
#include "Window.h"
#include "Events.h"
#include "Animation.h"


sfSprite *create_player(const char *texture_path)
{
    sfSprite *player = sfSprite_create();
    if (player == NULL) {
        PRINT_ERROR("Failed To Create Player Sprite");
        exit(EXIT_FAILURE);
    }
    sfTexture *texture = sfTexture_createFromFile(texture_path, NULL);
    if (texture == NULL) {
        PRINT_ERROR("Failed To Load Player Texture");
        exit(EXIT_FAILURE);
    }
    sfSprite_setTexture(player, texture, sfTrue);
    sfSprite_setTextureRect(player, (sfIntRect){0, 0, 32, 32});
    PRINT_SUCCESS("Create Player");
    return player;
}

int main(int argc, char const *argv[])
{
    window_t *window_manager = create_window(800, 600, 32, "RPG Game");        

    sfSprite *player = create_player("assets/player/idle.png");

    int framewidth = 32, frameHeight = 32;
    int totalFrames = 11;
    int currentFrame = 0;
    sfIntRect frameRect = {0, 0, 32, 32};
    AnimationState currentStat = ANIM_IDLE;

    sfClock *clock = sfClock_create();
    float frameTime = 0.1f;
    float timeSinceLastFrame = 0.0f;

    while (window_manager->is_open) {
        poll_events(window_manager);
        switch_animation(player, &currentStat, clock);

        clear(window_manager, sfBlack);
        sfRenderWindow_drawSprite(window_manager->window, player, NULL);
        display(window_manager);
    }

    destroy_window(window_manager);
    return 0;
}

