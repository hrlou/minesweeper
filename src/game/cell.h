#ifndef LOGIC_CELL_H
#define LOGIC_CELL_H

#include <stdint.h>
#include <stdbool.h>

// Enum representing different states a cell can have in the game
typedef enum uint8_t {
	CELL_OPEN = 0x1,         // Cell is open
	CELL_MINE = 0x2,         // Cell contains a mine
	CELL_FLAG = 0x4,         // Cell is flagged (for potential mines)
	CELL_SUPERPOSITION = 0x8 // Cell has superposition (e.g., multiple states)
} cell_state_e;

// Structure representing a cell, which holds its coordinates (x, y) and its state
typedef struct {
    uint16_t x, y;   // Coordinates of the cell on the grid
    uint8_t state;   // Holds the state of the cell (e.g., open, mine, flagged, etc.)
} cell_t;


// void cell_set_state(cell_t*, bool, cell_state_e);

// Function to initialize a cell with coordinates (x, y)
cell_t* cell_init(uint16_t x, uint16_t y);

// Function to flip the state of a cell (e.g., flagging or unflagging)
bool cell_flip_state(cell_t*, cell_state_e);

// Function to check if a specific state is set for a cell
bool cell_get_state(cell_t*, cell_state_e);

// Function to set the number of mines surrounding a cell (used to store adjacent mines count)
void cell_set_around(cell_t*, uint8_t);

// Function to get the number of mines surrounding a cell
uint8_t cell_get_around(cell_t*);

#endif // LOGIC_CELL_H