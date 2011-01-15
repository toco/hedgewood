#include "SDLincludes.h"


#include "graphicUpdate.h"
#define field_pic "./pictures/textur2.1.png"
#define start_pic "./pictures/startzonetest.png"
#define person_pic "./pictures/person.png"


int updateGraphics(SDL_Surface *l_screen,dataStore *data){

	int i,j,scrollposition=data->verticalScroll,startzone=0;
	float energy;
	SDL_Surface *image_start=NULL,*image_field=NULL,*image_person=NULL;
	SDL_Rect src, dst;

	if ((image_start =load_image(start_pic))== NULL) {
				printf("Can't load image red: %s\n", SDL_GetError());
				exit(1);
	}
	if ((image_field=load_image(field_pic)) == NULL) {
				printf("Can't load image red: %s\n", SDL_GetError());
				exit(1);
	}
	if ((image_person=load_image(person_pic)) == NULL) {
				printf("Can't load image red: %s\n", SDL_GetError());
				exit(1);
	}
	
	src.w =src.h = FIELDSIZE_FIELD;	
	dst.w = dst.h = FIELDSIZE_FIELD;
	for(j=0;j<12;j++){
		dst.y = FIELDSIZE_FIELD*j;
		if(data->hedgewood[j+scrollposition][1].type==-1)startzone=1;
		else startzone=0;
		
		for(i=0;i<16;i++){
			dst.x = FIELDSIZE_FIELD*i;
			
			if(startzone){
//				if(DEBUG)printf("Startzone\n");
				src.x = FIELDSIZE_FIELD*i;
				src.y = FIELDSIZE_FIELD*(j+scrollposition);
			}
			else{
//				if(DEBUG)printf("Field\n");
				src.x = FIELDSIZE_FIELD*data->hedgewood[j+scrollposition][i].type*data->hedgewood[j+scrollposition][i].visible;
				src.y = 0;
			}
			
			if(startzone)SDL_BlitSurface(image_start, &src, l_screen, &dst);
			else SDL_BlitSurface(image_field, &src, l_screen, &dst);
			
		}
	}
	SDL_FreeSurface(image_start);
	SDL_FreeSurface(image_field);
	src.x = FIELDSIZE_FIELD*data->player.heading;
	src.y = 0;
	src.w =src.h = FIELDSIZE_FIELD;
	dst.x = FIELDSIZE_FIELD*data->player.p_pos.x;
	dst.y = FIELDSIZE_FIELD*(data->player.p_pos.y-scrollposition);
	dst.w = dst.h = FIELDSIZE_FIELD;
	
	SDL_BlitSurface(image_person, &src, l_screen, &dst);
	
	src.x=dst.x = 25;
	src.y=dst.y = 25;
	dst.w = 200;
	src.h=dst.h = 25;
	energy=200*(((float)data->player.currentEnergy)/((float)data->player.maxEnergy));
	src.w = energy;
	SDL_FillRect(l_screen, &dst, SDL_MapRGBA( l_screen->format, 64, 0, 0,255));
	SDL_FillRect(l_screen, &src, SDL_MapRGBA( l_screen->format, 255, 64, 64,150));
	
    SDL_Flip(l_screen);
	SDL_FreeSurface(image_person);
			
	return 1;
}
					
void graphicLoop(SDL_Surface *l_screen,dataStore *data) {
	int done=0,i=0,aVal;
	SDL_Event event;
	position home;
	home.x=7;
	home.y=1;
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
				mouse_pos->y+=data->verticalScroll;
				if(DBPATH) aStar(data,mouse_pos);
				else positionListAdd(data,mouse_pos);
				if(DEBUG)printf("Player-Feld x: %d y: %d\n",data->player.p_pos.x,data->player.p_pos.y);
				updateGraphics(l_screen, data);
				free(mouse_pos);
				break;
			case SDL_KEYDOWN:
				/* Any keypress quits the app... */
				switch( event.key.keysym.sym ) {
				case SDLK_r:
					if((tmp =calloc(1,sizeof(struct position))) == NULL) {
						printf("MEM::graphicUpdate::104\n");
						return;
					}
					i=1;
					SDL_Delay(250);
					while(tmp!=NULL&&i) {
						while ( SDL_PollEvent(&event) ) {
							switch (event.type) {
							case SDL_KEYDOWN:
								switch( event.key.keysym.sym ) {
								case SDLK_r:
									i=0;
									break;
								default:
									break;
								}
							default:
								break;
							}
							
						}
						tmp=positionListRead(data);
						if(tmp!=NULL) {
								printf("Position Stack x: %d y: %d\n",tmp->x,tmp->y);
								headPositionUpdate(data,tmp);
								aVal=data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].aStarValue;
								SDL_Delay(aVal*30+100);
								data->player.currentEnergy-=aVal;
								data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].type=4;
								data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].aStarValue=1;
								updateGraphics(l_screen,data);
						}
					}
					free(tmp);
					break;
				case SDLK_h:
					aStar(data,&home);
					break;
				case SDLK_ESCAPE:
					ingameMenuStart(l_screen, data);
					updateGraphics(l_screen, data);
					break;
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

struct position *pixelToGrid(position *l_pos){

	struct position *pos=malloc(sizeof(struct position));
	pos->x=(l_pos->x)/FIELDSIZE_FIELD;
	pos->y=(l_pos->y)/FIELDSIZE_FIELD;
	pos->next=NULL;
	return pos;
}
struct position *gridToPixel(struct position *l_pos){
	struct position *pos=malloc(sizeof(struct position));
	pos->x=(l_pos->x)*FIELDSIZE_FIELD+25;
	pos->y=(l_pos->y)*FIELDSIZE_FIELD+25;
	return pos;
}

void verticalScrollPos(struct dataStore *data){
	int verticalScroll,verticalPos=data->player.p_pos.y;
	
	if(verticalPos<7)verticalScroll=0;
	else if (verticalPos>6 && verticalPos<FIELDSIZE_Y-5 )verticalScroll=verticalPos-6;
	else verticalScroll=FIELDSIZE_Y-12;

	data->verticalScroll=verticalScroll;
	if(DEBUG)printf("verticalScroll data/function: %d : %d\n",data->verticalScroll,verticalScroll);
}

void headPositionUpdate(dataStore *data,position *newPos){
	position old=data->player.p_pos,n_pos=(*newPos);
	int x=0,y=0,vis=data->player.vision,i,j;
	x=old.x-n_pos.x;
	y=old.y-n_pos.y;
	if(x<0)data->player.heading=1;
	if(x>0)data->player.heading=3;
	if(y<0)data->player.heading=2;
	if(y>0)data->player.heading=0;
	for(i=-vis; i<=vis;i++) {
		for(j=-vis; j<=vis;j++) {
		if(y>0 && i<0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
		if(x<0 && j>0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
		if(y<0 && i>0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
		if(x>0 && j<0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
		}
	}
	
	data->player.p_pos=n_pos;
	verticalScrollPos(data);
}
