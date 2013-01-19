//
// Player.h
//
// Player class header, for storing player direction and coordinates.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 05/04/05
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Sprite.h"

using namespace std;

enum Direction {UP, DOWN, LEFT, RIGHT};

class Player{
     public:
          // Constructors
          Player();

          // Destructors
          ~Player();
          
          // Manipulators
          bool init(int newXPos, int newYPos, Direction newDirection);
          bool draw();
          void setDirection(Direction newDirection);
          void setXCoord(int x);
          void setYCoord(int y);

          //Accessors
          int getXPos();
          int getYPos();
          int getXCoord();
          int getYCoord();
          Direction getDirection();

     private:
          Sprite up, down, left, right;
          int xPos, yPos, xCoord, yCoord, widthOffset, heightOffset;
          Direction face;
          
}; // end Player

#endif // PLAYER_H