#include "field.h"
#include "random.h"

#include <stdio.h>
#include <stdlib.h>

#define FIELD_INDEX(FIELD, X, Y) X + FIELD->width * Y;
#define FIELD_X(FIELD, INDEX) INDEX % FIELD->width;
#define FIELD_Y(FIELD, INDEX) INDEX / FIELD->width;

void _field_cleanup_cells(field_t* field) {
	if (field->cells == NULL) {
		return;
	}
	for (uint32_t i = 0; i < field->length; i++) {
		free(field->cells[i]);
	}
	field->last_cell = NULL;
	free(field->cells);
}

void _cell_count_around(field_t* field, cell_t* cell) {
	cell_t** around = field_get_around(field, cell);
	cell_t** work = around;
	uint8_t count = 0;
	for (; *work; *work++) {
		cell_t* child = *work;
		if (cell_get_state(child, CELL_MINE)) {
			count++;
		}
	}
	cell_set_around(cell, count);
	free(around);
}

void _field_count_around(field_t* field) {
	for (uint32_t i = 0; i < field->length; i++) {
		cell_t* cell = field->cells[i];
		_cell_count_around(field, cell);
	}
}

void _field_place_mines(field_t* field, uint32_t start) {
	for (uint32_t i = 0; i < field->mines; i++) {
		uint32_t index = random_generate(field->length - 1);
		cell_t* cell = field->cells[index];
		if (index == start || cell_get_state(cell, CELL_MINE)) {
			i--;
		} else {
			// cell_set_state(cell, true, CELL_MINE);
			cell_flip_state(cell, CELL_MINE);
		}
	}
}

field_t* field_init() {
	field_t* field = calloc(1, sizeof(field_t));
	return field;
}

void field_set_param(field_t* field, uint16_t width, uint16_t height, uint16_t mines) {
	field->width = width;
	field->height = height;
	field->mines = mines;
	field->length = field->width * field->height;
}

void field_reset(field_t* field) {
	_field_cleanup_cells(field);
	field->cells = calloc(field->length, sizeof(cell_t*));
	field->has_started = false;
	field->cells_flagged = 0;
	field->cells_open = 0;

	for (uint32_t i = 0; i < field->length; i++) {
		uint16_t x = FIELD_X(field, i);
		uint16_t y = FIELD_Y(field, i);
		*(field->cells+i) = cell_init(x, y);
	}
}

void field_start(field_t* field, uint16_t x, uint16_t y) {
	if (field->has_started) {
		field_reset(field);
	}
	field->has_started = true;
	uint32_t index = FIELD_INDEX(field, x, y);
	_field_place_mines(field, index);
	_field_count_around(field);
	field_open_cell(field, field->cells[index]);
}

void field_open_cell(field_t* field, cell_t* cell) {
	if (cell_get_state(cell, CELL_OPEN) || field_is_won(field) || field_is_failed(field)) {
		return;
	} else if (!field->has_started) {
		field_start(field, cell->x, cell->y);
		return;
	}
	// cell_set_state(cell, true, CELL_OPEN);
	cell_flip_state(cell, CELL_OPEN);
	field->last_cell = cell;
	field->cells_open++;
	if (cell_get_state(cell, CELL_MINE) || cell_get_around(cell) > 0) {
		return;
	}
	cell_t** around = field_get_around(field, cell);
	cell_t** work = around;
	for (; *work; work++) {
		field_open_cell(field, *work);
	}
	free(around);
}

void field_flag_cell(field_t* field, cell_t* cell) {
	if (cell_get_state(cell, CELL_OPEN) || field_is_won(field) || field_is_failed(field)) {
		return;
	}
	if (!cell_get_state(cell, CELL_FLAG) && field_flag_count(field) == 0) {
		return;
	}
	field->cells_flagged += cell_flip_state(cell, CELL_FLAG) ? 1 : -1;

}

uint16_t field_flag_count(field_t* field) {
	return field->mines - field->cells_flagged;
}

cell_t* field_get_cell(field_t* field, uint16_t x, uint16_t y) {
	uint32_t index = FIELD_INDEX(field, x, y);
	if (x > field->width || y > field->height) {
		return NULL;
	}
	return field->cells[index];
}

cell_t** field_get_around(field_t* field, cell_t* centre) {
	cell_t** around = calloc(8, sizeof(cell_t*));
	uint8_t index = 0;

	for (int x_offset = -1; x_offset <= 1; x_offset++) {
            for (int y_offset = -1; y_offset <= 1; y_offset++) {
                // this is pretty annoying to explain if it's on multiple lines
                // so I've divided it into 3 different if statements
                // this skips the "parent" cell
                if (x_offset == 0 && y_offset == 0) {
                    continue;
                }
                // prevents going to the next row/column
                if ((centre->x + x_offset) == field->width || (centre->y + y_offset) == field->height) {
                    continue;
                }
                // prevents going to the previous row/column
                if (centre->x + x_offset < 0 || centre->y + y_offset < 0) {
                    continue;
                }
		// printf("(%d, %d)", centre->x + x_offset, centre->y + y_offset);
                cell_t* child = field_get_cell(field, centre->x + x_offset, centre->y + y_offset);
                // add child to the array
		around[index++] = child;
            }
        }
	return around;
}

bool field_is_won(field_t* field) {
	if ((field->length - field->cells_open) == field->mines) {
            return true;
        }
	return false;
}

bool field_is_failed(field_t* field) {
	for (uint32_t i = 0; i < field->length; i++) {
		cell_t* cell = field->cells[i];
		if (cell_get_state(cell, CELL_MINE) && cell_get_state(cell, CELL_OPEN)) {
			return true;
		}
	}
	return false;
}


void field_cleanup(field_t* field) {
	_field_cleanup_cells(field);
	free(field);
}