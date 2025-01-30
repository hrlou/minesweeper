#include "session.h"
#include "sprite.h"
#include "debug.h"

#include <stdlib.h>

#define BORDER_SIZE 20  // Global constant for border size

session_t* g_s;
sprite_t* g_cell_sprite; // FOR TESTING ONLY
uint16_t g_cell_size = 0; // Defines the pixel size of a tile on the board
uint16_t x_offset = 0; // Centering offset for X-axis
uint16_t y_offset = 0; // Centering offset for Y-axis

void _session_calculate_cell_size(void) {
    if (g_cell_size == 0) {
        uint16_t available_width = g_s->width - 2 * BORDER_SIZE;
        uint16_t available_height = g_s->height - 2 * BORDER_SIZE;
        uint16_t size_by_width = available_width / g_s->field->width;
        uint16_t size_by_height = available_height / g_s->field->height;

        g_cell_size = size_by_width < size_by_height ? size_by_width : size_by_height;

        // Calculate centering offset
        x_offset = (g_s->width - (g_cell_size * g_s->field->width)) / 2;
        y_offset = (g_s->height - (g_cell_size * g_s->field->height)) / 2;
    }
}

void _session_draw_cell(cell_t* cell, uint16_t w, uint16_t h) {
    SDL_Rect pos;
    uint8_t serial = 0;

    if (cell_get_state(cell, CELL_FLAG)) {
        serial = 1;
    } else if (cell_get_state(cell, CELL_SUPERPOSITION)) {
        serial = 15;
    } else if (cell_get_state(cell, CELL_OPEN)) {
        serial = 15 - cell_get_around(cell);
    }
    if (field_is_failed(g_s->field)) {
        if (cell_get_state(cell, CELL_MINE)) {
            serial = 5;
            if (cell_get_state(cell, CELL_OPEN)) {
                serial = 3;
            }
        }
    }

    // Adjust position using centering offset
    pos.w = w;
    pos.h = h;
    pos.x = x_offset + (w * cell->x);
    pos.y = y_offset + (h * cell->y);

    sprite_draw(g_cell_sprite, &pos, 0, serial);
}

void _session_draw_field() {
    field_t* field = g_s->field;
    for (uint16_t y = 0; y < field->height; y++) {
        for (uint16_t x = 0; x < field->width; x++) {
            cell_t* cell = field_get_cell(field, x, y);
            _session_draw_cell(cell, g_cell_size, g_cell_size);
        }
    }
}

void _session_handle_field(SDL_MouseButtonEvent* e, uint16_t x, uint16_t y) {
    field_t* field = g_s->field;
    if (field_is_failed(field) || field_is_won(field)) {
        return;
    }

    // Adjust for offset to correctly determine clicked cell
    int16_t field_x = (e->x - x_offset) / g_cell_size;
    int16_t field_y = (e->y - y_offset) / g_cell_size;

    if (field_x < 0 || field_y < 0 || field_x >= field->width || field_y >= field->height) {
        return; // Clicked outside the field
    }

    cell_t* cell = field_get_cell(g_s->field, field_x, field_y);
    if (e->button == SDL_BUTTON_LEFT) {
        if (cell_get_state(cell, CELL_OPEN) || cell_get_state(cell, CELL_FLAG)) {
            return;
        }
        if (e->state == SDL_RELEASED) {
            cell = field->last_cell;
            cell_flip_state(cell, CELL_SUPERPOSITION);
            field_open_cell(field, cell);
        } else {
            field->last_cell = cell;
            cell_flip_state(cell, CELL_SUPERPOSITION);
        }
    } else if (e->button == SDL_BUTTON_RIGHT) {
        if (e->state == SDL_RELEASED) {
            field_flag_cell(field, cell);
        }
    }
}

void _session_handle_mouse(SDL_MouseButtonEvent* e) {
    _session_handle_field(e, e->x, e->y);
}

void session_create(field_t* field, const char* name, uint32_t width, uint32_t height) {
    g_s = calloc(1, sizeof(session_t));
    g_s->field = field;
    g_s->name = name;
    g_s->width = width;
    g_s->height = height;
}

session_t* session_get() {
	return g_s;
}

void session_init() {
    _session_calculate_cell_size();
    g_s->window = SDL_CreateWindow("Minesweeper", 100, 100, g_s->width, g_s->height, SDL_WINDOW_OPENGL);
    g_s->renderer = SDL_CreateRenderer(g_s->window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Init(SDL_INIT_VIDEO);

    g_cell_sprite = sprite_init("./assets/sprite/tiles.png", 1, 16);
}

void session_input() {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            g_s->event.type = EVENT_BREAK;
            return;
        } else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
            _session_handle_mouse(&e.button);
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_r) {
                field_reset(g_s->field);
            }
        }
    }
    g_s->event.type = EVENT_CONTINUE;
}

void session_draw() {
    SDL_RenderClear(g_s->renderer);
    _session_draw_field();

    SDL_SetRenderDrawColor(g_s->renderer, 98, 98, 98, 255);
    SDL_RenderPresent(g_s->renderer);
}

void session_loop() {
    for (;;) {
        session_input();
        if (g_s->event.type == EVENT_BREAK) {
            break;
        }
        session_draw();
    }
}

void session_cleanup() {
    SDL_DestroyRenderer(g_s->renderer);
    SDL_DestroyWindow(g_s->window);
    SDL_Quit();
}
