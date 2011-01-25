/*
 *  store.h
 *  Hedgewood
 *
 *  Created by Tobias Conradi on 13.01.11.
 *  Copyright 2011 ProzProg TUHH 10/11 Gruppe 34 . All rights reserved.
 *
 */

#ifndef store_H
#define store_H
#ifndef SDLINCLUDES_H
#include "SDLincludes.h"
#endif
#include "SDLfunctions.h"
#include "structs.h"

#include "hedgewoodIO.h"
#include "popUp.h"

#define ITEM_BUTTON 0
#define BACKPACK_BUTTON 1
#define VIEW_BUTTON 2
#define BACK_BUTTON 3
#define STOREBUTTONCOUNT 4
#define	ITEMPRICE 10
#define	BACKPACKPRICE 20
#define VIEWPRICE 30

int storeStart(SDL_Surface *screen, dataStore *data);
int displaystore(SDL_Surface *screen,  dataStore *data, menuDataStore *menuData);
int storeLoop(SDL_Surface *screen, dataStore *data, menuDataStore *menuData);


#endif