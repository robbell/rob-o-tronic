//
// Screen.cpp
//
// Screen class for setting up and using an SDL drawing surface.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 02/03/05
//

#include "Screen.h"

Screen::Screen(){
} // end constructor


Screen::~Screen(){

	if(screen){
		SDL_FreeSurface(screen); // frees sdl surface
		screen = NULL;
	}

} // end destructor


bool Screen::init(int w, int h, bool fullscreen, char *windowTitle){     

     SDL_ShowCursor(false);

     if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0 ){ // init SDL for video, audio and timers
          cout<<"Unable to initialize SDL: "<< SDL_GetError() <<"\n";
          return false;
     }

     atexit(SDL_Quit); // set SDL_Quit to be called when program termintates

     SDL_WM_SetCaption(windowTitle, NULL); // set window title

     if(fullscreen){ // create screen with fullscreen flag
          screen = SDL_SetVideoMode(w,h,32,SDL_SWSURFACE|SDL_FULLSCREEN|SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_ANYFORMAT);
     }
     else{
          screen = SDL_SetVideoMode(w,h,32,SDL_SWSURFACE|SDL_HWPALETTE|SDL_DOUBLEBUF|SDL_ANYFORMAT);
     }

     if ( screen == NULL ){
          cout<<"Unable to set "<< w << " x " << h << " video: " << SDL_GetError() <<"\n";
          return false;
     }

     return true;
     
} // end init


void Screen::flip(){

     SDL_Flip(screen); // flips the screen buffer

} // end flip


void Screen::clear(){

     SDL_FillRect(screen, NULL, 0); // fills screen to black

} // end clear
