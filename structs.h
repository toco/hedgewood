#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct field{
    int visible;
    int currency;
	//-1 := nicht begehbar
	int aStarValue;

    int type;
	//0 := Verdeckt			nicht begehbar
	//1 := linker Zaun		nicht begehbar
	//2 := rechter Zaun		nicht begehbar
	//3 := Bach				nicht begehbar
	//4 := Sand				sStarValue 1
	//5 := leichter Busch	sStarValue 10
	//6 := mittlerer Busch	sStarValue 20
	//7 := fester Busch		sStarValue 30
	//-1 := Startzone		sStarValue 0
}field;

typedef struct position{
    int x;
    int y;
    struct position *next;
}position;

//Rucksack für Süßigkeiten/Währung
typedef struct backpack{
    int maxVolume;
    int currentVolume;
}backpack;

typedef struct person{
    struct position p_pos;
    struct backpack bp;
	/* 0: UP
	 * 1: RIGHT
	 * 2: DOWN
	 * 3: LEFT
	 */
	int heading;
    int maxEnergy;
    int currentEnergy;
	int vision;
	struct position *anfang;
}person;

//Highscore-Element
typedef struct highscoreElement
{
	char name[10];
	int points;
}highscoreElement;


typedef struct dataStore{
    //pointer auf 2D Array welches das Spielfeld enthält
	//Zeile 0-1 sind der Startbereich
    field hedgewood[FIELDSIZE_Y][FIELDSIZE_X];
    struct person player;
    //Aktuell oberste sichtbar Zeile im Array
    int verticalScroll;
	//Highscore-Array max. 10 Einträge
	highscoreElement highscore[10];
}dataStore;

typedef struct pfNode{
	struct position n_pos;
	int F;
	int G;
	int H;
	//Für den Pfad
	struct pfNode *last;
	//Für die open/closed List
	struct pfNode *list;
}pfNode;


//Button-Rect
typedef struct myButton{
	SDL_Rect rect;
	char *name;
	int (*function)(SDL_Surface *screen, dataStore *data);
}myButton;

typedef struct menuDataStore
{
	myButton *buttons;
}menuDataStore;

#endif