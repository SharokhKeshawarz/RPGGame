#include "SFML/System.h"
#include "SFML/Graphics.h"
#include <stdbool.h>

// Enum to represent the different animation states
typedef enum {
    ANIM_IDLE,
    ANIM_RUNNING
} AnimationState;

// Structure to hold animation properties
typedef struct {
    int frameWidth;
    int frameHeight;
    int totalFrames;
    float frameTime;
    sfTexture* texture; // Texture specific to this animation
} Animation;

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
void switch_animation(sfSprite* sprite, AnimationState state, sfClock* clock, Animation* currentAnim) {
    if (state == ANIM_IDLE) {
        *currentAnim = (Animation){32, 32, 11, 0.1f, currentAnim->texture}; // Set to idle animation properties
        animate_sprite(sprite, *currentAnim, clock);
    } else if (state == ANIM_RUNNING) {
        *currentAnim = (Animation){32, 32, 6, 0.05f, currentAnim->texture}; // Set to running animation properties
        animate_sprite(sprite, *currentAnim, clock);
    }
}

int main() {
    // Create a video mode (window size)
    sfVideoMode mode = {640, 480, 32};

    // Create the window
    sfRenderWindow* window = sfRenderWindow_create(mode, "Idle and Running Animation", sfResize | sfClose, NULL);
    if (!window)
        return -1;

    // Load the sprite sheet textures for idle and running animations
    sfTexture* idleTexture = sfTexture_createFromFile("idle_spritesheet.png", NULL);
    sfTexture* runningTexture = sfTexture_createFromFile("running_spritesheet.png", NULL);
    
    if (!idleTexture || !runningTexture) {
        // Cleanup in case of failure
        if (idleTexture) sfTexture_destroy(idleTexture);
        if (runningTexture) sfTexture_destroy(runningTexture);
        return -1;
    }

    // Create the sprite
    sfSprite* sprite = sfSprite_create();
    sfSprite_setTexture(sprite, idleTexture, sfTrue); // Start with idle texture

    // Create a clock to handle the timing of the animation
    sfClock* clock = sfClock_create();
    AnimationState currentState = ANIM_IDLE; // Initially idle
    Animation currentAnim = {32, 32, 11, 0.1f, idleTexture}; // Idle animation properties

    // Define the initial frame rectangle (starts with idle animation)
    sfIntRect frameRect = {0, 0, 32, 32}; // First frame of 32x32 pixels
    sfSprite_setTextureRect(sprite, frameRect);

    // Main loop
    while (sfRenderWindow_isOpen(window)) {
        // Clear the window
        sfRenderWindow_clear(window, sfBlack);

        // Check keyboard input to update the animation state
        if (sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyLeft)) {
            currentState = ANIM_RUNNING; // Switch to running animation
            sfSprite_setTexture(sprite, runningTexture, sfTrue); // Change to running texture
            frameRect.top = 0; // Reset to the first frame of running animation
        } else {
            currentState = ANIM_IDLE; // Switch back to idle when no key is pressed
            sfSprite_setTexture(sprite, idleTexture, sfTrue); // Change to idle texture
            frameRect.top = 0;  // Reset to the first frame of idle animation
        }

        // Set the new frame rectangle position (for top row control based on animation)
        sfSprite_setTextureRect(sprite, frameRect);

        // Call the function to switch between animations based on the current state
        switch_animation(sprite, currentState, clock, &currentAnim);

        // Draw the sprite
        sfRenderWindow_drawSprite(window, sprite, NULL);

        // Display the contents of the window
        sfRenderWindow_display(window);
    }

    // Cleanup
    sfSprite_destroy(sprite);
    sfTexture_destroy(idleTexture);
    sfTexture_destroy(runningTexture);
    sfRenderWindow_destroy(window);
    sfClock_destroy(clock);

    return 0;
}
