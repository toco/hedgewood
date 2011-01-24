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
	mainMenuLoop(screen, menuData, data);
	
	free(menuData->buttons);
	free(menuData);	
}

int startGame( SDL_Surface *screen, dataStore *data)
{
	
//	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
//	SDL_Flip(screen);
	gameloop(data,screen);

	
	return 0;
}
int menuQuit(SDL_Surface __attribute__((unused)) *screen, dataStore __attribute__((unused)) *data)
{
	printf("Quit");
	return 0;
}
void setupMenu(SDL_Surface *screen, struct menuDataStore *dataStore)
{
	/*Background */
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));

	
#define BUTTONX 300
#define BUTTONWIDTH 200
#define BUTTONHEIGHT 50
	
	myButton *buttons = &(dataStore->buttons[0]);
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
						data->windowed = toggleFullscreen(screen, data->windowed);
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
