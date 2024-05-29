#include <conio.h>
#include "header/annisa_dian.h"
#include "header/harish.h"

int main() {
    DataTree *tree = buildTreeFromFile("../db/data.txt");
    int selectedOption = 1;
    int status = 1;
    getTahunSekarang();

    while(status == 1) {
        system("cls"); // Membersihkan layar
        // Menampilkan menu
        printf("================= Main Menu =================\n");
        printf("[%c] Insert Anggota Keluarga Kerajaan\n", (selectedOption == 1) ? 'X' : ' ');
        printf("[%c] Insert Partner\n", (selectedOption == 2) ? 'X' : ' ');
        printf("[%c] Print Royal Family Member\n", (selectedOption == 3) ? 'X' : ' ');
        printf("[%c] Hitung jumlah anak dari anggota kerajaan\n", (selectedOption == 4) ? 'X' : ' ');
        printf("[%c] Hitung jumlah generasi keluarga kerajaan\n", (selectedOption == 5) ? 'X' : ' ');
        printf("[%c] Mematikan salah satu anggota keluarga kerajaan\n", (selectedOption == 6) ? 'X' : ' ');
        printf("[%c] Menurunkan tahta kerajaan saat ini\n", (selectedOption == 7) ? 'X' : ' ');
        printf("[%c] Timeskip (lompat ke beberapa tahun ke depan)\n", (selectedOption == 8) ? 'X' : ' ');
        printf("[%c] Print log aktivitas\n", (selectedOption == 9) ? 'X' : ' ');
        printf("[%c] Reset Royal Family Member ke kondisi awal\n", (selectedOption == 10) ? 'X' : ' ');
        printf("[%c] Aturan\n", (selectedOption ==11) ? 'X' : ' ');
        printf("[%c] Ensiklopedia\n", (selectedOption == 12) ? 'X' : ' ');
        printf("[%c] ViewEnsiklopedia\n", (selectedOption == 13) ? 'X' : ' ');

        int keyboard = getch();

        switch (keyboard) {
            case 72: // Panah atas
                selectedOption = (selectedOption > 1) ? selectedOption - 1 : 13;
                break;
            case 80: // Panah bawah
                selectedOption = (selectedOption < 13) ? selectedOption + 1 : 1;
                break;
            case 13: // Tombol Enter
                switch (selectedOption) {
                    case 1:
                        insertFamilyMember(tree);
                        break;
                    case 2:
                        insertPartner(tree);
                        break;
                    case 3:
                        printRoyalFamilyMember(tree);
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
