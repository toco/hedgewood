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
	fprintf(dataFile, "!#highscore\n");
	int i;
	char tmp[10];
	for (i=0; i<10; i++) {
		sprintf(tmp, "%d",data->highscore[i].points);
		fprintf(dataFile, "%s\t%s\n",data->highscore[i].name,tmp);
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
	memset(read, 0, sizeof(char)*strlen(read));
	while (fgets(read,300, dataFile)) {
		printf("read\n");
		printf("%s",read);
	}
	fclose(dataFile);
	return 0;
}