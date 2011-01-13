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


SDL_Surface* initSDL()
{
	Uint32 initflags = SDL_INIT_VIDEO;  /* See documentation for details */
	SDL_Surface *screen;
	Uint8  video_bpp = WINDOWBPP;
	Uint32 videoflags = SDL_HWSURFACE | SDL_DOUBLEBUF;

	
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

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;
	
    //Get offsets
    offset.x = x;
    offset.y = y;
	
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
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

SDL_Surface *load_image(char *filename ) { 
	//Temporary storage for the image that's loaded 
	SDL_Surface* loadedImage = NULL; 
	//The optimized image that will be used 
	SDL_Surface* optimizedImage = NULL; 
	//Load the image 
	loadedImage = IMG_Load(filename); 
	//If nothing went wrong in loading the image 
	if( loadedImage != NULL ) { 
		//Create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedImage ); 
		//Free the old image 
		SDL_FreeSurface( loadedImage ); 
	} 
	if( optimizedImage != NULL ) {
			//Map the color key
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 255, 255 );
			//Set all pixels of color R 0 G 255, B 255 to be transparent
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
	}
	return optimizedImage;
}
TTF_Font *buttonFont()
{
	return arialFont(28); /*requires  	TTF_CloseFont(font); after use*/
}
TTF_Font *arialFont(int size)
{
	TTF_Font *font = NULL;
	//Open the font
	font = TTF_OpenFont("ArialBlack.ttf", size );
	
	if (font == NULL) {
		printf("Error: Font not loaded %s\n",SDL_GetError());
		exit(1);
	}
	return font; /*requires  	TTF_CloseFont(font); after use*/
}
int drawButton (SDL_Surface *destinationSurface, myButton *button)
{
	SDL_FillRect(destinationSurface, &button->rect, SDL_MapRGB( destinationSurface->format, 0x00, 0x00, 0xFF ));

	SDL_Surface *message;
	TTF_Font *font = buttonFont();
	SDL_Color textColor = { 255, 255, 255};
	if (!(message = TTF_RenderText_Blended( font, button->name, textColor )))
	{
		printf("%s\n",TTF_GetError());
		return 1;
	}
	TTF_CloseFont(font);
	SDL_Rect text = {button->rect.x+button->rect.w/2-message->w/2,button->rect.y+button->rect.h/2-message->h/2,0,0};
	if(0==SDL_BlitSurface( message, NULL, destinationSurface, &text))
		return 0;
	else {
		printf("%s\n",SDL_GetError());
		return 1;
	}
	SDL_FreeSurface(message);
}
int isButtonClicked(myButton *button, int x, int y)
{
	if (button->rect.x < x && x < button->rect.x+button->rect.w && button->rect.y < y && y < button->rect.y+button->rect.h)
		return 1;
	else
		return 0;
}
void printdb(char *str){
	if(DEBUG)printf("%s",str);

}