/* Die Hauptschleife des Spiels, die die entsprechenden Funktionen aufruft*/
#include "gameloop.h"
/*Zufallsfeld Erstellung und Figur auf Anfang*/
void createRandomField(dataStore *ingame) {
	int i,j,k=0,r;
	for(i=0; i<2; i++) {
		for(j=0; j<16; j++) {
			ingame->hedgewood[i][j].visible=1;
			ingame->hedgewood[i][j].type=-1;
			ingame->hedgewood[i][j].aStarValue=1;
		}
	}
	for(i=2; i<FIELDSIZE_Y-1; i++) {
		ingame->hedgewood[i][0].visible=1;
		ingame->hedgewood[i][0].type=1;
		ingame->hedgewood[i][0].aStarValue=-1;
		ingame->hedgewood[i][FIELDSIZE_X-1].visible=1;
		ingame->hedgewood[i][FIELDSIZE_X-1].type=2;
		ingame->hedgewood[i][FIELDSIZE_X-1].aStarValue=-1;
	}
	for(i=1; i<FIELDSIZE_X-1; i++) {
		ingame->hedgewood[FIELDSIZE_Y-1][i].visible=1;
		ingame->hedgewood[FIELDSIZE_Y-1][i].type=4;
		ingame->hedgewood[FIELDSIZE_Y-1][i].aStarValue=-1;
	}
	ingame->hedgewood[FIELDSIZE_Y-1][0].visible=1;
	ingame->hedgewood[FIELDSIZE_Y-1][0].type=3;
	ingame->hedgewood[FIELDSIZE_Y-1][0].aStarValue=-1;
	ingame->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].visible=1;
	ingame->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].type=5;
	ingame->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].aStarValue=-1;
	srand (10);
	//(unsigned) time(NULL)
	for(i=2; i<FIELDSIZE_Y-1; i++) {
		for(j=1; j<FIELDSIZE_X-1; j++) {
			k=rand()%100+i;
			
			if(i>2)ingame->hedgewood[i][j].visible=0;
			else ingame->hedgewood[i][j].visible=1;
			
			if (k>=100)
				k=9;
			else if(k>=50 && k<100)
				k=8;
			else if(k<50)
				k=7;
		
		ingame->hedgewood[i][j].type=k;
		if (k==4)
			k=1;
		else if(k==7)
			k=10;
		else if(k==8)
			k=20;
		else if(k==9)
			k=30;
		ingame->hedgewood[i][j].aStarValue=k;
		}
		}
	ingame->player.p_pos.x=7;
	ingame->player.p_pos.y=1;
	ingame->player.p_pos.next=NULL;
	ingame->player.heading=2;
	ingame->player.anfang=NULL;
	ingame->player.vision=1;
	ingame->player.maxEnergy=1000;
	ingame->player.currentEnergy=1000;
	ingame->verticalScroll=0;
}
int gameloop(dataStore *ingame,SDL_Surface *screen) {
	createRandomField(ingame);
	int done=0,i=0,aVal;
	SDL_Event event;
	position home;
	home.x=7;
	home.y=1;
	struct position *mouse_pos=NULL,*tmp=NULL;
	updateGraphics(screen,ingame);
	while (!done) {
		while ( SDL_PollEvent(&event) ) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ) {
				case SDLK_h:
					aStar(ingame,&home);
					break;
				case SDLK_ESCAPE:
					ingameMenuStart(screen, ingame);
					updateGraphics(screen, ingame);
					break;
				case SDLK_q:
					done = 1;
					break;
				default:
					break;
				}
			case SDL_MOUSEBUTTONDOWN:				
			mouse_pos=calloc(1,sizeof(struct position));
				SDL_GetMouseState(&mouse_pos->x,&mouse_pos->y);
				printf("Cusor-Position x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
				mouse_pos=pixelToGrid(mouse_pos);
				if(DEBUG)printf("Cusor-Feld x: %d y: %d\n",mouse_pos->x,mouse_pos->y);
				mouse_pos->y+=ingame->verticalScroll;
				aStar(ingame,mouse_pos);
				updateGraphics(screen, ingame);
				free(mouse_pos);
				if((tmp =calloc(1,sizeof(struct position))) == NULL) {
					printf("MEM::graphicUpdate::104\n");
					return 0;
				}
				i=1;
				SDL_Delay(250);
				while(tmp!=NULL&&i) {
					while ( SDL_PollEvent(&event) ) {
						switch (event.type) {
						case SDL_MOUSEBUTTONDOWN:
							i=0;
							break;
						case SDL_KEYDOWN:
							switch( event.key.keysym.sym ) {
							default:
								break;
							}
						default:
							break;
						}
					}
					tmp=positionListRead(ingame);
					if(tmp!=NULL) {
						printf("Position Stack x: %d y: %d\n",tmp->x,tmp->y);
						headPositionUpdate(ingame,tmp);
						aVal=ingame->hedgewood[ingame->player.p_pos.y][ingame->player.p_pos.x].aStarValue;
						SDL_Delay(aVal*30+100);
						ingame->player.currentEnergy-=aVal;
						ingame->hedgewood[ingame->player.p_pos.y][ingame->player.p_pos.x].type=6;
						ingame->hedgewood[ingame->player.p_pos.y][ingame->player.p_pos.x].aStarValue=1;
						updateGraphics(screen,ingame);
					}
				}
				free(tmp);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}
