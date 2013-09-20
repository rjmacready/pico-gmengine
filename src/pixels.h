#ifndef MGE_PIXELS_H
#define MGE_PIXELS_H

#include <linux/types.h>
#include <SDL/SDL.h>

void set_pixel(SDL_Surface *surface, int x, int y, uint32_t pixel);

#endif
