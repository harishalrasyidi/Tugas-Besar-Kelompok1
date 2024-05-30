//
// Created by hp on 27/05/2024.
//


#include "../header/annisa_dian.h"
#include <windows.h>

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

void warnateks(int warna) // Modul yang berfungsi untuk memberi warna ke karakter
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, warna);
}

void gotoxy(int x, int y) // Modul untuk memfungsikan fungsi gotoxy
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
/**** Pembuatan node baru ****/
NBTree* createNode(char *name, int yearOfBirth, Gender gender, bool isLeader, bool isRoyalFamilyMember, bool isMarriageApproved, char *parentName, char *partnerName, bool isAlive) {
/* IS : name, yearOfBirth, gender, isLeader, isRoyalFamilyMember, isMarriageApproved, parentName, partnerName, dan isAlive sembarang */
/* FS : mengembalikan node baru dengan nilai sesuai parameter yang diberikan */
    NBTree* newNode = (NBTree*)malloc(sizeof(NBTree));
    strcpy(newNode->Name, name);
    newNode->YearOfBirth = yearOfBirth;
    newNode->gender = gender;
    newNode->IsLeader = isLeader;
    newNode->IsRoyalFamilyMember = isRoyalFamilyMember;
    newNode->IsMarriageApproved = isMarriageApproved;
    strcpy(newNode->ParentName, parentName);
    strcpy(newNode->PartnerName, partnerName);
    newNode->IsAlive = isAlive;
    newNode->FirstSon = NULL;
    newNode->NextBrother = NULL;
    newNode->Parent = NULL;
    return newNode;
}

/**** Parsing string gender ****/
Gender parseGender(char *genderStr) {
/* IS : genderStr sembarang */
/* FS : mengembalikan nilai enum Gender sesuai dengan genderStr */
    if (strcmp(genderStr, "Male") == 0) {
        return Male;
    } else {
        return Female;
    }
}

/**** Parsing string boolean ****/
bool parseBool(char *boolStr) {
/* IS : boolStr sembarang */
/* FS : mengembalikan nilai boolean sesuai dengan boolStr */
    return strcmp(boolStr, "1") == 0;
}

void parseLine(char *line, char *name, int *yearOfBirth, Gender *gender, bool *isLeader, bool *isRoyalFamilyMember, bool *isMarriageApproved, char *parentName, char *partnerName, bool *isAlive) {
    char genderStr[10], isLeaderStr[10], isRoyalFamilyMemberStr[10], isMarriageApprovedStr[10], partnerNameTemp[100], isAliveStr[10];
    int parsed = sscanf(line, "%[^:]:%d:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%s", name, yearOfBirth, genderStr, isLeaderStr, isRoyalFamilyMemberStr, isMarriageApprovedStr, parentName, partnerNameTemp, isAliveStr);

    // Pastikan semua nilai sudah diparsing dengan benar
    if (parsed < 9) {
        strcpy(isAliveStr, "0");
    }
    if (parsed < 8) {
        partnerNameTemp[0] = '\0'; // Ensure partnerName is empty if not specified
    }
    if (parsed < 7) {
        parentName[0] = '\0'; // Ensure parentName is empty if not specified
    }
    if (strcmp(partnerNameTemp, "NULL") == 0){
        strcpy(partnerNameTemp, "");
    }

    // Handling empty partnerName
    if (strlen(partnerNameTemp) == 0) {
        strcpy(partnerName, ""); // Set partnerName to empty string
        *isAlive = parseBool(isAliveStr);
    } else {
        strcpy(partnerName, partnerNameTemp); // Copy partnerNameTemp to partnerName
        // If partnerName is not empty, parse isAlive from the end
        sscanf(line, "%*[^:]:%*d:%*[^:]:%*[^:]:%*[^:]:%*[^:]:%*[^:]:%*[^:]:%[^:]", isAliveStr);
        *isAlive = parseBool(isAliveStr);
    }

    *gender = parseGender(genderStr);
    *isLeader = parseBool(isLeaderStr);
    *isRoyalFamilyMember = parseBool(isRoyalFamilyMemberStr);
    *isMarriageApproved = parseBool(isMarriageApprovedStr);
}


/**** Menambahkan anak ke node parent ****/
void addChild(NBTree *parent, NBTree *child) {
/* IS : parent dan child sudah dialokasi, child belum memiliki parent */
/* FS : child ditambahkan sebagai anak dari parent, child menjadi anak pertama jika parent belum memiliki anak, jika sudah, child ditambahkan sebagai saudara dari anak-anak yang sudah ada */
    child->Parent = parent;
    if (parent->FirstSon == NULL) {
        parent->FirstSon = child;
    } else {
        NBTree *sibling = parent->FirstSon;
        while (sibling->NextBrother != NULL) {
            sibling = sibling->NextBrother;
        }
        sibling->NextBrother = child;
    }
}

/**** Mencari node berdasarkan nama ****/
NBTree* findNode(NBTree* root, char* name) {
/* IS : root adalah root dari tree, name sembarang */
/* FS : mengembalikan node dengan nama yang sesuai, jika tidak ditemukan mengembalikan NULL */
    if (root == NULL) return NULL;
    if (strcmp(root->Name, name) == 0) return root;

    NBTree* found = findNode(root->FirstSon, name);
    if (found != NULL) return found;

    return findNode(root->NextBrother, name);
}

/**** Membangun tree dari file ****/
DataTree* buildTreeFromFile(const char *filename) {
/* IS : filename adalah nama file data.txt yang berisi data tree, tree belum terbentuk */
/* FS : mengembalikan tree yang sudah terbentuk berdasarkan data dari file */
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    DataTree *tree = (DataTree*)malloc(sizeof(DataTree));
    tree->Root = NULL;
    char line[256];
    NBTree *nodes[100];
    char parentNames[200][20];
    char partnerNames[100][20];
    int nodeCount = 0;

    while (fgets(line, sizeof(line), file)) {
        char name[100], parentName[200] = "", partnerName[100] = "";
        int yearOfBirth;
        Gender gender;
        bool isLeader, isRoyalFamilyMember, isMarriageApproved, isAlive;

        parseLine(line, name, &yearOfBirth, &gender, &isLeader, &isRoyalFamilyMember, &isMarriageApproved, parentName, partnerName, &isAlive);

        NBTree *newNode = createNode(name, yearOfBirth, gender, isLeader, isRoyalFamilyMember, isMarriageApproved, parentName, partnerName, isAlive);

        nodes[nodeCount] = newNode;
        strcpy(parentNames[nodeCount], parentName);
        strcpy(partnerNames[nodeCount], partnerName);
        nodeCount++;

        if (tree->Root == NULL) {
            tree->Root = newNode;
        }
    }

    fclose(file);
    int i;
    for (i = 0; i < nodeCount; i++) {
        if (strlen(parentNames[i]) > 0) {
            NBTree *parentNode = findNode(tree->Root, parentNames[i]);
            if (parentNode != NULL) {
                addChild(parentNode, nodes[i]);
            } else {
                printf("Parent not found for %s\n", nodes[i]->Name);
            }
        }
    }

    return tree;
}

/**** Menambahkan node ke tree ****/
void insertNode(DataTree *tree, char *name, int yearOfBirth, Gender gender, bool isLeader, bool isRoyalFamilyMember, bool isMarriageApproved, char *parentName, char *partnerName, bool isAlive) {
/* IS : tree sudah terbentuk, name, yearOfBirth, gender, isLeader, isRoyalFamilyMember, isMarriageApproved, parentName, partnerName, dan isAlive sembarang */
/* FS : menambahkan node baru ke tree sesuai dengan parameter yang diberikan, jika parent ditemukan */
    NBTree *newNode = createNode(name, yearOfBirth, gender, isLeader, isRoyalFamilyMember, isMarriageApproved, parentName, partnerName, isAlive);
    NBTree *parentNode = findNode(tree->Root, parentName);
    if (parentNode != NULL) {
        addChild(parentNode, newNode);
    } else {
        printf("Parent not found for %s\n", name);
    }
}

/**** Menulis node ke file ****/
void writeNodeToFile(NBTree *node, FILE *file)
/* IS : node adalah node dari tree, file sudah terbuka untuk ditulisi */
/* FS : node dan seluruh keturunannya ditulis ke dalam file */
{
    if (node == NULL) return;
    fprintf(file, "%s:%d:%s:%d:%d:%d:%s:%s:%d\n",
        node->Name, node->YearOfBirth,
        node->gender == Male ? "Male" : "Female",
        node->IsLeader ? 1 : 0,
        node->IsRoyalFamilyMember ? 1 : 0,
        node->IsMarriageApproved ? 1 : 0,
        strlen(node->ParentName) > 0 ? node->ParentName : "NULL",
        strlen(node->PartnerName) > 0 ? node->PartnerName : "NULL",
        node->IsAlive ? 1 : 0);

    writeNodeToFile(node->FirstSon, file);
    writeNodeToFile(node->NextBrother, file);
}

/**** Memperbarui file dengan tree ****/
void updateFile(const char *filename, DataTree *tree)
/* IS : tree sudah terbentuk, filename sembarang */
/* FS : file dengan nama filename berisi data dari tree */
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    writeNodeToFile(tree->Root, file);
    fclose(file);
}

// Fungsi untuk menampilkan pesan dan menunggu tombol enter
void waitForEnter() {
    printf("\nTekan tombol Enter untuk melanjutkan...");
    while (getch() != 13); // 13 adalah kode ASCII untuk tombol Enter
}

void insertFamilyMember(DataTree *tree) {
	clearscreen();
	displayTree(tree);
    char parentName[100];
    char childName[100];
    int parentYearOfBirth, childYearOfBirth;
    Gender childGender;

    printf("\nMasukkan informasi anggota keluarga kerajaan:\n");
	NBTree *parent;
    // Input nama orang tua
	do {
	    printf("Nama orang tua (klik 'x' untuk keluar): ");
	    fgets(parentName, sizeof(parentName), stdin);
	    parentName[strcspn(parentName, "\n")] = '\0'; // Hilangkan newline dari input

	    if (strcmp(parentName, "x") == 0) {
	        // Kembali ke menu utama jika user memilih untuk keluar
	        return;
	    }

	    // Mencari node orang tua
	    parent = findNode(tree->Root, parentName);

	    if (parent == NULL) {
	        printf("Orang tua dengan nama '%s' tidak ditemukan.\n", parentName);
	    } else if (strlen(parent->PartnerName) == 0) {
	        printf("Orang tua '%s' belum memiliki pasangan. Tidak bisa memiliki anak.\n", parentName);
	    } else {
	        break; // Keluar dari loop jika orang tua valid dan telah menikah
	    }
	} while (true);

	// Input nama anak
	printf("Nama anak: ");
	fgets(childName, sizeof(childName), stdin);
	childName[strcspn(childName, "\n")] = '\0'; // Hilangkan newline dari input

	// Input tahun lahir anak
	do {
	    printf("Tahun lahir anak (klik 'x' untuk keluar): ");
	    char input[100];
	    fgets(input, sizeof(input), stdin);

	    if (strcmp(input, "x\n") == 0) {
	        // Kembali ke menu utama jika user memilih untuk keluar
	        return;
	    }

	    sscanf(input, "%d", &childYearOfBirth);

	    if (childYearOfBirth - parent->YearOfBirth < 19) {
	        printf("Tahun lahir anak harus terpaut minimal 19 tahun dari tahun lahir orang tua.\n");
	    }
	} while (childYearOfBirth - parent->YearOfBirth < 19);

    // Input gender anak
    char genderStr[10];
	do {
	    printf("Gender anak (Male/Female) (klik 'x' untuk keluar): ");
	    fgets(genderStr, sizeof(genderStr), stdin);
	    genderStr[strcspn(genderStr, "\n")] = '\0'; // Hilangkan newline dari input

	    if (strcmp(genderStr, "x") == 0) {
	        // Kembali ke menu utama jika user memilih untuk keluar
	        return;
	    }

	    if (strcmp(genderStr, "Male") != 0 && strcmp(genderStr, "Female") != 0) {
	        printf("Inputan tidak valid. Gender anak harus 'Male' atau 'Female'.\n");
	    }
	} while (strcmp(genderStr, "Male") != 0 && strcmp(genderStr, "Female") != 0);

    // Memperbarui file dengan menambahkan node anak baru
    insertNode(tree, childName, childYearOfBirth, childGender, 0, 1, 1, parentName, "NULL", 1);
    updateFile("../db/data.txt", tree);
    printf("Anggota keluarga berhasil ditambahkan.\n");
    waitForEnter();
}

void insertPartner(DataTree *tree) {
	clearscreen();
    // Menampilkan daftar anggota keluarga kerajaan yang belum memiliki pasangan
    printf("Daftar anggota keluarga kerajaan:\n");
    displayTree(tree);

	    // Loop akan terus berjalan hingga input nama anggota keluarga valid
	char name[100];
	NBTree *member;
    do {
        printf("\nMasukkan nama anggota keluarga yang ingin diberikan pasangan (klik 'x' untuk keluar): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; // Hilangkan newline dari input

        if (strcmp(name, "x") == 0) {
            // Kembali ke menu utama jika user memilih untuk keluar
            return;
        }

        member = findNode(tree->Root, name);
        if (member == NULL) {
            printf("Anggota keluarga dengan nama '%s' tidak ditemukan.\n", name);
        } else if (strlen(member->PartnerName) > 0) {
            printf("%s sudah memiliki pasangan.\n", name);
            member = NULL; // Reset member jika sudah memiliki pasangan
        } else {
            int age = calculateAge(member->YearOfBirth);
            if (age < 18) {
                printf("%s belum cukup umur untuk menikah.\n", name);
                member = NULL; // Reset member jika belum cukup umur
            }
        }
    } while (member == NULL);

    // Menampilkan informasi anggota keluarga
    int age = calculateAge(member->YearOfBirth);
    printf("Informasi Anggota Keluarga:\n");
    // Memanggil fungsi ASCII sesuai dengan jenis kelamin
    if (member->gender == Male) {
        printFromFile("../db/king_ascii.txt");
    } else {
        printFromFile("../db/queen_ascii.txt");
    }
    printf("\nNama: %s\n", member->Name);
    printf("Umur: %d tahun\n", age);
    printf("Jenis Kelamin: %s\n", (member->gender == Male) ? "Male" : "Female");
    printf("Status Menikah: %s\n\n", (strlen(member->PartnerName) > 0) ? "Menikah" : "Single");

    // Validasi input nama partner
    char partnerName[100];
    do {
        printf("Masukkan nama partner (klik 'x' untuk keluar): ");
        fgets(partnerName, sizeof(partnerName), stdin);
        partnerName[strcspn(partnerName, "\n")] = '\0'; // Hilangkan newline dari input

        if (strcmp(partnerName, "x") == 0) {
            // Kembali ke menu utama jika user memilih untuk keluar
            return;
        }

        if (strlen(partnerName) == 0) {
            printf("Nama partner tidak boleh kosong.\n");
        }
    } while (strlen(partnerName) == 0);

    // Validasi usia partner
    int partnerAge;
    do {
        printf("Masukkan usia partner (klik 'x' untuk keluar): ");
        char input[100];
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "x\n") == 0) {
            // Kembali ke menu utama jika user memilih untuk keluar
            return;
        }
        sscanf(input, "%d", &partnerAge);

        if (partnerAge < 18) {
            printf("%s belum cukup umur untuk menikah.\n", partnerName);
        }
    } while (partnerAge < 18);

    // Validasi jenis kelamin partner
    char genderStr[10];
    Gender partnerGender;
    do {
        printf("Masukkan jenis kelamin partner (Male/Female) (klik 'x' untuk keluar): ");
        fgets(genderStr, sizeof(genderStr), stdin);
        genderStr[strcspn(genderStr, "\n")] = '\0'; // Hilangkan newline dari input

        if (strcmp(genderStr, "x") == 0) {
            // Kembali ke menu utama jika user memilih untuk keluar
            return;
        }

        partnerGender = parseGender(genderStr);

        if (partnerGender == member->gender) {
            printf("Pernikahan ini sudah dipastikan dilarang karena jenis kelamin sama.\n");
        }
    } while (partnerGender == member->gender);

    // Menampilkan informasi partner
    printf("\nInformasi Partner:\n");
    printf("Nama: %s\n", partnerName);
    printf("Umur: %d tahun\n", partnerAge);
    printf("Jenis Kelamin: %s\n", (partnerGender == Male) ? "Male" : "Female");

	// Menanyakan restu keluarga
	int consent;
	do {
	    printf("\nPasangan Anda cocok, mari kita tanyakan restu keluarga? (1: Ya / 0: Tidak): ");
	    scanf("%d", &consent);

	    if (consent != 0 && consent != 1) {
	        printf("Inputan tidak valid. Harap masukkan 1 untuk Ya atau 0 untuk Tidak.\n");
	        // Membersihkan input buffer
	        while (getchar() != '\n');
	    }
	} while (consent != 0 && consent != 1);


    // Memproses restu keluarga
    if (consent == 1) {
        // Memperbarui data anggota keluarga dengan pasangan baru
        strcpy(member->PartnerName, partnerName);
        member->IsMarriageApproved = true;
    } else {
        // Jika tidak disetujui, mengubah status anggota keluarga menjadi non-kerajaan
        strcpy(member->PartnerName, partnerName);
        member->IsMarriageApproved = false;
        member->IsRoyalFamilyMember = false;
    }

    // Update file dengan perubahan
    updateFile("../db/data.txt", tree);

    // Menampilkan pesan
    if (consent == 1) {
        printf("Pasangan Anda telah disetujui. Selamat menempuh hidup baru!\n");
        marriageAscii(member->Name, partnerName, member->gender, partnerGender);
    } else {
        printf("Restu keluarga tidak diberikan. Maaf atas ketidakcocokan ini.\n");
            waitForEnter();
    }
}

void printRoyalFamilyMember(DataTree *tree) {
int selectedOption = 1;
    int status = 1;

    while(status == 1) {
		system("cls"); // Membersihkan layar
        // Menampilkan menu
        gotoxy(30, 2);
        warnateks(11);
        printf("================= Member =================\n");

        setOptionColor(1, selectedOption);
        gotoxy(30, 4);
        printf("[%c] Print All Family Members\n", (selectedOption == 1) ? 'X' : ' ');

        setOptionColor(2, selectedOption);
        gotoxy(30, 5);
        printf("[%c] Print Royal Family Members\n", (selectedOption == 2) ? 'X' : ' ');

        setOptionColor(3, selectedOption);
        gotoxy(30, 6);
        printf("[%c] Kembali\n", (selectedOption == 3) ? 'X' : ' ');

        warnateks(11); // Reset to default color
        int keyboard = getch();

        switch (keyboard) {
            case 72: // Panah atas
                selectedOption = (selectedOption > 1) ? selectedOption - 1 : 3;
                Beep(800, 100);
                break;
            case 80: // Panah bawah
                selectedOption = (selectedOption < 3) ? selectedOption + 1 : 1;
                Beep(800, 100);
                break;
            case 13: // Tombol Enter
                Beep(800, 300);
                switch (selectedOption) {
                    case 1:
                        displayTree(tree);
                            waitForEnter();
                        break;
                    case 2:
                        displayTreeFromLeader(tree);
                            waitForEnter();
                        break;
                    case 3:
                        return;
                        break;
                }
                break;
        }
    }
    waitForEnter();
}

/**** Fungsi untuk mencetak node dengan indentasi ****/
void printNode(NBTree *node, int level, bool isLastChild)
/* IS : node adalah node dari tree, level adalah level node tersebut, isLastChild menunjukkan apakah node ini anak terakhir */
/* FS : menampilkan node dengan indentasi sesuai level */
{
    if (node == NULL) return;
    int i;
    // Print indentation
    for (i = 0; i < level; i++) {
        printf("    ");
    }

    // Print connector and node
    if (level > 0) {
        if (isLastChild) {
            printf("+--");
        } else {
            printf("+--");
        }
    }
	if (node->IsRoyalFamilyMember) {
        warnateks(LIGHT_BLUE); // Merah
    } else {
    	warnateks(WHITE);

	}
    // Print node name and partner name if present
    if (strlen(node->PartnerName) > 0) {
        printf("[%s] & [%s]", node->Name, node->PartnerName);
    } else {
        printf("[%s]", node->Name);
    }

    if (node->IsLeader){
        printf( " (Pemimpin saat ini)");
    }

    printf("\n");
}

/** Mendapatkan level node dengan isLeader true **/
int getLeaderLevel(NBTree *node, int level)
/* IS : node adalah node dari tree, level adalah level node tersebut */
/* FS : mengembalikan level dari node yang isLeader-nya true, atau -1 jika tidak ditemukan */
{
    if (node == NULL) return -1;

    if (node->IsLeader) return level;

    int result = getLeaderLevel(node->FirstSon, level + 1);
    if (result != -1) return result;

    return getLeaderLevel(node->NextBrother, level);
}

/** Cetak pohon dari level tertentu **/
void printTreeAtLevel(NBTree *node, int currentLevel, int targetLevel, bool isLastChild)
/* IS : node adalah node dari tree, currentLevel adalah level node tersebut, targetLevel adalah level dari mana mulai mencetak */
/* FS : menampilkan tree dari targetLevel dan ke bawah */
{
    if (node == NULL) return;
    if (currentLevel >= targetLevel && node->IsRoyalFamilyMember && node->IsAlive) {
        printNode(node, currentLevel - targetLevel, isLastChild);
    }

    if (node->FirstSon != NULL) {
        printTreeAtLevel(node->FirstSon, currentLevel + 1, targetLevel, node->NextBrother == NULL);
    }

    if (node->NextBrother != NULL) {
        printTreeAtLevel(node->NextBrother, currentLevel, targetLevel, false);
    }
}

/** Menampilkan pohon mulai dari level isLeader true **/
void displayTreeFromLeader(DataTree *tree)
/* IS : tree sudah terbentuk */
/* FS : menampilkan tree mulai dari level node yang isLeader-nya true */
{
    if (tree == NULL || tree->Root == NULL) {
        printf("Tree is empty.\n");
    }

    int leaderLevel = getLeaderLevel(tree->Root, 0);
    if (leaderLevel == -1) {
        printf("No leader found in the tree.\n");
    } else {
        printTreeAtLevel(tree->Root, 0, leaderLevel, true);
    }
}

/**** Cetak pohon ****/
void printTree(NBTree *node, int level, bool isLastChild)
/* IS : node adalah node dari tree, level adalah level node tersebut, isLastChild menunjukkan apakah node ini anak terakhir */
/* FS : menampilkan tree dengan indentasi sesuai level */
{
    if (node == NULL) return;

    printNode(node, level, isLastChild);

    if (node->FirstSon != NULL) {
        printTree(node->FirstSon, level + 1, node->NextBrother == NULL);
    }

    if (node->NextBrother != NULL) {
        printTree(node->NextBrother, level, false);
    }
}

/**** Menampilkan tree ****/
void displayTree(DataTree *tree)
/* IS : tree sudah terbentuk */
/* FS : menampilkan tree */
{
    clearscreen();
    if (tree == NULL || tree->Root == NULL) return;
    printTree(tree->Root, 0, true);
}

void encyclopedia(DataTree *tree) {
    clearscreen();
    printf("========== MENU INSERT ENSIKLOPEDIA ==========");
    printf("Daftar anggota keluarga kerajaan :\n\n");
	displayTree(tree);

	printf("\nMasukkan nama anggota keluarga untuk menambahkan deskripsi naratif: ");
	char name[100];
	fgets(name, sizeof(name), stdin);
	// Menghilangkan karakter newline yang dihasilkan oleh fgets
	name[strcspn(name, "\n")] = '\0';

    NBTree *selectedNode = findNode(tree->Root, name);
    if (selectedNode != NULL && selectedNode->IsRoyalFamilyMember) {
        printf("Masukkan deskripsi naratif untuk %s:\n", name);
        char description[1000];
        scanf(" %[^\n]", description);

        // Simpan deskripsi naratif ke dalam file ensiklopedia.txt
        FILE *encyclopediaFile = fopen("../db/ensiklopedia.txt", "a");
        if (encyclopediaFile == NULL) {
            printf("Gagal membuka file ensiklopedia.txt\n");
            return;
        }

        fprintf(encyclopediaFile, "%s: %s\n", name, description);
        fclose(encyclopediaFile);

        printf("Deskripsi naratif untuk %s berhasil disimpan.\n", name);
    } else {
        printf("Anggota keluarga dengan nama %s tidak ditemukan atau tidak aktif.\n", name);
    }

    waitForEnter();
}

int calculateAge(int yearOfBirth) {
    // Menghitung umur
    return currentYear - yearOfBirth;
}


void replaceString(char *str, const char *old, const char *new) {
    char *ptr = strstr(str, old);
    if (ptr != NULL) {
        size_t old_len = strlen(old);
        size_t new_len = strlen(new);
        memmove(ptr + new_len, ptr + old_len, strlen(ptr + old_len) + 1);
        memcpy(ptr, new, new_len);
    }
}
void marriageAscii(const char *name1, const char *name2, Gender gender1, Gender gender2) {
    // Buka file untuk dibaca
    FILE *file = fopen("../db/marriage_ascii.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk dibaca.\n");
        return;
    }

    // Buat placeholder dengan panjang yang cukup
    char placeholder1[MAX_LINE_LENGTH];
    char placeholder2[MAX_LINE_LENGTH];

    if (gender1 == Female) {
        sprintf(placeholder1, "||  {   %s  }   ||       &       ||   {   %s   }  ||\n", name1, name2);
    } else {
        sprintf(placeholder1, "||  {   %s  }   ||       &       ||   {   %s   }  ||\n", name2, name1);
    }

    // Baca isi file baris per baris
    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        // Hitung jumlah baris
        line_count++;

        // Cetak baris yang sudah diubah dengan warna yang berbeda untuk setiap bagian
        if (line_count <= 5) {
            warnateks(DARK_BLUE); // Warna putih untuk bagian atas
        } else if (line_count > 5 && line_count <= 10) {
            warnateks(TURQUOISE); // Warna biru untuk bagian tengah
        } else {
            warnateks(LIGHT_BLUE); // Warna merah untuk bagian bawah
        }

        // Ganti bagian yang ingin diubah dengan input dinamis
        replaceString(line, "||  {   STEVE   }   ||      &        ||   {   JENNY   }  ||", placeholder1);

        // Cetak baris yang sudah diubah
        printf("%s", line);
    }
	warnateks(WHITE);
    // Tutup file
    fclose(file);
    waitForEnter();
}


void printFromFile(const char* location){
	FILE *read;
	char c;

	read=fopen(location, "rt");
	while((c=fgetc(read))!=EOF){
		printf("%c", c);
	}

	fclose(read);
}

void printFromFileSplash(const char* location) {
    FILE *file = fopen(location, "rt");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    // Baca isi file baris per baris
    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        // Hitung jumlah baris
        line_count++;

        // Cetak baris yang sudah diubah dengan warna yang berbeda untuk setiap bagian
        if (line_count <= 8) {
            warnateks(DARK_BLUE); // Warna biru untuk bagian atas
        } else if (line_count > 8 && line_count <= 20) {
            warnateks(TURQUOISE); // Warna turquoise untuk bagian tengah
        } else {
            warnateks(LIGHT_BLUE); // Warna merah untuk bagian bawah
        }

        // Cetak baris yang sudah diubah
        printf("%s", line);
        warnateks(LIGHT_BLUE); // Reset warna setelah setiap baris
    }

    // Tutup file
    fclose(file);
}
