#ifndef MGE_CIRCLES_H
#define MGE_CIRCLES_H

#include <linux/types.h>
#include <SDL/SDL.h>
#include "pixels.h"

void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, uint32_t pixel);

void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, uint32_t pixel);

#endif
