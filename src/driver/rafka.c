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

    displayTree(tree);

    char selectedName[100];
    printf("Masukkan nama anggota keluarga kerajaan yang meninggal: ");
    fgets(selectedName, sizeof(selectedName), stdin);
    selectedName[strcspn(selectedName, "\n")] = '\0';

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

    if (tree->IsLeader) {
        NBTree *current = tree->FirstSon;
        NBTree *nextSuccessor = NULL;

        // cari anak raja - derajat 1
        while (current != NULL) {
            if (current->IsAlive && current->IsRoyalFamilyMember) {
                if (nextSuccessor == NULL || current->YearOfBirth < nextSuccessor->YearOfBirth) {
                    nextSuccessor = current;
                }
            }
            current = current->NextBrother;
        }

        // cari anak dari adik raja - derajat 2
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

        // cari anak dari anak adik orangtua raja - derajat 3
        if (nextSuccessor == NULL) {
            NBTree *current = tree->Parent; // orangtua raja
            if (current!= NULL) {
                NBTree *uncle = current->NextBrother; // adik orangtua raja
                while (uncle!= NULL) {
                    NBTree *nephew = uncle->FirstSon; // anak adik orangtua raja
                    while (nephew!= NULL) {
                        NBTree *grandchild = nephew->FirstSon; // cucu adik orangtua raja
                        while (grandchild!= NULL) {
                            if (grandchild->IsAlive && grandchild->IsRoyalFamilyMember) {
                                if (nextSuccessor == NULL || grandchild->YearOfBirth < nextSuccessor->YearOfBirth) {
                                    nextSuccessor = grandchild;
                                }
                            }
                            if (nextSuccessor != NULL) {
                                printf("Pewaris selanjutnya adalah: %s\n", nextSuccessor->Name);
                                tree->IsLeader = false;
                                nextSuccessor->IsLeader = true;
                                return;
                            }
                            grandchild = grandchild->NextBrother;
                        }
                        nephew = nephew->NextBrother;
                    }
                    uncle = uncle->NextBrother;
                }
            }
        }


        if (nextSuccessor != NULL) {
            printf("Pewaris selanjutnya adalah: %s\n", nextSuccessor->Name);
            tree->IsLeader = false;
            nextSuccessor->IsLeader = true;
        }
    }
}
