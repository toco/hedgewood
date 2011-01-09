#include "graphicUpdate.h"
#define field_pic "./pictures/test.bmp"
#define start_pic "./pictures/startzone.bmp"
#define person_pic "./pictures/person.bmp"


int updateGraphics(SDL_Surface *l_screen, struct dataStore *data){

	int i,j;
	SDL_Surface *image;
	SDL_Rect src, dst;
	
	for(i=0;i<16;i++){
		for(j=0;j<12;j++){
			if(j<2){
				image=SDL_LoadBMP(start_pic);
			}
			else{
				image=SDL_LoadBMP(field_pic);
			}
			if (image == NULL) {
				printf("Can't load image red: %s\n", SDL_GetError());
				exit(1);
			}
			src.x = 50*data->hedgewood[j][i].type;
			src.y = 0;
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

	return 1;
}