/*
 *  highscore.h
 *  Hedgewood
 *
 *  Created by Tobias Conradi on 11.01.11.
 *  Copyright 2011 ProzProg TUHH 10/11 Gruppe 34 . All rights reserved.
 *
 */

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdio.h>
#include "SDLincludes.h"
#include "structs.h"
#include "SDLfunctions.h"
#include "hedgewoodIO.h"
#include "popUp.h"

/**
 * need to be called to add an Highscore
 * just call it with the points and checking and name-input will be done 
 * when returned the previous screen needs to redraw itself
 * @param screen a SDL_Surface to draw on
 * @param data the dataStore
 * @param the points the player achieved
 * @return 1 if the player was added highscore
 * @return 0 if the player is not in highscore
 */int addHighscore(SDL_Surface *screen ,dataStore *data, int points);

/**
 * displays the highscore on the surface screen
 * when return the previous screen needs to redraw itself
 * @param screen a SDL_Surface to draw on
 * @param data the dataStore
 * @return 0
 */
int displayHighscore(SDL_Surface *screen, dataStore *data);



#endif

