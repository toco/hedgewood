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

/* to try to add an new highscore just use this function*/
int addHighscore(SDL_Surface *screen ,dataStore *data, int points);



int sortHighscore(dataStore *data);
/*returns 1 if points are higher than the last rank in highscore*/
int inHighscore(dataStore *data, int points);
/*Displays the Highscore fullscreen*/
/*needs redraw when returned*/
int displayHighscore(SDL_Surface *screen, dataStore *data);



#endif

