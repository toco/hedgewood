/*
 *  about.h
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 10.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */
#ifndef ABOUT_H
#define ABOUT_H

#include <stdio.h>
#include "SDLincludes.h"
#include "SDLfunctions.h"
#include "structs.h"

int displayAbout(SDL_Surface *screen, dataStore *data);
int renderMultiLineText(TTF_Font *font, char text[][100],int lines, SDL_Color textColor, SDL_Surface *screen);


#endif