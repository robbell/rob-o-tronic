//
// Player.cpp
//
// Player class, for storing player direction and coordinates.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 05/04/05
//

#include "Player.h"

Player::Player(){
} // end constructor


Player::~Player(){
} // end destructor


bool Player::init(int newXPos, int newYPos, Direction newDirection){
     
     xPos = newXPos;
     yPos = newYPos;
     face = newDirection;

     if(!up.init("gfx/player/up.bmp", 255, 0, 255)) return false; // init each face
     if(!down.init("gfx/player/down.bmp", 255, 0, 255)) return false;
     if(!left.init("gfx/player/left.bmp", 255, 0, 255)) return false;
     if(!right.init("gfx/player/right.bmp", 255, 0, 255)) return false;
     
     heightOffset = left.height(); // adjust for player image height
     widthOffset = left.width()/2; // horizontally center image
     
     return true;

} // end init


bool Player::draw(){

     // draw player according to the direction faced
     if(face == UP){
          if(up.draw(xPos-widthOffset, yPos-heightOffset)) return true;
     }
     else if(face == DOWN){
          if(down.draw(xPos-widthOffset, yPos-heightOffset)) return true;
     }
     else if(face == LEFT){
          if(left.draw(xPos-widthOffset, yPos-heightOffset)) return true;
     }
     else if(face == RIGHT){
          if(right.draw(xPos-widthOffset, yPos-heightOffset)) return true;
     }
     else{
          return false;
     }

     return false;

} // end draw


void Player::setDirection(Direction newDirection){

     face = newDirection;

} // end setDirection


Direction Player::getDirection(){

     return face;

} // end getDirection


int Player::getXPos(){

     return xPos;

} // end getXPos


int Player::getYPos(){

     return yPos;

} // end getYPos


void Player::setXCoord(int x){

     xCoord = x;

} // end setXCoord


void Player::setYCoord(int y){

     yCoord = y;

} // end setYCoord


int Player::getXCoord(){

     return xCoord;

} // end getXCoord


int Player::getYCoord(){

     return yCoord;

} // end getYCoord



