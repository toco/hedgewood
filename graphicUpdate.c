#include "graphicUpdate.h"
#define field_pic "./pictures/test.bmp"
#define start_pic "./pictures/startzone.bmp"
#define person_pic "./pictures/person.bmp"


int updateGraphics(SDL_Surface *l_screen, struct dataStore *data){

	int i,j;
	SDL_Surface *image;
	SDL_Rect src, dst;
	
	for(j=0;j<12;j++){
		for(i=0;i<16;i++){
			if(j<2){
				image=SDL_LoadBMP(start_pic);
				printf("Startzone\n");
				src.x = 50*i;
				src.y = 50*j;
			}
			else{
				image=SDL_LoadBMP(field_pic);
				printf("Field\n");
				src.x = 50*data->hedgewood[j][i].type;
				src.y = 0;
			}
			if (image == NULL) {
				printf("Can't load image red: %s\n", SDL_GetError());
				exit(1);
			}
			
			
			src.w =src.h = 50;
			dst.x = 50*i;
			dst.y = 50*j;
			dst.w = dst.h = 50;
			SDL_BlitSurface(image, &src, l_screen, &dst);
		}
	}
    SDL_UpdateRect(l_screen, 0, 0, 0, 0);
	printf("Test\n");
	SDL_FreeSurface(image);
			
			int done=0;
			SDL_Event event;
			
			while (!done) {
				/* Check for events */
				while ( SDL_PollEvent(&event) ) {
					switch (event.type) {
					
					case SDL_KEYDOWN:
					/* Any keypress quits the app... */
						switch( event.key.keysym.sym )
					{

						case SDLK_ESCAPE:
						case SDLK_q:
							done = 1;
							break;
						default:
							break;
					}	
						break;
					default:
						break;
					}
				}
			}

	return 1;
}