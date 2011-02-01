/*
 *  menu.c
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


#include "menu.h"


void menuStart(SDL_Surface *screen, dataStore *data)
{
	//alloc menuDataStore
	menuDataStore *menuData = malloc(sizeof(menuDataStore));
	menuData->buttons = malloc(sizeof(myButton)*BUTTONCOUNT);

	
	setupMenu(screen, menuData);
	drawMenu(screen, menuData);

	Mix_PlayMusic( data->startmusic, -1);
	mainMenuLoop(screen, menuData, data);
	
	free(menuData->buttons);
	free(menuData);	
}

int startGame( SDL_Surface *screen, dataStore *data)
{
	
//	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
//	SDL_Flip(screen);
	gameloop(data,screen);
	
	Mix_PlayMusic( data->startmusic, -1);
	
	return 0;
}
int menuQuit(SDL_Surface __attribute__((unused)) *screen, dataStore __attribute__((unused)) *data)
{
	printf("Quit");
	return 0;
}
void setupMenu(SDL_Surface *screen, struct menuDataStore *menuData)
{
	//init the buttons


	myButton *buttons = &(menuData->buttons[0]);
	buttons[ STARTEN_BUTTON ].rect.x=screen->clip_rect.w/2-BUTTONWIDTH/2;
	buttons[ STARTEN_BUTTON ].rect.y=screen->clip_rect.h/2-125-BUTTONHEIGHT/2;
	buttons[ STARTEN_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ STARTEN_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ STARTEN_BUTTON ].name="Start Game";
	buttons[ STARTEN_BUTTON ].function=startGame;

	buttons[ HIGHSCORE_BUTTON ].rect.x=screen->clip_rect.w/2-BUTTONWIDTH/2;
	buttons[ HIGHSCORE_BUTTON ].rect.y=screen->clip_rect.h/2-25-BUTTONHEIGHT/2;
	buttons[ HIGHSCORE_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ HIGHSCORE_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ HIGHSCORE_BUTTON ].name="Highscore";
	buttons[ HIGHSCORE_BUTTON ].function=displayHighscore;

	buttons[ ABOUT_BUTTON ].rect.x=screen->clip_rect.w/2-BUTTONWIDTH/2;
	buttons[ ABOUT_BUTTON ].rect.y=screen->clip_rect.h/2+25+BUTTONHEIGHT/2;
	buttons[ ABOUT_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ ABOUT_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ ABOUT_BUTTON ].name="About/Help";
	buttons[ ABOUT_BUTTON ].function=displayAbout;

	buttons[ QUIT_BUTTON ].rect.x=screen->clip_rect.w/2-BUTTONWIDTH/2;
	buttons[ QUIT_BUTTON ].rect.y=screen->clip_rect.h/2+125+BUTTONHEIGHT/2;
	buttons[ QUIT_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ QUIT_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ QUIT_BUTTON ].name="Quit";
	buttons[ QUIT_BUTTON ].function=menuQuit;
}
void drawMenu(SDL_Surface *screen, menuDataStore *menuData)
{

	
	/*Background */
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));

	
	TTF_Font *font = theFont(60);
	SDL_Surface *message;
	int y=40;
	//text
	SDL_Color textColor = { 255, 255, 255,0};
	if (!(message = TTF_RenderText_Blended( font, GAMENAME, textColor ))) {
		printf("%s\n",TTF_GetError());
	}
	SDL_Rect textRect = {screen->clip_rect.w/2-message->w/2,y,0,0};
	if(0!=SDL_BlitSurface( message, NULL, screen, &textRect)) {
		printf("%s\n",SDL_GetError());
	}

	
	TTF_CloseFont(font);
	SDL_FreeSurface(message);
	
	
	myButton *buttons = &(menuData->buttons[0]);

	/*Buttons */	
	int buttonID;
	for (buttonID = 0; buttonID<BUTTONCOUNT; buttonID++) {
		drawButton(screen, &buttons[buttonID]);
	}
	
	SDL_Flip(screen);
}
int mainMenuLoop(SDL_Surface *screen, struct menuDataStore *menuData, dataStore *data)
{
	int done, mouseX, mouseY;
	SDL_Event event;
		
	Uint32 startTime, stopTime, diffTime;
	Uint32 innerStartTime, innerStopTime;

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
#if (DEBUG==1)					
					printf("Cusor-Position x: %d y: %d\n",mouseX,mouseY);
#endif
					int buttonID;
					for (buttonID = 0; buttonID<BUTTONCOUNT; buttonID++) {
						if (isButtonClicked(&menuData->buttons[buttonID],mouseX,mouseY)) {
							(menuData->buttons[buttonID].function)(screen, data);
							drawMenu(screen, menuData);
							if (buttonID==QUIT_BUTTON) {
								done = 1;
							}
						}
					}
					break;
				case SDL_KEYDOWN:
					/* Any keypress quits the app... */
					switch( event.key.keysym.sym )
				{
					case SDLK_f:
						data->windowed = toggleFullscreen(screen, data->windowed);
						drawMenu(screen,menuData);
						break;
						
					case SDLK_ESCAPE:
//					case SDLK_q:
						done = 1;
						break;
					default:
						break;
						
				}	
					break;
				case SDL_QUIT:
					done = 1;
					quitSDL(data);
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
	return 0;
}
