//
// Screen.h
//
// Screen class header for setting up and using an SDL drawing surface.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 02/03/05
//

#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
#include <iostream>

using namespace std;

class Screen{
     public:
          // Constructors
          Screen();

          // Destructors
          ~Screen();
          
          // Manipulators
          bool init(int w, int h, bool fullscreen, char *windowTitle);
          void flip();
          void clear();

     private:
          SDL_Surface *screen;
          
}; // end Screen

#endif // SCREEN_H