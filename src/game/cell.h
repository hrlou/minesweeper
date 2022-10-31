#ifndef LOGIC_CELL_H
#define LOGIC_CELL_H

#include <stdint.h>
#include <stdbool.h>

// makes state self explanitory
typedef enum uint8_t {
	CELL_OPEN = 0x1,
	CELL_MINE = 0x2,
	CELL_FLAG = 0x4,
	CELL_SUPERPOSITION = 0x8
} cell_state_e;

typedef struct {
    uint16_t x, y;
    uint8_t state;    
} cell_t;

cell_t* cell_init(uint16_t, uint16_t);

// void cell_set_state(cell_t*, bool, cell_state_e);
bool cell_flip_state(cell_t*, cell_state_e);
bool cell_get_state(cell_t*, cell_state_e);

void cell_set_around(cell_t*, uint8_t);
uint8_t cell_get_around(cell_t*);

#endif // LOGIC_CELL_H