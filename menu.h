/*
 *  menu.h
 *  Hedgewood
 *	
 *	Prozedurale Programmierung WS10/11	TUHH
 *
 *  Created by Tobias Conradi
 *	Version 09.01.11
 *
 *  Copyright 2011 Gruppe 34. All rights reserved.
 *	
 *	Description:
 *	
 *	
 */
#ifndef MENU_H
#define MENU_H

#include "about.h"
#include "highscore.h"
#include "structs.h"
#include "ingameMenu.h"
#include "gameloop.h"

#define STARTEN_BUTTON 0
#define HIGHSCORE_BUTTON 1
#define ABOUT_BUTTON 2
#define QUIT_BUTTON 3

#define BUTTONCOUNT 4


void menuStart(SDL_Surface *screen, dataStore *data);

void setupMenu(SDL_Surface *screen, struct menuDataStore *menuData);

int testLoop(SDL_Surface *screen, struct menuDataStore *menuData, dataStore *data);

#endif