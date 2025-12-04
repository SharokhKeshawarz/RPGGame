#include "Events.h"

events_s* events_init()
{
    events_s* events = malloc(sizeof(events_s));
    return events;
}

void events_destroy(events_s* events)
{
    free(events);
}
