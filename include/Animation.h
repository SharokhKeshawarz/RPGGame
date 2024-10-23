#ifndef ANIMATION_H
#define ANIMATION_H

#include "main.h"

typedef enum {
    ANIM_IDLE,
    ANIM_RUNNING
} AnimationState;

typedef struct {
    int frameWidth;
    int frameHeight;
    int totalFrames;
    float frameTime;
} Animation;

void animate_sprite(sfSprite* sprite, Animation anim, sfClock* clock);
void switch_animation(sfSprite* sprite, AnimationState *state, sfClock* clock);

#endif /* ANIMATION_H */
