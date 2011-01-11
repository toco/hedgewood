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


#define STARTEN_BUTTON 0
#define HIGHSCORE_BUTTON 1
#define ABOUT_BUTTON 2
#define QUIT_BUTTON 3

void menuStart(SDL_Surface *screen)
{
	struct menuDataStore *dataStore = malloc(sizeof(struct menuDataStore));
	
	
    /*Update Screen*/
    SDL_Flip( screen );
	
	setupMenu(screen, dataStore);
	testLoop(screen, dataStore);
	
	free(dataStore);	
}

void setupMenu(SDL_Surface *screen, struct menuDataStore *dataStore)
{
	/*Background */
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ));
	if (TTF_Init() == -1)
	{
		printf("Error: TTF could not be initialized %s\n", SDL_GetError());
		exit(1);
	}
	TTF_Font *font = buttonFont();
	
#define BUTTONX 300
#define BUTTONWIDTH 200
#define BUTTONHEIGHT 50
	SDL_Surface *message;
	
	SDL_Rect *buttons = &(dataStore->buttons[0]);
	buttons[ STARTEN_BUTTON ].x=BUTTONX;
	buttons[ STARTEN_BUTTON ].y=100;
	buttons[ STARTEN_BUTTON ].w=BUTTONWIDTH;
	buttons[ STARTEN_BUTTON ].h=BUTTONHEIGHT;
	buttons[ HIGHSCORE_BUTTON ].x=BUTTONX;
	buttons[ HIGHSCORE_BUTTON ].y=200;
	buttons[ HIGHSCORE_BUTTON ].w=BUTTONWIDTH;
	buttons[ HIGHSCORE_BUTTON ].h=BUTTONHEIGHT;
	buttons[ ABOUT_BUTTON ].x=BUTTONX;
	buttons[ ABOUT_BUTTON ].y=300;
	buttons[ ABOUT_BUTTON ].w=BUTTONWIDTH;
	buttons[ ABOUT_BUTTON ].h=BUTTONHEIGHT;
	buttons[ QUIT_BUTTON ].x=BUTTONX;
	buttons[ QUIT_BUTTON ].y=400;
	buttons[ QUIT_BUTTON ].w=BUTTONWIDTH;
	buttons[ QUIT_BUTTON ].h=BUTTONHEIGHT;
	
	SDL_FillRect(screen, &buttons[STARTEN_BUTTON], SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF ));
	SDL_FillRect(screen, &buttons[HIGHSCORE_BUTTON], SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF));
	SDL_FillRect(screen, &buttons[ABOUT_BUTTON], SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF ));
	SDL_FillRect(screen, &buttons[QUIT_BUTTON], SDL_MapRGB( screen->format, 0x00, 0x00, 0xFF ));
	
	SDL_Color textColor = { 255, 255, 255,0};

	int buttonID;
	
	if (!(message = TTF_RenderText_Blended( font, "Start Game", textColor )))
		printf("%s\n",TTF_GetError());;
	buttonID = STARTEN_BUTTON;
	apply_surface( buttons[buttonID].x+buttons[buttonID].w/2-message->w/2, buttons[buttonID].y+buttons[buttonID].h/2-message->h/2, message, screen, NULL );
	if(!(message = TTF_RenderText_Blended( font, "Highscore", textColor )))
		printf("%s\n",TTF_GetError());
	buttonID = HIGHSCORE_BUTTON;
	apply_surface( buttons[buttonID].x+buttons[buttonID].w/2-message->w/2, buttons[buttonID].y+buttons[buttonID].h/2-message->h/2, message, screen, NULL );
	if (!(message = TTF_RenderText_Blended( font, "About/Help", textColor )))
		printf("%s\n",TTF_GetError());
	buttonID = ABOUT_BUTTON;
	apply_surface( buttons[buttonID].x+buttons[buttonID].w/2-message->w/2, buttons[buttonID].y+buttons[buttonID].h/2-message->h/2, message, screen, NULL );
	if (!(message = TTF_RenderText_Blended( font, "Quit", textColor )))
		printf("%s\n",TTF_GetError());
	buttonID = QUIT_BUTTON;
	apply_surface( buttons[buttonID].x+buttons[buttonID].w/2-message->w/2, buttons[buttonID].y+buttons[buttonID].h/2-message->h/2, message, screen, NULL );
	
	SDL_FreeSurface(message);
	
	TTF_CloseFont(font);
	
	SDL_Flip(screen);
	
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

int whichButtonClicked(int x, int y, SDL_Rect buttons[])
{
	int i;
	for (i=0; i<BUTTONCOUNT ;i++) {
		SDL_Rect aButton = buttons[i];
		if (x>aButton.x&&x<aButton.x+aButton.w&&y>aButton.y&&y<aButton.y+aButton.h) {
			return i;
		}
	}
	return -1;
}
int testLoop(SDL_Surface *screen, struct menuDataStore *dataStore)
{
	int done, mouseX, mouseY;
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
					
					SDL_GetMouseState(&mouseX,&mouseY);
					
					printf("Cusor-Position x: %d y: %d\n",mouseX,mouseY);
					int buttonClicked = whichButtonClicked(mouseX, mouseY,&dataStore->buttons[0]);
					printf("Button %i clicked\n",buttonClicked);
					if (buttonClicked == STARTEN_BUTTON) {
						printf("start game\n");
					}
					else if (buttonClicked == HIGHSCORE_BUTTON)
					{
						displayHighscore(screen);
						printf("display highscore\n");
						setupMenu(screen, dataStore);

					}
					else if (buttonClicked == ABOUT_BUTTON)
					{
						printf("display about\n");
						displayAbout(screen);
						printf("back in Menu\n");
						setupMenu(screen, dataStore);
					}
					else if (buttonClicked == QUIT_BUTTON)
					{
						printf("Quit Programm\n");
						done = 1;
					}
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
