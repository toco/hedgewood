/*
 *  highscore.c
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 11.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */

#include "highscore.h"


// "privat" functions


/**
 * checks if the player is in highscore
 * @param data the dataStore
 * @param the points the player achieved
 * @return 1 if the player is in highscore
 * @return 0 if the player is not in highscore
 */
int inHighscore(dataStore *data, int points);

/**
 * Sorts the Highscore
 * @param data the dataStore
 * @return 0
 */

int sortHighscore(dataStore *data);


//implementation
int addHighscore(SDL_Surface *screen ,dataStore *data, int points)
{
	if (inHighscore(data, points)) {
		char *playerName = malloc(sizeof(char)*15);
		inputPopUp(screen,data,"Highscore! Please enter your Name:", playerName, 15, "Ok", NULL);
		strcpy(data->highscore[9].name,playerName);
		data->highscore[9].points = points;
		sortHighscore(data);
		saveDataStore(data, 1, 0);
		displayHighscore(screen,data);
		return 1;
	}
	return 0;
}

int sortHighscore(dataStore *data)
{
	highscoreElement *highscore=data->highscore;
	highscoreElement temp;
	int i,n,changed,steps=0;
	for (i=0; i<10; i++) {
		changed=0;
		for (n=1; n<10-i; n++) {
			if (highscore[n-1].points<highscore[n].points) {
				memcpy(&temp,&highscore[n-1],sizeof(highscoreElement));
				memcpy(&highscore[n-1],&highscore[n],sizeof(highscoreElement));
				memcpy(&highscore[n],&temp,sizeof(highscoreElement));
				changed++;
			}
			
			steps++;
		}
		if (changed==0) {
			break;
		}
	}
	return 0;
}

int inHighscore(dataStore *data, int points)
{
	sortHighscore(data);
	if (points>data->highscore[9].points)
		return 1;
	else
		return 0;
}


int displayHighscore(SDL_Surface *screen, dataStore *data)
{
	int done, mouseX, mouseY;
	SDL_Event event;
	SDL_Surface *message;
	highscoreElement *highscore=data->highscore;
	
	
	
	TTF_Font *aButtonFont = arialFont(32);
	SDL_Color textColor = { 255, 255, 255,0};
	
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
	
	if (!(message = TTF_RenderText_Blended( aButtonFont, "Highscore", textColor )))
		printf("%s\n",TTF_GetError());
	
	SDL_Rect offset;
	offset.x =  screen->clip_rect.w/2-message->w/2;
	offset.y = 20;
	//Blit
	SDL_BlitSurface( message, NULL, screen, &offset );
	SDL_FreeSurface(message);
	TTF_CloseFont(aButtonFont);

	
	SDL_Rect rankRect={screen->clip_rect.w/2-200,screen->clip_rect.h/2-230,0,0};
	SDL_Rect nameRect={screen->clip_rect.w/2-150,screen->clip_rect.h/2-230,0,0};
	SDL_Rect pointsRect={screen->clip_rect.w/2+250,screen->clip_rect.h/2-230,0,0};
	int pointRight=pointsRect.x;
	TTF_Font *midFont = arialFont(28);
	
	int i;
	int lineOffset = 40;
	char tmp[15];
	for (i=0;i<10 ; i++) {
		/*Rank*/
		sprintf(tmp, "%d",i+1);
		if (!(message = TTF_RenderText_Blended( midFont,tmp, textColor )))
			printf("%s\n",TTF_GetError());
		SDL_BlitSurface( message, NULL, screen, &rankRect);
		SDL_FreeSurface(message);
		rankRect.y+=lineOffset;
		/*Name*/
		if (!(message = TTF_RenderText_Blended( midFont,highscore[i].name, textColor )))
			printf("%s\n",TTF_GetError());
		SDL_BlitSurface( message, NULL, screen, &nameRect);
		SDL_FreeSurface(message);
		nameRect.y+=lineOffset;
		/*Points*/
		sprintf(tmp, "%d",highscore[i].points);
		if (!(message = TTF_RenderText_Blended( midFont,tmp, textColor )))
			printf("%s\n",TTF_GetError());
		pointsRect.x=pointRight-message->w;
		SDL_BlitSurface( message, NULL, screen, &pointsRect);
		SDL_FreeSurface(message);
		pointsRect.y+=lineOffset;
	}
	
	TTF_CloseFont(midFont);
	
	
	myButton button;
	button.rect.x = screen->clip_rect.w/2-BUTTONWIDTH/2;
	button.rect.y = screen->clip_rect.h-50-BUTTONHEIGHT;
	button.rect.w = BUTTONWIDTH;
	button.rect.h = BUTTONHEIGHT;
	button.name="Back";
	
	drawButton(screen, &button);
	
	SDL_Flip(screen);
	
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
					if (isButtonClicked(&button, mouseX, mouseY)) {
						done = 1;
					}
#if (DEBUG==1)
					printf("Cusor-Position x: %d y: %d\n",mouseX,mouseY);
#endif
					break;
				case SDL_KEYDOWN:
					/* Any keypress quits the app... */
					switch( event.key.keysym.sym )
				{
					case SDLK_f:
						break;
						
					case SDLK_ESCAPE:
						done = 1;
						break;
/*					case SDLK_q:
						break;
*/					default:
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