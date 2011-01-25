/*
 *  store.c
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
#include "store.h"
int storeStart(SDL_Surface *screen, dataStore *data) {
	int rtnValue;
	menuDataStore *menuData = malloc(sizeof(menuDataStore));
	menuData->buttons = malloc(sizeof(myButton)*INGAMEBUTTONCOUNT);
	myButton *buttons = menuData->buttons;
	/*background from 150 to 450 */
	buttons[ ITEM_BUTTON ].rect.y=screen->clip_rect.h/2-125-BUTTONHEIGHT/2;
	buttons[ ITEM_BUTTON ].rect.w=BUTTONWIDTH*2+20;
	buttons[ ITEM_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ ITEM_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[ITEM_BUTTON].rect.w/2;
	buttons[ ITEM_BUTTON ].name="Item Upgrade (800)";
	buttons[ ITEM_BUTTON ].function=NULL;
	buttons[ BACKPACK_BUTTON ].rect.y=screen->clip_rect.h/2-25-BUTTONHEIGHT/2;
	buttons[ BACKPACK_BUTTON ].rect.w=BUTTONWIDTH*2+20;
	buttons[ BACKPACK_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ BACKPACK_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[BACKPACK_BUTTON].rect.w/2;
	buttons[ BACKPACK_BUTTON ].name="Backpack Upgrade (1000)";
	buttons[ BACKPACK_BUTTON ].function=NULL;
	buttons[ VIEW_BUTTON ].rect.y=screen->clip_rect.h/2+25+BUTTONHEIGHT/2;
	buttons[ VIEW_BUTTON ].rect.w=BUTTONWIDTH*2+20;
	buttons[ VIEW_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ VIEW_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[VIEW_BUTTON].rect.w/2;
	buttons[ VIEW_BUTTON ].name="View Upgrade (1200)";
	buttons[ VIEW_BUTTON ].function=NULL;
	buttons[ BACK_BUTTON ].rect.y=screen->clip_rect.h/2+125+BUTTONHEIGHT/2;
	buttons[ BACK_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ BACK_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ BACK_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[BACK_BUTTON].rect.w/2;
	buttons[ BACK_BUTTON ].name="Back";
	buttons[ BACK_BUTTON ].function=NULL;
	displayStore(screen, data, menuData);
	rtnValue = storeLoop(screen, data, menuData);
	free(menuData->buttons);
	free(menuData);
	return rtnValue;
}

//TODO: maxEngery, Backpacksize, curentMoney 
int displayStore(SDL_Surface *screen, dataStore *data, menuDataStore *menuData) {
	/*Background */
	//	int width = 400, height = 350;
	//	SDL_Rect background = {screen->clip_rect.w/2-width/2,screen->clip_rect.h/2-height/2,width,height};
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
	
	/*Buttons*/
	int buttonID;
	for (buttonID = 0; buttonID<INGAMEBUTTONCOUNT; buttonID++) {
		drawButton(screen, &menuData->buttons[buttonID]);
	}
	
	
	
	SDL_Flip(screen);
	return 0;
}
int storeLoop(SDL_Surface *screen, dataStore *data, menuDataStore *menuData) {
	int done, mouseX, mouseY;
	SDL_Event event;
	int  diffmoney;
	unsigned int startTime, stopTime, diffTime;
	unsigned int innerStartTime, innerStopTime;
	int buttonID;
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
				
				for (buttonID = 0; buttonID<INGAMEBUTTONCOUNT; buttonID++) {
					
					if (isButtonClicked(&menuData->buttons[buttonID],mouseX,mouseY)) {
						displayStore(screen, data,menuData);
						if (buttonID==ITEM_BUTTON) {
							if (data->player.candystash + data->player.bp.currentVolume>=ITEMPRICE) {
								data->player.cutSpeed+=0.5;
								diffmoney= data->player.bp.currentVolume - ITEMPRICE;
								if(diffmoney<0) {
									data->player.bp.currentVolume=0;
									data->player.candystash += diffmoney;
								} else data->player.bp.currentVolume -= ITEMPRICE;
							}
						}
						else if (buttonID==BACKPACK_BUTTON ) {
							if (data->player.candystash + data->player.bp.currentVolume>=BACKPACKPRICE) {
								data->player.bp.maxVolume+=200;
								diffmoney= data->player.bp.currentVolume - BACKPACKPRICE;
								if(diffmoney<0) {
									data->player.bp.currentVolume=0;
									data->player.candystash += diffmoney;
								} else data->player.bp.currentVolume -= BACKPACKPRICE;
							}
						}
						else if (buttonID==VIEW_BUTTON ) {
						
							if (data->player.candystash + data->player.bp.currentVolume>=VIEWPRICE) {
								data->player.vision+=1;
								diffmoney= data->player.bp.currentVolume - VIEWPRICE;
								if(diffmoney<0) {
									data->player.bp.currentVolume=0;
									data->player.candystash += diffmoney;
								} else data->player.bp.currentVolume -= VIEWPRICE;
							}
						}						
						else if (buttonID==BACK_BUTTON){
							
							done=1;
						break;
						
						}
					}
				}
					break;
				case SDL_KEYDOWN:
					/* Any keypress quits the app... */
					switch( event.key.keysym.sym ) {
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
