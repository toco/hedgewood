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
	menuDataStore *menuData = malloc(sizeof(menuDataStore));
	menuData->buttons = malloc(sizeof(myButton)*BUTTONCOUNT);
	
	
	setupMenu(screen, menuData);
	testLoop(screen, menuData, data);
	
	free(menuData->buttons);
	free(menuData);	
}

int startGame( SDL_Surface *screen, dataStore *data)
{
	printf("Start ingame Menu\n");
	
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
	SDL_Flip(screen);
	ingameMenuStart(screen, data);

	printf("StartGame Clicked\n");
	
	return 0;
}
int menuQuit(SDL_Surface *screen, dataStore *data)
{
	printf("Quit");
	return 0;
}
void setupMenu(SDL_Surface *screen, struct menuDataStore *dataStore)
{
	/*Background */
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
	if (TTF_Init() == -1)
	{
		printf("Error: TTF could not be initialized %s\n", SDL_GetError());
		exit(1);
	}
	
#define BUTTONX 300
#define BUTTONWIDTH 200
#define BUTTONHEIGHT 50
	
	myButton *buttons = &(dataStore->buttons[0]);
	buttons[ STARTEN_BUTTON ].rect.x=BUTTONX;
	buttons[ STARTEN_BUTTON ].rect.y=100;
	buttons[ STARTEN_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ STARTEN_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ STARTEN_BUTTON ].name="Start Game";
	buttons[ STARTEN_BUTTON ].function=startGame;

	buttons[ HIGHSCORE_BUTTON ].rect.x=BUTTONX;
	buttons[ HIGHSCORE_BUTTON ].rect.y=200;
	buttons[ HIGHSCORE_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ HIGHSCORE_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ HIGHSCORE_BUTTON ].name="Highscore";
	buttons[ HIGHSCORE_BUTTON ].function=displayHighscore;

	
	buttons[ ABOUT_BUTTON ].rect.x=BUTTONX;
	buttons[ ABOUT_BUTTON ].rect.y=300;
	buttons[ ABOUT_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ ABOUT_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ ABOUT_BUTTON ].name="About/Help";
	buttons[ ABOUT_BUTTON ].function=displayAbout;

	
	buttons[ QUIT_BUTTON ].rect.x=BUTTONX;
	buttons[ QUIT_BUTTON ].rect.y=400;
	buttons[ QUIT_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ QUIT_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ QUIT_BUTTON ].name="Quit";
	buttons[ QUIT_BUTTON ].function=menuQuit;

	
//	SDL_FillRect(screen, &buttons[STARTEN_BUTTON].rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF ));
//	SDL_FillRect(screen, &buttons[HIGHSCORE_BUTTON].rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF));
//	SDL_FillRect(screen, &buttons[ABOUT_BUTTON].rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF ));
//	SDL_FillRect(screen, &buttons[QUIT_BUTTON].rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF ));
//	

	int buttonID;
	
	for (buttonID = 0; buttonID<BUTTONCOUNT; buttonID++) {
		drawButton(screen, &buttons[buttonID]);
	}


	SDL_Flip(screen);
	
}

int testLoop(SDL_Surface *screen, struct menuDataStore *menuData, dataStore *data)
{
	int done, mouseX, mouseY;
	SDL_Event event;
	
	int windowed = 1;
	
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
				case SDL_MOUSEBUTTONDOWN:
					
					SDL_GetMouseState(&mouseX,&mouseY);
					
					printf("Cusor-Position x: %d y: %d\n",mouseX,mouseY);
					int buttonID;
					for (buttonID = 0; buttonID<BUTTONCOUNT; buttonID++) {
						if (isButtonClicked(&menuData->buttons[buttonID],mouseX,mouseY)) {
							(menuData->buttons[buttonID].function)(screen, data);
							setupMenu(screen, menuData);
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
						windowed = toggleFullscreen(screen, windowed);
						setupMenu(screen,menuData);
						break;
						
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
			if (4>diffTime) 
				SDL_Delay(4-diffTime);
		}
		stopTime = SDL_GetTicks();
		diffTime = (stopTime-startTime);
		//25 Frames per second (40 Milliseconds per frame)
		if (4>diffTime) 
			SDL_Delay(4-diffTime);

	}
	return 0;
}
