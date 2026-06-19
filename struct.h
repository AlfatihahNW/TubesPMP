#ifndef STRUCT_H
#define STRUCT_H

#if defined(ARDUINO) && defined(__AVR__)
#include <stdio.h>
#include <avr/pgmspace.h>
#undef printf
#define printf(fmt, ...) printf_P(PSTR(fmt), ##__VA_ARGS__)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// Definisi struktur Barang
struct Barang {
    char id[8];
    char nama[16];
    int8_t kategori; 
    int16_t stok;
    char lokasi[8];
    int8_t status;
    char pemilik[8];
    char pic[8];
    struct Barang* next;
};
typedef struct Barang Barang;

// Deklarasi variabel global database
extern Barang* database; 

void hapusBarang(char* id);
void tambahBarang();
void cari(char* id);
void updateStok(char* id, int stok_baru);
void updateStatus(char* id, char* status_baru);
void tampilkanSemua();
void tampilkanRingkasan();

void bersihkan_layar();
void bacaInput(char* buffer, int max_len);
void menu();
void jalankan_sistem();

#ifdef ARDUINO
void arduino_read_string(char* buffer, int max_len);
#endif

#ifdef __cplusplus
}
#endif

#endif
