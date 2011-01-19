/*
 *  popUp.c
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 19.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */

#include "popUp.h"

#include<stdio.h>

int popUp(SDL_Surface *screen, char *text, char *button0Title, char *button1Title)
{
#ifdef DEBUG
	printf("Display popUp with Message: \"%s\" buttons \"%s\" \"%s\"\n",text,button0Title,button1Title);
#endif
	int btnCount;
	if (button0Title==NULL||button1Title==NULL) {
		btnCount = 1;
	}
	else {
		btnCount = 2;
	}

	menuDataStore *menuData = malloc(sizeof(menuDataStore));
	menuData->buttons = malloc(sizeof(myButton)*btnCount);
	menuData->buttonCount = btnCount;
	myButton *buttons = menuData->buttons;
	
	char *rightBtn;
	
	/*background from 150 to 450 */
	if	(btnCount==1 && button1Title == NULL)
	{
		rightBtn = button0Title;
	}
	else if (btnCount ==1 && button0Title == NULL)
	{
		rightBtn = button1Title;
	
	}
	
	buttons[ BUTTON0 ].rect.w=BUTTONWIDTH;
	buttons[ BUTTON0 ].rect.h=BUTTONHEIGHT;
	buttons[ BUTTON0 ].rect.y=screen->clip_rect.h/2+POPUP_HEIGHT/2-buttons[BUTTON0].rect.h-25;
	buttons[ BUTTON0 ].rect.x=screen->clip_rect.w/2+POPUP_WIDTH/2-buttons[BUTTON0].rect.w-25;
	buttons[ BUTTON0 ].name=rightBtn;
	buttons[ BUTTON0 ].function=NULL;
	
	if (btnCount==2) {
		char *leftBtn;
		if (rightBtn==button0Title) {
			leftBtn = button1Title;
		}
		else {
			leftBtn = button0Title;
		}

		buttons[ BUTTON1 ].rect.w=BUTTONWIDTH;
		buttons[ BUTTON1 ].rect.h=BUTTONHEIGHT;
		buttons[ BUTTON1 ].rect.y=screen->clip_rect.h/2+POPUP_HEIGHT/2-buttons[BUTTON0].rect.h-25;
		buttons[ BUTTON1 ].rect.x=buttons[BUTTON0].rect.x-buttons[BUTTON1].rect.w-25;
		buttons[ BUTTON1 ].name=leftBtn;
		buttons[ BUTTON1 ].function=NULL;
		
	}
	
	displayPopup(screen, menuData, text);
	int retVal = popUpLoop(screen, menuData);
	
	free(menuData->buttons);
	free(menuData);
	return retVal;
}

int displayPopup(SDL_Surface *screen, menuDataStore *menuData, char *text)
{
	/*Background */
	int width = POPUP_WIDTH+2, height = POPUP_HEIGHT+2;
	SDL_Rect background = {screen->clip_rect.w/2-width/2,screen->clip_rect.h/2-height/2,width,height};
	SDL_FillRect( screen, &background, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ));
	background.x+=1;
	background.y+=1;
	background.w-=2;
	background.h-=2;
	SDL_FillRect( screen, &background, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
	
	/*Draw Text */
	SDL_Surface *message;
	TTF_Font *font = arialFont(24);
	SDL_Color textColor = { 255, 255, 255,0};
	if (!(message = TTF_RenderText_Blended( font, text, textColor )))
	{
		printf("%s\n",TTF_GetError());
		return 1;
	}
	TTF_CloseFont(font);
	SDL_Rect textRect = {background.x+20,background.y+10,0,0};
	if(0!=SDL_BlitSurface( message, NULL, screen, &textRect))
	{
		printf("%s\n",SDL_GetError());
		return 1;
	}
	SDL_FreeSurface(message);
	
	/*Draw Buttons*/
	int buttonID;
	
	for (buttonID = 0; buttonID<menuData->buttonCount; buttonID++) {
		drawButton(screen, &menuData->buttons[buttonID]);
	}
	SDL_Flip(screen);
	
	return 0;
}


int popUpLoop(SDL_Surface *screen, menuDataStore *menuData)
{
	int done, mouseX, mouseY;
	SDL_Event event;
	
	unsigned int startTime, stopTime, diffTime;
	unsigned int innerStartTime, innerStopTime;
	
	done = 0;
	while ( !done ) {
		startTime = SDL_GetTicks();
		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			innerStartTime = SDL_GetTicks();
			
			
			switch (event.type) {
					
				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEBUTTONUP:
					
					SDL_GetMouseState(&mouseX,&mouseY);
					
					printf("Cusor-Position x: %d y: %d\n",mouseX,mouseY);
					int buttonID;
					for (buttonID = 0; buttonID<menuData->buttonCount; buttonID++) {
						if (isButtonClicked(&menuData->buttons[buttonID],mouseX,mouseY)) {
							return buttonID;							
						}
					}
					break;
				case SDL_KEYDOWN:
					/* Any keypress quits the app... */
					switch( event.key.keysym.sym )
				{
						
					case SDLK_ESCAPE:
					case SDLK_q:
						done = 1;
						break;
					default:
						break;
						
				}	
					break;
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
			
			innerStopTime = SDL_GetTicks();
			diffTime=(innerStopTime-innerStartTime);
			//25 Frames per second (40 Milliseconds per frame)
			if (MS_FRAMETIME>diffTime) 
				SDL_Delay(MS_FRAMETIME-diffTime);
		}
		stopTime = SDL_GetTicks();
		diffTime = (stopTime-startTime);
		//25 Frames per second (40 Milliseconds per frame)
		if (MS_FRAMETIME>diffTime) 
			SDL_Delay(MS_FRAMETIME-diffTime);
		
	}
	return -1;
	
}