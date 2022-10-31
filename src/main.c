#include "game/cell.h"
#include "game/field.h"

#include "session.h"
#include "main.h"

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	field_t* field = field_init();
	field_set_param(field, 10, 10, 10);
	field_reset(field);
	session_create(field, "Minesweeper", 1280, 720);
	session_init();
	session_loop();
	session_cleanup();
	return 0;
}