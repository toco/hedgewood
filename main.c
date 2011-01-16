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
	for(i=2;i<FIELDSIZE_Y;i++){
		test->hedgewood[i][0].visible=1;
		test->hedgewood[i][0].type=1;
		test->hedgewood[i][0].aStarValue=-1;
		test->hedgewood[i][FIELDSIZE_X-1].visible=1;
		test->hedgewood[i][FIELDSIZE_X-1].type=2;
		test->hedgewood[i][FIELDSIZE_X-1].aStarValue=-1;
	}
	for(i=1;i<15;i++){
		test->hedgewood[23][i].visible=1;
		test->hedgewood[23][i].type=3;
		test->hedgewood[23][i].aStarValue=-1;
		
	}
	
	for(i=2;i<23;i++){
		k=0;
		for(j=1;j<15;j++){
			test->hedgewood[i][j].visible=0;
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
	test->player.vision=1;
	test->verticalScroll=0;
	
}

void createRandomField(dataStore *test)
{
	int i,j,k=0,r;
	double fortschritt,sand,mittel,leicht,schwer,tmp;
	/* testdata for updateGrapics */
	for(i=0;i<1;i++){
		for(j=0;j<16;j++){
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=-1;
			if (j==0||j==15)
				test->hedgewood[i][j].aStarValue=1;

			else
				test->hedgewood[i][j].aStarValue=-1;
		}
	}
	for(i=1;i<2;i++){
		for(j=0;j<16;j++){
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=-1;
			test->hedgewood[i][j].aStarValue=1;
		}
	}
	for(i=2;i<FIELDSIZE_Y-1;i++){
		test->hedgewood[i][0].visible=1;
		test->hedgewood[i][0].type=1;
		test->hedgewood[i][0].aStarValue=-1;
		test->hedgewood[i][FIELDSIZE_X-1].visible=1;
		test->hedgewood[i][FIELDSIZE_X-1].type=2;
		test->hedgewood[i][FIELDSIZE_X-1].aStarValue=-1;
	}
	for(i=1;i<FIELDSIZE_X-1;i++){
		test->hedgewood[FIELDSIZE_Y-1][i].visible=1;
		test->hedgewood[FIELDSIZE_Y-1][i].type=3;
		test->hedgewood[FIELDSIZE_Y-1][i].aStarValue=-1;
	}
	
	srand (356745667);
	for(i=2;i<FIELDSIZE_Y-1;i++){
		fortschritt = (double)i/(double)FIELDSIZE_Y;
		for(j=1;j<FIELDSIZE_X-1;j++){
			
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
			if(i==2)test->hedgewood[i][j].visible=1;
			else test->hedgewood[i][j].visible=0;
			
			
			if (r<sand*100)
				k=4;
			else if(r<sand*100+leicht*100)
				k=5;
			else if(r<sand*100+leicht*100+mittel*100)
				k=6;
			else{
				k=7;
			}
			test->hedgewood[i][j].type=k;
			test->hedgewood[i][j].aStarValue=(k-4)*10+1;
		}
	}
	test->player.p_pos.x=7;
	test->player.p_pos.y=1;
	test->player.p_pos.next=NULL;
	test->player.heading=0;
	test->player.anfang=NULL;
	test->player.vision=6;
	test->player.maxEnergy=1000;
	test->player.currentEnergy=1000; 
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


