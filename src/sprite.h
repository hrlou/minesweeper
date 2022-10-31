#ifndef SPRITE_H
#define SPRITE_H

#include "session.h"

typedef struct {
    SDL_Rect clip;
    SDL_Texture* img;
} sprite_t;

sprite_t* sprite_init(const char* path, uint8_t rows, uint8_t columns);
void sprite_draw(sprite_t* s, SDL_Rect* pos, uint8_t x, uint8_t y);
void sprite_destroy(sprite_t*);

#endif // SPRITE_H