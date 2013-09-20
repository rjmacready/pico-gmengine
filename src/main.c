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


int main(int argc, char **argv) {
  int cont = 1;
  // init cl stuff
  cl_boot(argc, argv);

  extern void init_lib_MAIN_LISP(cl_object);
  ecl_init_module(NULL, init_lib_MAIN_LISP);

  // prepare cl stuff
  // * prepare a function-application to call on the game loop
  cl_object run_onupdate = c_string_to_object("(run-onupdate)");
  // * load scripts
  cl_safe_eval(c_string_to_object("(load-scripts)"), Cnil, Cnil);

  // init SDL stuff
  SDL_Event event;  
  SDL_Surface* screen = NULL;
  SDL_Init( SDL_INIT_EVERYTHING );

  screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

  // create game instance and call game.on-startup
  cl_safe_eval(c_string_to_object("(init-game)"), Cnil, Cnil);
  
  while(cont) {
    while( SDL_PollEvent( &event ) ) {
      if(event.type == SDL_QUIT) {
        cont = 0;
      }
    }

    // this is the game loop
    // loop through all game objects and exec stuff something ...
    cl_safe_eval(run_onupdate, Cnil, Cnil);

    // draw all stuff
    

    SDL_Flip( screen );
  }

  // do we really need to release stuff? fuck it
  //SDL_Quit();
  //cl_shutdown();
  return 0;
}
