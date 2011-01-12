#include "SDLincludes.h"


#include "graphicUpdate.h"
#define field_pic "./pictures/textur2.1.png"
#define start_pic "./pictures/startzone.bmp"
#define person_pic "./pictures/person.bmp"


int updateGraphics(SDL_Surface *l_screen, struct dataStore *data){

	int i,j,scrollposition=data->verticalScroll;
	SDL_Surface *image=NULL;
	SDL_Rect src, dst;

	for(j=0;j<12;j++){
		for(i=0;i<16;i++){
			if(data->hedgewood[j+scrollposition][i].type==-1){
				image=load_image(start_pic);
//				if(DEBUG)printf("Startzone\n");
				src.x = 50*i;
				src.y = 50*j;
			}
			else{

				image=load_image(field_pic);
//				if(DEBUG)printf("Field\n");
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
	dst.y = 50*(data->player.p_pos.y-scrollposition);
	dst.w = dst.h = 50;
	SDL_BlitSurface(image, &src, l_screen, &dst);
    SDL_Flip(l_screen);
	SDL_FreeSurface(image);
			
	return 1;
}
					
void graphicLoop(SDL_Surface *l_screen, struct dataStore *data){
	int done=0;
	SDL_Event event;
	struct position *mouse_pos=NULL,*tmp=NULL;
			
			while (!done) {
				/* Check for events */
				while ( SDL_PollEvent(&event) ) {
					switch (event.type) {
						
					case SDL_MOUSEBUTTONDOWN:
						mouse_pos=calloc(1,sizeof(struct position));
						SDL_GetMouseState(&mouse_pos->x,&mouse_pos->y);
							
						printf("Cusor-Position x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
						mouse_pos=pixelToGrid(mouse_pos);
						if(DEBUG)printf("Cusor-Feld x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
						data->player.p_pos.x=mouse_pos->x;
						data->player.p_pos.y=mouse_pos->y+=data->verticalScroll;
						positionListAdd(data,mouse_pos);
						if(DEBUG)printf("Player-Feld x: %d y: %d\n",data->player.p_pos.x,data->player.p_pos.y);
						verticalScrollPos(data);
						updateGraphics(l_screen, data);
						free(mouse_pos);
						break;
						
					case SDL_KEYDOWN:
					/* Any keypress quits the app... */
						switch( event.key.keysym.sym )
					{
						case SDLK_o:
							if((tmp =calloc(1,sizeof(struct position))) == NULL) {
								printf("MEM::pathfinding::42\n");
								return;
							}
							tmp=positionListRead(data);
							if(tmp!=NULL){
								printf("Position Stack x: %d y: %d\n",tmp->x,tmp->y);
								free(tmp);
							};
							
							
							break;
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

void verticalScrollPos(struct dataStore *data){
	int verticalScroll,verticalPos=data->player.p_pos.y;
	
	if(verticalPos<7)verticalScroll=0;
	else if (verticalPos>6 && verticalPos<19 )verticalScroll=verticalPos-6;
	else verticalScroll=12;

	data->verticalScroll=verticalScroll;
	printf("verticalScroll data/function: %d : %d\n",data->verticalScroll,verticalScroll);
}
