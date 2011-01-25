#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "SDLfunctions.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define pfNode_list 1
#define pfNode_last 2

void aStar( dataStore *data, position *end);
void positionListAdd( dataStore *data,  position *pos_add);
void positionListDelete( dataStore *data);
position *positionListRead( dataStore *data);
pfNode *aStarListAdd( pfNode *list,pfNode *node_add,int stack);
pfNode *aStarSearchF(pfNode *list);
pfNode *aStarListSearchBool(pfNode *list,pfNode *element);
int aStarManhatten(position start, position end);
pfNode *aStarListRemove(pfNode *list,pfNode *node_add, int stack);
void aStarListDelete(pfNode *list);
void positionQListAdd(dataStore *data,  position *pos_add);

#endif