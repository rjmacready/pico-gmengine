//#include "scripts.h"
#include <ecl/ecl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define FAIL(msg)				\
  do { \
    fprintf(stderr, msg);			\
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

cl_object cl_load_font(cl_object fontname, cl_object size) {
  //  (void) fontname->string;
  char *c_fontname = (char*) fontname->string.self;
  int c_size = fix(size);
  printf("cl_load_font(%s, %d)\n", c_fontname, c_size);

  TTF_Font* font = TTF_OpenFont(c_fontname, c_size);
  if(NULL == font) {
    fprintf(stderr, "TTF Error: %s\n", TTF_GetError());
    FAIL("Error loading font");
  }
  return ecl_make_pointer(font);
}

cl_object cl_rendertext_solid(cl_object font, cl_object message, cl_object color) {
  TTF_Font* w_font = ecl_to_pointer(font);
  char* w_message = (char*) message->string.self;
  //int w_color = fix(color);
  SDL_Color w_color = {255, 255, 255};
  SDL_Surface* ret = TTF_RenderText_Solid(w_font, w_message, w_color);
  if(NULL == ret) {
    fprintf(stderr, "TTF Error: %s\n", TTF_GetError());
    FAIL("Error rendering message");
  }
  return ecl_make_pointer(ret);
}

cl_object cl_draw_circle(cl_object surface, 
		      cl_object x, cl_object y,
		      cl_object radius, cl_object color) 
{  
  SDL_Surface* screen = (SDL_Surface*)keyword_to_ptr(surface);
  if(NULL == screen)
    FAIL("draw_circle needs a surface!");
  
  int w_x = fix(x), w_y = fix(y), w_radius = fix(radius), w_color = fix(color); 

  draw_circle(screen, w_x, w_y, w_radius, w_color);
}

cl_object cl_get_color(cl_object r, cl_object g, cl_object b) {
  
  Uint32 color = SDL_MapRGB(screen->format, (Uint8)fix(r), (Uint8)fix(g), (Uint8)fix(b));
  return MAKE_FIXNUM(color);
} 

cl_object cl_draw_rect(cl_object d_surface, 
		       cl_object d_x, cl_object d_y,
		       cl_object d_w, cl_object d_h,
		       cl_object s_color) 
{
  int w_d_x = fix(d_x), w_d_y = fix(d_y), w_d_w = fix(d_w), w_d_h = fix(d_h);
  
  SDL_Surface* w_d_surface = (SDL_Surface*)keyword_to_ptr(d_surface);
  if(NULL == screen)
    FAIL("cl_draw_surface needs a surface!");
  
  SDL_Rect clip;
  clip.x = w_d_x;
  clip.y = w_d_y;
  clip.w = w_d_w;
  clip.h = w_d_h;
  
  SDL_FillRect(w_d_surface, &clip, (Uint32)fix(s_color));

  return MAKE_FIXNUM(1);
}

cl_object cl_draw_surface(cl_object d_surface, cl_object d_x, cl_object d_y,
			  cl_object s_surface, cl_object clip) {

  //  printf("cl_draw_surface\n");

  int w_d_x = fix(d_x), w_d_y = fix(d_y);
  
  SDL_Surface* w_d_surface = (SDL_Surface*)keyword_to_ptr(d_surface);
  if(NULL == screen)
    FAIL("cl_draw_surface needs a surface!");
  
  SDL_Surface* w_s_surface = ecl_to_pointer(s_surface);
  
  SDL_Rect offset;
  offset.x = w_d_x;
  offset.y = w_d_y;
  SDL_BlitSurface(w_s_surface, NULL, w_d_surface, &offset);

  return MAKE_FIXNUM(1);
}

cl_object cl_get_ticks() {
  return MAKE_FIXNUM(SDL_GetTicks());
}
 
int main(int argc, char **argv) {
  // init SDL stuff
  SDL_Event event;
  SDL_Init( SDL_INIT_EVERYTHING );

  TTF_Init();

  // init cl stuff
  cl_boot(argc, argv);

  extern void init_lib_MAIN_LISP(cl_object);
  ecl_init_module(NULL, init_lib_MAIN_LISP);

  // define C functions. mostly drawing stuff.
  DEFUN("draw-circle", cl_draw_circle, 5);
  DEFUN("load-font", cl_load_font, 2);
  DEFUN("rendertext-solid", cl_rendertext_solid, 3);
  DEFUN("draw-surface", cl_draw_surface, 5);
  DEFUN("get-ticks", cl_get_ticks, 0);
  DEFUN("get-color", cl_get_color, 3);
  DEFUN("draw-rect", cl_draw_rect, 6);

  // prepare cl stuff
  // * prepare a function-application to call on the game loop
  cl_object run_onupdate = c_string_to_object("(run-onupdate)");
  cl_object run_ondraw = c_string_to_object("(run-ondraw)");
  // * load scripts
  cl_safe_eval(c_string_to_object("(load-scripts)"), Cnil, Cnil);

  screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

  // create game instance and call game.on-startup
  cl_safe_eval(c_string_to_object("(init-game)"), Cnil, Cnil);
  //cl_funcall(2, c_string_to_object("init-game"), ecl_make_pointer(screen));

  //  int cont = 1;
  int frame = 0;  
  int start_ticks = -1;
  while(1) { // cont
    //start_ticks = SDL_GetTicks();
    
    while( SDL_PollEvent( &event ) ) {
      if(event.type == SDL_QUIT) {
	// quit immediatly
	//cont = 0;
	goto _end;
      }
    }

    ++frame;

    // TODO do events
    // ...
    
    // this is the game loop
    // loop through all game objects and exec stuff something ...
    cl_safe_eval(run_onupdate, Cnil, Cnil);


    // clear screen
    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

    // draw all stuff
    cl_safe_eval(run_ondraw, Cnil, Cnil);

    SDL_Flip( screen );

    // TODO do frame rate adjustments
    
  }

 _end:

  // do we really need to release stuff? fuck it
  //SDL_Quit();
  //cl_shutdown();
  return 0;
}
