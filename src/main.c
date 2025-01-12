#include "game/cell.h"
#include "game/field.h"

#include "session.h"
#include "main.h"

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	uint16_t width, height, mines;
} options_t;

options_t options_dialog() {
	options_t opt; 
	opt.width = 16;
	opt.height = 16;
	opt.mines = 24;
	return opt;
}

int main(int argc, char* argv[]) {
	field_t* field = field_init();
	options_t opt = options_dialog();
	field_set_param(field, opt.width, opt.height, opt.mines);
	field_reset(field);
	session_create(field, "Minesweeper", 1000, 1000);
	session_init();
	session_loop();
	session_cleanup();
	return 0;
}