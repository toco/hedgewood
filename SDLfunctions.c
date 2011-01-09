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
#define red "./pictures/red.bmp"
#define green "./pictures/green.bmp"



SDL_Surface* initSDL()
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
	
	/* Set 800x600 video mode */
	screen=SDL_SetVideoMode(800,600, video_bpp, videoflags);
	if (screen == NULL) {
		fprintf(stderr, "Couldn't set 800x600x%d video mode: %s\n",
				video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	
	return screen;
}

int testLoop(SDL_Surface *l_screen)
{
	int    done,x,y;
	SDL_Event event;
	
	done = 0;
	while ( !done ) {
		
		/* Check for events */
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
					
				case SDL_MOUSEMOTION:
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&x,&y);
					printf("Cusor-Position x: %d y: %d\n",x,y);
					updateGraphics(l_screen, x,y); 
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

int updateGraphics(SDL_Surface *l_screen, int l_x, int l_y){

	SDL_Surface *image;
	SDL_Rect src, dst;
	image=SDL_LoadBMP(red);
	if (image == NULL) {
        printf("Can't load image red: %s\n", SDL_GetError());
        exit(1);
    }
	
	src.x = 0;
	src.y = 0;
	src.w = image->w;
	src.h = image->h;
	dst.x = l_x;
	dst.y = l_y;
	dst.w = image->w;
	dst.h = image->h;
	
    SDL_BlitSurface(image, &src, l_screen, &dst);
    SDL_UpdateRect(l_screen, 0, 0, 0, 0);
	printf("Test\n");
	SDL_FreeSurface(image);

	return 1;
}