import serial
import time

#untuk disesuaikan
port = "/dev/ttyACM0" 




try:
    ser = serial.Serial(port, 9600)
    time.sleep(3) 
except:
    print("koneksi gagal")
    exit()

try:
    f = open("database.csv", "r")
    baris_semua = f.readlines()
    f.close()
except:
    print("file tidak ditemukan!")
    exit()

indeks = 1

for baris in baris_semua:
    b = baris.replace('\n', '').replace('\r', '')
    
    if b == "" or b[0] == '#':
        pass 
    else:
        pecah = b.split(";")
        
        id_brg = pecah[0]
        nama = pecah[1]
        kat = pecah[2]
        stok = pecah[3]
        lok = pecah[4]
        stat = pecah[5]
        milik = pecah[6]
        pic = pecah[7]
        
        print(f"Mengirim barang ke-{indeks}: {nama}...")
        

        ser.write("1\n".encode())
        time.sleep(0.5)
        

        ser.write((id_brg + "\n").encode())
        time.sleep(0.2)
        ser.write((nama + "\n").encode())
        time.sleep(0.2)
        ser.write((kat + "\n").encode())
        time.sleep(0.2)
        ser.write((stok + "\n").encode())
        time.sleep(0.2)
        ser.write((lok + "\n").encode())
        time.sleep(0.2)
        ser.write((stat + "\n").encode())
        time.sleep(0.2)
        ser.write((milik + "\n").encode())
        time.sleep(0.2)
        ser.write((pic + "\n").encode())
        time.sleep(0.2)
        
        time.sleep(1) 
        baca = ""
        while ser.in_waiting > 0:
            baca = baca + ser.read().decode('utf-8', errors='ignore')
        
        if "Berhasil menambahkan data." in baca:
            print("Pengiriman sukses.")
        elif "Kapasitas memori hampir habis!" in baca:
            print("Peringatan: Memori Arduino penuh. Menghentikan pengiriman otomatis.")
            break
        else:
            print("Pengiriman gagal.")
            
        indeks += 1

print("Proses isi database selesai.")

print("\nTampilan data:")
ser.read(ser.in_waiting) 
ser.write("6\n".encode()) 
time.sleep(2) 
baca = ""
while ser.in_waiting > 0:
    baca += ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
    time.sleep(0.1)

if baca:
    print(baca, end="")

print("\nmode uart transfer, bisa kirim perintah langsung ke arduino \n ")


try:
    while True:
        
        perintah = input("").strip()
        
        if perintah != "":
            ser.read(ser.in_waiting) 
            
            ser.write((perintah + "\n").encode())
            
            time.sleep(1)
            
            baca = ""
            while ser.in_waiting > 0:
                baca += ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
                time.sleep(0.1)
                
            if baca:
                print(baca, end="")
except KeyboardInterrupt:
    print("\nMenutup program. Terima kasih.")
    
ser.close()
