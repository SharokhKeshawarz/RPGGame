#include "Animation.h"

// Function to animate a sprite based on the current animation state
void animate_sprite(sfSprite* sprite, Animation anim, sfClock* clock) {
    static int currentFrame = 0;         // Keeps track of the current frame
    static float timeSinceLastFrame = 0; // Time since the last frame update
    sfIntRect frameRect = sfSprite_getTextureRect(sprite); // Get the current frame rect

    // Update the time since the last frame
    timeSinceLastFrame += sfTime_asSeconds(sfClock_getElapsedTime(clock));
    sfClock_restart(clock);

    // If enough time has passed, move to the next frame
    if (timeSinceLastFrame >= anim.frameTime) {
        currentFrame = (currentFrame + 1) % anim.totalFrames; // Loop through frames
        frameRect.left = currentFrame * anim.frameWidth;      // Update the texture rect to the next frame
        sfSprite_setTextureRect(sprite, frameRect);           // Apply the updated frame rect to the sprite

        // Reset the timer
        timeSinceLastFrame = 0.0f;
    }
}

// Function to switch between animations based on state
void switch_animation(sfSprite* sprite, AnimationState *state, sfClock* clock) {
    // Define different animations for idle and running
    Animation idleAnim = {32, 32, 11, 0.1f};     // Idle animation (11 frames, 32x32 size, 0.1s per frame)
    Animation runningAnim = {32, 32, 6, 0.05f};  // Running animation (6 frames, 32x32 size, 0.05s per frame)

    // Select the animation based on the current state
    if (state == ANIM_IDLE) {
        animate_sprite(sprite, idleAnim, clock);
    } else if (state == ANIM_RUNNING) {
        animate_sprite(sprite, runningAnim, clock);
    }
}
