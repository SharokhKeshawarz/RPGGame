#include "Time.h"

global_time_s* global_time_init()
{
    global_time_s* global_time = malloc(sizeof(global_time_s));

    global_time->clock = sfClock_create();
    global_time->deltaTime = 0.0f;

    return global_time;
}

void global_time_update(global_time_s* global_time)
{
    global_time->deltaTime = sfTime_asSeconds(sfClock_restart(global_time->clock));
}

sfClock* global_time_get_clock(global_time_s* global_time)
{
    return global_time->clock;
}

float global_time_get_deltatime(global_time_s* global_time)
{
    return global_time->deltaTime;
}

void global_time_destroy(global_time_s *global_time)
{
    sfClock_destroy(global_time->clock);
    free(global_time);
}
