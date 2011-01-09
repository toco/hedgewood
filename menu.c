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
#include<stdio.h>


void menuStart(SDL_Surface *screen)
{
	
	SDL_Surface *hello;
	
	hello = SDL_LoadBMP( "hello.bmp" );
	
    /*Apply image to screen*/
    SDL_BlitSurface( hello, NULL, screen, NULL );
	
    /*Update Screen*/
    SDL_Flip( screen );
	
	SDL_FreeSurface(hello);
	setupMenu(screen);
	testLoop(screen);
}

void setupMenu(SDL_Surface *screen)
{
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF ) );
	
	
	
	SDL_UpdateRect(screen, 0, 0, 0, 0);

}

int testLoop(SDL_Surface *screen)
{
	int    done;
	SDL_Event event;
	
	int windowed = 1;
	
	done = 0;
	while ( !done ) {
		
		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
					
				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_KEYDOWN:
					/* Any keypress quits the app... */
					switch( event.key.keysym.sym )
                {
					case SDLK_f:
						windowed = toggleFullscreen(screen, windowed);
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
