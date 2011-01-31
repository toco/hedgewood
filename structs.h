/** @file strucs.h
    Our structs file.
    Here you can find every struct we used in Hedgewood
*/

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct field{
    int visible;
	/**
	1-10 wenig
	11-20 mittel
	21-30 viel
	*/
    int currency;			
	
	int aStarValue;
	/**<-1 := nicht begehbar*/
	
    
/**	0 := Verdeckt			nicht begehbar
	1 := linker Zaun		nicht begehbar
	2 := rechter Zaun		nicht begehbar
	3 := Bach Zaun links	nicht begehbar
	4 := Bach 				nicht begehbar
	5 := Bach Zaun rechts	nicht begehbar
	6 := Sand				aStarValue 2
	7 := Stein				nicht begehbar
	8 := Mauer				nicht begehbar
	9 := leichter Busch	aStarValue 10
	10 := mittlerer Busch	aStarValue 20
	11 := fester Busch		aStarValue 30
	-1 := Startzone		aStarValue 0*/
	int type;
}field;

typedef struct position{
    int x;
    int y;
    struct position *next;
}position;

/**Rucksack für Süßigkeiten/Währung*/
typedef struct backpack{
    int maxVolume;
    int currentVolume;
	int maxOverall;
}backpack;

typedef struct person{
    struct position p_pos;
    struct backpack bp;
	
	int candystash;
	/** 0: UP
	 * 1: RIGHT
	 * 2: DOWN
	 * 3: LEFT
	 */
	int heading;
    int maxEnergy;
    int currentEnergy;
	int vision;
	float cutSpeed;
	struct position *anfang;
}person;

/**Highscore-Element*/
typedef struct highscoreElement
{
	char name[25];
	int points;
}highscoreElement;


typedef struct dataStore{
   /**pointer auf 2D Array welches das Spielfeld enthält.
	  Zeile 0-1 sind der Startbereich
	*/
    field hedgewood[FIELDSIZE_Y][FIELDSIZE_X];
    struct person player;
    /**Aktuell oberste sichtbar Zeile im Array*/
    int verticalScroll;
	int horizontalScroll;
	/**Highscore-Array max. 10 Einträge*/
	highscoreElement highscore[10];
	position home;
	position stash;
	int windowed;
	SDL_Surface *screen;	
}dataStore;

typedef struct pfNode{
	struct position n_pos;
	int F;
	int G;
	int H;
	/**Für den Pfad*/
	struct pfNode *last;
	/**Für die open/closed List */
	struct pfNode *list;
}pfNode;


/**Button-Rect*/
typedef struct myButton{
	SDL_Rect rect;
	char *name;
	int (*function)(SDL_Surface *screen, dataStore *data);
	int disabled;
}myButton;

typedef struct menuDataStore
{
	myButton *buttons;
	int buttonCount;
	char *text;
	char *inputText;
	int inputLength;
}menuDataStore;

#endif