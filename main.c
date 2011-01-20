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
#include <time.h>
void makeTestData(dataStore *test)
{
	int i,j,k=0,r,r_currency;
	double fortschritt,sand,mittel,leicht,schwer,tmp;
	/* testdata for updateGrapics */
	for(i=0; i<4; i++) {
		for(j=0; j<16; j++) {
			test->hedgewood[i][j].visible=1;
			test->hedgewood[i][j].type=-1;
			if(j==0||j==15||i==0)test->hedgewood[i][j].aStarValue=-1;
			else test->hedgewood[i][j].aStarValue=0;
			test->hedgewood[i][j].aStarValue=1;
			test->hedgewood[i][j].currency=0;
		}
	}
	for(i=4; i<FIELDSIZE_Y-1; i++) {
		test->hedgewood[i][0].visible=1;
		test->hedgewood[i][0].type=1;
		test->hedgewood[i][0].aStarValue=-1;
		test->hedgewood[i][0].currency=0;
		test->hedgewood[i][FIELDSIZE_X-1].visible=1;
		test->hedgewood[i][FIELDSIZE_X-1].type=2;
		test->hedgewood[i][FIELDSIZE_X-1].aStarValue=-1;
		test->hedgewood[i][FIELDSIZE_X-1].currency=0;
	}
	for(i=1; i<FIELDSIZE_X-1; i++) {
		test->hedgewood[FIELDSIZE_Y-1][i].visible=1;
		test->hedgewood[FIELDSIZE_Y-1][i].type=3;
		test->hedgewood[FIELDSIZE_Y-1][i].aStarValue=-1;
		test->hedgewood[FIELDSIZE_Y-1][i].currency=0;
	}
	test->hedgewood[FIELDSIZE_Y-1][0].visible=1;
	test->hedgewood[FIELDSIZE_Y-1][0].type=3;
	test->hedgewood[FIELDSIZE_Y-1][0].aStarValue=-1;
	test->hedgewood[FIELDSIZE_Y-1][0].currency=0;
	test->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].visible=1;
	test->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].type=5;
	test->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].aStarValue=-1;
	test->hedgewood[FIELDSIZE_Y-1][FIELDSIZE_X-1].currency=0;
	
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
			if(i==2)test->hedgewood[i][j].visible=1;
			else test->hedgewood[i][j].visible=0;
			if (r<sand*100)
				k=6;
			else if(r<sand*100+leicht*100)
				k=7;
			else if(r<sand*100+leicht*100+mittel*100)
				k=8;
			else {
				k=9;
			}
			test->hedgewood[i][j].type=k;
			test->hedgewood[i][j].aStarValue=(k-6)*10+2;
			if (r<=50)
				r_currency=0;                                
		else if (r<=60)
				r_currency=1;
		else if (r_currency<=70)
				r_currency=3;
		else if (r<=80)
				r_currency=6;
		else if (r<=90)
				r_currency=7;
		else 
			r_currency= 10;                            
		test->hedgewood[i][j].currency=(k-6)*r_currency;
			
		}
	}
	test->player.p_pos.x=7;
	test->player.p_pos.y=1;
	test->player.p_pos.next=NULL;
	test->player.heading=0;
	test->player.anfang=NULL;
	test->player.vision=1;
	test->player.maxEnergy=1000;
	test->player.currentEnergy=1000;
	test->verticalScroll=0;
	test->player.bp.currentVolume=0;
	test->player.bp.maxVolume=400;
	test->player.candystash=0;
}
void highscoreTestdata(dataStore *store) {
	char *test = "nobody";
	int i;
	for (i=0; i<10; i++) {
		store->highscore[i].points=0;
		strncpy(store->highscore[i].name,test,strlen(test));
	}
}
int main(int argc, char *argv[]) {
	printf("%s %d",argv[0],argc);
	dataStore *test = calloc(1,sizeof(dataStore));
	highscoreTestdata(test);
	SDL_Surface* screen=initSDL();
	readDataStore(test);
	menuStart(screen, test);
	saveDataStore(test);
	/* just for testing*/
	makeTestData(test);
	//createRandomField(test);
	updateGraphics(screen,test);
	graphicLoop(screen,test);
//	gameloop(test,screen);
	quitSDL();
//	free(test);
	return 0;
}
