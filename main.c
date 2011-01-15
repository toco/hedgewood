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

void makeTestData(dataStore *test)

{
	int i,j,k=0;

	/* testdata for updateGrapics */
	for(i=0;i<2;i++){
		for(j=0;j<16;j++){
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=-1;
			test->hedgewood[i][j].aStarValue=1;
		}
	}
	for(i=2;i<24;i++){
		test->hedgewood[i][0].visible=1;
		test->hedgewood[i][0].type=1;
		test->hedgewood[i][0].aStarValue=-1;
		test->hedgewood[i][15].visible=1;
		test->hedgewood[i][15].type=2;
		test->hedgewood[i][15].aStarValue=-1;
	}
	for(i=1;i<15;i++){
		test->hedgewood[23][i].visible=1;
		test->hedgewood[23][i].type=3;
		test->hedgewood[23][i].aStarValue=-1;
		
	}
	
	for(i=2;i<23;i++){
		k=0;
		for(j=1;j<15;j++){
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=(k%4)+4;
			test->hedgewood[i][j].aStarValue=((k%4)+1)*10;
			k++;
		}
	}
	test->player.p_pos.x=7;
	test->player.p_pos.y=1;
	test->player.p_pos.next=NULL;
	test->player.heading=0;
	test->player.anfang=NULL;
	test->verticalScroll=0;
	
}

void createRandomField(dataStore *test)
{
	int i,j,k=0;
	
	/* testdata for updateGrapics */
	for(i=0;i<2;i++){
		for(j=0;j<16;j++){
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=-1;
			test->hedgewood[i][j].aStarValue=1;
		}
	}
	for(i=2;i<24;i++){
		test->hedgewood[i][0].visible=1;
		test->hedgewood[i][0].type=1;
		test->hedgewood[i][0].aStarValue=-1;
		test->hedgewood[i][15].visible=1;
		test->hedgewood[i][15].type=2;
		test->hedgewood[i][15].aStarValue=-1;
	}
	for(i=1;i<15;i++){
		test->hedgewood[23][i].visible=1;
		test->hedgewood[23][i].type=3;
		test->hedgewood[23][i].aStarValue=-1;
	}
	srand (1);
	for(i=2;i<23;i++){
		for(j=1;j<15;j++){
			k=rand()%4+4;
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=(k%4)+4;
			if (k=4)
				k=1;
			else if(k=5)
				k=10;
			else if(k=6)
				k=20;
			else if(k=7)
				k=30;
			test->hedgewood[i][j].aStarValue=k;
		}
	}
	test->player.p_pos.x=7;
	test->player.p_pos.y=1;
	test->player.p_pos.next=NULL;
	test->player.heading=0;
	test->player.anfang=NULL;
	test->verticalScroll=0;
}
void highscoreTestdata(dataStore *store)
{
	char *test = "nobody";
	int i;
	for (i=0; i<10; i++) {
		store->highscore[i].points=0;
		strncpy(store->highscore[i].name,test,strlen(test));

	}
}

int main(int argc, char *argv[])
{
	printf("%s %d",argv[0],argc);


	dataStore *test = malloc(sizeof(dataStore));
	
	highscoreTestdata(test);
	
	SDL_Surface* screen=initSDL();
	
	readDataStore(test);
	
	menuStart(screen, test);
	

	saveDataStore(test);

/* just for testing*/
 
	//makeTestData(test);
	createRandomField(test);
	updateGraphics(screen,test);
	graphicLoop(screen,test);


	quitSDL();
//	free(test);
	
	return 0;
}