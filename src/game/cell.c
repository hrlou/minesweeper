#include "cell.h"

#include <stdlib.h>

// Function to initialize a new cell with given x and y coordinates
cell_t* cell_init(uint16_t x, uint16_t y) {
	// Allocate memory for the new cell and set its coordinates and initial state to 0
	cell_t* cell = calloc(1, sizeof(cell_t));
	cell->x = x;
	cell->y = y;
	cell->state = 0;  // Default state is 0 (no flags, not open, not a mine)
	return cell;
}

/* 
void cell_set_state(cell_t* cell, bool val, cell_state_e state) {
	if (val == true) {
		cell->state |= state;  
	} else {
		cell->state &= ~state;
	}
} */

// Flip the state of a specific cell
bool cell_flip_state(cell_t* cell, cell_state_e state) {
	// Flip the given state using XOR (if state is present, it will be cleared, if absent, it will be set)
	cell->state ^= state;
	// Return true if the input state is set, otherwise false
	return !!(cell->state & state);
}

// Check if a specific state is set for a cell
bool cell_get_state(cell_t* cell, cell_state_e state) {
	// Return true if the given state is set, otherwise false
	return (bool)(cell->state & state);
}

// Set the number of mines surrounding a cell by encoding it in the cell's state
void cell_set_around(cell_t* cell, uint8_t count) {
	// Store the count of surrounding mines in the upper 4 bits of the state
	cell->state |= count << 4;
}

// Function to retrieve the number of surrounding mines encoded in the cell's state
uint8_t cell_get_around(cell_t* cell) {
	// Extract and return the number of surrounding mines from the upper 4 bits of the state
	return (cell->state >> 4);
}