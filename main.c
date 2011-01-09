/*
 *  main.c
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 08.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */

#include "main.h"



int main(int argc, char *argv[])
{
	int i,j,k=0;
	
	SDL_Surface* screen=initSDL();
	menuStart(screen);
	struct dataStore *test = malloc(sizeof(struct dataStore));
	
	for(i=0;i<2;i++){
		for(j=0;j<16;j++){
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=-1;
		}
	}
	for(i=2;i<12;i++){
			test->hedgewood[i][0].visible=1;
			test->hedgewood[i][0].type=0;
			test->hedgewood[i][15].visible=1;
			test->hedgewood[i][15].type=0;
	}
	for(i=1;i<15;i++){
			test->hedgewood[11][i].visible=1;
			test->hedgewood[11][i].type=0;
			
	}
	
	for(i=2;i<11;i++){
		for(j=1;j<15;j++){
			test->hedgewood[i][j].visible=1;
			if(k++>3)k=1;
			test->hedgewood[i][j].type=k;
		}
	}
	
	
	quitSDL();
	

	return 0;
}