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


/**
 * called to display the about-screen
 * @param screen a SDL_Surface to draw on
 * @param data the gameData
 */

int displayAbout(SDL_Surface *screen, dataStore *data);

/**
 * draws multiline text on the screen
 * just call it with the points and checking and name-input will be done
 * @param font the font to draw with
 * @param text[][100] the array of textlines with max length 100
 * @param lines the number of lines
 * @param textColor the color of the text
 * @param screen a SDL_Surface to draw on
 */
int renderMultiLineText(TTF_Font *font, int xPos, int yPos, char text[][100],int lines, SDL_Color textColor, SDL_Surface *screen);


#endif