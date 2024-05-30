//
// Created by hp on 27/05/2024.
//

#ifndef TUBES_ANNISA_DIAN_H
#define TUBES_ANNISA_DIAN_H

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_LINE_LENGTH 1000
#include <windows.h>
#include <time.h>

#define BLACK           0
#define DARK_BLUE       1
#define GREEN           2
#define TURQUOISE       3
#define DARK_RED        4
#define PURPLE          5
#define FOREST_GREEN    6
#define LIGHT_GRAY      7
#define GRAY            8
#define BLUE            9
#define LIGHT_GREEN    10
#define LIGHT_BLUE     11
#define RED            12
#define PINK            13
#define YELLOW         14
#define WHITE          15
#define STDALERT      140
#define STDHEADER     143
#define STDBACKGROUND 159
// Enumeration for gender
typedef enum {
    Male,
    Female
} Gender;

// Typedef for information type
typedef char InfoType[200];

// Typedef for tree address
typedef struct TNBTree *TNBTreeAddress;

// Tree node structure
typedef struct TNBTree {
    InfoType Name;
    int YearOfBirth;
    Gender gender;
    bool IsLeader;
    bool IsRoyalFamilyMember;
    bool IsMarriageApproved;
    InfoType ParentName;
    InfoType PartnerName;
    bool IsAlive;
    struct TNBTree *FirstSon, *NextBrother, *Parent;
} NBTree;

// Data tree structure
typedef struct {
    NBTree *Root;
} DataTree;

// Function prototypes
NBTree* createNode(char *name, int yearOfBirth, Gender gender, bool isLeader, bool isRoyalFamilyMember, bool isMarriageApproved, char *parentName, char *partnerName, bool isAlive);
DataTree* buildTreeFromFile(const char *filename);
void insertNode(DataTree *tree, char *name, int yearOfBirth, Gender gender, bool isLeader, bool isRoyalFamilyMember, bool isMarriageApproved, char *parentName, char *partnerName, bool isAlive);
void updateFile(const char *filename, DataTree *tree);
void displayTree(DataTree *tree);
int calculateAge(int yearOfBirth);
void displayEncyclopediaDescription(char *name);
void mainMenu(DataTree *tree);
void insertFamilyMember(DataTree *tree);
void insertPartner(DataTree *tree);
void printRoyalFamilyMember(DataTree *tree);
void displayActiveRoyalFamily(NBTree *node);
void encyclopedia(DataTree *tree);
void viewEncyclopedia(DataTree *tree);
void waitForEnter();
NBTree* findNode(NBTree *tree, char* name);
void displayActiveRoyalFamilyMembers(NBTree *tree);
void displayEncyclopediaEntry(DataTree *tree, char *name);
void printFromFileSplash(const char* location);
//perlu include untuk var global currentyear
#include "../header/harish.h"

#endif //TUBES_ANNISA_DIAN_H
