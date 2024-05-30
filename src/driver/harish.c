//
// Created by hp on 27/05/2024.
//

#include "../header/harish.h"

int currentYear;
//fungsi mendapatkan tahun sekarang
void getTahunSekarang(){
    // Mendapatkan tahun sekarang
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    currentYear = local->tm_year + 1900;
}


//blok fungsi untuk opsi 4 = hitung jumlah anak suatu node
void countChildren(DataTree *tree) {
    clearscreen();
    char parentName[100];
    displayTree(tree);
    printf("\n\n");

    do{
        printf("Masukan nama Royal Family Member yang ingin dihitung jumlah anaknya (ketik ");
        warnateks(RED);printf("'exit'");warnateks(11);
        printf(" untuk keluar) : ");
        fgets(parentName, sizeof(parentName), stdin);
        parentName[strcspn(parentName, "\n")] = '\0'; // Hilangkan newline dari input

        if (strcmp(parentName, "exit") == 0) {
            return; // Exit the function if the user types 'exit'
        }

        //mencari apkah ada atau tidak node yang dimaksud
        NBTree *parentNode = findNode(tree->Root, parentName);
        if (parentNode != NULL) {
            //memanggil fungsi memanggil fungsi hitung jumlah anak alias degree suatu node
            int numChildren = prosesCountChildren(parentNode);
            printf("Jumlah anak dari %s adalah %d.\n", parentName, numChildren);
        } else {
            printf("Anggota keluarga dengan nama '%s' tidak ditemukan.\n", parentName);
            printf("Silakan coba lagi.\n\n");
        }

    } while(1);

    waitForEnter();
}

// Fungsi untuk menghitung jumlah anak dari anggota kerajaan
int prosesCountChildren(NBTree *parent) {
    if (parent == NULL) {
        return 0;
    }

    int count = 0;
    NBTree *child = parent->FirstSon;

    // Iterasi melalui semua anak langsung dari parent
    while (child != NULL) {
        count++;
        child = child->NextBrother;
    }

    return count;
}


//blok fungsi untuk opsi 5 (hitung level tree atau jumlah generasi Royal Fam Member)
void countGeneration(DataTree *tree) {
    clearscreen();
    if (tree == NULL || tree->Root == NULL) {
        gotoxy(30, 4);
        printf("Pohon Royal Family Member kosong.\n");
        waitForEnter();
        return;
    }

    int treeLevel;
    treeLevel = prosesCountGeneration(tree->Root);
    gotoxy(30, 5);
    warnateks(11); // Set color to light blue
    printf("==========================================");
    gotoxy(30, 6);
    printf("|                                        |");
    gotoxy(30, 7);
    printf("|    Jumlah level atau generasi dalam    |");
    gotoxy(30, 8);
    printf("|    pohon Royal Family Member adalah    |");
    gotoxy(30, 9);
    printf("|                  %d                     |", treeLevel);
    gotoxy(30, 10);
    printf("|                                        |");
    gotoxy(30, 11);
    printf("==========================================");

//    printf("Jumlah level atau generasi dalam pohon Royal Family Member adalah %d.\n", treeLevel);
    Sleep(500);
    waitForEnter();
}

// Fungsi rekursif untuk menghitung level pohon
int prosesCountGeneration(NBTree *node) {
    if (node == NULL) {
        return 0;
    }

    int maxLevel = 0;
    NBTree *child = node->FirstSon;

    // Iterasi melalui semua anak dan menghitung level maksimum dari setiap cabang
    while (child != NULL) {
        int childLevel;
        childLevel = prosesCountGeneration(child);
        if (childLevel > maxLevel) {
            maxLevel = childLevel;
        }
        child = child->NextBrother;
    }

    // Menambahkan 1 untuk level saat ini
    return maxLevel + 1;
}


//blok fungsi untuk opsi 8 (timeskip)
void yearPasses(DataTree *tree) {
    clearscreen();
    gotoxy(30,4);
    printf("========== Menu Lompat Tahun (Timeskip)==========");
    gotoxy(30,6);
    printf("Tahun saat ini adalah %d.\n", currentYear);

    int years;
    Sleep(500);
    gotoxy(30,7);
    printf("Masukkan jumlah tahun untuk melompat ke depan: ");
    scanf("%d", &years);

    //memanggil fungsi timeskip untuk memproses lompat tahun
    prosesTimeskip(years);


    loading();
    clearscreen();
    gotoxy(30,5);
    printf("Tahun saat ini adalah %d.\n\n\n", currentYear);
    waitForEnter();
}

//fungsi untuk update waktu terkini setelah timeskip
void prosesTimeskip(int years) {
    currentYear += years;
}


//blok fungsi opsi 10 (reset kondisi ke initial state)
//void resetProgress(DataTree **tree, const char *filename){
void resetProgress(DataTree **tree, const char *initialFilename, const char *dataFilename){
    clearscreen();
    // Hapus pohon lama
    if (*tree != NULL) {
        free(*tree);
    }

    // meload kembali isi tree dari file
//    *tree = buildTreeFromFile(filename);
//    printf("Progres telah direset.\n");

    //membuka file initial data untuk read
    FILE *initialFile = fopen(initialFilename, "r");
    if (initialFile == NULL) {
        perror("Failed to open initial data file");
        exit(EXIT_FAILURE);
    }

    //membuka file data untuk write sehingga konten di dalam nya hilang
    FILE *dataFile = fopen(dataFilename, "w");
    if (dataFile == NULL) {
        perror("Failed to open data file");
        fclose(initialFile);
        exit(EXIT_FAILURE);
    }

    //baca tiap baris dari initialdata dan ditulis ke data
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), initialFile)) {
        fputs(buffer, dataFile);
    }

    fclose(initialFile);
    fclose(dataFile);


    //mengembalikan tahun ke tahun sekarang
    getTahunSekarang();

    loading();
    waitForEnter();
}




//view ensiklopedi
void displayEncyclopediaDescription(char *name) {
//    FILE *file = fopen("ensiklopedia.txt", "r");
    FILE *file = fopen("../db/ensiklopedia.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file ensiklopedia.\n");
        return;
    }

    char line[200];
    char entryName[100];
    bool found = false;

    // Mencari deskripsi untuk nama yang sesuai
    while (fgets(line, sizeof(line), file)) {
        // Memisahkan baris menjadi nama dan deskripsi
        char *token = strtok(line, ":");
        if (token != NULL) {
            strcpy(entryName, token); // Menyimpan nama
            if (strcmp(entryName, name) == 0) {
                found = true;
                // Menampilkan deskripsi
                token = strtok(NULL, ":"); // Mengambil bagian deskripsi
                if (token != NULL) {
                    printf("%s\n", token);
                }
                break;
            }
        }
    }

    fclose(file);

    // Jika nama tidak ditemukan dalam ensiklopedia
    if (!found) {
        printf("Deskripsi untuk anggota keluarga '%s' tidak ditemukan dalam ensiklopedia.\n", name);
    }
}

void displayEncyclopediaEntry(DataTree *tree, char *name) {
    NBTree *member = findNode(tree->Root, name);
    if (member == NULL) {
        printf("Anggota keluarga dengan nama '%s' tidak ditemukan.\n", name);
        return;
    }

    // Tampilkan informasi anggota keluarga
    printf("\nInformasi Anggota Keluarga:\n");
    printf("Nama: %s\n", member->Name);
    printf("Umur: %d tahun\n", calculateAge(member->YearOfBirth));
    printf("Status Pernikahan: %s\n", (member->IsMarriageApproved) ? "Menikah dengan" : "Single");
    if (member->IsMarriageApproved) {
        printf("Nama Pasangan: %s\n", member->PartnerName);
    }

    // Tampilkan deskripsi dari file ensiklopedia.txt
    printf("\nDeskripsi:\n");
    displayEncyclopediaDescription(member->Name);
}

void viewEncyclopedia(DataTree *tree) {
    clearscreen();
    gotoxy(30,4);printf("========== Ensiklopedia ==========");
    printf("\n\nDaftar anggota keluarga kerajaan dalam Ensiklopedia:\n\n");

    // Tampilkan terlebih dahulu silsilah kerajaan yang aktif IsRoyalFamilyMember bernilai True
//    printf("Anggota Keluarga Kerajaan yang Aktif:\n");
    displayTree(tree);

    char name[100];
    bool nameFound = false;

    do {
        // Meminta input nama anggota keluarga untuk menampilkan ensiklopedianya
        printf(" ");
        printf("\nMasukkan nama anggota keluarga untuk menampilkan ensiklopedianya (Ketik ");
        warnateks(RED);printf("'exit'");warnateks(11);
        printf(" untuk kembali ke menu utama): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; // Hilangkan newline dari input

        if (strcmp(name, "exit") == 0) {
            return; // Keluar dari fungsi jika pengguna memilih untuk kembali ke menu utama
        }

        // Tampilkan ensiklopedianya jika nama ditemukan
        if (findNode(tree->Root, name) != NULL) {
            clearscreen();
            displayEncyclopediaEntry(tree, name);
            nameFound = true;
        } else {
            warnateks(YELLOW);
            printf("\nAnggota keluarga dengan nama '%s' tidak ditemukan.\n", name);
            warnateks(11);
            nameFound = false;
        }

    } while (!nameFound);

    /*
    // Meminta input nama anggota keluarga untuk menampilkan ensiklopedianya
    char name[100];
    printf("\nMasukkan nama anggota keluarga untuk menampilkan ensiklopedianya: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Hilangkan newline dari input

    // Tampilkan ensiklopedianya
    displayEncyclopediaEntry(tree, name);
    */
    // Tunggu sampai pengguna menekan tombol Enter untuk kembali ke menu utama
    printf("\nTekan tombol Enter untuk kembali ke menu utama...");
    while (getch() != 13); // 13 adalah kode ASCII untuk tombol Enter
}


//aturan
void displayAturan() {

    clearscreen();
    printLine();
 // Castle format
    printf("              !                                         !\n");
    printf("              |>>>                                      |>>>\n");
    printf("              |>>>                                      |>>>\n");
    printf("              |_   _   _                       _   _   _|\n");
    printf("  !._         | |_| |_| |                     | |_| |_| |           !._\n");
    printf("  |* '-._     \\_________/                     \\_________/           |* '-._\n");
    printf("  |CC  _.'     \\ .-.   /                       \\   .-. /            |CC  _.'.\n");
    printf("  |.--'         ||_|  |                         |  |_||             |.--'\n");
    printf("  |_   _   _   _|  _  |_   _   _   _   _   _   _|  _  |_   _   _   _|\n");
    printf("  | |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |\n");
    printf("  \\_________________________________________________________________/\n");
    printf("   |   .-.          .-.           .-.           .-.          .-.    |\n");
    printf("   |   |_|          |_|           |_|           |_|          |_|    |\n");
    printf("   |                                                                |\n");
    printf("   |                          ATURAN PENURUTAN TAHTA                |\n");
    printf("   |                                                                |\n");
    printf("   | Pewaris Utama: Anak tertua dari raja/ratu yang sedang berkuasa,|\n");
    printf("   | tanpa memandang jenis kelamin (putra atau putri).              |\n");
    printf("   |                                                                |\n");
    printf("   | Pewaris Selanjutnya: Kalau anak tertua meninggal dunia sebelum |\n");
    printf("   | raja/ratu, maka hak suksesi jatuh pada anak tertua selanjutnya |\n");
    printf("   | dari raja/ratu tersebut.                                       |\n");
    printf("   |                                                                |\n");
    printf("   | Keluarga Kerajaan: Kalau raja/ratu tidak memiliki keturunan,   |\n");
    printf("   | takhta akan diwariskan kepada anggota keluarga kerajaan lainnya|\n");
    printf("   | berdasarkan urutan yang ditetapkan dalam konstitusi. Urutan ini|\n");
    printf("   | memprioritaskan kerabat dekat dengan derajat kekerabatan       |\n");
    printf("   | pertama, kedua, dan ketiga.                                    |\n");
    printf("   |                                                                |\n");
    printf("   | Derajat Kekerabatan:                                           |\n");
    printf("   | a. Derajat Pertama: Hubungan orang tua-anak.                   |\n");
    printf("   | b. Derajat Kedua: Hubungan saudara kandung, kakek-nenek dan    |\n");
    printf("   | cucu.                                                          |\n");
    printf("   | c. Derajat Ketiga: Hubungan paman/bibi dan keponakan.          |\n");
    printf("   |                                                                |\n");
    printf("   | Kehilangan Hak Suksesi:                                        |\n");
    printf("   | a. Kerabat dengan derajat kekerabatan lebih jauh dari ketiga.  |\n");
    printf("   | b. Anggota keluarga kerajaan yang menikah tanpa persetujuan    |\n");
    printf("   | parlemen.                                                      |\n");
    printf("   |                                                                |\n");
    printf("   | Ketentuan lain: Raja/ratu diperbolehkan turun takhta atas      |\n");
    printf("   | kehendak sendiri.                                              |\n");
    printf("   | ______________________________________________________________ |\n");
    printf("   ~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\"^\"~\n");

    printLine();
    waitForEnter();
}

void setOptionColor(int option, int selectedOption) {
    if (option == selectedOption) {
        warnateks(15); // Highlight color for the selected option
    } else {
        warnateks(11); // Regular color for unselected options
    }
}

void loading(){
	system("cls");

        gotoxy(58,10);
        printf("LOADING");
		Sleep(500);
		gotoxy(30,11);printf("\t\t\t_____                 ");
		gotoxy(30,12);printf("\t\t\t~~~~~                 ");
		Sleep(500);
		gotoxy(30, 11); printf("\t\t\t_______             ");
		gotoxy(30, 12); printf("\t\t\t~~~~~~~             ");
		Sleep(500);
		gotoxy(30, 11); printf("\t\t\t________________       ");
		gotoxy(30, 12); printf("\t\t\t~~~~~~~~~~~~~~~~       ");
		Sleep(500);
		gotoxy(30,11);printf("\t\t\t_________________________");
		gotoxy(30,12);printf("\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~");
		Sleep(900);
		clearscreen();
}


//fungsi tampilan
void clearscreen() {
    system("cls");
}

void printLine() {
    printf("+-----------------------------------------------------------------------------+\n");
}

