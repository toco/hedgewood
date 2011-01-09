struct field{
    int visible;
    int currency;
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
    struct position position;
    struct backpack backpack;
    int maxEnergy;
    int currentEnergy;
};

struct dataStore{
    //pointer auf 2D Array welches das Spielfeld enthält
	//Zeile 0-1 sind der Startbereich
    struct field hedgewood[12][16];
    struct person *player;
    //Aktuell oberste sichtbar Zeile im Array
    int *verticalScroll;

};