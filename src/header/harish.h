//
// Created by hp on 27/05/2024.
//

#ifndef TUBES_HARISH_H
#define TUBES_HARISH_H

#include "../header/annisa_dian.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


//variabel global untuk waktu terkini (support untuk timeskip)
extern int currentYear;

void getTahunSekarang();
void countChildren(DataTree *tree);
int prosesCountChildren(NBTree *parent);
void countGeneration(DataTree *tree);
int prosesCountGeneration(NBTree *node);
void yearPasses(DataTree *tree);
void prosesTimeskip(int years);
//void resetProgress(DataTree **tree, const char *filename);
void resetProgress(DataTree **tree, const char *initialFilename, const char *dataFilename);
void displayAturan();

#endif //TUBES_HARISH_H
