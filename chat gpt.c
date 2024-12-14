#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int i;
// Definisi struktur untuk produk
typedef struct {
    long long int idProduk;
    char namaProduk[100];
    char kategoriProduk[100];
    long long int hargaProduk;
    int stokProduk;
} Produk;

// Prototipe fungsi
void tampilkanMenu();
void tambahProduk();
void tampilkanProduk();
void ubahProduk();
void hapusProduk();
void tulisDataKeFile(FILE* file, Produk produk);

int main() {
    enum {
        TAMBAH = 1,
        TAMPIL,
        UBAH,
        HAPUS,
        KELUAR,
    };

    int pilihan;
    int kondisi = 1;

    do {
        tampilkanMenu();
        scanf("%d", &pilihan);
        getchar(); // Buang newline dari input

        switch (pilihan) {
            case TAMBAH:
                tambahProduk();
                break;
            case TAMPIL:
                tampilkanProduk();
                break;
            case UBAH:
                ubahProduk();
                break;
            case HAPUS:
                hapusProduk();
                break;
            case KELUAR:
                kondisi = 0;
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
                break;
        }
    } while (kondisi > 0);

    return 0;
}

// Implementasi fungsi void tampilkanMenu()
void tampilkanMenu() {
    printf("Pilih Aksi :\n");
    printf("1. Tambahkan Data\n");
    printf("2. Tampilkan Data\n");
    printf("3. Update Data\n");
    printf("4. Hapus Data\n");
    printf("5. Keluar\n");
    printf("Masukkan Pilihan: ");
}

void tambahProduk() {
    FILE* file = fopen("data_produk.txt", "a");
    if (!file) {
        printf("Error: Gagal membuka file untuk menulis.\n");
        return;
    }

    Produk produk;

    // Input data produk
    printf("Masukkan ID Produk: ");
    scanf("%lld", &produk.idProduk);
    getchar();

    printf("Masukkan Nama Produk: ");
    fgets(produk.namaProduk, sizeof(produk.namaProduk), stdin);
    produk.namaProduk[strcspn(produk.namaProduk, "\n")] = 0; // Hapus newline

    printf("Masukkan Kategori Produk: ");
    fgets(produk.kategoriProduk, sizeof(produk.kategoriProduk), stdin);
    produk.kategoriProduk[strcspn(produk.kategoriProduk, "\n")] = 0;

    printf("Masukkan Harga Produk: ");
    scanf("%lld", &produk.hargaProduk);

    printf("Masukkan Stok Produk: ");
    scanf("%d", &produk.stokProduk);

    // Tulis ke file menggunakan fungsi tulisDataKeFile
    tulisDataKeFile(file, produk);

    printf("\nProduk berhasil ditambahkan.\n");
    fclose(file);
}

void tampilkanProduk() {
    FILE* file = fopen("data_produk.txt", "r");
    if (!file) {
        printf("Error: File tidak ditemukan.\n");
        return;
    }

    char buffer[300];
    printf("Data Produk:\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

void ubahProduk() {
    char buffer[300], idProdukCari[20];
    int ditemukan = 0;

    printf("Masukkan ID Produk yang ingin diubah: ");
    fgets(idProdukCari, sizeof(idProdukCari), stdin);
    idProdukCari[strcspn(idProdukCari, "\n")] = 0; // Hapus newline

    FILE* file = fopen("data_produk.txt", "r");
    if (!file) {
        printf("Error: File tidak ditemukan.\n");
        return;
    }

    FILE* tempFile = fopen("data_produk_sementara.txt", "w");
    if (!tempFile) {
        printf("Error: Gagal membuat file sementara.\n");
        fclose(file);
        return;
    }

    Produk produkBaru;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, idProdukCari) && strstr(buffer, "ID :")) {
            ditemukan = 1;

            // Input data baru
            printf("Data ditemukan. Masukkan data baru.\n");
            printf("Nama Produk Baru: ");
            fgets(produkBaru.namaProduk, sizeof(produkBaru.namaProduk), stdin);
            produkBaru.namaProduk[strcspn(produkBaru.namaProduk, "\n")] = 0;

            printf("Kategori Produk Baru: ");
            fgets(produkBaru.kategoriProduk, sizeof(produkBaru.kategoriProduk), stdin);
            produkBaru.kategoriProduk[strcspn(produkBaru.kategoriProduk, "\n")] = 0;

            printf("Harga Produk Baru: ");
            scanf("%lld", &produkBaru.hargaProduk);

            printf("Stok Produk Baru: ");
            scanf("%d", &produkBaru.stokProduk);
            getchar();

            produkBaru.idProduk = atoll(idProdukCari); // ID tetap

            // Tulis data baru ke file sementara
            tulisDataKeFile(tempFile, produkBaru);

            // Lewati data lama
            for (i = 0; i < 5; i++) {
                fgets(buffer, sizeof(buffer), file);
            }
        } else {
            fputs(buffer, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        remove("data_produk.txt");
        rename("data_produk_sementara.txt", "data_produk.txt");
        printf("Data berhasil diubah.\n");
    } else {
        remove("data_produk_sementara.txt");
        printf("Data tidak ditemukan.\n");
    }
}

void hapusProduk() {
    char buffer[300], idProdukCari[20];
    int ditemukan = 0;

    printf("Masukkan ID Produk yang ingin dihapus: ");
    fgets(idProdukCari, sizeof(idProdukCari), stdin);
    idProdukCari[strcspn(idProdukCari, "\n")] = 0;

    FILE* file = fopen("data_produk.txt", "r");
    if (!file) {
        printf("Error: File tidak ditemukan.\n");
        return;
    }

    FILE* tempFile = fopen("data_produk_sementara.txt", "w");
    if (!tempFile) {
        printf("Error: Gagal membuat file sementara.\n");
        fclose(file);
        return;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, idProdukCari) && strstr(buffer, "ID :")) {
            ditemukan = 1;
            // Lewati data lama
            for (i = 0; i < 5; i++) {
                fgets(buffer, sizeof(buffer), file);
            }
        } else {
            fputs(buffer, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan = 1) {
        remove("data_produk.txt");
        rename("data_produk_sementara.txt", "data_produk.txt");
        printf("Data berhasil dihapus.\n");
    } else {
        remove("data_produk_sementara.txt");
        printf("Data tidak ditemukan.\n");
    }
}

void tulisDataKeFile(FILE* file, Produk produk) {
    fprintf(file, "ID : %lld\n", produk.idProduk);
    fprintf(file, "Nama : %s\n", produk.namaProduk);
    fprintf(file, "Kategori : %s\n", produk.kategoriProduk);
    fprintf(file, "Harga : %lld\n", produk.hargaProduk);
    fprintf(file, "Stok : %d\n\n", produk.stokProduk);
}
