//
// Sprite.cpp
//
// Sprite class for loading a bitmap to an SDL surface.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 02/03/05
//

#include "Sprite.h"

Sprite::Sprite(){

	image = NULL;
     rect.x = 0;
     rect.y = 0;
     rect.w = 0;
     rect.h = 0;

} // end constructor


Sprite::~Sprite(){

	if(image){
		SDL_FreeSurface(image); // frees sdl surface
		image = NULL;
	}

} // end destructor


bool Sprite::init(const char *filename){ // non transparent sprite

     SDL_Surface *temp;
     temp = SDL_LoadBMP(filename);

     if (temp == NULL) { // check image loaded
          cout<<"Could not load "<< filename << ": " << SDL_GetError() <<"\n";
          return false;
     }

     if((image = SDL_DisplayFormat(temp)) == NULL){ // check image converted to correct format
          cout<<"Could not convert "<< filename << ": " << SDL_GetError() <<"\n";
		return false;
	}

     SDL_FreeSurface(temp);

     rect.w = image->w;
     rect.h = image->h;

     return true;
} // end init


bool Sprite::init(const char *filename, Uint8 r, Uint8 g, Uint8 b){ // transparent sprite

     SDL_Surface *temp;
     temp = SDL_LoadBMP(filename);

     if(temp == NULL) { // check image loaded
          cout<<"Could not load "<< filename << ": " << SDL_GetError() <<"\n";
          return false;
     }

     if( SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, r, g, b)) < 0){ // check color key set for transparency
          cout<<"Could not set ColorKey for "<< filename << ": " << SDL_GetError() <<"\n";
		return false;
	}

     if((image = SDL_DisplayFormat(temp)) == NULL){ // check image converted to correct format
          cout<<"Could not convert "<< filename << ": " << SDL_GetError() <<"\n";
		return false;
	}

     SDL_FreeSurface(temp);

     rect.w = image->w;
     rect.h = image->h;

     return true;
} // end init


bool Sprite::draw(int x, int y){

     rect.x = x;
     rect.y = y;

     if(SDL_BlitSurface(image, NULL, SDL_GetVideoSurface(), &rect) < 0){ // attempt to draw sprite
		cout<<"BlitSurface error" << SDL_GetError() <<"\n";
		return false;
	}
     else{
          return true;
     }
} // end draw


int Sprite::width(){

     return rect.w;

} // end width


int Sprite::height(){

     return rect.h;

} // end height