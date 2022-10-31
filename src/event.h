#ifndef EVENT_H
#define EVENT_H

#include "game/cell.h"

typedef enum {
    EVENT_CONTINUE,
    EVENT_BREAK,
    EVENT_RESET,
    EVENT_OPEN,
    EVENT_FLAG
} event_e;

typedef struct {
    event_e type;
    cell_t* cell;
} event_t;

#endif // EVENT_H