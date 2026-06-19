#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

Barang* database = NULL; 
int jumlah_node = 0;

int getKategori(char* str) {
#ifdef ARDUINO
    if(strcmp_P(str, PSTR("Mikro")) == 0 || strcmp_P(str, PSTR("1")) == 0) return 0;
    if(strcmp_P(str, PSTR("Sensor")) == 0 || strcmp_P(str, PSTR("2")) == 0) return 1;
    if(strcmp_P(str, PSTR("Motor")) == 0 || strcmp_P(str, PSTR("3")) == 0) return 2;
    if(strcmp_P(str, PSTR("Display")) == 0 || strcmp_P(str, PSTR("4")) == 0) return 3;
    if(strcmp_P(str, PSTR("Kabel")) == 0 || strcmp_P(str, PSTR("5")) == 0) return 4;
    if(strcmp_P(str, PSTR("Komputer")) == 0 || strcmp_P(str, PSTR("6")) == 0) return 5;
    if(strcmp_P(str, PSTR("Pendukung")) == 0 || strcmp_P(str, PSTR("7")) == 0) return 6;
    if(strcmp_P(str, PSTR("Modul")) == 0 || strcmp_P(str, PSTR("8")) == 0) return 7;
    return 8;
#else
    if(strcmp(str, "Mikro") == 0 || strcmp(str, "1") == 0) return 0;
    if(strcmp(str, "Sensor") == 0 || strcmp(str, "2") == 0) return 1;
    if(strcmp(str, "Motor") == 0 || strcmp(str, "3") == 0) return 2;
    if(strcmp(str, "Display") == 0 || strcmp(str, "4") == 0) return 3;
    if(strcmp(str, "Kabel") == 0 || strcmp(str, "5") == 0) return 4;
    if(strcmp(str, "Komputer") == 0 || strcmp(str, "6") == 0) return 5;
    if(strcmp(str, "Pendukung") == 0 || strcmp(str, "7") == 0) return 6;
    if(strcmp(str, "Modul") == 0 || strcmp(str, "8") == 0) return 7;
    return 8;
#endif
}

int getStatus(char* str) {
#ifdef ARDUINO
    if(strcmp_P(str, PSTR("Tersedia")) == 0 || strcmp_P(str, PSTR("1")) == 0) return 0;
    if(strcmp_P(str, PSTR("Dipinjam")) == 0 || strcmp_P(str, PSTR("2")) == 0) return 1;
    if(strcmp_P(str, PSTR("Rusak")) == 0 || strcmp_P(str, PSTR("3")) == 0) return 2;
    return 3;
#else
    if(strcmp(str, "Tersedia") == 0 || strcmp(str, "1") == 0) return 0;
    if(strcmp(str, "Dipinjam") == 0 || strcmp(str, "2") == 0) return 1;
    if(strcmp(str, "Rusak") == 0 || strcmp(str, "3") == 0) return 2;
    return 3;
#endif
}

void printKategori(int k) {
    if(k==0) printf("Mikro");
    else if(k==1) printf("Sensor");
    else if(k==2) printf("Motor");
    else if(k==3) printf("Display");
    else if(k==4) printf("Kabel");
    else if(k==5) printf("Komputer");
    else if(k==6) printf("Pendukung");
    else if(k==7) printf("Modul");
    else printf("Lainnya");
}

void printStatus(int s) {
    if(s==0) printf("Tersedia");
    else if(s==1) printf("Dipinjam");
    else if(s==2) printf("Rusak");
    else printf("Habis");
}

void tambahBarang() {
    if(jumlah_node >= 25) {
        printf("Kapasitas memori hampir habis!\n");
        char dummy[20];
        printf("ID (maks 7 karakter):\n"); bacaInput(dummy, 8);
        printf("Nama (maks 15 karakter):\n"); bacaInput(dummy, 16);
        printf("Kategori (1=Mikro, 2=Sensor, 3=Motor, 4=Display, 5=Kabel, 6=Komputer, 7=Pendukung, 8=Modul, 9=Lainnya):\n"); bacaInput(dummy, 20);
        printf("Stok (angka bulat):\n"); bacaInput(dummy, 10);
        printf("Lokasi (maks 7 karakter):\n"); bacaInput(dummy, 8);
        printf("Status (1=Tersedia, 2=Dipinjam, 3=Rusak):\n"); bacaInput(dummy, 20);
        printf("Pemilik (maks 7 karakter):\n"); bacaInput(dummy, 8);
        printf("PIC (maks 7 karakter):\n"); bacaInput(dummy, 8);
        return;
    }

    char temp_id[8];
    printf("ID (maks 7 karakter):\n");
    bacaInput(temp_id, 8);
    
    Barang* cek = database;
    int duplicate = 0;
    while(cek != NULL) {
        if(strcmp(cek->id, temp_id) == 0) {
            duplicate = 1;
            break;
        }
        cek = cek->next;
    }
    
    if(duplicate) {
        printf("ID duplikat!\n");
        char dummy[20];
        printf("Nama (maks 15 karakter):\n"); bacaInput(dummy, 16);
        printf("Kategori (1=Mikro, 2=Sensor, 3=Motor, 4=Display, 5=Kabel, 6=Komputer, 7=Pendukung, 8=Modul, 9=Lainnya):\n"); bacaInput(dummy, 20);
        printf("Stok (angka bulat):\n"); bacaInput(dummy, 10);
        printf("Lokasi (maks 7 karakter):\n"); bacaInput(dummy, 8);
        printf("Status (1=Tersedia, 2=Dipinjam, 3=Rusak):\n"); bacaInput(dummy, 20);
        printf("Pemilik (maks 7 karakter):\n"); bacaInput(dummy, 8);
        printf("PIC (maks 7 karakter):\n"); bacaInput(dummy, 8);
        return;
    }
    
    Barang* node = (Barang*)malloc(sizeof(Barang));
    if (node == NULL) {
        printf("Kapasitas memori hampir habis!\n");
        char dummy[20];
        printf("Nama (maks 15 karakter):\n"); bacaInput(dummy, 16);
        printf("Kategori (1=Mikro, 2=Sensor, 3=Motor, 4=Display, 5=Kabel, 6=Komputer, 7=Pendukung, 8=Modul, 9=Lainnya):\n"); bacaInput(dummy, 20);
        printf("Stok (angka bulat):\n"); bacaInput(dummy, 10);
        printf("Lokasi (maks 7 karakter):\n"); bacaInput(dummy, 8);
        printf("Status (1=Tersedia, 2=Dipinjam, 3=Rusak):\n"); bacaInput(dummy, 20);
        printf("Pemilik (maks 7 karakter):\n"); bacaInput(dummy, 8);
        printf("PIC (maks 7 karakter):\n"); bacaInput(dummy, 8);
        return;
    }
    
    char temp_kategori[20];
    char temp_status[20];
    char temp_stok[10];
    
    strcpy(node->id, temp_id);
    printf("Nama (maks 15 karakter):\n");
    bacaInput(node->nama, 16);
    printf("Kategori (1=Mikro, 2=Sensor, 3=Motor, 4=Display, 5=Kabel, 6=Komputer, 7=Pendukung, 8=Modul, 9=Lainnya):\n");
    bacaInput(temp_kategori, 20);
    node->kategori = getKategori(temp_kategori);
    printf("Stok (angka bulat):\n");
    bacaInput(temp_stok, 10);
    node->stok = atoi(temp_stok);
    printf("Lokasi (maks 7 karakter):\n");
    bacaInput(node->lokasi, 8);
    printf("Status (1=Tersedia, 2=Dipinjam, 3=Rusak):\n");
    bacaInput(temp_status, 20);
    node->status = getStatus(temp_status);
    printf("Pemilik (maks 7 karakter):\n");
    bacaInput(node->pemilik, 8);
    printf("PIC (maks 7 karakter):\n");
    bacaInput(node->pic, 8);
    
    node->next = NULL;
    if(database == NULL) {
        database = node;
    } else {
        Barang* temp = database;
        while(temp->next != NULL) temp = temp->next;
        temp->next = node;
    }
    jumlah_node++;
    printf("Berhasil menambahkan data.\n");
}

void hapusBarang(char* id) {
    if(database == NULL) {
        printf("Data kosong.\n");
        return;
    }
    
    Barang* temp = database;
    Barang* prev = NULL;
    
    if(strcmp(temp->id, id) == 0) {
        database = temp->next;
        free(temp);
        jumlah_node--;
        printf("Data berhasil dihapus.\n");
        return;
    }
    
    while(temp != NULL && strcmp(temp->id, id) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if(temp == NULL) {
        printf("Data tidak ditemukan.\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    jumlah_node--;
    printf("Data berhasil dihapus.\n");
}

void cari(char* id) {
    if(database == NULL) {
        printf("Data kosong.\n");
        return;
    }
    Barang* temp = database;
    while(temp != NULL) {
        if(strcmp(temp->id, id) == 0) {
            printf("Data ditemukan:\n");
            printf("ID: %s, Nama: %s, Kategori: ", temp->id, temp->nama);
            printKategori(temp->kategori);
            printf(", Stok: %d\n", temp->stok);
            return;
        }
        temp = temp->next;
    }
    printf("Data tidak ditemukan.\n");
}

void updateStok(char* id, int stok_baru) {
    if(database == NULL) {
        printf("Data kosong.\n");
        return;
    }
    if(stok_baru < 0) {
        printf("Stok tidak mencukupi.\n");
        return;
    }
    Barang* temp = database;
    while(temp != NULL) {
        if(strcmp(temp->id, id) == 0) {
            temp->stok = stok_baru;
            if(stok_baru == 0) {
                temp->status = 3; 
            }
            printf("Stok berhasil diperbarui.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Data tidak ditemukan.\n");
}

void updateStatus(char* id, char* status_baru) {
    if(database == NULL) {
        printf("Data kosong.\n");
        return;
    }
    Barang* temp = database;
    while(temp != NULL) {
        if(strcmp(temp->id, id) == 0) {
            temp->status = getStatus(status_baru);
            printf("Status berhasil diperbarui.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Data tidak ditemukan.\n");
}

void tampilkanSemua() {
    if(database == NULL) {
        printf("Data kosong.\n");
        return;
    }
    Barang* temp = database;
    while(temp != NULL) {
        printf("- ID: %s, Nama: %s, Kategori: ", temp->id, temp->nama);
        printKategori(temp->kategori);
        printf(", Stok: %d, Lokasi: %s, Status: ", temp->stok, temp->lokasi);
        printStatus(temp->status);
        printf(", Pemilik: %s, PIC: %s\n", temp->pemilik, temp->pic);
        temp = temp->next;
    }
}

void tampilkanRingkasan() {
    if(database == NULL) {
        printf("Data kosong.\n");
        return;
    }
    int total = 0;
    int stok = 0;
    Barang* temp = database;
    while(temp != NULL) {
        total++;
        stok = stok + temp->stok;
        temp = temp->next;
    }
    printf("Total Jenis: %d\n", total);
    printf("Total Stok: %d\n", stok);
}

void bersihkan_layar() {
    for(int i=0; i<15; i++) printf("\n");
}

void bacaInput(char* buffer, int max_len) {
#ifdef ARDUINO
    arduino_read_string(buffer, max_len);
#else
    if (fgets(buffer, max_len, stdin) != NULL) {
        int len = strlen(buffer);
        if(len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
            len--;
        }
        if(len > 0 && buffer[len-1] == '\r') {
            buffer[len-1] = '\0';
        }
    }
#endif
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Tambah Data\n");
    printf("2. Hapus Data\n");
    printf("3. Cari Data\n");
    printf("4. Perbarui Stok\n");
    printf("5. Perbarui Status\n");
    printf("6. Tampilkan Semua Data\n");
    printf("7. Ringkasan Inventaris\n");
    printf("8. Keluar\n");
    printf("Pilihan Anda: ");
}

void jalankan_sistem() {
    int jalan = 1;
    char pilihan[10];
    
    while(jalan == 1) {
        menu();
        bacaInput(pilihan, 10);
        
        int pilih = 0;
        // Cari angka pertama buat jaga-jaga kalau user copas "Pilihan Anda: 7"
        for(int i = 0; i < strlen(pilihan); i++) {
            if(pilihan[i] >= '1' && pilihan[i] <= '9') {
                pilih = pilihan[i] - '0';
                break;
            }
        }
        
        if(pilih == 1) {
            tambahBarang();
        }
        else if(pilih == 2) {
            char id[8];
            printf("ID yang akan dihapus (maks 7 karakter):\n");
            bacaInput(id, 8);
            hapusBarang(id);
        }
        else if(pilih == 3) {
            char id[8];
            printf("ID yang dicari (maks 7 karakter):\n");
            bacaInput(id, 8);
            cari(id);
        }
        else if(pilih == 4) {
            char id[8];
            char stok_str[10];
            printf("ID Barang (maks 7 karakter):\n");
            bacaInput(id, 8);
            printf("Stok baru (angka bulat):\n");
            bacaInput(stok_str, 10);
            updateStok(id, atoi(stok_str));
        }
        else if(pilih == 5) {
            char id[8];
            char stat[20];
            printf("ID Barang (maks 7 karakter):\n");
            bacaInput(id, 8);
            printf("Status baru (1=Tersedia, 2=Dipinjam, 3=Rusak):\n");
            bacaInput(stat, 20);
            updateStatus(id, stat);
        }
        else if(pilih == 6) {
            tampilkanSemua();
        }
        else if(pilih == 7) {
            tampilkanRingkasan();
        }
        else if(pilih == 8) {
            jalan = 0;
            printf("Keluar dari program. Terima kasih.\n");
        }
        else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
}
