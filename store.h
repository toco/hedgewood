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
#define INGAMEBUTTONCOUNT 4

#define	ITEMPRICE 8
#define	BACKPACKPRICE 10
#define VIEWPRICE 12

#define NOTENOUGHMONEY "You haven't got enough money to buy this!"

int storeStart(SDL_Surface *screen, dataStore *data);
int displayStore(SDL_Surface *screen,  dataStore *data, menuDataStore *menuData);
int storeLoop(SDL_Surface *screen, dataStore *data, menuDataStore *menuData);


#endif