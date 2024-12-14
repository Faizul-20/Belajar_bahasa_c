#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MaxData 100
int i = 0;
typedef enum{
	Insert = 1,
	Show,
	Update,
	Erase,
	Exit,
}menu;

void tampilan();
void Insert_File();
void Show_File();
void Update_File();
void Erase_product();
void Data_writer();
int search_engine(); 
typedef struct{
	int Product_ID;
	char Product_Name[100];
	char Product_Categories[100];
	float harga;
	int stok;
}Product_data;
Product_data database[MaxData]; 
int record_count = 0;

int main(){
	menu choice;
	do{
	tampilan();
	int choice2;
	printf("Masukan Pilihan : ");
	scanf("%d",&choice2);
	choice = (menu)choice2;
	
	switch(choice){
	case Insert:
		Insert_File();
		break;
	case Show:
		Show_File();	
		break;
	case Update:
		Update_File();
		break;
	case Erase:
		Erase_product();
		break;
	case Exit:
		printf("Data Bisa Dilihat di file Produk_Toko.txt\n");
		break;
	default:
		break;
	}
	}while(choice < 5 || choice != 5 );
		
	return 0;
}

void tampilan(){
	printf("Pilih Aksi :\n");
	printf("Menu :\n");
	printf("1. Tambahkan Produk Baru\n");
	printf("2. Tampilkan Produk Baru\n");
	printf("3. Update Informasi Produk Baru\n");
	printf("4. Hapus Produk\n");
	printf("5. Keluar\n");
}
void Data_writer(FILE *data,int a){
	fprintf(data,"\n\nDetail Produk ke-%d\n",record_count+1);
	fprintf(data,"ID Produk : %d\n",database[a].Product_ID);
	fprintf(data,"Nama Produk :%s\n",database[a].Product_Name);
	fprintf(data,"Kategori data : %s\n",database[a].Product_Categories);
	fprintf(data,"Harga : %.2f\n",database[a].harga);
	fprintf(data,"Stok Produk : %d\n",database[a].stok);
	fprintf(data,"-----------------------------\n");
	
}

void Insert_File(){
	FILE *Product_Detail = fopen("Produk_Toko.txt", "a");
	if (Product_Detail == NULL){
		printf("Membuat file Produk_Toko.txt. Membuat file baru..");
		Product_Detail = fopen("Produk_Toko.txt", "w");
		if(Product_Detail == NULL){
			perror("Gagal membuat file\n");
			return;
		}
	}
	int Data_amount;
	printf("Banyak data yang ingin di tambahkan : ");
	scanf("%d",&Data_amount);
	getchar();
	for (i = 0;i < Data_amount ; i++){
		printf("Masukan data ke %d :\n",i+1);
		printf("Masukan ID produk : ");
		scanf("%d",&database[record_count].Product_ID);
		getchar();
		printf("Masukan Nama Produk : ");
		fgets(database[record_count].Product_Name,sizeof(database[record_count].Product_Name),stdin);
		database[record_count].Product_Name[strcspn(database[record_count].Product_Name,"\n")] = '\0';
		printf("Masukan Kategori Produk : ");
		fgets(database[record_count].Product_Categories,sizeof(database[record_count].Product_Categories),stdin);
		database[record_count].Product_Categories[strcspn(database[record_count].Product_Categories,"\n")]='\0';
		printf("Masukan Harga Produk : ");
		scanf("%f",&database[record_count].harga);
		getchar();
		printf("Masukan stok barang : ");
		scanf("%d",&database[record_count].stok);
		getchar();
		Data_writer(Product_Detail,i);
		record_count++;
	}	
	getchar();
	fclose(Product_Detail);
}

void Show_File(){
	FILE *Product_Detail = fopen("Produk_Toko.txt", "r");
	char buffering[300];
	if (Product_Detail == NULL){
		perror("Data Tidak berhasil di temukan\n");
		printf("Buat data terlebih dahulu\n");
		return;
	}else
	{
	while(fgets(buffering,sizeof(buffering),Product_Detail)){
		printf("%s",buffering);
	}
	}
	
	fclose(Product_Detail);
}
void Update_File(){
	
	
}
void Erase_product(){
	char buffering[300],IDprodukcari[25];
	int found = 0;
	printf("Masukan ID yang ingin hapus : ");
	fgets(IDprodukcari,sizeof(IDprodukcari),stdin);
	IDprodukcari[strcspn(IDprodukcari,"\n")]='\0';
	FILE *Product_Detail = fopen("Produk_Toko.txt", "r");
	if(Product_Detail == NULL){
		perror("File tidak dapat di buka : \n");
		return;
	}
	FILE *TrashBin;
	TrashBin = fopen("Ricycle_bin.txt","w");
	if (TrashBin == NULL){
		fclose(Product_Detail);
		perror("File tidak dapat di buat : \n");
		return;
	}
	
	while(fgets(buffering,sizeof(buffering),Product_Detail))
	{	if(strstr(buffering,"ID Produk :")){
		for(i = 0;i < 6;i++){	
			fgets(buffering,sizeof(buffering),Product_Detail);
		}
		}else
		{
			fputs(buffering,TrashBin);
		}
		
	}
	record_count--;
	fclose(Product_Detail);
    fclose(TrashBin);

    if (found) {
        remove("Produk_Toko.txt");
        rename("Ricycle_bin.txt", "Produk_Toko.txt");
        printf("Data berhasil dihapus.\n");
    } else {
        remove("Ricycle_bin.txt");
        printf("Data tidak ditemukan.\n");
    }
	
}