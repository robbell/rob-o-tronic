//
// Tile.cpp
//
// Tile class for storing the attributes and sprite of a tile in a map.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 17/03/05
//

#include "Tile.h"

Tile::Tile(){
} // end constructor


Tile::~Tile(){
} // end destructor


bool Tile::init(const char *filename, int newPassable, int newTransparent, int mapTileHeight){

     passable = newPassable;
     transparent = newTransparent;
     
     if(transparent){ // if transparent, create a transparent sprite
          if(!image.init(filename, 255, 0, 255)) return false;
     }
     else{
          if(!image.init(filename)) return false;
     }

     heightOffset = image.height() - mapTileHeight; // adjust position, so taller tiles appear at the same level
     
     return true;
} // end init


bool Tile::draw(int x, int y){

     if(!image.draw(x, y-heightOffset)) return false; // draw image with height offset        

     return true;

} // end draw


bool Tile::isPassable(){

     if(passable){
          return true;
     }
     else{
          return false;
     }
}


bool Tile::isExit(){

     if(passable == 2){ // if tile is an exit
          return true;
     }
     else{
          return false;
     }
}
