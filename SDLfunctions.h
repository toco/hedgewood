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


#define WINDOWWIDTH 800
#define WINDOWHEIGTH 600
#define WINDOWBPP 32

SDL_Surface* initSDL();

int toggleFullscreen(SDL_Surface *screen, int windowed);

void quitSDL();

SDL_Surface *load_image(char *filename );
void printdb(char *str);

TTF_Font *buttonFont();
/*requires  	TTF_CloseFont(font);*/
