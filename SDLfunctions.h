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

#ifndef SDLFUNCTIONS_H
#define SDLFUNCTIONS_H
#ifndef SDLINCLUDES_H
#include "SDLincludes.h"
#endif
#ifndef STRUCTS_H
#include "structs.h"
#endif


SDL_Surface* initSDL(dataStore *data);

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

int toggleFullscreen(SDL_Surface *screen, int windowed);

void quitSDL();

SDL_Surface *load_image(char *filename );
void printdb(char *str);

TTF_Font *buttonFont(); /*requires  	TTF_CloseFont(font); after use*/
TTF_Font *arialFont(int size); /*requires  	TTF_CloseFont(font); after use*/

int drawButton (SDL_Surface *destinationSurface, myButton *button);
int isButtonClicked(myButton *button, int x, int y);


#endif
