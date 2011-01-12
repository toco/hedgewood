#ifndef STRUCTS_H
#define STRUCTS_H

struct field{
    int visible;
    int currency;
	int aStarValue;
	//0 := Bach
	//-1 := Startzone
    int type;
};

struct position{
    int x;
    int y;
    struct position *next;
};

//Rucksack für Süßigkeiten/Währung
struct backpack{
    int maxVolume;
    int currentVolume;
};
struct person{
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
	struct position *anfang;
	struct position *next;
};

//Highscore-Element
typedef struct highscoreElement
{
	char name[10];
	int points;
}highscoreElement;

typedef struct dataStore{
    //pointer auf 2D Array welches das Spielfeld enthält
	//Zeile 0-1 sind der Startbereich
    struct field hedgewood[24][16];
    struct person player;
    //Aktuell oberste sichtbar Zeile im Array
    int verticalScroll;
	//Highscore-Array max. 10 Einträge
	highscoreElement highscore[10];
}dataStore;

#endif