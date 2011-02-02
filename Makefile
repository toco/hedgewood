#
#  Makefile
#  Hedgewood
#	
#	Prozedurale Programmierung WS10/11	TUHH
#
#  Created by Tobias Conradi
#	Version 08.01.11
#
#  Copyright 2011 Gruppe 34. All rights reserved.
#	
#	Description:



CC = gcc 
# Fuer Kompilerflags wird meistens die Konstante CFLAGS definiert
#CFLAGS = -Wall -Wextra -ansi -pedantic -DPARAUSGABE -O3 -mtune=core2 -march=core2 
CFLAGS = -g -Wall -Wextra -std=c99 -pedantic
#CFLAGS = -Wall -Wextra
SDLFLAGS = `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf -lSDL_mixer
CPRECOMPILER = -save-temps

Hedgewood: main.o SDLfunctions.o menu.o graphicUpdate.o about.o highscore.o pathfinding.o hedgewoodIO.o ingameMenu.o gameloop.o popUp.o store.o
	$(CC) $(SDLFLAGS) $(CFLAGS) -o Hedgewood main.o SDLfunctions.o menu.o graphicUpdate.o about.o highscore.o pathfinding.o hedgewoodIO.o ingameMenu.o gameloop.o popUp.o store.o

main.o: main.c main.h SDLincludes.h structs.h hedgewoodIO.o gameloop.o store.o
	$(CC)  $(CFLAGS)  -c main.c
#gcc `sdl-config --cflags --libs` -lSDL_gfx -Wall -Wextra -o Hedgewood main.c

SDLfunctions.o: SDLfunctions.c SDLfunctions.h SDLincludes.h structs.h 
	$(CC)  $(CFLAGS) -c SDLfunctions.c SDLincludes.h

menu.o: menu.c menu.h SDLincludes.h SDLfunctions.o about.o highscore.o structs.h gameloop.o
	$(CC)  $(CFLAGS) -c menu.c
	
about.o: about.h about.c SDLfunctions.o SDLincludes.h
	$(CC)  $(CFLAGS) -c about.c

highscore.o: highscore.c highscore.h SDLfunctions.o SDLincludes.h structs.h
	$(CC)  $(CFLAGS) -c highscore.c

graphicUpdate.o: graphicUpdate.c graphicUpdate.h pathfinding.o structs.h SDLincludes.h ingameMenu.o store.o
	$(CC)  $(CFLAGS) -c graphicUpdate.c
	
pathfinding.o: pathfinding.c pathfinding.h SDLincludes.h SDLfunctions.o structs.h
	$(CC)  $(CFLAGS) -c pathfinding.c

hedgewoodIO.o: hedgewoodIO.h hedgewoodIO.c structs.h SDLincludes.h
	$(CC)  $(CFLAGS) -c hedgewoodIO.h hedgewoodIO.c
	
ingameMenu.o: ingameMenu.h ingameMenu.c structs.h SDLincludes.h SDLfunctions.o hedgewoodIO.o popUp.o
	$(CC)  $(CFLAGS) -c ingameMenu.c
	
gameloop.o: gameloop.c gameloop.h structs.h SDLincludes.h SDLfunctions.o graphicUpdate.o highscore.o pathfinding.o hedgewoodIO.o ingameMenu.o store.o
	$(CC)  $(CFLAGS) -c gameloop.c gameloop.h
popUp.o: popUp.c popUp.h SDLfunctions.o structs.h
	$(CC)  $(CFLAGS) -c popUp.c
	
store.o: store.h store.c structs.h SDLincludes.h SDLfunctions.o hedgewoodIO.o popUp.o 
	$(CC)  $(CFLAGS) -c store.c store.h 

# Aufruf des Targets "clean" löscht  alle nicht mehr benötigten Dateien
clean: 
	rm *.o # lösche alle Objektdateien 
	rm *.gch # lösche precompiled header

doku:
	doxygen Doxyfile