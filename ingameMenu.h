/*
 *  ingameMenu.h
 *  Hedgewood
 *
 *  Created by Tobias Conradi on 13.01.11.
 *  Copyright 2011 ProzProg TUHH 10/11 Gruppe 34 . All rights reserved.
 *
 */

#ifndef INGAMEMENU_H
#define INGAMEMENU_H
#include "SDLincludes.h"
#include "SDLfunctions.h"
#include "structs.h"

#include "hedgewoodIO.h"

#define SAVEGAME_BUTTON 0
#define LOADGAME_BUTTON 1
#define CONTINUE_BUTTON 2
#define INGAMEBUTTONCOUNT 3

int ingameMenuStart(SDL_Surface *screen, dataStore *data);

int displayIngameMenu(SDL_Surface *screen, dataStore *data, menuDataStore *menuData);
int ingameMenuLoop(SDL_Surface *screen, dataStore *data, menuDataStore *menuData);

int saveGame(SDL_Surface *screen, dataStore *data);
int loadGame(SDL_Surface *screen, dataStore *data);

#endif