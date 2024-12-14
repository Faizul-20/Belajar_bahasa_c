#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MaxData 100
typedef enum{
	Insert = 1,
	Show,
	Update,
	Erase,
}menu;

void tampilan();
void Insert_File(int a,FILE *data);
void Show_File(FILE *data);
void Update_File(int a,FILE *data);
void Erase_product(int a,FILE *data);
void Data_writer(FILE *data);
int search_engine(int a,FILE *data); 
typedef struct{
	char Product_Name[100];
	char Product_Categories[100];
	int harga;
	int stok;
} Product_ID;
typedef struct 
{
	int ID_Product;
	Product_ID detail;
}Product_Data;

Product_Data database[MaxData]; 
int record_count = 0;

int main(){
	FILE *Product_Detail;
	Product_Detail = fopen("Produk_Toko.txt", "w");
	if (Product_Detail == NULL){
		perror("Data Tidak berhasil di buat");
		exit(0);
		return 1;
	}	
	fclose(Product_Detail);
	menu choice;
	do{
	
	tampilan();
	int choice2;
	printf("Masukan Pilihan : ");
	scanf("%d",&choice2);
	choice = (menu)choice2;
	
	switch(choice){
	case Insert:
		Product_Detail = fopen("Produk_Toko.txt", "a");
		if (Product_Detail == NULL){
			perror("File Tidak Berhasil di temukan\n");
			exit(0);
		}else{
		int Data_amount;
		printf("masukan Jumlah Produk Yang ingin di tambahkan : ");
		scanf("%d",&Data_amount);
		getchar();
		Insert_File(Data_amount,Product_Detail);
		printf("\nData Berhasil Di Tambahkan\n");
		}
		fclose(Product_Detail);
		break;
	case Show:
		Product_Detail = fopen("Produk_Toko.txt", "r");
		if (Product_Detail == NULL){
			perror("File Tidak Berhasil di temukan\n");
			exit(0);
		}else
		{
		Show_File(Product_Detail);
		printf("\nData Berhasil ditampilkan\n");	
		}
		fclose(Product_Detail);
		break;
	case Update:
		Product_Detail = fopen("Produk_Toko.txt", "w");
		if(Product_Detail == NULL){
			perror("Data Tidak bisa diakses");
			exit(0);
		}else{
		int ID_update;
		printf("Masukan ID Poduct yang ingin di update :");
		scanf("%d",&ID_update);
		getchar();
		Update_File(ID_update,Product_Detail);
		}
		fclose(Product_Detail);
		break;
	case Erase:
		Product_Detail = fopen("Produk_Toko.txt", "w");
		if(Product_Detail == NULL){
			perror("Data tidak berhasil di temukan");
			exit(0);
		}else{
		int Erase_ProductId;
		printf("Masukan ID Produk yang akan di hapus : ");
		scanf("%d",&Erase_ProductId);
		getchar();
		Erase_product(Erase_ProductId,Product_Detail);
		}
		fclose(Product_Detail);
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

void Insert_File(int a,FILE *data){
		int i;
		for (i = 0;i < a ;i++){
			printf("\nMasukan data produk ke-%d \n",i+1);
			while(2){
			printf("Masukan ID : ");
			scanf("%d",&database[record_count].ID_Product);
			int result = search_engine(database[record_count].ID_Product,data);	
			if(result == 1){
			break;	
			}
			}
			getchar();
			printf("Masukan Nama Barang : ");
			fgets(database[record_count].detail.Product_Name,sizeof(database[record_count].detail.Product_Name),stdin);
			database[record_count].detail.Product_Name[strcspn(database[record_count].detail.Product_Name,"\n")] = '\0';
			printf("Masukan Kategori Barang :");
			fgets(database[record_count].detail.Product_Categories,sizeof(database[record_count].detail.Product_Categories),stdin);
			database[record_count].detail.Product_Categories[strcspn(database[record_count].detail.Product_Categories,"\n")] = '\0';
			printf("Masukan Harga : ");
			scanf("%d",&database[record_count].detail.harga);
			printf("Masukan Stok : ");
			scanf("%d",&database[record_count].detail.stok);
			record_count++;
		}	
		Data_writer(data);
}
void Data_writer(FILE *data){
	int i;
	
	for(i=0;i < record_count;i++){
		fprintf(data, "\nID Produk: %d\n", database[i].ID_Product);
        fprintf(data, "Nama Produk: %s\n", database[i].detail.Product_Name);
        fprintf(data, "Kategori Produk: %s\n", database[i].detail.Product_Categories);
        fprintf(data, "Harga: %d\n", database[i].detail.harga);
        fprintf(data, "Stok: %d\n", database[i].detail.stok);
        fprintf(data, "-----------------------------\n");
	}
}
void Show_File(FILE *data){
	char buff[1000];
	while(fgets(buff,sizeof(buff),data)){
		printf("%s",buff);
	} 
}
	
void Update_File(int a,FILE *data){
	int i;
	int found = 0;
	for(i=0;i<record_count;i++){
		if (a == database[i].ID_Product){
			printf("Data Di temukan\n");
			found = 1;
			printf("ID data yang akan di update : %d\n",a);
			printf("Masukan Nama Barang Baru: ");
			fgets(database[i].detail.Product_Name,sizeof(database[i].detail.Product_Name),stdin);
			database[i].detail.Product_Name[strcspn(database[i].detail.Product_Name,"\n")] = '\0';
			printf("Masukan Kategori Barang Baru:");
			fgets(database[i].detail.Product_Categories,sizeof(database[i].detail.Product_Categories),stdin);
			database[i].detail.Product_Categories[strcspn(database[i].detail.Product_Categories,"\n")] = '\0';
			printf("Masukan Harga Baru: ");
			scanf("%d",&database[i].detail.harga);
			printf("Masukan Stok Baru: ");
			scanf("%d",&database[i].detail.stok);
			printf("\n\nData Berhasil Di update\n\n");
			break;
		}
	}
	if(a != database[i].ID_Product){
			printf("\n\n\nData tidak di temukan\n");}
	Data_writer(data);
}
void Erase_product(int a,FILE *data){
	int i;
	int j;
	int found = 0;
	char erase_choice;
	for(i=0;i<record_count;i++){
		if (a == database[i].ID_Product){
			printf("Data Di temukan\n");
			found = 1;
			printf("ID data yang akan di hapus: %d\n",a);
			printf("Apakah anda yakin ingin menghapus data anda : (Y/N)");
			scanf("%c",&erase_choice);
			int choice = tolower(erase_choice);
			if(choice == 'y'){
					for(j = 0;j < record_count - 1;j++){
						database[i] = database[j];
						database[j] = database[j+1];
					}
				record_count--;	
				printf("\n\nData Berhasil Di hapus\n\n");
				break;
			}else{
			printf("\n\nData Tidak Di hapus\n\n");
			break;
			}		
		}
	}
	if(a != database[i].ID_Product){
			printf("\n\n\nData tidak di temukan\n");
			}
	Data_writer(data);
}
	
int search_engine(int a,FILE *data){
	int i;
	for(i=0;i<record_count;i++){
		if (a == database[i].ID_Product){
			printf("\nID sudah ada!\n");
			printf("Tolong masukan ID lain\n");
			return 0;
		}
	}
	return 1;
}	
