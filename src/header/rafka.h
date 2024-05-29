//
// Created by hp on 27/05/2024.
//

#ifndef TUBES_RAFKA_H
#define TUBES_RAFKA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "../header/harish.h"
#include "../header/annisa_dian.h"

void header(const char *menu);
void passedAway(DataTree *tree);
void abdicate(DataTree *tree);
NBTree* findLeader(NBTree *tree);
void nextSuccessor(NBTree *tree);

#endif //TUBES_RAFKA_H
