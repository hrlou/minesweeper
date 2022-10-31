#ifndef SESSION_H
#define SESSION_H

#include "game/field.h"
#include "event.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
	const char* name;
	uint32_t width, height;
	SDL_Window* window;
	SDL_Renderer* renderer;
	event_t event;
	field_t* field;
} session_t;

session_t* session_get();
void session_create(field_t*, const char*, uint32_t, uint32_t);
void session_init();
void session_input();
void session_draw();
void session_loop();
void session_cleanup();

#endif // SESSION_H