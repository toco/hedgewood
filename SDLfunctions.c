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
	Uint8  video_bpp = WINDOWBPP;
	Uint32 videoflags = SDL_SWSURFACE;

	
	/* Initialize the SDL library */
	if ( SDL_Init(initflags) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
				SDL_GetError());
		exit(1);
	}
	

	/* Set 640x480 video mode */
	screen=SDL_SetVideoMode(WINDOWWIDTH,WINDOWHEIGTH, video_bpp, videoflags);

	if (screen == NULL) {
		fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",
				WINDOWWIDTH,WINDOWHEIGTH,video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}

	
	return screen;
}


int toggleFullscreen(SDL_Surface *screen, int windowed)
{
	int windowOK;
	//If the screen is windowed
    if( windowed)
    {
        //Set the screen to fullscreen
        screen = SDL_SetVideoMode( WINDOWWIDTH, WINDOWHEIGTH, WINDOWBPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN );
		
        //If there's an error
        if( screen == NULL )
        {
            windowOK = 0;
            return -1;
        }
        
        //Set the window state flag
        windowed = 0;
    }
    //If the screen is fullscreen
    else if( windowed == 0 )
    {
        //Window the screen
        screen = SDL_SetVideoMode( WINDOWWIDTH, WINDOWHEIGTH, WINDOWBPP, SDL_SWSURFACE | SDL_RESIZABLE);
		
        //If there's an error
        if( screen == NULL )
        {
            windowOK = 0;
            return -1;
        }
		
        //Set the window state flag
        windowed = 1;
    }
	return windowed;

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