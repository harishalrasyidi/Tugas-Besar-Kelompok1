# Tugas-Besar-Kelompok1
Tugas besar SDA praktek semester 2

<h1 align="center" id="title">Kerajaan Belanda</h1>

<p align="center"><img src="https://socialify.git.ci/harishalrasyidi/Tugas-Besar-Kelompok1/image?description=1&forks=1&issues=1&language=1&name=1&owner=1&stargazers=1&theme=Dark"></p>

<p id="description">Program ini merupakan sebuah sistem informasi berbasis CLI untuk memperlihatkan keanggotaan keluarga kerajaan Belanda. Program ini diadaptasi dari aturan-aturan yang berlaku di kerajaan tersebut sehingga mampu menyajikan situasi yang riil yang sesuai dengan kenyataan disana.</p>

<p align="center"><img src="https://img.shields.io/github/commit-activity/t/harishalrasyidi/Tugas-Besar-Kelompok1" alt="shields"><img src="https://img.shields.io/github/languages/top/harishalrasyidi/Tugas-Besar-Kelompok1" alt="shields"><img src="https://img.shields.io/github/downloads/harishalrasyidi/Tugas-Besar-Kelompok1/total" alt="shields"><img src="https://img.shields.io/github/license/harishalrasyidi/Tugas-Besar-Kelompok1" alt="shields"><img src="https://img.shields.io/github/languages/code-size/harishalrasyidi/Tugas-Besar-Kelompok1" alt="shields"><img src="https://img.shields.io/github/directory-file-count/harishalrasyidi/Tugas-Besar-Kelompok1" alt="shields"></p>

  
<h2>🧐 Features</h2>

Berikut fitur yang ada pada program ini:

*   Insert Family Member
*   Insert Partner
*   Insert Ensiklopedia
*   Lihat Anggota Keluarga Kerajaan
*   Hitung Jumlah Anak
*   Hitung Jumlah Generasi
*   Bunuh Anggota Keluarga Kerajaan
*   Pemimpin Turun Tahta
*   Pindah ke Tahun di Masa Depan
*   Reset Progress
*   Ensiklopedia

<h2> Data Structure</h2>


Node : variabel bertipe komposit dengan sub variabel sebagai berikut :
	`Name` : variabel tunggal bertipe array of char
	`YearOfBirth` : variabel tunggal bertipe integer
	`Gender` : enum(‘Man’,’Woman’)
	`IsLeader` : variabel tunggal bertipe booelan
	`IsRoyalFamilyMember` : variabel tunggal bertipe boolea
	`IsMarriageApproved` : variabel tunggal bertipe boolean
	`PartnerName` : variabel tunggal bertipe array of char
	`ParentName` : variabel tunggal bertipe array of char
	`IsAlive` : variabel tunggal bertipe boolean
	`FS` : variabel tunggal bertipe pointer ke Node
	`NB` : variabel tunggal bertipe pointer ke Node
	`PR` : variabel tunggal bertipe pointer ke Node

  
<h2>💻 Built with</h2>

Technologies used in the project:

*   Dev-CPP - CLion - Codeblocks
*   C/C++ Language
