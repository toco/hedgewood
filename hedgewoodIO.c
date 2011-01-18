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
		printf("Error opening File: %s \n",GAMEDATA_PATH);
	}
	
	
	/*Highscore*/
	fprintf(dataFile, "!#highscore\n");
	int i;
	for (i=0; i<10; i++) {
		fprintf(dataFile,"%s\t%d\n",data->highscore[i].name,data->highscore[i].points);
	}
	
	/*Person*/
	fprintf(dataFile, "!#person\n");
	fprintf(dataFile, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",data->player.p_pos.x,data->player.p_pos.y,data->player.bp.maxVolume,data->player.bp.currentVolume,data->player.heading,data->player.maxEnergy,data->player.currentEnergy,data->player.vision);

	/*fieldArray*/
	fprintf(dataFile, "!#fieldArray\n");
	int x,y;
	for (y=0; y<FIELDSIZE_Y; y++) {
		for (x=0; x<FIELDSIZE_X; x++) {
			fprintf(dataFile,"%d\t%d\t%d\t%d\t%d\t%d\n",y,x,data->hedgewood[y][x].visible,data->hedgewood[y][x].currency,data->hedgewood[y][x].aStarValue,data->hedgewood[y][x].type);
		}
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
		printf("Could not open file: %s will not overwrite default data\n",GAMEDATA_PATH);
		return 1;
	}
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
		if (importHighscore==1&&linecounter<10) {
			tabPos = strcspn(read,tab);
			strncpy(tmp,read,tabPos);
			strcpy(data->highscore[linecounter].name, tmp);
			data->highscore[linecounter].points=atoi(&read[tabPos]);
			linecounter++;
		}
		/*Import Person*/
		else if(importPerson==1)
		{
			readPtr=&read[0];
			tabPos=0;
			/*p_pos x*/
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			data->player.p_pos.x=atoi(tmp);
			/*p_pos y*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			data->player.p_pos.y=atoi(tmp);
			/*maxVolume backpack*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			data->player.bp.maxVolume=atoi(tmp);
			/*currentVolume backpack*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			data->player.bp.currentVolume=atoi(tmp);
			/*heading*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			data->player.heading=atoi(tmp);
			/*maxEnergy*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			data->player.maxEnergy=atoi(tmp);
			/*currentEnergy*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			data->player.currentEnergy=atoi(tmp);
			/*vison*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,newLine);
			strncpy(tmp,readPtr,tabPos);
			data->player.vision=atoi(tmp);
			
		}
		else if(importFieldArray==1)
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
			data->hedgewood[y][x].visible=atoi(tmp);
			/*currency*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			data->hedgewood[y][x].currency=atoi(tmp);
			/*aStarValue*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,tab);
			strncpy(tmp,readPtr,tabPos);
			data->hedgewood[y][x].aStarValue=atoi(tmp);
			/*type*/
			readPtr+=tabPos+1;
			memset(tmp, '\0', sizeof(char)*100);
			tabPosOld=tabPos;
			tabPos = strcspn(readPtr,newLine);
			strncpy(tmp,readPtr,tabPos);
			data->hedgewood[y][x].type=atoi(tmp);

		}
		else {
			printf("Not imported: %s",read);
		}
	}
	fclose(dataFile);
	return 0;
}