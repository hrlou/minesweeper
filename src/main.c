#include "game/cell.h"
#include "game/field.h"

#include "session.h"
#include "main.h"

#include "debug.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	uint16_t width, height, mines;
	uint16_t res_width, res_height;
} options_t;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

options_t console_options_dialog() {
	   int choice;
    options_t opt = {0, 0, 0, 800, 800};

    printf("Select Difficulty:\n");
    printf("1. Easy (9x9, 10 mines)\n");
    printf("2. Medium (16x16, 40 mines)\n");
    printf("3. Hard (30x30, 99 mines)\n");
    printf("4. Custom\n");
    printf("Enter choice (1-4): ");

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("Invalid input. Enter a number between 1 and 4: ");
        clear_input_buffer();
    }

    switch (choice) {
        case 1:
            opt.width = 9;
            opt.height = 9;
            opt.mines = 10;
            break;
        case 2:
            opt.width = 16;
            opt.height = 16;
            opt.mines = 40;
            break;
        case 3:
            opt.width = 30;
            opt.height = 30;
            opt.mines = 99;
            break;
        case 4:
            printf("Enter custom width (min 5, max 50): ");
            while (scanf("%hu", &opt.width) != 1 || opt.width < 5 || opt.width > 50) {
                printf("Invalid width. Enter a number between 5 and 50: ");
                clear_input_buffer();
            }

            printf("Enter custom height (min 5, max 50): ");
            while (scanf("%hu", &opt.height) != 1 || opt.height < 5 || opt.height > 50) {
                printf("Invalid height. Enter a number between 5 and 50: ");
                clear_input_buffer();
            }

            uint16_t max_mines = (opt.width * opt.height) / 2;
            printf("Enter number of mines (min 1, max %hu): ", max_mines);
            while (scanf("%hu", &opt.mines) != 1 || opt.mines < 1 || opt.mines > max_mines) {
                printf("Invalid mine count. Enter a number between 1 and %hu: ", max_mines);
                clear_input_buffer();
            }
            break;
    }

	    printf("\nSelect Resolution:\n");
    printf("1. Low (600x600)\n");
    printf("2. Medium (800x800)\n");
    printf("3. High (1000x1000)\n");
    printf("4. Custom\n");
    printf("Enter choice (1-4): ");

    while (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("Invalid input. Enter a number between 1 and 4: ");
        clear_input_buffer();
    }

    return opt;
}

int main(int argc, char* argv[]) {
	field_t* field = field_init();
	options_t opt = console_options_dialog();
	field_set_param(field, opt.width, opt.height, opt.mines);
	field_reset(field);
	session_create(field, "Minesweeper: Press R to reset", opt.res_width, opt.res_height);
	session_init();
	session_loop();
	session_cleanup();
	return 0;
}