#include "circles.h"
#include <math.h>

void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, uint32_t pixel)
{
  // if the first pixel in the screen is represented by (0,0) (which is in sdl)
  // remember that the beginning of the circle is not in the middle of the pixel
  // but to the left-top from it:
 
  double error = (double)-radius;
  double x = (double)radius -0.5;
  double y = (double)0.5;
  double cx = n_cx - 0.5;
  double cy = n_cy - 0.5;
 
  while (x >= y)
    {
      set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
      set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);
 
      if (x != 0)
        {
	  set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
	  set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }
 
      if (y != 0)
        {
	  set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
	  set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }
 
      if (x != 0 && y != 0)
        {
	  set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
	  set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }
 
      error += y;
      ++y;
      error += y;
 
      if (error >= 0)
        {
	  --x;
	  error -= x;
	  error -= x;
        }
    }
}

void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, uint32_t pixel)
{
  // Note that there is more to altering the bitrate of this 
  // method than just changing this value.  See how pixels are
  // altered at the following web page for tips:
  //   http://www.libsdl.org/intro.en/usingvideo.html
  static const int BPP = 4;
 
  double r = (double)radius, dy;
 
  for (dy = 1; dy <= r; dy += 1.0)
    {
      // This loop is unrolled a bit, only iterating through half of the
      // height of the circle.  The result is used to draw a scan line and
      // its mirror image below it.
 
      // The following formula has been simplified from our original.  We
      // are using half of the width of the circle because we are provided
      // with a center and we need left/right coordinates.
 
      double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
      int x = cx - dx;
 
      // Grab a pointer to the left-most pixel for each half of the circle
      uint8_t *target_pixel_a = (uint8_t *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
      uint8_t *target_pixel_b = (uint8_t *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
 
      for (; x <= cx + dx; x++)
        {
	  *(uint32_t *)target_pixel_a = pixel;
	  *(uint32_t *)target_pixel_b = pixel;
	  target_pixel_a += BPP;
	  target_pixel_b += BPP;
        }
    }
}
