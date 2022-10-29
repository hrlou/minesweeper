#ifndef LOGIC_FIELD_H
#define LOGIC_FIELD_H

#include "cell.h"

#include <stdbool.h>

typedef struct {
	uint16_t width, height;
	uint32_t length;
	uint16_t mines;
	cell_t** cells;
	cell_t* last_cell;
	uint16_t cells_flagged, cells_open;
	bool has_started;
} field_t;

field_t* field_init();
void field_set_param(field_t*, uint16_t, uint16_t, uint16_t);
void field_reset(field_t*);
void field_start(field_t*, uint16_t, uint16_t);
void field_open_cell(field_t*, cell_t*);
void field_flag_cell(field_t*, cell_t*);
uint16_t field_flag_count(field_t*);
cell_t* field_get_cell(field_t*, uint16_t, uint16_t);
cell_t** field_get_around(field_t*, cell_t*);
void field_cleanup(field_t*);

bool field_is_won(field_t*);
bool field_is_failed(field_t*);

#endif // LOGIC_FIELD_H