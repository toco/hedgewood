/*
 *  SDLfunctions.c
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 08.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */

#include "SDLfunctions.h"

int initSDL()
{
	Uint32 initflags = SDL_INIT_VIDEO;  /* See documentation for details */
	SDL_Surface *screen;
	Uint8  video_bpp = 0;
	Uint32 videoflags = SDL_SWSURFACE;

	
	/* Initialize the SDL library */
	if ( SDL_Init(initflags) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
				SDL_GetError());
		exit(1);
	}
	
	/* Set 640x480 video mode */
	screen=SDL_SetVideoMode(800,600, video_bpp, videoflags);
	if (screen == NULL) {
		fprintf(stderr, "Couldn't set 800x600x%d video mode: %s\n",
				video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	return 0;
}

int testLoop()
{
	int    done;
	SDL_Event event;
	
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
void quitSDL()
{
	/* Clean up the SDL library */
	SDL_Quit();
}