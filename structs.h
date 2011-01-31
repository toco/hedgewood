/*! \file structs.h
    \brief Our global struct definition.
    
    Every struct we used is in here.
*/
#ifndef STRUCTS_H
#define STRUCTS_H

/** Gamefield struct*/
typedef struct field{
    int visible;
	/**
	1-10 wenig\n
	11-20 mittel\n
	21-30 viel
	*/
    int currency;			
	
	int aStarValue;
	/**<-1 := nicht begehbar*/
	
    
/**	0 := Verdeckt			nicht begehbar\n
	1 := linker Zaun		nicht begehbar\n
	2 := rechter Zaun		nicht begehbar\n
	3 := Bach Zaun links	nicht begehbar\n
	4 := Bach 				nicht begehbar\n                 
	5 := Bach Zaun rechts	nicht begehbar\n
	6 := Sand				aStarValue 2\n
	7 := Stein				nicht begehbar\n
	8 := Mauer				nicht begehbar\n
	9 := leichter Busch	aStarValue 10\n
	10 := mittlerer Busch	aStarValue 20\n
	11 := fester Busch		aStarValue 30\n
	-1 := Startzone		aStarValue 0*/
	int type;
}field;

/**Position struct.
 * with pointer to the next position
 */
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
/**Person struct.
 * stores information about the player
 */
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

/**Stores the game data.*/
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
	Mix_Chunk *chaingo;
	int chainChannel;
	/**channel der Chainsaw */
	Mix_Music *startmusic;
	Mix_Music *ingamemusic;
}dataStore;

/**Stores the information about a node used by A*.
 * @see aStar */
typedef struct pfNode{
	struct position n_pos;
	int F; /**<G + H*/
	int G; /**<Die Bewegungskosten, um vom Startpunkt A zu einem gegebenen Quadrat des Gitters unter Verwendung des dafür ermittelten Pfades zu gelangen*/
	int H; /**<Die geschätzten Kosten, um von dem gegebenen Quadrat zum Zielpunkt B zu gelangen*/
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