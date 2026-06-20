# TubesPMP
Tubes PMP membuat sistem inventory barang berbasis arduino

Berikut adalah link-link yang diperlukan dalam rangka memenuhi persyaratan Tugas Besar ini:
1. Link Slide PPT: https://www.canva.com/design/DAHNADv14HI/96hAwjJV0hNsqm-VpbtqIQ/edit
2. Link youtube: https://www.youtube.com/watch?v=y6t9wuDihVY&feature=youtu.be

## Persyaratan Library

Sistem ini hanya membutuhkan satu library tambahan untuk python guna komunikasi serial dengan Arduino.

* **Pustaka Python:** `pyserial`
* **Fungsi:** Menghubungkan script Python dengan Arduino melalui port USB.
* **Cara Instalasi:** Buka Terminal atau Command Prompt, lalu jalankan perintah berikut:
  ```bash
  pip install pyserial

## Struktur dan Guna File
* tubes/tubes.ino : File utama (entry point) yang akan di-upload langsung ke board Arduino.
* tubes/struct.h : File header C yang berisi deklarasi struktur data (struct Barang) dan prototipe fungsi CRUD.
* tubes/struct.c : File inti yang memuat seluruh logika pemrograman C untuk manipulasi Linked List (Tambah, Hapus, Update, Cari).
* tubes/main.c : File pengujian (unit test) untuk menjalankan dan mengetes kode C secara lokal di PC tanpa perlu Arduino.
* database.csv : File database awal berformat CSV yang berisi daftar komponen laboratorium.
* import_serial-2.py : Script Python pengontrol yang berfungsi untuk membaca data dari CSV, mengirimnya ke Arduino via Serial (UART), dan menyediakan antarmuka terminal interaktif bagi pengguna.
* README.md : Dokumentasi panduan sistem ini.
* Laporan_Tubes_PMP.md : Dokumen laporan resmi Tugas Besar.
