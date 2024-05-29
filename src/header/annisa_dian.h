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
#include <time.h>
#define MAX_LINE_LENGTH 200

// Enumeration for gender
typedef enum {
    Male,
    Female
} Gender;

// Typedef for information type
typedef char InfoType[100];

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

//perlu include untuk var global currentyear
#include "../header/harish.h"

#endif //TUBES_ANNISA_DIAN_H
