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
//initialisiert das SDL_Surface
SDL_Surface* initSDL(dataStore *data)
{
	Uint32 initflags = SDL_INIT_VIDEO;  /* See documentation for details */
	SDL_Surface *screen;
	Uint8  video_bpp = WINDOWBPP;
	Uint32 videoflags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWPALETTE;
	data->windowed = 1;
	/* Initialize the SDL library */
	if ( SDL_Init(initflags) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
		        SDL_GetError());
		exit(1);
	}
	/* Set 800x600 video mode */
	screen=SDL_SetVideoMode(WINDOWWIDTH,WINDOWHEIGTH, video_bpp, videoflags);
	if (screen == NULL) {
		fprintf(stderr, "Couldn't set %dx%dx%d video mode: %s\n",
		        WINDOWWIDTH,WINDOWHEIGTH,video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	SDL_WM_SetCaption(GAMENAME, NULL );
	/*TTF init for font*/
	if (TTF_Init() == -1) {
		printf("Error: TTF could not be initialized %s\n", SDL_GetError());
		exit(1);
	}
	return screen;
}
//beendet SDL
void quitSDL(dataStore *data)
{
	
	saveDataStore(data,1,0);
	
	/*quit TTF */
	TTF_Quit();
	/* Clean up the SDL library */
	SDL_Quit();
	
	exit(0);
}

//wechselt zwischen fullscreen und windows mode, return: mode nach umschalten
int toggleFullscreen(SDL_Surface *screen, int windowed)
{
	int windowOK;
	//If the screen is windowed
	if( windowed) {
		//Set the screen to fullscreen
		screen = SDL_SetVideoMode( WINDOWWIDTH, WINDOWHEIGTH, WINDOWBPP, SDL_HWSURFACE | SDL_FULLSCREEN | SDL_DOUBLEBUF| SDL_HWPALETTE); /* | SDL_RESIZABLE */
		//If there's an error
		if( screen == NULL ) {
			windowOK = 0;
			return -1;
		}
		//Set the window state flag
		windowed = 0;
	}
	//If the screen is fullscreen
	else if( windowed == 0 ) {
		//Window the screen
		screen = SDL_SetVideoMode( WINDOWWIDTH, WINDOWHEIGTH, WINDOWBPP, SDL_HWSURFACE | SDL_DOUBLEBUF| SDL_HWPALETTE); /* | SDL_RESIZABLE */
		//If there's an error
		if( screen == NULL ) {
			windowOK = 0;
			return -1;
		}
		//Set the window state flag
		windowed = 1;
	}
	return windowed;
}
SDL_Surface *load_image(char *filename )
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	//Load the image
	loadedImage = IMG_Load(filename);
	if( loadedImage != NULL ) {
		//If nothing went wrong in loading the image
		Uint32 colorkey = SDL_MapRGB( loadedImage->format, 0, 255, 255 );
		//Set all pixels of color R 0 G 255, B 255 to be transparent
		SDL_SetColorKey( loadedImage, SDL_SRCCOLORKEY, colorkey);
		//Create an optimized image
		optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

		//Free the old image
		SDL_FreeSurface( loadedImage );
	}
	return optimizedImage;
}

//gibt eine vollständig initialisierte Font mit der Größe für Buttons zurück
TTF_Font *buttonFont()
{
	return arialFont(28); /*requires  	TTF_CloseFont(font); after use*/
}
//gibt eine vollständig initialisierte Font mit der Größe size zurück
TTF_Font *arialFont(int size)
{
	TTF_Font *font = NULL;
	//Open the font
	font = TTF_OpenFont("./ArialBlack.ttf", size );
	//if font not correctly opened
	if (font == NULL) {
		printf("Error: Font not loaded %s\n",SDL_GetError());
		exit(1);
	}
	return font; /*requires  	TTF_CloseFont(font); after use*/
}
//zeichnet einen Button und ignoriert den state
int drawButton (SDL_Surface *destinationSurface, myButton *button)
{
	return drawButtonWithState (destinationSurface, button, 0);
}
//zeichnet einen Button wenn withState = 1 wird der state aus dem Button-Strukt berücksichtigt
//returns 1 on error – return 0 on no error
int drawButtonWithState (SDL_Surface *destinationSurface, myButton *button, int withState)
{
	//draw border
	SDL_Rect buttonBorder = button->rect;
	buttonBorder.h++;
	buttonBorder.w++;
	buttonBorder.x--;
	buttonBorder.y--;
	SDL_FillRect(destinationSurface, &buttonBorder, SDL_MapRGB( destinationSurface->format, 0xFF, 0xFF, 0xFF ));
	//draw button
	if (button->disabled&&withState) {
		SDL_FillRect(destinationSurface, &button->rect, SDL_MapRGB( destinationSurface->format, 0x73, 0x73, 0x73 ));
	} else {
		SDL_FillRect(destinationSurface, &button->rect, SDL_MapRGB( destinationSurface->format, 0x00, 0x00, 0xFF ));
	}
	//draw button title
	SDL_Surface *message;
	TTF_Font *font = buttonFont();
	SDL_Color blackTextColor = { 0, 0, 0,0};
	//text shade
	if (!(message = TTF_RenderText_Blended( font, button->name, blackTextColor ))) {
		printf("%s\n",TTF_GetError());
		return 1;
	}
	SDL_Rect textBlack = {button->rect.x+button->rect.w/2-message->w/2+2,button->rect.y+button->rect.h/2-message->h/2+2,0,0};
	if(0!=SDL_BlitSurface( message, NULL, destinationSurface, &textBlack)) {
		printf("%s\n",SDL_GetError());
		return 1;
	}
	//text
	SDL_Color textColor = { 255, 255, 255,0};
	if (!(message = TTF_RenderText_Blended( font, button->name, textColor ))) {
		printf("%s\n",TTF_GetError());
		return 1;
	}
	SDL_Rect text = {button->rect.x+button->rect.w/2-message->w/2,button->rect.y+button->rect.h/2-message->h/2,0,0};
	TTF_CloseFont(font);
	if(0!=SDL_BlitSurface( message, NULL, destinationSurface, &text)) {
		printf("%s\n",SDL_GetError());
		return 1;
	}
	SDL_FreeSurface(message);
	return 0;
}
//check if the button is clicked
//returns 1 if the button is clicked
int isButtonClicked(myButton *button, int x, int y)
{
	if (button->rect.x < x && x < button->rect.x+button->rect.w && button->rect.y < y && y < button->rect.y+button->rect.h) {
#if (DEBUG==1)
		printf("%s clicked \n",button->name);
#endif
		return 1;
	} else
		return 0;
}

void printdb(char *str)
{
	if(DEBUG)printf("%s",str);
}
