#include "graphicUpdate.h"
#define field_pic "./pictures/test.bmp"
#define start_pic "./pictures/startzone.bmp"
#define person_pic "./pictures/person.bmp"


int updateGraphics(SDL_Surface *l_screen, struct dataStore *data){

	int i,j,scrollposition=0;
	SDL_Surface *image=NULL,*test;
	SDL_Rect src, dst;
	
	for(j=0;j<12;j++){
		for(i=0;i<16;i++){
			if(data->hedgewood[j+scrollposition][i].type==-1){
				test= SDL_LoadBMP(start_pic);
				image=SDL_DisplayFormat( test );
				SDL_FreeSurface(test);
				if(DEBUG)printf("Startzone\n");
				src.x = 50*i;
				src.y = 50*j;
			}
			else{
				test= SDL_LoadBMP(field_pic);
				image=SDL_DisplayFormat( test );
				SDL_FreeSurface(test);
				if(DEBUG)printf("Field\n");
				src.x = 50*data->hedgewood[j+scrollposition][i].type;
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
			SDL_FreeSurface(image);
		}
	}
	
	image=load_image(person_pic);
	src.x = 50*data->player.heading;
	src.y = 0;
	src.w =src.h = 50;
	dst.x = 50*data->player.p_pos.x;
	dst.y = 50*data->player.p_pos.y;
	dst.w = dst.h = 50;
	SDL_BlitSurface(image, &src, l_screen, &dst);
    SDL_Flip(l_screen);
	printf("Test\n");
	SDL_FreeSurface(image);
			
	return 1;
}
					
void graphicLoop(SDL_Surface *l_screen, struct dataStore *data){
	int done=0;
	SDL_Event event;
	struct position *mouse_pos=malloc(sizeof(struct position)); //*tmp=NULL;
			
			while (!done) {
				/* Check for events */
				while ( SDL_PollEvent(&event) ) {
					switch (event.type) {
						
					case SDL_MOUSEBUTTONDOWN:
						//tmp=malloc(sizeof(struct position));
						SDL_GetMouseState(&mouse_pos->x,&mouse_pos->y);
						printf("Cusor-Position x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
						mouse_pos=pixelToGrid(mouse_pos);
						printf("Cusor-Feld x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
						data->player.p_pos.x=mouse_pos->x;
						data->player.p_pos.y=mouse_pos->y;
						printf("Player-Feld x: %d y: %d\n",data->player.p_pos.x,data->player.p_pos.y);
						updateGraphics(l_screen, data);
						break;
						
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
}

struct position *pixelToGrid(struct position *l_pos){
	int gridsize=50;
	struct position *pos=malloc(sizeof(struct position));
	pos->x=(l_pos->x)/gridsize;
	pos->y=(l_pos->y)/gridsize;
	return pos;
}
struct position *gridToPixel(struct position *l_pos){
	int gridsize=50;
	struct position *pos=malloc(sizeof(struct position));
	pos->x=(l_pos->x)*gridsize+25;
	pos->y=(l_pos->y)*gridsize+25;
	return pos;
}

