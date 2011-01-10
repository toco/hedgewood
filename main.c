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

void makeTestData(struct dataStore *test)

{
	int i,j,k=0;

	/* testdata for updateGrapics */
	for(i=0;i<2;i++){
		for(j=0;j<16;j++){
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=-1;
		}
	}
	for(i=2;i<24;i++){
		test->hedgewood[i][0].visible=1;
		test->hedgewood[i][0].type=0;
		test->hedgewood[i][15].visible=1;
		test->hedgewood[i][15].type=0;
	}
	for(i=1;i<15;i++){
		test->hedgewood[23][i].visible=1;
		test->hedgewood[23][i].type=0;
		
	}
	
	for(i=2;i<23;i++){
		for(j=1;j<15;j++){
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=(k%3)+1;
			k++;
		}
	}
	test->player.p_pos.x=7;
	test->player.p_pos.y=1;
	test->player.heading=0;
	test->verticalScroll=0;
	
}
int main(int argc, char *argv[])
{
	
	SDL_Surface* screen=initSDL();
	menuStart(screen);
	
	struct dataStore *test = malloc(sizeof(struct dataStore));

/* just for testing*/
 
	makeTestData(test);
	updateGraphics(screen,test);
	graphicLoop(screen,test);

	
	quitSDL();
	free(test);
	
	return 0;
}