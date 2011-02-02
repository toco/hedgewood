/*
 *  ingameMenu.c
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 13.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */

#include "ingameMenu.h"

int ingameMenuStart(SDL_Surface *screen, dataStore *data)
{
	
	int rtnValue;
	
	menuDataStore *menuData = malloc(sizeof(menuDataStore));
	menuData->buttons = malloc(sizeof(myButton)*INGAMEBUTTONCOUNT);
	
	
	myButton *buttons = menuData->buttons;
	
	/*background from 150 to 450 */
	buttons[ CONTINUE_BUTTON ].rect.y=screen->clip_rect.h/2-125-BUTTONHEIGHT/2;
	buttons[ CONTINUE_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ CONTINUE_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ CONTINUE_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[CONTINUE_BUTTON].rect.w/2;
	buttons[ CONTINUE_BUTTON ].name="Continue";
	buttons[ CONTINUE_BUTTON ].function=NULL;
	

	buttons[ SAVEGAME_BUTTON ].rect.y=screen->clip_rect.h/2-25-BUTTONHEIGHT/2; 
	buttons[ SAVEGAME_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ SAVEGAME_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ SAVEGAME_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[SAVEGAME_BUTTON].rect.w/2;
	buttons[ SAVEGAME_BUTTON ].name="Save Game";
	buttons[ SAVEGAME_BUTTON ].function=saveGame;
	
	buttons[ LOADGAME_BUTTON ].rect.y=screen->clip_rect.h/2+25+BUTTONHEIGHT/2;
	buttons[ LOADGAME_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ LOADGAME_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ LOADGAME_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[LOADGAME_BUTTON].rect.w/2;
	buttons[ LOADGAME_BUTTON ].name="Load Game";
	buttons[ LOADGAME_BUTTON ].function=loadGame;
	
	buttons[ QUIT_BUTTON ].rect.y=screen->clip_rect.h/2+125+BUTTONHEIGHT/2;
	buttons[ QUIT_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ QUIT_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ QUIT_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[LOADGAME_BUTTON].rect.w/2;
	buttons[ QUIT_BUTTON ].name="Quit Game";
	buttons[ QUIT_BUTTON ].function=NULL;
	
	displayIngameMenu(screen, data, menuData);
	rtnValue = ingameMenuLoop(screen, data, menuData);
	
	free(menuData->buttons);
	free(menuData);
	return rtnValue;
}


int displayIngameMenu(SDL_Surface *screen, dataStore *data, menuDataStore *menuData)
{
	/*Background */
//	int width = 400, height = 350;
//	SDL_Rect background = {screen->clip_rect.w/2-width/2,screen->clip_rect.h/2-height/2,width,height};
	
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
	
	
	
	TTF_Font *font = theFont(45);
	SDL_Surface *message;
	int y=40;
	//text
	SDL_Color textColor = { 255, 255, 255,0};
	if (!(message = TTF_RenderText_Blended( font, "GAME PAUSED", textColor ))) {
		printf("%s\n",TTF_GetError());
	}
	SDL_Rect textRect = {screen->clip_rect.w/2-message->w/2,y,0,0};
	if(0!=SDL_BlitSurface( message, NULL, screen, &textRect)) {
		printf("%s\n",SDL_GetError());
	}
	
	
	int buttonID;
	
	for (buttonID = 0; buttonID<INGAMEBUTTONCOUNT; buttonID++) {
		drawButton(screen, &menuData->buttons[buttonID]);
	}
	SDL_Flip(screen);
	
	return 0;
}

int ingameMenuLoop(SDL_Surface *screen, dataStore *data, menuDataStore *menuData)
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
#if (DEBUG==1)					
					printf("Cusor-Position x: %d y: %d\n",mouseX,mouseY);
#endif
					int buttonID;
					for (buttonID = 0; buttonID<INGAMEBUTTONCOUNT; buttonID++) {
						if (isButtonClicked(&menuData->buttons[buttonID],mouseX,mouseY)) {
							if(menuData->buttons[buttonID].function!=NULL)
								(menuData->buttons[buttonID].function)(screen, data);
							displayIngameMenu(screen, data,menuData);
							if (buttonID==CONTINUE_BUTTON) {
								done = 1;
							}
							else if(buttonID == QUIT_BUTTON){
//								quitSDL(data);
								done = 1;
								return 1;
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
						displayIngameMenu(screen, data, menuData);
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
					if(!popUp(screen, data, "Save game before quit?", "Yes", "No"))
						saveDataStore(data, 1, 1);
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

int saveGame(SDL_Surface __attribute__((unused)) *screen, dataStore *data)
{
	printf("Save Game\n");
	if (saveDataStore(data,1,1))
	{
		
	}
	popUp(screen, data, "Successfully saved game!", "OK", NULL);
	
	return 0;
}
int loadGame(SDL_Surface __attribute__((unused)) *screen, dataStore *data)
{
	printf("Load Game\n");
	readDataStore(data,1,1);
	popUp(screen, data, "Successfully loaded game!", "OK", NULL);
	
	return 0;
}