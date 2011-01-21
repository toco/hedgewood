/* Die Hauptschleife des Spiels, die die entsprechenden Funktionen aufruft*/
#include "gameloop.h"
/*Zufallsfeld Erstellung und Figur auf Anfang*/
void createRandomField(dataStore *data) {
	int i,j,k=0,r,r_currency;
	double fortschritt,sand,mittel,leicht,schwer,tmp;

	for(i=0; i<4; i++) {
		for(j=0; j<16; j++) {
			data->hedgewood[i][j].visible=1;
			data->hedgewood[i][j].type=-1;
			if(j==0||j==15||i==0)data->hedgewood[i][j].aStarValue=-1;
			else {
			data->hedgewood[i][j].aStarValue=0;
			data->hedgewood[i][j].currency=0;
			}
		}
	}
	for(i=4; i<FIELDSIZE_Y-1; i++) {
		data->hedgewood[i][0].visible=1;
		data->hedgewood[i][0].type=1;
		data->hedgewood[i][0].aStarValue=-1;
		data->hedgewood[i][0].currency=0;
		data->hedgewood[i][FIELDSIZE_X-1].visible=1;
		data->hedgewood[i][FIELDSIZE_X-1].type=2;
		data->hedgewood[i][FIELDSIZE_X-1].aStarValue=-1;
		data->hedgewood[i][FIELDSIZE_X-1].currency=0;
	}
	for(i=1; i<FIELDSIZE_X-1; i++) {
		data->hedgewood[FIELDSIZE_Y-1][i].visible=1;
		data->hedgewood[FIELDSIZE_Y-1][i].type=4;
		data->hedgewood[FIELDSIZE_Y-1][i].aStarValue=-1;
		data->hedgewood[FIELDSIZE_Y-1][i].currency=0;
	}
	data->hedgewood[FIELDSIZE_Y-1][0].visible=1;
	data->hedgewood[FIELDSIZE_Y-1][0].type=3;
	data->hedgewood[FIELDSIZE_Y-1][0].aStarValue=-1;
	data->hedgewood[FIELDSIZE_Y-1][0].currency=0;
	data->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].visible=1;
	data->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].type=5;
	data->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].aStarValue=-1;
	data->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].currency=0;
	srand (time(0));
	for(i=4; i<FIELDSIZE_Y-1; i++) {
		fortschritt = (double)i/(double)FIELDSIZE_Y;
		for(j=1; j<FIELDSIZE_X-1; j++) {
			sand = 0.2 - fortschritt / 10;
			if (fortschritt < 0.5) {
				leicht = 1 - fortschritt * 2;
				if (leicht < 0.05) leicht = 0.05;
				mittel = 1 - leicht;
				if (mittel > sand) {
					mittel-= sand;
				} else {
					leicht -= sand;
				}
				schwer = 0;
			} else {
				leicht = 0.05;
				mittel = 0.95 - (fortschritt-0.5)*2;
				if (mittel < 0.05) mittel = 0.05;
				schwer = 1 - mittel;
				if (schwer > sand) {
					schwer -= sand;
				} else {
					mittel -= sand;
				}
			}
			tmp=sand+leicht+mittel+schwer;
			r=rand()%100+1;
			if(i==4)data->hedgewood[i][j].visible=1;
			else data->hedgewood[i][j].visible=0;
			if (r<sand*100)
				k=6;
			else if(r<sand*100+leicht*100)
				k=7;
			else if(r<sand*100+leicht*100+mittel*100)
				k=8;
			else {
				k=9;
			}
			data->hedgewood[i][j].type=k;
			data->hedgewood[i][j].aStarValue=(k-6)*10+2;
			if (r<=50)
				r_currency=0;
			else if (r<=60)
				r_currency=6;
			else if (r_currency<=70)
				r_currency=7;
			else if (r<=80)
				r_currency=8;
			else if (r<=90)
				r_currency=9;
			else
				r_currency= 10;
			data->hedgewood[i][j].currency=(k-6)*r_currency;
		}
	}
	data->player.p_pos.x=7;
	data->player.p_pos.y=1;
	data->player.p_pos.next=NULL;
	data->player.heading=0;
	data->player.anfang=NULL;
	data->player.vision=1;
	data->player.maxEnergy=1000;
	data->player.currentEnergy=1000;
	data->verticalScroll=0;
	data->player.bp.currentVolume=0;
	data->player.bp.maxVolume=400;
	data->player.candystash=0;
	data->home.x=7;
	data->home.y=2;
	data->player.cutSpeed=1.0;
	
}

int gameloop(dataStore *data,SDL_Surface *screen)
{
	
	createRandomField(data);	
	
	clock_t innerStartTime, innerStopTime, startTime, stopTime, diffTime,mouseTime,mT,mousetimewait=500;
	int done=0,i=0,aVal,motionPath=0,runPath=0,drawPath=0;
	position *lastmouse=NULL,*mouse_pos=NULL,*tmp=NULL;
	SDL_Event event;
	GraphicUpdate(screen,data);
	
	while (!done) {
		/* Check for events */
		startTime = SDL_GetTicks();
		while ( SDL_PollEvent(&event) ) {
			innerStartTime = SDL_GetTicks();
			switch (event.type) {
			case SDL_MOUSEMOTION:
			//Prüft ob sich die Maus aus dem 50x50 Feld bewegt hat
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
						return -1;
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
						return -1;
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
					aStar(data,&(data->home));
					runPath=1;
					break;
				case SDLK_ESCAPE:
					done = ingameMenuStart(screen, data);
					if (!done)
						GraphicUpdate(screen, data);
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
			if (MS_FRAMETIME>diffTime)SDL_Delay(MS_FRAMETIME-diffTime);
		}
		mT=SDL_GetTicks();
		if((mouseTime + mousetimewait)< mT && lastmouse!=0) {
			motionPath=1;
		}
		if((motionPath || runPath) && !done) {
			if(motionPath) {
				lastmouse->y+=data->verticalScroll;
				aStar(data,lastmouse);
				if(DEBUG)printf("Player-Feld x: %d y: %d\n",data->player.p_pos.x,data->player.p_pos.y);
				GraphicUpdate(screen, data);
				aStarPathPrint(data,screen);
				free(lastmouse);
				lastmouse=NULL;
				motionPath=0;
				drawPath=0;
			}
			if(runPath) {
				i=1;
				tmp=data->player.anfang;				
				while(tmp!=NULL&&i) {
					//Schleife um die Laufbewegung Abzubrechen
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
						SDL_Delay((aVal*60/data->player.cutSpeed)+100);
						
						if(aVal>0){
							data->player.currentEnergy-=aVal;
							if(data->player.currentEnergy<0){
								printf("YOU ARE DEAD\n NEW GAME\n");
								return 1;
							}
							else {
								data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].type=6;
								data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].aStarValue=2;
								data->player.bp.currentVolume+=data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].currency;
								if(data->player.bp.currentVolume > data->player.bp.maxVolume) data->player.bp.currentVolume=data->player.bp.maxVolume;
								data->hedgewood[data->player.p_pos.y][data->player.p_pos.x].currency=0;
							}
						}
						
						GraphicUpdate(screen,data);
					}
				}				
				runPath=0;
			}
		}
		stopTime = SDL_GetTicks();
		diffTime = (stopTime-startTime);
		if (MS_FRAMETIME>diffTime)SDL_Delay(MS_FRAMETIME-diffTime);
	}
	return 0;
}
