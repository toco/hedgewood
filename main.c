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

void highscoreTestdata(dataStore *store) {
	char *test = "nobody";
	int i;
	for (i=0; i<10; i++) {
		store->highscore[i].points=0;
		strncpy(store->highscore[i].name,test,strlen(test));
	}
}
int main(int argc, char *argv[]) {
	printf("%s %d\n",argv[0],argc);
	dataStore *test = calloc(1,sizeof(dataStore));
	highscoreTestdata(test);
	SDL_Surface* screen=initSDL(test);
	readDataStore(test);
	addHighscore(screen, test, 1000);
	menuStart(screen, test);
	saveDataStore(test);
	quitSDL();
	return 0;
}
