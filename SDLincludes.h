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

#ifndef SDLINCLUDES_H
#define SDLINCLUDES_H

#ifdef __APPLE__
#include "/usr/local/include/SDL/SDL.h"
#include "/usr/local/include/SDL/SDL_image.h"	/* http://www.libsdl.org/projects/SDL_image/ */
#include "/usr/local/include/SDL/SDL_ttf.h"		/* http://www.libsdl.org/projects/SDL_ttf/ */
#include "/usr/local/include/SDL/SDL_mixer.h"

#elif __WIN32__ || _MSC_VER 
#include "Bla" 
#include "Blubb"
#elif __linux__ 
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_ttf.h"
#include "/usr/include/SDL/SDL_mixer.h"
#endif

#define GAMENAME "Hedgewood"

#define GAMEDATA_PATH "Hedgewood.dataStore"

#define ABOUT_PATH "about.txt"

#define BUTTONX 300
#define BUTTONWIDTH 200
#define BUTTONHEIGHT 50


/*defines for SDL surface and screen settings */
#define WINDOWWIDTH 800
#define WINDOWHEIGTH 600
#define WINDOWBPP 32

//250 Frames per second (4 Milliseconds per frame)
#define MS_FRAMETIME 5

#define DEBUG 0
#define DBPATH 0
#define STARTCANDYSTASH 0

#define AVGASTAR 5
#define FIELDSIZE_X 200
#define FIELDSIZE_Y 200
#define FIELDSIZE_FIELD 50


/*soundConfigs */

#define CHAINSAWSOUND1 "sound/chainsaw1.wav"
#define CHAINSAWSOUND2 "sound/chainsaw2.wav"
#define CHAINSAWCHANNEL1 1
#define CHAINSAWCHANNEL2 2
#define INGAMEMUSIC "sound/Voices.wav"
#define MENUMUSIC "sound/Talking About.wav"


#endif