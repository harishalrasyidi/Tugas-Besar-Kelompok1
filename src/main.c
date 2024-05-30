#include <conio.h>
#include "header/annisa_dian.h"
#include "header/harish.h"

int main() {
    DataTree *tree = buildTreeFromFile("../db/data.txt");
    int selectedOption = 1;
    int status = 1;
    getTahunSekarang();
    printFromFileSplash("../db/splash_screen.txt");
    waitForEnter();

    while(status == 1) {
        system("cls"); // Membersihkan layar
        // Menampilkan menu
        warnateks(11);

        gotoxy(30, 2);
        printf("================= Main Menu =================\n");
        setOptionColor(1, selectedOption);
        gotoxy(30, 4);
        printf("[%c] Insert Anggota Keluarga Kerajaan", (selectedOption == 1) ? 'X' : ' ');

        setOptionColor(2, selectedOption);
        gotoxy(30, 5);
        printf("[%c] Insert Partner", (selectedOption == 2) ? 'X' : ' ');

        setOptionColor(3, selectedOption);
        gotoxy(30, 6);
        printf("[%c] Print Royal Family Member", (selectedOption == 3) ? 'X' : ' ');

        setOptionColor(4, selectedOption);
        gotoxy(30, 7);
        printf("[%c] Hitung jumlah anak dari anggota kerajaan", (selectedOption == 4) ? 'X' : ' ');

        setOptionColor(5, selectedOption);
        gotoxy(30, 8);
        printf("[%c] Hitung jumlah generasi keluarga kerajaan", (selectedOption == 5) ? 'X' : ' ');

        setOptionColor(6, selectedOption);
        gotoxy(30, 9);
        printf("[%c] Mematikan salah satu anggota keluarga kerajaan", (selectedOption == 6) ? 'X' : ' ');

        setOptionColor(7, selectedOption);
        gotoxy(30, 10);
        printf("[%c] Menurunkan tahta kerajaan saat ini", (selectedOption == 7) ? 'X' : ' ');

        setOptionColor(8, selectedOption);
        gotoxy(30, 11);
        printf("[%c] Timeskip (lompat ke beberapa tahun ke depan)", (selectedOption == 8) ? 'X' : ' ');

        setOptionColor(9, selectedOption);
        gotoxy(30, 12);
        printf("[%c] Print log aktivitas", (selectedOption == 9) ? 'X' : ' ');

        setOptionColor(10, selectedOption);
        gotoxy(30, 13);
        printf("[%c] Reset Royal Family Member ke kondisi awal", (selectedOption == 10) ? 'X' : ' ');

        setOptionColor(11, selectedOption);
        gotoxy(30, 14);
        printf("[%c] Aturan", (selectedOption == 11) ? 'X' : ' ');

        setOptionColor(12, selectedOption);
        gotoxy(30, 15);
        printf("[%c] Ensiklopedia", (selectedOption == 12) ? 'X' : ' ');

        setOptionColor(13, selectedOption);
        gotoxy(30, 16);
        printf("[%c] ViewEnsiklopedia", (selectedOption == 13) ? 'X' : ' ');

        warnateks(11);
        int keyboard = getch();

        switch (keyboard) {
            case 72: // Panah atas
                selectedOption = (selectedOption > 1) ? selectedOption - 1 : 13;
                Beep(800, 100);
                break;
            case 80: // Panah bawah
                selectedOption = (selectedOption < 13) ? selectedOption + 1 : 1;
                Beep(800, 100);
                break;
            case 13: // Tombol Enter
                Beep(800, 300);
                switch (selectedOption) {
                    case 1:
                        insertFamilyMember(tree);
                        break;
                    case 2:
                        insertPartner(tree);
                        break;
                    case 3:
//                        printRoyalFamilyMember(tree);
                        displayTree(tree);
                        waitForEnter();
                        break;
                    case 4:
                        //memanggil fungsi yang bersangkutan
                        countChildren(tree);
                        break;
                    case 5:
                        //memanggil fungsi yang bersangkutan
                        countGeneration(tree);
                        break;
                    case 6:
                        //memanggil fungsi yang bersangkutan
                        passedAway(tree);
                        break;
                    case 7:
                        //memanggil fungsi yang bersangkutan
                        abdicate(tree);
                        break;
                    case 8:
                        //memanggil fungsi yang bersangkutan
                        yearPasses(tree);
                        break;
                    case 9:
                        //memanggil fungsi yang bersangkutan
                        break;
                    case 10:
                        //memanggil fungsi yang bersangkutan
//                        resetProgress(&tree, "data.txt");
                        resetProgress(&tree, "../db/initial_data.txt", "../db/data.txt");
                        tree = buildTreeFromFile("../db/data.txt");
                        break;
                    case 11:
                        //memanggil fungsi yang bersangkutan
                        displayAturan();
                        break;
                    case 12:
                        encyclopedia(tree);
                        break;
                    case 13:
                        viewEncyclopedia(tree);
                        break;
                }
                break;
        }
    }
    return 0;
}
