#include "sprite.h"
#include "session.h"

#include <stdlib.h>

sprite_t* sprite_init(const char* path, uint8_t rows, uint8_t columns) {
	session_t* g_s = session_get();
	sprite_t* s = calloc(1, sizeof(sprite_t));
	s->img = IMG_LoadTexture(g_s->renderer, path);
	SDL_QueryTexture(s->img, NULL, NULL, &s->clip.w, &s->clip.h);\
	// printf("%d, %d\n", s->clip.w, s->clip.h);
	s->clip.w /= rows;
	s->clip.h /= columns;
	// printf("%d, %d\n", s->clip.w, s->clip.h);
	return s;
}

void sprite_draw(sprite_t* s, SDL_Rect* pos, uint8_t x, uint8_t y) {
	session_t* g_s = session_get();
	SDL_Rect clip = s->clip;
	clip.x = x * s->clip.w;
    	clip.y = y * s->clip.h;
	// printf("%d, %d\n", clip.x, clip.y);
	SDL_RenderCopy(g_s->renderer, s->img, &clip, pos);
	// SDL_BlitSurface(s->img, &clip, g_s->window, pos);
	// SDL_Draw
}

void sprite_destroy(sprite_t* s) {
	SDL_DestroyTexture(s->img);
	free(s);
}