//#include "scripts.h"
#include <ecl/ecl.h>
#include <SDL/SDL.h>

#define FAIL(msg) \
  do { \
  fprintf(stderr, msg); \
  exit(1); \
  } while(0)

/*cl_object blit_surface(cl_object source, 
		       cl_object source_offset, 
		       cl_object destination,
		       cl_object destination_offset) 
{
  if(! Null(source_offset)) {
    FAIL("source_offset not supported!");
  }

  if(! Null(destination_offset)) {
    FAIL("destination_offset not supported!");
  }

  SDL_BlitSurface(source, NULL, destination, NULL);
  
  return ECL_T;
  }*/

#define DEFUN(name,fun,args) \
 cl_def_c_function(c_string_to_object(name), \
   (cl_objectfn_fixed)fun, \
		   args)

SDL_Surface* screen = NULL;

void* keyword_to_ptr(cl_object kw) {
  if(cl_equal(c_string_to_object(":SCREEN"), kw)) {
    return (void*)screen;
  }
  return NULL;
}

cl_object cl_draw_circle(cl_object surface, 
		      cl_object x, cl_object y,
		      cl_object radius, cl_object color) 
{  
  SDL_Surface* screen = (SDL_Surface*)keyword_to_ptr(surface);
  if(NULL == screen)
    FAIL("draw_circle needs a surface!");
  
  int w_x = fix(x), w_y = fix(y), w_radius = fix(radius), w_color = fix(color); 

  printf("%d %d\n", w_x, w_y);
  draw_circle(screen, w_x, w_y, w_radius, w_color);  
  printf(".\n");
}

int main(int argc, char **argv) {
  int cont = 1;
  // init cl stuff
  cl_boot(argc, argv);

  extern void init_lib_MAIN_LISP(cl_object);
  ecl_init_module(NULL, init_lib_MAIN_LISP);

  // define C functions. mostly drawing stuff.
  DEFUN("draw-circle", cl_draw_circle, 5);

  // prepare cl stuff
  // * prepare a function-application to call on the game loop
  cl_object run_onupdate = c_string_to_object("(run-onupdate)");
  cl_object run_ondraw = c_string_to_object("(run-ondraw)");
  // * load scripts
  cl_safe_eval(c_string_to_object("(load-scripts)"), Cnil, Cnil);

  // init SDL stuff
  SDL_Event event;
  SDL_Init( SDL_INIT_EVERYTHING );

  screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

  // create game instance and call game.on-startup
  cl_safe_eval(c_string_to_object("(init-game)"), Cnil, Cnil);
  //cl_funcall(2, c_string_to_object("init-game"), ecl_make_pointer(screen));

  int frame = 0;  
  int start_ticks = -1;
  while(cont) {
    //start_ticks = SDL_GetTicks();
    
    while( SDL_PollEvent( &event ) ) {
      if(event.type == SDL_QUIT) {
        cont = 0;
      }
    }

    ++frame;

    // this is the game loop
    // loop through all game objects and exec stuff something ...
    cl_safe_eval(run_onupdate, Cnil, Cnil);

    // draw all stuff
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

    cl_safe_eval(run_ondraw, Cnil, Cnil);

    SDL_Flip( screen );

    //printf("%f\n", (float)frame / (float)SDL_GetTicks() * 1000);
  }

  // do we really need to release stuff? fuck it
  //SDL_Quit();
  //cl_shutdown();
  return 0;
}
