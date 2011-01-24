
#ifndef GRAPHICUPDATE_H
#define GRAPHICUPDATE_H
#include "SDLfunctions.h"
#include "pathfinding.h"
#include "ingameMenu.h"
#include <time.h>
#include "store.o"

int GraphicUpdate(SDL_Surface *l_screen,  dataStore *data);

 position *pixelToGrid(position *l_pos);
 position *gridToPixel( position *l_pos,dataStore *data);
void verticalScrollPos( dataStore *data);
int headPositionUpdate(dataStore *data,position *newPos);
void aStarPathPrint(dataStore *data,SDL_Surface *l_screen);
int storeLoop(SDL_Surface *screen, dataStore *data, menuDataStore *menuData)

#endif