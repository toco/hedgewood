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


int saveDataStore(dataStore *data, int highscore, int game)
{

	dataStore *tmpData = malloc(sizeof(dataStore));
	memcpy(tmpData,data, sizeof(dataStore));
	int tmpHighscore, tmpGame;
	if (highscore)
		tmpHighscore=0;
	else
		tmpHighscore=1;
	if (game) 
		tmpGame=0;
	else 
		tmpGame=1;
	readDataStore(tmpData, tmpHighscore, tmpGame);
	
	FILE *dataFile;
	dataFile = fopen(GAMEDATA_PATH, "w");
	if (!dataFile) {
		printf("Error opening File: %s \n",GAMEDATA_PATH);
	}
	
	/*Highscore*/
	fprintf(dataFile, "!#highscore\n");
	int i;
	for (i=0; i<10; i++) {
		fprintf(dataFile,"%s\t%d\n",tmpData->highscore[i].name,tmpData->highscore[i].points);
	}
	
	/*Person*/
	fprintf(dataFile, "!#person\n");
	fprintf(dataFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",tmpData->player.p_pos.x,tmpData->player.p_pos.y,tmpData->player.bp.maxVolume,tmpData->player.bp.currentVolume,tmpData->player.heading,tmpData->player.maxEnergy,tmpData->player.currentEnergy,tmpData->player.vision);
	
	/*fieldArray*/
	fprintf(dataFile, "!#fieldArray\n");
	int x,y;
	for (y=0; y<FIELDSIZE_Y; y++) {
		for (x=0; x<FIELDSIZE_X; x++) {
			fprintf(dataFile,"%d\t%d\t%d\t%d\t%d\t%d\n",y,x,tmpData->hedgewood[y][x].visible,tmpData->hedgewood[y][x].currency,tmpData->hedgewood[y][x].aStarValue,tmpData->hedgewood[y][x].type);
		}
	}
	free(tmpData);
	fclose(dataFile);
	printf("Successfully written Game-Data\n");
	return 1;
}

int readDataStore(dataStore *data, int highscore, int game)
{
	
	
	printf("Read saved tmpData\n");
	FILE *dataFile;
	dataFile = fopen(GAMEDATA_PATH, "r");
	if (dataFile==NULL) {
		printf("Could not open file: %s will not overwrite default tmpData\n",GAMEDATA_PATH);
		return 1;
	}
	
	dataStore *tmpData = malloc(sizeof(dataStore)); 
	char read[300];
	memset(read, '\0', sizeof(char)*300);
	int importHighscore=0;
	int importPerson=0;
	int importFieldArray=0;
	int linecounter=0;
	int tabPos,tabPosOld;
	int x,y;
	char *tab = "\t";
	char *newLine= "\n";
	
	char tmp[100];
	memset(tmp, '\0', sizeof(char)*100);
	char *readPtr;
	while (fgets(read,300, dataFile)) {
		
		memset(tmp, '\0', sizeof(char)*100);
		
		if (!strcmp(read,"!#highscore\n")) {
			importHighscore=1;
			importPerson=0;
			importFieldArray=0;
			linecounter=0;
			printf("Import highscore\n");
			continue;
		}
		else if (!strcmp(read,"!#person\n"))
		{
			importHighscore=0;
			importPerson=1;
			importFieldArray=0;
			printf("Import person\n");
			continue;
		}
		else if (!strcmp(read,"!#fieldArray\n"))
		{
			importHighscore=0;
			importPerson=0;
			importFieldArray=1;
			printf("Import fieldArray\n");
			continue;
		}
		
		/*Import Highscore*/
		if (highscore==1&&importHighscore==1&&linecounter<10) {
			tabPos = strcspn(read,tab);
			strncpy(tmp,read,tabPos);
			strcpy(tmpData->highscore[linecounter].name, tmp);
			tmpData->highscore[linecounter].points=atoi(&read[tabPos]);
			linecounter++;
		}
		/*Import Person*/
		else if(game==1&&importPerson==1)
		{
			readPtr=&read[0];
			tabPos=0;
			/*p_pos x*/
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->player.p_pos.x=atoi(tmp);
			/*p_pos y*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->player.p_pos.y=atoi(tmp);
			/*maxVolume backpack*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->player.bp.maxVolume=atoi(tmp);
			/*currentVolume backpack*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->player.bp.currentVolume=atoi(tmp);
			/*heading*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->player.heading=atoi(tmp);
			/*maxEnergy*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->player.maxEnergy=atoi(tmp);
			/*currentEnergy*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->player.currentEnergy=atoi(tmp);
			/*vison*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,newLine);
			strncpy(tmp,readPtr,tabPos);
			tmpData->player.vision=atoi(tmp);
			
		}
		else if(game==1&&importFieldArray==1)
		{
			readPtr=&read[0];
			tabPos=0;
			/*y*/
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			y=atoi(tmp);
			/*x*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			x=atoi(tmp);
			/*visible*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->hedgewood[y][x].visible=atoi(tmp);
			/*currency*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->hedgewood[y][x].currency=atoi(tmp);
			/*aStarValue*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			tmpData->hedgewood[y][x].aStarValue=atoi(tmp);
			/*type*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,newLine);
			strncpy(tmp,readPtr,tabPos);
			tmpData->hedgewood[y][x].type=atoi(tmp);
			
		}
		else {
			printf("Not imported: %s",read);
		}
	}
	
	if (highscore&&game) {
		memcpy(data, tmpData, sizeof(dataStore));
	} else if (highscore) {
		memcpy(&data->highscore, &tmpData->highscore, sizeof(data->highscore));
	} else if (game){
		memcpy(&data->player, &tmpData->player, sizeof(data->player));
		memcpy(&data->hedgewood, &tmpData->hedgewood, sizeof(data->hedgewood));
	}

	
	fclose(dataFile);
	return 0;
}