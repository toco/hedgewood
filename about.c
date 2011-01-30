/*
 *  about.c
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 10.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */



#include "about.h"


int renderMultiLineText(TTF_Font *font, char text[][100],int lines, SDL_Color textColor, SDL_Surface *screen)
{
	SDL_Surface *lineSurface = NULL;
	char *line;
	int yPos = 50;
	int xMax = 0;
	/*pch = first line of text*/
	int i;
	for (i = 0; i<lines;i++)
	{
		lineSurface = NULL;
		if (!(lineSurface = TTF_RenderText_Blended(font, text[i], textColor)))
			printf("%s\n",TTF_GetError());
		SDL_Rect offset;
		//Get offsets
		offset.x = 100;
		offset.y = yPos;
		//Blit
		SDL_BlitSurface( lineSurface, NULL, screen, &offset );
		yPos+=lineSurface->h;
		if (xMax<lineSurface->w) {
			xMax=lineSurface->w;
		}
		SDL_FreeSurface(lineSurface);
		line = strtok (NULL, " ,.-");
	}

	SDL_Flip(screen);

	return 1;
	
}

int displayAbout(SDL_Surface *screen, dataStore *data)
{
	int done, mouseX, mouseY;
	SDL_Event event;

	SDL_Color textColor = { 255, 255, 255,0};
	
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));

	myButton button;
	button.rect.x = screen->clip_rect.w/2-BUTTONWIDTH/2;
	button.rect.y = screen->clip_rect.h-BUTTONHEIGHT-100;
	button.rect.w = BUTTONWIDTH;
	button.rect.h = BUTTONHEIGHT;
	button.name="Back";
	
	drawButton(screen, &button);
	
	TTF_Font *font = arialFont(18);
	
	char aboutText[6][100] = {"Hedgewood is a Programm written by:"," - toco"," - tk"," - JTR","   "," we hope you enjoy it."};
	
	if (!(renderMultiLineText(font, &aboutText[0],6, textColor,screen)))
		printf("%s\n",TTF_GetError());
	
	
	SDL_Flip(screen);
	TTF_CloseFont(font);

//	SDL_FreeSurface(message);
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
