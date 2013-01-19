//
// Tile.h
//
// Tile class header for storing the attributes and sprite of a tile in a map.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 17/03/05
//

#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "Sprite.h"

using namespace std;

class Tile{
     public:
          // Constructors
          Tile();

          // Destructors
          ~Tile();
          
          // Manipulators
          bool init(const char *filename, int newPassable, int newTransparent, int mapTileHeight);
          bool draw(int x, int y);

          // Accessors
          bool isPassable();
          bool isExit();

     private:
          Sprite image;
          int heightOffset;
          int passable, transparent;
          
}; // end Tile

#endif // TILE_H