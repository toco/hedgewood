/*
 *  menu.h
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 09.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */

#include "SDLfunctions.h"

int menuStart(SDL_Surface *screen);

void setupMenu(SDL_Surface *screen, struct menuDataStore *dataStore);

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);


int testLoop(SDL_Surface *screen, struct menuDataStore *dataStore);


