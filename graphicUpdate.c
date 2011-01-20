#include "SDLincludes.h"
#include "graphicUpdate.h"
#define field_pic "./pictures/textur5.png"
#define start_pic "./pictures/startzonetest.png"
#define person_pic "./pictures/person.png"
#define kreis_pic "./pictures/kreis.png"
#define candy_pic "./pictures/zuckerstangen.png"
int updateGraphics(SDL_Surface *l_screen,dataStore *data) {
	int i,j,scrollposition=data->verticalScroll,startzone=0;
	float energy;
	SDL_Surface *image_start=NULL,*image_field=NULL,*image_person=NULL,*image_candy=NULL;
	SDL_Rect src, dst, src2;
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
	if ((image_candy=load_image(candy_pic)) == NULL) {
		printf("Can't load image person: %s\n", SDL_GetError());
		exit(1);
	}
	src.w =src.h = FIELDSIZE_FIELD;
	dst.w = dst.h = FIELDSIZE_FIELD;
	for(j=0; j<12; j++) {
		dst.y = FIELDSIZE_FIELD*j;
		if(data->hedgewood[j+scrollposition][1].type==-1)startzone=1;
		else startzone=0;
		for(i=0; i<16; i++) {
			dst.x = FIELDSIZE_FIELD*i;
			if(startzone) {
				src.x = FIELDSIZE_FIELD*i;
				src.y = FIELDSIZE_FIELD*(j+scrollposition);
			} else {
				src.x = FIELDSIZE_FIELD*data->hedgewood[j+scrollposition][i].type*data->hedgewood[j+scrollposition][i].visible;
				src.y = 0;
			}
			if(startzone)SDL_BlitSurface(image_start, &src, l_screen, &dst);
			else {
				SDL_BlitSurface(image_field, &src, l_screen, &dst);
				//print candy
				if(data->hedgewood[j+scrollposition][i].currency > 0 && src.x>0) {
					src2=src;
					src2.x=50*((data->hedgewood[j+scrollposition][i].currency-1)/10);
					SDL_BlitSurface(image_candy, &src2, l_screen, &dst);
				}
			}
		}
	}
	SDL_FreeSurface(image_start);
	SDL_FreeSurface(image_field);
	SDL_FreeSurface(image_candy);
	//print Person
	src.x = FIELDSIZE_FIELD*data->player.heading;
	src.y = 0;
	src.w =src.h = FIELDSIZE_FIELD;
	dst.x = FIELDSIZE_FIELD*data->player.p_pos.x;
	dst.y = FIELDSIZE_FIELD*(data->player.p_pos.y-scrollposition);
	dst.w = dst.h = FIELDSIZE_FIELD;
	SDL_BlitSurface(image_person, &src, l_screen, &dst);
	//print energy bar
	src.x= 25;
	dst.x = 23;
	src.y=25;
	dst.y = 23;
	dst.w = 204;
	src.h=25;
	dst.h = 29;
	energy=200*(((float)data->player.currentEnergy)/((float)data->player.maxEnergy));
	src.w = energy;
	SDL_FillRect(l_screen, &dst, SDL_MapRGBA( l_screen->format, 0,0, 0,255));
	dst.x = 573;
	SDL_FillRect(l_screen, &dst, SDL_MapRGBA( l_screen->format, 0,0, 0,255));
	dst.x = 25;
	dst.y += 2;
	dst.w -= 4;
	dst.h -= 4;
	SDL_FillRect(l_screen, &dst, SDL_MapRGBA( l_screen->format, 255, 115, 0,255));
	SDL_FillRect(l_screen, &src, SDL_MapRGBA( l_screen->format, 255,201, 0,255));
	//print candy bar
	src.x=dst.x = 575;
	energy=200*(((float)data->player.bp.currentVolume)/((float)data->player.bp.maxVolume));
	src.w = energy;
	SDL_FillRect(l_screen, &dst, SDL_MapRGBA( l_screen->format, 160, 32, 64,255));
	SDL_FillRect(l_screen, &src, SDL_MapRGBA( l_screen->format, 255, 128, 192,255));
	
	for(i=0;i<3;i+=2){
	   /*Draw Text */
        char text[50];
		sprintf(text,"%d IN STASH",(data->player.candystash));
		
        SDL_Surface *message;
        TTF_Font *font = arialFont(20);
        SDL_Color textColor = { 255*i, 255*i, 255*i,0};
        if (!(message = TTF_RenderText_Blended( font, text, textColor )))
        {
                printf("%s\n",TTF_GetError());
                return 1;
        }
        TTF_CloseFont(font);
        SDL_Rect textRect = {275-i,22-i,0,0};
        if(0!=SDL_BlitSurface( message, NULL, l_screen, &textRect))
        {
                printf("%s\n",SDL_GetError());
                return 1;
        }
        SDL_FreeSurface(message);
	}
	for(i=0;i<3;i+=2){
	   /*Draw Text */
        char text[50];
		sprintf(text,"%d von %d",data->player.bp.currentVolume,data->player.bp.maxVolume);
		
        SDL_Surface *message;
        TTF_Font *font = arialFont(10);
        SDL_Color textColor = { 255*i, 255*i, 255*i,0};
        if (!(message = TTF_RenderText_Blended( font, text, textColor )))
        {
                printf("%s\n",TTF_GetError());
                return 1;
        }
        TTF_CloseFont(font);
        SDL_Rect textRect = {687-i,29-i,0,0};
        if(0!=SDL_BlitSurface( message, NULL, l_screen, &textRect))
        {
                printf("%s\n",SDL_GetError());
                return 1;
        }
        SDL_FreeSurface(message);
	}
	//end
	SDL_FreeSurface(image_person);
	aStarPathPrint(data,l_screen);
	SDL_Flip(l_screen);
	return 1;
}
void graphicLoop(SDL_Surface *l_screen,dataStore *data) {
	clock_t startTime, stopTime, diffTime,mouseTime,mT,mousetimewait=500;
	clock_t innerStartTime, innerStopTime;
	printf("Clocks: %d\n",(int)CLOCKS_PER_SEC);
	int done=0,i=0,aVal,motionPath=0,runPath=0,drawPath=0;
	SDL_Event event;
	position home,*lastmouse=NULL;
	home.x=7;
	home.y=1;
	position *mouse_pos=NULL,*tmp=NULL;
	while (!done) {
		/* Check for events */
		startTime = SDL_GetTicks();
		while ( SDL_PollEvent(&event) ) {
			innerStartTime = SDL_GetTicks();
			switch (event.type) {
			case SDL_MOUSEMOTION:
				mouse_pos=calloc(1,sizeof(struct position));
				SDL_GetMouseState(&mouse_pos->x,&mouse_pos->y);
				mouse_pos=pixelToGrid(mouse_pos);
				if(lastmouse!=NULL) {
					if(lastmouse->x!=mouse_pos->x || lastmouse->y!=mouse_pos->y)mouseTime=SDL_GetTicks(),drawPath=1;
					else {
						if(drawPath) {
							mT=SDL_GetTicks();
							if((mouseTime + mousetimewait)< mT) {
								motionPath=1;
							}
						}
					}
				} else {
					mouseTime = SDL_GetTicks();
					drawPath=1;
					if((lastmouse=calloc(1,sizeof(position))) == NULL) {
						printf("Kein Speicherplatz vorhanden fuer position\n");
						return;
					}
				}
				memcpy(lastmouse,mouse_pos,sizeof(position));
				free(mouse_pos);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse_pos=calloc(1,sizeof(struct position));
				SDL_GetMouseState(&mouse_pos->x,&mouse_pos->y);
				if(DEBUG)printf("Cusor-Position x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
				mouse_pos=pixelToGrid(mouse_pos);
				if(DEBUG)printf("Cusor-Feld x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
				if(lastmouse==NULL) {
					if((lastmouse=calloc(1,sizeof(position))) == NULL) {
						printf("Kein Speicherplatz vorhanden fuer position\n");
						return;
					}
				}
				memcpy(lastmouse,mouse_pos,sizeof(position));
				free(mouse_pos);
				mouse_pos=NULL;
				motionPath=1;
				runPath=1;
				break;
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ) {
				case SDLK_r:
					break;
				case SDLK_h:
					aStar(data,&home);
					runPath=1;
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
			innerStopTime = SDL_GetTicks();
			diffTime=(innerStopTime-innerStartTime);
			//25 Frames per second (40 Milliseconds per frame)
			if (4>diffTime)SDL_Delay(4-diffTime);
		}
		mT=SDL_GetTicks();
		if((mouseTime + mousetimewait)< mT && lastmouse!=0) {
			motionPath=1;
		}
		if(motionPath || runPath) {
			if(motionPath) {
				lastmouse->y+=data->verticalScroll;
				aStar(data,lastmouse);
				if(DEBUG)printf("Player-Feld x: %d y: %d\n",data->player.p_pos.x,data->player.p_pos.y);
				updateGraphics(l_screen, data);
				aStarPathPrint(data,l_screen);
				free(lastmouse);
				lastmouse=NULL;
				motionPath=0;
				drawPath=0;
			}
			if(runPath) {
				i=1;
				SDL_Delay(250);
				tmp=data->player.anfang;
				while(tmp!=NULL&&i) {
					while ( SDL_PollEvent(&event) ) {
						switch (event.type) {
						case SDL_MOUSEBUTTONUP:
							i=0;
							break;
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
						if(aVal>0){
						data->player.currentEnergy-=aVal;
						data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].type=6;
						data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].aStarValue=2;
						data->player.bp.currentVolume+=data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].currency;
						data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].currency=0;
						}
						updateGraphics(l_screen,data);
					}
				}
				runPath=0;
			}
		}
		stopTime = SDL_GetTicks();
		diffTime = (stopTime-startTime);
		//25 Frames per second (40 Milliseconds per frame)
		if (4>diffTime)SDL_Delay(4-diffTime);
	}
}
position *pixelToGrid(position *l_pos) {
	position *pos=calloc(1,sizeof( position));
	pos->x=(l_pos->x)/FIELDSIZE_FIELD;
	pos->y=(l_pos->y)/FIELDSIZE_FIELD;
	pos->next=NULL;
	return pos;
}
void verticalScrollPos( dataStore *data) {
	int verticalScroll,verticalPos=data->player.p_pos.y;
	if(verticalPos<7)verticalScroll=0;
	else if (verticalPos>6 && verticalPos<FIELDSIZE_Y-5 )verticalScroll=verticalPos-6;
	else verticalScroll=FIELDSIZE_Y-12;
	data->verticalScroll=verticalScroll;
	if(DEBUG)printf("verticalScroll data/function: %d : %d\n",data->verticalScroll,verticalScroll);
}
void headPositionUpdate(dataStore *data,position *newPos) {
	position old=data->player.p_pos,n_pos=(*newPos);
	int x=0,y=0,vis=data->player.vision,i,j;
	x=old.x-n_pos.x;
	y=old.y-n_pos.y;
	if(x<0)data->player.heading=1;
	if(x>0)data->player.heading=3;
	if(y<0)data->player.heading=2;
	if(y>0)data->player.heading=0;
	for(i=-vis; i<=vis; i++) {
		for(j=-vis; j<=vis; j++) {
			if(n_pos.y+i>0&&n_pos.y+i<FIELDSIZE_Y &&n_pos.x+i>0&&n_pos.x+i<FIELDSIZE_X) {
				if(y>0 && i<0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
				else if(x<0 && j>0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
				else if(y<0 && i>0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
				else if(x>0 && j<0)data->hedgewood[n_pos.y+i][n_pos.x+j].visible=1;
			}
		}
	}
	if(n_pos.y==2){
		if(n_pos.x==7)data->player.currentEnergy=data->player.maxEnergy;
		else if(n_pos.x==13){
		data->player.candystash+=data->player.bp.currentVolume;
		data->player.bp.currentVolume=0;
		printf("CANDYSTASH: %d\n",data->player.candystash);
		}	
	}
	data->player.p_pos=n_pos;
	verticalScrollPos(data);
}
void aStarPathPrint(dataStore *data,SDL_Surface *l_screen) {
	SDL_Surface *kreis=NULL;
	SDL_Rect  src,dst;
	if ((kreis =load_image(kreis_pic))== NULL) {
		printf("Can't load image start: %s\n", SDL_GetError());
		exit(1);
	}
	position *tmp=data->player.anfang;
	src.w=src.h=dst.w=dst.h=FIELDSIZE_FIELD;
	while(tmp!=NULL) {
		dst.x=tmp->x*FIELDSIZE_FIELD;
		dst.y=(tmp->y-data->verticalScroll)*FIELDSIZE_FIELD;
		if(tmp->next==NULL)src.x=50;
		else src.x=0;
		src.y=0;
		if(dst.y>=0)SDL_BlitSurface(kreis, &src, l_screen, &dst);
		tmp=tmp->next;
	}
	SDL_Flip(l_screen);
	SDL_FreeSurface(kreis);
}
