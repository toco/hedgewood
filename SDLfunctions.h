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

//#define WINDOWWIDTH 800
//#define WINDOWHEIGTH 600
//#define WINDOWBPP 32

SDL_Surface* initSDL(dataStore *data);

//wechselt zwischen fullscreen und windows mode, return: mode nach umschalten
int toggleFullscreen(SDL_Surface *screen, int windowed);

void quitSDL();

SDL_Surface *load_image(char *filename );
void printdb(char *str);

TTF_Font *buttonFont(); /*requires  	TTF_CloseFont(font); after use*/
TTF_Font *arialFont(int size); /*requires  	TTF_CloseFont(font); after use*/

//draws button and ignores state
//return 0 on no errors – return 1 on errors
int drawButton (SDL_Surface *destinationSurface, myButton *button);
//draw button and if withState==1 it uses the state from myButton-struct
int drawButtonWithState (SDL_Surface *destinationSurface, myButton *button, int withState);
//returns 1 if button is clicked else 0
int isButtonClicked(myButton *button, int x, int y);


#endif
