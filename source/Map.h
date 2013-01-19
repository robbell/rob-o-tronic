//
// Map.h
//
// Map class header for loading and drawing a map file.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 10/03/05
//

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Tile.h"
#include "Player.h"

using namespace std;

class Map{
     public:
          // Constructors
          Map();

          // Destructors
          ~Map();
          
          // Manipulators
          bool init(char *mapName, int screenWidth, int screenHeight, int tileW, int tileH);
          bool draw(Player& player);
          void moveX(int distance);
          void moveY(int distance);
          void playerScreenToCoord();

          // Accessors
          int checkCell(int x, int y);

     private:
          int mapWidth, mapHeight, screenWidth, screenHeight, tileWidth, tileHeight, xOffset, yOffset;
          vector< vector<Tile> > map;
          Player mapPlayer;
          
}; // end Map

#endif // MAP_H