//
// Game.cpp
//
// Game class for creating screen and map objects and running though the game loop.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 23/03/05
//

#include "Game.h"

Game::Game(){
} // end constructor


Game::~Game(){
} // end destructor


bool Game::init(int newScreenWidth, int newScreenHeight, int newTileWidth, int newTileHeight, int newLevels){

     level = 1; // starting level
     levels = newLevels; // number of levels
     quit = false;
     screenWidth = newScreenWidth;
     screenHeight = newScreenHeight;
     tileWidth = newTileWidth;
     tileHeight = newTileHeight;

     if(!screen.init(screenWidth, screenHeight, 1, "The Adventures of Rob-o-tronic")) return false; // set up screen

     if(!player.init(336, 258, LEFT)) return false; // init player starting position and face
     
     waitScreen("menu.bmp"); // draw menu
     if(quit) return true;

     waitScreen("menu2.bmp"); // draw instructions
     if(quit) return true;

     while(level <= levels && !quit){ // while there are levels to be played

          if(!quit){   
               
               loadLevel();       
               loop(); // enter level game loop
               level++; // increment level number
               if(!quit) waitScreen("complete.bmp"); // show level completion screen

          }
     }

     if(!quit) waitScreen("finish.bmp"); // if all levels complete, show finish screen

     return true;

} // end init


void Game::waitScreen(const char *screenName){

     Sprite screenImage;
     char path[256];

     strcpy(path, "gfx/screens/"); // form filename path
     strcat(path, screenName);

     screenImage.init(path); // load menu image     

     Uint8 *keystates;
     keystates = SDL_GetKeyState(0);

     SDL_Event event;
     bool done = false;     

     while(!done){ // loop until enter is pressed          

          while(SDL_PollEvent(&event)){ // check for quit events

               switch(event.type){ 

				case SDL_QUIT:
                         quit = true;
					done = true;
				break;

				default:
				break;
			}
		}

          if(keystates[SDLK_RETURN]){ // if enter is pressed, break from loop
               done = true;
          }
          if(keystates[SDLK_ESCAPE]){ // if escape is pressed, break from loop, and exit
               quit = true;
               done = true;
          }

          screen.clear();
          screenImage.draw(0,0); // draw menu
          screen.flip();                    
     }

     delay(1000);

} // end waitScreen


void Game::loop(){
     
     Uint8 *keystates;
     SDL_Event event;

     int frameTimer;
     int speed = 3;
     int step = 0;

     bool done = false;
     bool moving = false;

     int xMovement = tileWidth/(speed*2); // adjust movement amounts
     int yMovement = tileHeight/(speed*2);

     keystates = SDL_GetKeyState(0);

     map.draw(player); // initially draw player to get coordinates from map

     while(!done){
          
          frameTimer = SDL_GetTicks(); // get current time

          while(SDL_PollEvent(&event)){ // check for quit events

			switch(event.type){

				case SDL_QUIT:
					done = true;
				break;

				default:
				break;
			}
		}

          if(keystates[SDLK_ESCAPE]){ // if escape is pressed, break from loop, and exit
               quit = true;
               done = true;
          }
          if(keystates[SDLK_RETURN]){ // if enter is pressed, reload level
               loadLevel();
               moving = false;
          }
          
          if(!moving){ // if the player is not currently moving

               if(keystates[SDLK_UP]){ // if up key pressed
                    player.setDirection(UP); // set player direction
                    if(map.checkCell(player.getXCoord()-1, player.getYCoord())) moving = true; // check player can move in to tile
               }
               else if(keystates[SDLK_DOWN]){
                    player.setDirection(DOWN);
                    if(map.checkCell(player.getXCoord()+1, player.getYCoord())) moving = true;
               }
               else if(keystates[SDLK_LEFT]){
                    player.setDirection(LEFT);
                    if(map.checkCell(player.getXCoord(), player.getYCoord()+1)) moving = true;
               }
               else if(keystates[SDLK_RIGHT]){
                    player.setDirection(RIGHT);
                    if(map.checkCell(player.getXCoord(), player.getYCoord()-1)) moving = true;
               }

          }
          else{ // if the player is moving

               if(step < speed){ // if the player hasnt completed moving in to a new tile
                    if(player.getDirection() == UP){ // move player in correct direction
                         map.moveX(xMovement);
                         map.moveY(yMovement);                    
                    }
                    else if(player.getDirection() == DOWN){
                         map.moveX(-xMovement);
                         map.moveY(-yMovement);                    
                    }
                    else if(player.getDirection() == LEFT){
                         map.moveX(xMovement);
                         map.moveY(-yMovement);                    
                    }
                    else if(player.getDirection() == RIGHT){
                         map.moveX(-xMovement);
                         map.moveY(yMovement);
                    }
                    step++; // increment step until player has reached tile
               }
               else{ // if player was moving, but reached tile
                    if(player.getDirection() == UP){

                         // check to see if he can carry on moving
                         if(map.checkCell(player.getXCoord()-1, player.getYCoord())) moving = true;
                         else moving = false; // if not, stop moving
                    }
                    else if(player.getDirection() == DOWN){

                         if(map.checkCell(player.getXCoord()+1, player.getYCoord())) moving = true;
                         else moving = false;                 
                    }
                    else if(player.getDirection() == LEFT){

                         if(map.checkCell(player.getXCoord(), player.getYCoord()+1)) moving = true;
                         else moving = false;              
                    }
                    else if(player.getDirection() == RIGHT){

                         if(map.checkCell(player.getXCoord(), player.getYCoord()-1)) moving = true;
                         else moving = false;
                    }
                    else{
                         moving = false;
                    }

                    step = 0; // reset step
               }
          }
          
          if(map.checkCell(player.getXCoord(), player.getYCoord()) == 2){ // if player has reached an exit
               done = true; // map complete
          }

          screen.clear(); 
          map.draw(player); // draw map and player
          screen.flip();

          while((SDL_GetTicks()-frameTimer) < 25); // wait until time has passed before moving to next frame
     }

} // end loop


bool Game::loadLevel(){

     map = Map(); // clear old map data
     char path[256];
     char levelString[50];
     
     strcpy(path, "data/maps/"); // form map path string
     sprintf(levelString, "%d", level);
     strcat(path, levelString);
     strcat(path, ".aam");

     if(!map.init(path, screenWidth, screenHeight, tileWidth, tileHeight)) return false; // load map

     return true;

} // end loadLevel


void Game::delay(int time){

     int frameTimer;

     frameTimer = SDL_GetTicks();
     while((SDL_GetTicks()-frameTimer) < time); // wait until time has passed

} // end delay

