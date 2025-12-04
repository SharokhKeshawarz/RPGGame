#include "main.h"

#define DEBUG 0
#define SF_INFINIT_FPS 0

typedef enum player_animation_e {
    ATTACK_1,
    ATTACK_2,
    ATTACK_3,
    DEATH,
    DEFEND,
    HURT,
    IDLE,
    JUMP,
    RUN,
    WALK,
    END
} player_animation_e;

typedef struct player_animation_s
{
    sfIntRect* frames;
    sfTexture* texture;
    int32_t frameCount;
    int32_t currentFrame;
    float frameTime;
    float lastFrameTime;
    int32_t left, top, width, height;
} player_animation_s;

typedef struct player_s {
    sfVector2f position;
    sfVector2f size;
    sfColor color;
    sfInt32 speed;
    sfTexture* texture;
    sfSprite* sprite;
    
    player_animation_s animations[END];
    player_animation_e currentAnimation;
} player_s;

player_s* player_init()
{
    player_s* player = malloc(sizeof(player_s));

    player->position = (sfVector2f){400.0f, 300.0f};
    player->size = (sfVector2f){84.0f, 84.0f};
    player->speed = 200.0f;

    player->texture = sfTexture_createFromFile("assets/player/IDLE.png", NULL);

    player->sprite = sfSprite_create();
    sfSprite_setScale(player->sprite, (sfVector2f){1.0f, 1.0f});
    sfSprite_setTexture(player->sprite, player->texture, sfTrue);
    sfSprite_setTextureRect(player->sprite, (sfIntRect){0, 0, 84, 84});
    sfSprite_setPosition(player->sprite, player->position);

    player->animations[IDLE].texture = sfTexture_createFromFile("assets/player/IDLE.png", NULL);
    player->animations[IDLE].frameCount = 7;
    player->animations[IDLE].currentFrame = 0;
    player->animations[IDLE].frameTime = 0.08f;
    player->animations[IDLE].left = 0;
    player->animations[IDLE].top = 0;
    player->animations[IDLE].width = 96;
    player->animations[IDLE].height = 84;

    player->animations[IDLE].frames = malloc(sizeof(sfIntRect) * player->animations[IDLE].frameCount);
    player->animations[IDLE].lastFrameTime = 0.0f;
    for (int i = 0; i < player->animations[IDLE].frameCount; i++) {
        player->animations[IDLE].frames[i] = (sfIntRect){
            96 * i,
            0,
            96,
            84
        };
    }

    player->animations[HURT].texture = sfTexture_createFromFile("assets/player/HURT.png", NULL);
    player->animations[HURT].frameCount = 4;
    player->animations[HURT].currentFrame = 0;
    player->animations[HURT].frameTime = 0.1f;
    player->animations[HURT].left = 0;
    player->animations[HURT].top = 0;
    player->animations[HURT].width = 96;
    player->animations[HURT].height = 84;

    player->animations[HURT].frames = malloc(sizeof(sfIntRect) * player->animations[HURT].frameCount);
    player->animations[HURT].lastFrameTime = 0.0f;
    for (int i = 0; i < player->animations[HURT].frameCount; i++) {
        player->animations[HURT].frames[i] = (sfIntRect){
            96 * i,
            0,
            96,
            84
        };
    }

    player->currentAnimation = IDLE;
    sfSprite_setTexture(player->sprite, player->animations[IDLE].texture, sfTrue);
    sfSprite_setTextureRect(player->sprite, player->animations[IDLE].frames[0]);

    return player;
}

void player_set_animation(player_s* player, player_animation_e animationType)
{
    if (player->currentAnimation != animationType) {
        player->currentAnimation = animationType;
        sfSprite_setTexture(player->sprite, player->animations[animationType].texture, sfTrue);
        sfSprite_setTextureRect(player->sprite, player->animations[animationType].frames[0]);
        player->animations[player->currentAnimation].currentFrame = 0;
        player->animations[player->currentAnimation].lastFrameTime = 0.0f;
    }
}

void player_update(player_s* player, float deltaTime)
{
    player_animation_s* anim = &player->animations[player->currentAnimation];

    anim->lastFrameTime += deltaTime;
    printf("Texture size = %d x %d\n", sfTexture_getSize(anim->texture).x, sfTexture_getSize(anim->texture).y);
    // Change frame
    if (anim->lastFrameTime >= anim->frameTime) {
        anim->lastFrameTime = 0.0f;
        anim->currentFrame++;

        if (anim->currentFrame >= anim->frameCount)
            anim->currentFrame = 0; // loop animation

        // Apply the animation frame to the sprite
        sfSprite_setTexture(player->sprite, anim->texture, sfTrue);
        sfSprite_setTextureRect(player->sprite, anim->frames[anim->currentFrame]);
    }

    // Update sprite position (optional)
    sfSprite_setPosition(player->sprite, player->position);
}

void player_draw(sfRenderWindow* window, player_s* player)
{
    sfRenderWindow_drawSprite(window, player->sprite, NULL);
}

void player_destroy(player_s* player)
{
    sfSprite_destroy(player->sprite);
    sfTexture_destroy(player->texture);
    free(player);
}

int main(void)
{
    sfRenderWindow* window = sfRenderWindow_create(
        (sfVideoMode){800, 600, 32},
        "Game",
        sfClose,
        NULL
    );
    sfRenderWindow_setFramerateLimit(window, SF_INFINIT_FPS);

    player_s* player = player_init();
    player_set_animation(player, HURT);
    sfClock* clock = sfClock_create();

    while (sfRenderWindow_isOpen(window)) {
        float deltaTime = sfTime_asSeconds(sfClock_restart(clock));

        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        player_update(player, deltaTime);

        sfRenderWindow_clear(window, sfBlack);
        
        player_draw(window, player);

        sfRenderWindow_display(window);
    }

    player_destroy(player);
    sfRenderWindow_destroy(window);

    return 0;
}
