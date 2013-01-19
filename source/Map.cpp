//
// Map.cpp
//
// Map class for loading and drawing a map file.
//
// Author: Robert Bell <rob@kontent.co.uk>
// Date: 16/03/05
//

#include "Map.h"

Map::Map(){
     
     screenWidth = 0;
     screenHeight = 0;
     mapWidth = 0;
     mapHeight = 0;
     tileWidth = 0;
     tileHeight = 0;
     xOffset = 0;
     yOffset = 0;

} // end constructor


Map::~Map(){
} // end destructor


bool Map::init(char *mapName, int screenW, int screenH, int tileW, int tileH){

     screenWidth = screenW;
     screenHeight = screenH;
     tileWidth = tileW;
     tileHeight = tileH;

     ifstream mapFile(mapName); // open file stream

     if(!mapFile.is_open()){ // could not open file

          cout << "Unable to open Map " << mapName << "\n";
          mapFile.close();
          return false;

     }
     else{ // continue to read map

          cout << mapName << " loaded\n";

          mapFile >> mapWidth >> mapHeight >> xOffset >> yOffset; // read in mapsize and starting position

          xOffset = xOffset * (tileWidth/2); // calculate starting position based on tile sizes
          yOffset = yOffset * (tileHeight/2);

          map.resize(mapHeight); // adjust outer vector size to mapHeight

          int j = 0;
          
          
          for(vector< vector<Tile> >::iterator row = map.begin(); row != map.end(); ++row){ // go through each vector 

               row->resize(mapWidth); // resize inner vector to mapWidth

               for(int i = 0; i < mapWidth; i++){ // go through each tile in a row

                    char filename[256];
                    char path[256];
                    int passable, transparent;

                    mapFile >> filename >> passable >> transparent; // read tile filename and attributes
                    
                    strcpy(path, "gfx/tiles/"); // form filename path
                    strcat(path, filename); 

                    if(!map[j][i].init(path, passable, transparent, tileHeight)){ //create new tile current position

                         cout << "map reading error\n";
                         return false;
                    }
               }

               j++; // repeat for each column
          }

          cout << "graphics loaded\n";
          mapFile.close();

          return true;
     }
     
} // end init


bool Map::draw(Player& player){

     mapPlayer = player;

     playerScreenToCoord(); // calculate which tile the player is on

     for(int j = 0; j < mapHeight; j++){ // loop though the map
          for(int i = 0; i < mapWidth; i++){
               
               int tileX = ((tileWidth/2)*(i-j))+xOffset; // draw tiles with movement offset
               int tileY = ((tileHeight/2)*(i+j))+yOffset;
               
               if(tileX < (screenWidth+tileWidth) && tileX > (0-tileWidth)){ // only draw tiles if theyre on screen

                    if(tileY < (screenHeight+tileHeight) && tileY > (0-tileHeight)){
          
                         map[j][i].draw(tileX, tileY);

                         if(mapPlayer.getXCoord() == i && mapPlayer.getYCoord() == j){ // if player is on this tile, draw player

                              mapPlayer.draw();

                         }

                    }
               }

          }
     }

     player = mapPlayer;

     return true;
} // end draw


void Map::moveX(int distance){

     xOffset += distance;

} // end moveX


void Map::moveY(int distance){

     yOffset += distance;

} // end moveY


void Map::playerScreenToCoord(){

     int x = mapPlayer.getXPos() - (xOffset - (tileWidth/2)); // convert screen position to coordinate
     int y = mapPlayer.getYPos() - (yOffset); // adjust for tile offsets

     int xCoord = y + (x/2);
     int yCoord = y - (x/2);

     if(xCoord < 0) xCoord -= (tileWidth-1);
     if(yCoord < 0) yCoord -= (tileHeight-1);

     xCoord /= tileHeight;
     yCoord /= tileHeight;

     xCoord -= 1;
     yCoord += 1;     

     mapPlayer.setXCoord(xCoord); // set player coordinates for drawing
     mapPlayer.setYCoord(yCoord);

} // end playerScreenToCoord


int Map::checkCell(int x, int y){
     
     if(map[y][x].isExit()){ // if the cell type is an exit
          return 2;
     }
     else if(map[y][x].isPassable()){ // if the cell is passable
          return 1;
     }
     else{
          return 0;
     }
} // end checkCell