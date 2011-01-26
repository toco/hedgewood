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
	int rtnValue,buttonID;
	menuDataStore *menuData = malloc(sizeof(menuDataStore));
	menuData->buttons = malloc(sizeof(myButton)*STOREBUTTONCOUNT);
	myButton *buttons = menuData->buttons;
	/*background from 150 to 450 */
	for (buttonID = 0; buttonID<STOREBUTTONCOUNT; buttonID++) {
		buttons[buttonID].name=calloc(30,sizeof(char));
	}
	buttons[ ITEM_BUTTON ].rect.y=screen->clip_rect.h/2-150-BUTTONHEIGHT/2;
	buttons[ ITEM_BUTTON ].rect.w=BUTTONWIDTH*2+20;
	buttons[ ITEM_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ ITEM_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[ITEM_BUTTON].rect.w/2;
	sprintf(buttons[ ITEM_BUTTON ].name,"Tool Upgrade %.0f",data->player.cutSpeed*1000);	
	buttons[ ITEM_BUTTON ].function=NULL;
	buttons[ ITEM_BUTTON ].disabled=1;
	buttons[ BACKPACK_BUTTON ].rect.y=screen->clip_rect.h/2-50-BUTTONHEIGHT/2;
	buttons[ BACKPACK_BUTTON ].rect.w=BUTTONWIDTH*2+20;
	buttons[ BACKPACK_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ BACKPACK_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[BACKPACK_BUTTON].rect.w/2;
	sprintf(buttons[ BACKPACK_BUTTON ].name,"Backpack Upgrade %d",data->player.bp.maxVolume*3);
	buttons[ BACKPACK_BUTTON ].function=NULL;
	buttons[ BACKPACK_BUTTON ].disabled=1;
	buttons[ VIEW_BUTTON ].rect.y=screen->clip_rect.h/2+0+BUTTONHEIGHT/2;
	buttons[ VIEW_BUTTON ].rect.w=BUTTONWIDTH*2+20;
	buttons[ VIEW_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ VIEW_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[VIEW_BUTTON].rect.w/2;
	sprintf(buttons[ VIEW_BUTTON ].name,"View Upgrade %d",data->player.vision*1000);
	buttons[ VIEW_BUTTON ].function=NULL;
	buttons[ VIEW_BUTTON ].disabled=1;
	buttons[ ENERGY_BUTTON ].rect.y=screen->clip_rect.h/2+100+BUTTONHEIGHT/2;
	buttons[ ENERGY_BUTTON ].rect.w=BUTTONWIDTH*2+20;
	buttons[ ENERGY_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ ENERGY_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[ENERGY_BUTTON].rect.w/2;
	sprintf(buttons[ ENERGY_BUTTON ].name,"Energy Upgrade %d",data->player.maxEnergy);
	buttons[ ENERGY_BUTTON ].function=NULL;
	buttons[ ENERGY_BUTTON ].disabled=1;
	buttons[ BACK_BUTTON ].rect.y=screen->clip_rect.h/2+200+BUTTONHEIGHT/2;
	buttons[ BACK_BUTTON ].rect.w=BUTTONWIDTH;
	buttons[ BACK_BUTTON ].rect.h=BUTTONHEIGHT;
	buttons[ BACK_BUTTON ].rect.x=screen->clip_rect.w/2-buttons[BACK_BUTTON].rect.w/2;
	buttons[ BACK_BUTTON ].name="Back";
	buttons[ BACK_BUTTON ].disabled=0;
	buttons[ BACK_BUTTON ].function=NULL;	

	displayStore(screen, data, menuData);
	if(storeLoop(screen, data, menuData))storeStart(screen,data);
	free(menuData->buttons);
	free(menuData);
	return rtnValue;
}

//TODO: maxEngery, Backpacksize, curentMoney 
int displayStore(SDL_Surface *screen, dataStore *data, menuDataStore *menuData) {
	
	menuData->buttons[ITEM_BUTTON].disabled=!(data->player.candystash + data->player.bp.currentVolume>=data->player.cutSpeed*1000);
	menuData->buttons[VIEW_BUTTON].disabled=!(data->player.candystash + data->player.bp.currentVolume>=data->player.bp.maxVolume*3);
	menuData->buttons[BACKPACK_BUTTON].disabled=!(data->player.candystash + data->player.bp.currentVolume>=data->player.vision*1000);
	menuData->buttons[ ENERGY_BUTTON ].disabled=!(data->player.candystash + data->player.bp.currentVolume>=data->player.maxEnergy);
	
	
	
	
	
	/*Background */
	//	int width = 400, height = 350;
	//	SDL_Rect background = {screen->clip_rect.w/2-width/2,screen->clip_rect.h/2-height/2,width,height};
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
	int i;
	for(i=0;i<3;i+=2){
	   /*Draw Text */
        char text[50];
		sprintf(text,"%d CANDY",(data->player.candystash+data->player.bp.currentVolume));
		
        SDL_Surface *message;
        TTF_Font *font = arialFont(25);
        SDL_Color textColor = { 255*i, 255*i, 255*i,0};
        if (!(message = TTF_RenderText_Blended( font, text, textColor )))
        {
                printf("%s\n",TTF_GetError());
                return 1;
        }
        TTF_CloseFont(font);
        SDL_Rect textRect = {300-i,22-i,0,0};
        if(0!=SDL_BlitSurface( message, NULL, screen, &textRect))
        {
                printf("%s\n",SDL_GetError());
                return 1;
        }
        SDL_FreeSurface(message);
	}
	
	/*Buttons*/
	int buttonID;
	for (buttonID = 0; buttonID<STOREBUTTONCOUNT; buttonID++) {
		drawButtonWithState(screen, &menuData->buttons[buttonID],1);
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
				for (buttonID = 0; buttonID<STOREBUTTONCOUNT; buttonID++) {					
					if (isButtonClicked(&menuData->buttons[buttonID],mouseX,mouseY)) {						
						displayStore(screen, data,menuData);
						if (buttonID==ITEM_BUTTON) {
							if (data->player.candystash + data->player.bp.currentVolume>=data->player.cutSpeed*1000) {
								data->player.cutSpeed+=0.5;
								diffmoney= data->player.bp.currentVolume - data->player.cutSpeed*1000;
								if(diffmoney<0) {
									data->player.bp.currentVolume=0;
									data->player.candystash += diffmoney;
								} else data->player.bp.currentVolume -= data->player.cutSpeed*1000;
							}
							done=2;
						}
						else if (buttonID==BACKPACK_BUTTON ) {
							if (data->player.candystash + data->player.bp.currentVolume>=data->player.bp.maxVolume*3) {
								data->player.bp.maxVolume+=200;
								diffmoney= data->player.bp.currentVolume - data->player.bp.maxVolume*3;
								if(diffmoney<0) {
									data->player.bp.currentVolume=0;
									data->player.candystash += diffmoney;
								} else data->player.bp.currentVolume -= data->player.bp.maxVolume*3;
							}
							done=2;
						}
						else if (buttonID==VIEW_BUTTON ) {
						
							if (data->player.candystash + data->player.bp.currentVolume>=data->player.vision*1000) {
								data->player.vision+=1;
								diffmoney= data->player.bp.currentVolume - data->player.vision*1000;
								if(diffmoney<0) {
									data->player.bp.currentVolume=0;
									data->player.candystash += diffmoney;
								} else data->player.bp.currentVolume -= data->player.vision*1000;
							}
							done=2;
						}
						else if (buttonID==ENERGY_BUTTON) {
						
							if (data->player.candystash + data->player.bp.currentVolume>=data->player.maxEnergy) {
								data->player.maxEnergy+=100;
								diffmoney= data->player.bp.currentVolume - data->player.maxEnergy;
								if(diffmoney<0) {
									data->player.bp.currentVolume=0;
									data->player.candystash += diffmoney;
								} else data->player.bp.currentVolume -= data->player.maxEnergy;
							}
							done=2;
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
	return (done-1);
}
