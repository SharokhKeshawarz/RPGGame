#pragma once
#ifndef _EVENTS_H_
#define _EVENTS_H_

#include "main.h"

typedef struct events_s {
    
    sfEvent event;

} events_s;

events_s* events_init();
void events_destroy(events_s* events);

#endif
