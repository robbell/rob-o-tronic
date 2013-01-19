//
// Sprite.h
//
// Sprite class header for loading a bitmap to an SDL surface.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 02/03/05
//

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <iostream>

using namespace std;

class Sprite{
     public:
          // Constructors
          Sprite();

          // Destructors
          ~Sprite();
          
          // Manipulators
          bool init(const char *filename);
          bool init(const char *filename, Uint8 r, Uint8 g, Uint8 b);
          bool draw(int x, int y);

          // Accessors
          int width();
          int height();

     private:
          SDL_Surface *image;
          SDL_Rect rect;
          
}; // end Sprite

#endif // SPRITE_H