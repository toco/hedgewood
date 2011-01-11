#include "SDLfunctions.h"
#include "structs.h"

//void aStar(struct dataStore *data,struct position *end);
void positionListAdd(struct dataStore *data, struct position *pos_add);
void positionListDelete(struct dataStore *data);
struct position *positionListRead(struct dataStore *data);
