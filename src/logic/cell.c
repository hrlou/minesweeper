#include "cell.h"

#include <stdlib.h>

cell_t* cell_init(uint16_t x, uint16_t y) {
	cell_t* cell = calloc(1, sizeof(cell_t));
	cell->x = x;
	cell->y = y;
	cell->state = 0;
	return cell;
}

void cell_set_state(cell_t* cell, bool val, cell_state_e state) {
	if (val == true) {
		cell->state |= state;
	} else {
		cell->state &= ~state;
	}
}

bool cell_get_state(cell_t* cell, cell_state_e state) {
	return (bool)(cell->state & state);
}

void cell_set_around(cell_t* cell, uint8_t count) {
	cell->state |= count << 4;
}

uint8_t cell_get_around(cell_t* cell) {
	return (cell->state >> 4);
}