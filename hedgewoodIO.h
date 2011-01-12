/*
 *  hedgewoodIO.h
 *  Hedgewood
 *
 *  Created by Tobias Conradi on 12.01.11.
 *  Copyright 2011 ProzProg TUHH 10/11 Gruppe 34 . All rights reserved.
 *
 */

#ifndef HEDGEWOODIO_H
#define HEDGEWOODIO_H

#include <stdio.h>
#include "structs.h"
#include "SDLincludes.h"


int saveDataStore(dataStore *data);
int readDataStore(dataStore *data);


#endif