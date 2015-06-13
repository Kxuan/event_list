#pragma once
#include "../event_list.h"
#include <time.h>

typedef void (*ontime_callback) (void *mod_name, time_t time);
EVENT_LIST_PROTO(ontime, ontime_callback);
extern event_list_ontime_t el_ontime;

void time_init(void);
