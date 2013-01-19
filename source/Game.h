//
// Game.h
//
// Game class header for creating screen and map objects and running though the game loop.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 28/03/05
//

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>

#include "Screen.h"
#include "Map.h"
#include "Player.h"
#include "Sprite.h"

using namespace std;

class Game{
     public:
          // Constructors
          Game();

          // Destructors
          ~Game();
          
          // Manipulators
          bool init(int newScreenWidth, int newScreenHeight, int newTileWidth, int newTileHeight, int newLevels);
          void loop();
          void waitScreen(const char *screenName);
          bool loadLevel();
          void delay(int time);

     private:          
          Screen screen;
          Player player;
          Map map;
          bool quit;
          int screenWidth, screenHeight, tileWidth, tileHeight, levels, level;
          
}; // end Game

#endif // GAME_H