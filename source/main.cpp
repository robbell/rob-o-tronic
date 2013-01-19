//
// main.cpp
//
// Main source file for isometric engine.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 02/03/05
//

#include "Game.h"

int main(int argc, char *argv[]){

     Game game;

     if(!game.init(640, 480, 84, 42, 4)) return 1; // init game with screen sizes, tile sizes and number of levels

     return 0;
}