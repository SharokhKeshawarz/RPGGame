#pragma once
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

typedef struct global_time_s {

    sfClock* clock;
    float deltaTime;

} global_time_s;

global_time_s* global_time_init();
void global_time_update(global_time_s* global_time);
sfClock* global_time_get_clock(global_time_s* global_time);
float global_time_get_deltatime(global_time_s* global_time);
void global_time_destroy(global_time_s *global_time);

#endif
