
#ifndef GRAPHICUPDATE_H
#define GRAPHICUPDATE_H
#include "SDLfunctions.h"
#include "pathfinding.h"
#include "ingameMenu.h"
#include <time.h>

int updateGraphics(SDL_Surface *l_screen,  dataStore *data);
void graphicLoop(SDL_Surface *l_screen, dataStore *data);
 position *pixelToGrid(position *l_pos);
 position *gridToPixel( position *l_pos,dataStore *data);
void verticalScrollPos( dataStore *data);
void headPositionUpdate(dataStore *data,position *newPos);
void aStarPathPrint(dataStore *data,SDL_Surface *l_screen);
#endif