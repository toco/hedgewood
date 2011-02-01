/*
 *  popUp.h
 *  Hedgewood
 *
 *  Created by Tobias Conradi on 19.01.11.
 *  Copyright 2011 ProzProg TUHH 10/11 Gruppe 34 . All rights reserved.
 *
 */

#ifndef POPUP_H
#define POPUP_H
#ifndef SDLINCLUDES_H
#include "SDLincludes.h"
#endif
#include "SDLfunctions.h"
#include "structs.h"


#define BUTTON0 0
#define BUTTON1 1
#define POPUP_HEIGHT 200
#define POPUP_WIDTH 600

/*Used to display a PopUp-Message on "screen" with "text" and buttons with Titles, button1Title be NULL to display only one Button*/
/*button0 is right, button1 is on the left side of button 0*/
/*text has to be a string without \n or \t"*/
int popUp(SDL_Surface *screen, dataStore *data, char *text, char *button0Title, char *button1Title);

/*same as popUp but also inputText can be typed in by User*/
/*inputText pointer to string – inputLength maxStringLength */
int inputPopUp(SDL_Surface *screen, dataStore *data, char *text, char *inputText, int inputLenght, char *button0Title, char *button1Title);


int displayPopup(SDL_Surface *screen, dataStore *data, menuDataStore *menuData);
int popUpLoop(SDL_Surface *screen, dataStore *data, menuDataStore *menuData);


#endif