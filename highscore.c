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

int inHighscore(int points, dataStore *data)
{
	if (points>data->highscore[9])
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
	
	apply_surface( screen->clip_rect.w/2-message->w/2, 20, message, screen, NULL );
	SDL_FreeSurface(message);
	TTF_CloseFont(aButtonFont);

	
	SDL_Rect rankRect={200,70,0,0};
	SDL_Rect nameRect={250,70,0,0};
	SDL_Rect pointsRect={650,70,0,0};
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
	button.rect.y = 500;
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
					printf("Cusor-Position x: %d y: %d\n",mouseX,mouseY);
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
					case SDLK_q:
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