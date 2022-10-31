#ifndef DEBUG_H
#define DEBUG_H

#include "game/cell.h"
#include "game/field.h"

#include <stdio.h>
#include <stdlib.h>

#define BOOL(x) x ? "true" : "false"

void debug_print_bits(char val);
void debug_print_cell(cell_t* cell);
void debug_print_field(field_t* field);
void debug_print_status(field_t* field);
void debug_get_input(field_t* field);
void debug_play_game(field_t* field);

#endif // DEBUG_H