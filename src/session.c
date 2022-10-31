#include "session.h"
#include "sprite.h"
#include "debug.h"

#include <stdlib.h>

session_t* g_s;

// FOR TESTING ONLINE
sprite_t* g_sprite;

void _session_draw_cell(cell_t* cell, uint16_t w, uint16_t h) {
	SDL_Rect pos;
	uint8_t serial = 0;
	if (cell_get_state(cell, CELL_MINE)) {
		serial = 2;
	} else if (cell_get_state(cell, CELL_FLAG)) {
		serial = 1;
	}
	// there is something wrong with open checking
	if (cell_get_state(cell, CELL_OPEN)) {
		serial = 15 - cell_get_around(cell);	
	}
	pos.w = w; pos.h = h; pos.x = w * cell->x; pos.y = h * cell->y;
	// printf("draw (%d, %d)\n", cell->x, cell->y);
	// printf("%d, %d, %d, %d", pos.w, pos.h, pos.x, pos.y);
	sprite_draw(g_sprite, &pos, 0, serial);

}

void _session_draw_field() {
	field_t* field = g_s->field;
	for (uint16_t y = 0; y < field->height; y++) {
		for (uint16_t x = 0; x < field->width; x++) {
			cell_t* cell = field_get_cell(field, x, y);
			_session_draw_cell(cell, 64, 64);
		}
	}
}

session_t* session_get() {
	return g_s;
}

void session_create(field_t* field, const char* name, uint32_t width, uint32_t height) {
	g_s = calloc(1, sizeof(session_t));
	g_s->field = field;
	g_s->name = name;
	g_s->width = width;
	g_s->height = height;
}


void session_init() {
	g_s->window = SDL_CreateWindow("Minesweeper", 100, 100, g_s->width, g_s->height, SDL_WINDOW_OPENGL);
	g_s->renderer = SDL_CreateRenderer(g_s->window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Init(SDL_INIT_VIDEO);

	g_sprite = sprite_init("assets/tiles.png", 1, 16);
}

void session_input() {
	SDL_Event e;
	if ( SDL_PollEvent(&e) ) {
		if (e.type == SDL_QUIT) {
			g_s->event.type = EVENT_BREAK;
			return;
		}
	}
	g_s->event.type = EVENT_CONTINUE;
	return;
}

void session_draw() {
	SDL_Rect pos;
	_session_draw_field();
	SDL_RenderPresent(g_s->renderer);
}

void session_loop() {
	for (;;) {
		session_input();
		if (g_s->event.type == EVENT_BREAK) {
			break;
		}
		SDL_RenderClear(g_s->renderer);
		session_draw();
		// _debug_get_input(g_s->field);
	}
}

void session_cleanup() {
	SDL_DestroyRenderer(g_s->renderer);
	SDL_DestroyWindow(g_s->window);
	SDL_Quit();
}