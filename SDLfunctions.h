/*
 *  SDLfunctions.h
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 08.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */

#include "SDLincludes.h"

SDL_Surface* initSDL();

int testLoop(SDL_Surface *l_screen);

void quitSDL();

int updateGraphics(SDL_Surface *l_screen, int l_x, int l_y);

