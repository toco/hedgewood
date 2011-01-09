/*
 *  SDLincludes.h
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


#ifdef __APPLE__
#include "SDL.h"
#include "/usr/local/include/SDL/SDL_gfxPrimitives.h"
#elif __WIN32__ || _MSC_VER 
#include "Bla" 
#include "Blubb"
#elif __linux__ 
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_gfxPrimitives.h"
#endif

#define GAMENAME "Hedgewood"

/*defines for SDL surface and screen settings */
#define WINDOWWIDTH 800
#define WINDOWHEIGTH 600
#define WINDOWBPP 32
