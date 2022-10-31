#ifndef DEBUG_H
#define DEBUG_H

#include "game/cell.h"
#include "game/field.h"

#include <stdio.h>
#include <stdlib.h>

#define BOOL(x) x ? "true" : "false"

void _debug_print_bits(char val) {
	for (int i = 7; 0 <= i; i--) {
		if ((i + 1) % 4 == 0) {
			putchar(' ');
		}
		printf("%c", (val & (1 << i)) ? '1' : '0');
	}
	putchar('\n');
}

void _debug_print_cell(cell_t* cell) {
	char serial = 'X';
        serial = cell_get_state(cell, CELL_MINE) ? 'M' : serial;
        serial = cell_get_state(cell, CELL_FLAG) ? 'F' : serial; 
	if (cell_get_state(cell, CELL_OPEN)) {
		int around = cell_get_around(cell);
		serial = "_12345678"[around];
		serial = cell_get_state(cell, CELL_MINE) ? '!' : serial;
	}
	putchar(serial);
}

void _debug_print_field(field_t* field) {
	for (uint16_t y = 0; y < field->height; y++) {
		if (y == 0) {
			printf("   ");
			for (uint16_t x = 0; x < field->width; x++) {
				printf("%d ", x);
			}
			putchar('\n');
		}
		for (uint16_t x = 0; x < field->width; x++) {
			if (x == 0) {
				printf("%d  ", y);
			}
			cell_t* cell = field_get_cell(field, x, y);
			_debug_print_cell(cell);
			putchar(' ');
		}
		putchar('\n');
	}
	putchar('\n');
}

void _debug_print_status(field_t* field) {
	if (field_is_failed(field) || field_is_won(field)) {
		puts(field_is_won(field) ? "WON" : "FAILED");
	}
	printf("Flags: %2d\n", field_flag_count(field));
	putchar('\n');
}

void _debug_get_input(field_t* field) {
	char c;
	int x, y;
	printf("f/o (x, y): ");
	scanf("%c %d %d", &c, &x, &y);
	cell_t* cell = field_get_cell(field, x, y);
	if (c == 'f') {
		field_flag_cell(field, cell);
	} else {
		field_open_cell(field, cell);
	}
}

void _debug_play_game(field_t* field) {
	for (;;) {
		_debug_print_field(field);
		_debug_print_status(field);
		_debug_get_input(field);
		putchar('\n');
	} 
}

#endif // DEBUG_H