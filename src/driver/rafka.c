//
// Created by hp on 27/05/2024.
//
//
// Created by hp on 27/05/2024.
//

#include "../header/rafka.h"

void header(const char *menu) {
    int padding = (63 - strlen("Sistem Informasi Kerajaan Belanda - ") - strlen(menu)) / 2;
    printf("===============================================================\n");
    printf("%*sSistem Informasi Kerajaan Belanda - %s%*s\n", padding, "", menu, padding, "");
    printf("===============================================================\n");
}

void passedAway(DataTree *tree){
    system("cls");
    header("Kematian Anggota Keluarga");

//    displayActiveRoyalFamily(tree->Root);

    char selectedName[100];
    printf("Masukkan nama anggota keluarga kerajaan yang meninggal: ");
    fgets(selectedName, sizeof(selectedName), stdin);
    selectedName[strcspn(selectedName, "\n")] = '\0'; // Hilangkan newline dari input

    NBTree *selectedNode = findNode(tree->Root, selectedName);
    printf("%s",selectedNode->Name);
    printf("%d",selectedNode->IsAlive);
    if (selectedNode != NULL) {
        if (selectedNode->IsAlive){
            selectedNode->IsAlive = false;
            selectedNode->IsRoyalFamilyMember = false;

            if (selectedNode->IsLeader){
                nextSuccessor(selectedNode);
            }

//            updateFile("db/data.txt", tree);
            waitForEnter();
        } else {
            printf("Maaf, nama yang anda masukkan sudah meninggal.\n");
            waitForEnter();
            passedAway(tree);
        }
    } else {
        printf("Maaf, nama yang anda masukkan tidak ditemukan.\n");
        waitForEnter();
        passedAway(tree);
    }
}

void abdicate(DataTree *tree){
    system("cls");
    header("Pemimpin Turun Tahta");

    NBTree *leaderNode = findLeader(tree->Root);

    printf("Pada tahun %d, %s memilih mengundurkan diri", currentYear, leaderNode->Name);
    nextSuccessor(leaderNode);

//    updateFile("db/data.txt", tree);
    waitForEnter();
}

NBTree* findLeader(NBTree* root) {
    if (root == NULL) return NULL;

    if (root->IsLeader) {
        return root;
    }

    NBTree *found = findLeader(root->FirstSon);
    if (found != NULL) return found;

    return findLeader(root->NextBrother);
}

// Define the nextSuccessor function
void nextSuccessor(NBTree *tree) {
    if (tree == NULL) {
        return;
    }

    if (true){//(tree->IsLeader) {
        NBTree *current = tree->FirstSon;
        NBTree *nextSuccessor = NULL;

        // Check if the king/queen has children
        while (current != NULL) {
            if (current->IsAlive && current->IsRoyalFamilyMember) {
                if (nextSuccessor == NULL || current->YearOfBirth < nextSuccessor->YearOfBirth) {
                    nextSuccessor = current;
                }
            }
            current = current->NextBrother;
        }

        // If no children, check siblings and their children
        if (nextSuccessor == NULL) {
            current = tree->NextBrother;
            while (current != NULL) {
                NBTree *nephew = current->FirstSon;
                while (nephew != NULL) {
                    if (nephew->IsAlive && nephew->IsRoyalFamilyMember) {
                        if (nextSuccessor == NULL || nephew->YearOfBirth < nextSuccessor->YearOfBirth) {
                            nextSuccessor = nephew;
                        }
                    }
                    nephew = nephew->NextBrother;
                }
                current = current->NextBrother;
            }
        }

        // If no siblings or nephews, check other relatives
        if (nextSuccessor == NULL) {
            current = tree->Parent;
            while (current != NULL) {
                // Check uncles and aunts and their children
                NBTree *uncle = current->Parent->FirstSon;
                while (uncle != current->Parent) {
                    if (uncle != tree->Parent) {
                        NBTree *cousin = uncle->FirstSon;
                        while (cousin != NULL) {
                            if (cousin->IsAlive && cousin->IsRoyalFamilyMember) {
                                if (nextSuccessor == NULL || cousin->YearOfBirth < nextSuccessor->YearOfBirth) {
                                    nextSuccessor = cousin;
                                }
                            }
                            cousin = cousin->NextBrother;
                        }
                    }
                    uncle = uncle->NextBrother;
                }

                // Check grandparents and their siblings and their children
                if (nextSuccessor == NULL && current->Parent != NULL) {
                    NBTree *grandparent = current->Parent->Parent;
                    NBTree *greatUncle = grandparent->FirstSon;
                    while (greatUncle != grandparent->NextBrother) {
                        if (greatUncle != current->Parent->Parent) {
                            NBTree *secondCousin = greatUncle->FirstSon;
                            while (secondCousin != NULL) {
                                if (secondCousin->IsAlive && secondCousin->IsRoyalFamilyMember) {
                                    if (nextSuccessor == NULL || secondCousin->YearOfBirth < nextSuccessor->YearOfBirth) {
                                        nextSuccessor = secondCousin;
                                    }
                                }
                                secondCousin = secondCousin->NextBrother;
                            }
                        }
                        greatUncle = greatUncle->NextBrother;
                    }
                }

                current = current->Parent;
            }
        }

        if (nextSuccessor != NULL) {
            printf("Pewaris selanjutnya adalah: %s\n", nextSuccessor->Name);
            tree->IsLeader = false;
            nextSuccessor->IsLeader = true;
        }
    }
}

