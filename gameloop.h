


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pathfinding.h"
#include "SDLfunctions.h"
#include "SDLincludes.h"
#include "structs.h"
#include "graphicUpdate.h"
#include "highscore.h"


int gameloop(dataStore *ingame,SDL_Surface *screen);
void createRandomField(dataStore *data);
int calcHighscore(dataStore *data);