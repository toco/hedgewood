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

#include<stdio.h>
#include "SDLfunctions.h"

#include "about.h"



int displayAbout(SDL_Surface *screen)
{
	int done, mouseX, mouseY;
	SDL_Event event;
	SDL_Surface *message;

	SDL_Rect button;/* = {BUTTONX,750,BUTTONWIDTH,BUTTONHEIGHT};*/
	button.x = BUTTONX;
	button.y = 700;
	button.w = BUTTONWIDTH;
	button.h = BUTTONHEIGHT;

	/* init button.h not working ? */
	/* @TODO */
	
	TTF_Font *font = buttonFont();
	SDL_Color textColor = { 255, 255, 255,0};
	
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));

	
	SDL_FillRect(screen, &button, SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF ));

	printf("should show button\n");
	
	if (!(message = TTF_RenderText_Blended( font, "Back", textColor )))
		printf("%s\n",TTF_GetError());
	apply_surface( button.x+15, button.y+5, message, screen, NULL );
	
	SDL_Flip(screen);
	
	TTF_CloseFont(font);
	SDL_FreeSurface(message);
	done = 0;
	while ( !done ) {
		
		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
					
				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEBUTTONDOWN:
					
					SDL_GetMouseState(&mouseX,&mouseY);
					
					printf("Cusor-Position x: %d y: %d\n",mouseX,mouseY);
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
		}
	}
	return 0;
}
