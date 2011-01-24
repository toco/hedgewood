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
#ifndef SDLINCLUDES_H
#include "SDLincludes.h"
#endif
#include "SDLfunctions.h"
#include "structs.h"

#include "hedgewoodIO.h"
#include "popUp.h"

#define CONTINUE_BUTTON 0
#define SAVEGAME_BUTTON 1
#define LOADGAME_BUTTON 2
#define QUIT_BUTTON 3
#define INGAMEBUTTONCOUNT 4

int ingameMenuStart(SDL_Surface *screen, dataStore *data);

int displayIngameMenu(SDL_Surface *screen,  dataStore *data, menuDataStore *menuData);
int ingameMenuLoop(SDL_Surface *screen, dataStore *data, menuDataStore *menuData);

int saveGame(SDL_Surface __attribute__((unused)) *screen, __attribute__((unused)) dataStore *data);
int loadGame(SDL_Surface __attribute__((unused)) *screen, __attribute__((unused)) dataStore *data);

#endif