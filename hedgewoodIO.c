/*
 *  hedgewoodIO.c
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 12.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */

#include "hedgewoodIO.h"


int saveDataStore(dataStore *data)
{
	FILE *dataFile;
	dataFile = fopen(GAMEDATA_PATH, "w");
	if (!dataFile) {
		printf("Error opening File: %s",GAMEDATA_PATH);
	}
	
	/*Highscore*/
	fprintf(dataFile, "!#highscore\n");
	int i;
	for (i=0; i<10; i++) {
		fprintf(dataFile,"%s\t%d\n",data->highscore[i].name,data->highscore[i].points);
	}
	
	
	
	fclose(dataFile);
	printf("Successfully written Game-Data\n");
	return 1;
}

int readDataStore(dataStore *data)
{
	printf("Read saved data\n");
	FILE *dataFile;
	dataFile = fopen(GAMEDATA_PATH, "r");
	if (dataFile==NULL) {
		printf("Error opening File: %s\n",GAMEDATA_PATH);
		return 1;
	}
	char read[300];
	memset(read, '\0', sizeof(char)*300);
	int highscore=0;
	int linecounter = 0;
	int tabPos;
	char tab = '\t';
	while (fgets(read,300, dataFile)) {
		if (read=="!#highscore") {
			highscore=1;
			printf("highscore tag\n");
		}
		
		if (highscore=1) {
			printf("in highscore data\n");
			tabPos = strcspn(read,&tab);
			strncpy(data->highscore[linecounter].name,read,tabPos);
			data->highscore[linecounter].points=atoi(&read[tabPos]);
			//@TODO: not working
			printf("%s %d\n",data->highscore[linecounter].name,data->highscore[linecounter].points);
			linecounter++;
		}
	}
	fclose(dataFile);
	return 0;
}