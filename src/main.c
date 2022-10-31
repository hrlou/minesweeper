#include "game/cell.h"
#include "game/field.h"

#include "session.h"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	field_t* field = field_init();
	field_set_param(field, 9, 9, 10);
	field_reset(field);
	field_start(field, 1, 1);
	field_flag_cell(field, field_get_cell(field, 2, 1));
	session_create(field, "Minesweeper", 1280, 720);
	session_init();
	session_loop();
	session_cleanup();
	return 0;
}