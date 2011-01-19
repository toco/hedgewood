#include "SDLincludes.h"


#include "graphicUpdate.h"
#define field_pic "./pictures/textur5.png"
#define start_pic "./pictures/startzonetest.png"
#define person_pic "./pictures/person.png"
#define kreis_pic "./pictures/kreis.png"


int updateGraphics(SDL_Surface *l_screen,dataStore *data){

	int i,j,scrollposition=data->verticalScroll,startzone=0;
	float energy;
	SDL_Surface *image_start=NULL,*image_field=NULL,*image_person=NULL;
	SDL_Rect src, dst;

	if ((image_start =load_image(start_pic))== NULL) {
				printf("Can't load image start: %s\n", SDL_GetError());
				exit(1);
	}
	if ((image_field=load_image(field_pic)) == NULL) {
				printf("Can't load image field: %s\n", SDL_GetError());
				exit(1);
	}
	if ((image_person=load_image(person_pic)) == NULL) {
				printf("Can't load image person: %s\n", SDL_GetError());
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
	aStarPathPrint(data,l_screen);		
	return 1;
}
					
void graphicLoop(SDL_Surface *l_screen,dataStore *data) {
	clock_t startTime, stopTime, diffTime;
	clock_t innerStartTime, innerStopTime;
	printf("Clocks: %d\n",(int)CLOCKS_PER_SEC);
	
	int done=0,i=0,aVal;
	
	SDL_Event event;
	position home;
	home.x=7;
	home.y=1;
	struct position *mouse_pos=NULL,*tmp=NULL;
	while (!done) {
		/* Check for events */
		startTime = clock();
		while ( SDL_PollEvent(&event) ) {
			innerStartTime = clock();
			switch (event.type) {
			case SDL_MOUSEBUTTONUP:
				mouse_pos=calloc(1,sizeof(struct position));
				SDL_GetMouseState(&mouse_pos->x,&mouse_pos->y);
				printf("Cusor-Position x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
				mouse_pos=pixelToGrid(mouse_pos);
				if(DEBUG)printf("Cusor-Feld x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
				mouse_pos->y+=data->verticalScroll;
				aStar(data,mouse_pos);
				if(DEBUG)printf("Player-Feld x: %d y: %d\n",data->player.p_pos.x,data->player.p_pos.y);
				updateGraphics(l_screen, data);
				free(mouse_pos);
				aStarPathPrint(data,l_screen);
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
								data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].type=6;
								data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].aStarValue=1;
								updateGraphics(l_screen,data);
						}
					}
					free(tmp);
					break;
				case SDLK_h:
					aStar(data,&home);
					break;
				case SDLK_p:
					aStarPathPrint(data,l_screen);
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
			innerStopTime = clock();
			diffTime=1000*(innerStopTime-innerStartTime)/CLOCKS_PER_SEC;
			//25 Frames per second (40 Milliseconds per frame)
			if (4>diffTime)
				SDL_Delay(4-diffTime);
				
		}
		stopTime = clock();
		diffTime = 1000*(stopTime-startTime)/CLOCKS_PER_SEC;
		//25 Frames per second (40 Milliseconds per frame)
		if (4>diffTime)
			
			SDL_Delay(4-diffTime);	
	
		
	}
}

struct position *pixelToGrid(position *l_pos){

	struct position *pos=malloc(sizeof(struct position));
	pos->x=(l_pos->x)/FIELDSIZE_FIELD;
	pos->y=(l_pos->y)/FIELDSIZE_FIELD;
	pos->next=NULL;
	return pos;
}
struct position *gridToPixel(struct position *l_pos,dataStore *data){
	struct position *pos=malloc(sizeof(struct position));
	pos->x=(l_pos->x)*FIELDSIZE_FIELD;
	pos->y=(l_pos->y-data->verticalScroll)*FIELDSIZE_FIELD;
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
			if(n_pos.y+i>0&&n_pos.y+i<FIELDSIZE_Y &&n_pos.x+i>0&&n_pos.x+i<FIELDSIZE_X){
				if(y>0 && i<0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
				else if(x<0 && j>0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
				else if(y<0 && i>0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
				else if(x>0 && j<0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
			} 
		}
	}
	
	data->player.p_pos=n_pos;
	verticalScrollPos(data);
}

void aStarPathPrint(dataStore *data,SDL_Surface *l_screen){
	
	SDL_Surface *kreis=NULL;
	SDL_Rect  src,dst;

	if ((kreis =load_image(kreis_pic))== NULL) {
				printf("Can't load image start: %s\n", SDL_GetError());
				exit(1);
	}
	position *tmp=data->player.anfang,*tmpPixel;
	src.w=src.h=dst.w=dst.h=FIELDSIZE_FIELD;
	while(tmp!=NULL){
		tmpPixel=gridToPixel(tmp,data);
		dst.x=tmpPixel->x;
		dst.y=tmpPixel->y;
		if(tmp->next==NULL)src.x=50;
		else src.x=0;
		src.y=0;
		if(dst.y>=0)SDL_BlitSurface(kreis, &src, l_screen, &dst);
		free(tmpPixel);
		tmp=tmp->next;
	}
	SDL_Flip(l_screen);
	SDL_FreeSurface(kreis);
	
	
}