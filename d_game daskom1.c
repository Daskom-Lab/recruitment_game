#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void login_admin();
void login_user();//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
void regis_user();//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
void update_rank();//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
void admin();
void menu_user();
void user_landing(); 
void ranking();
void user_topup(); 
void acc(); //bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
void input(); //bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
void beli_item(); //bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
void admin_topup();
void update();

struct user{ //data-data milik user
	char user[100],pass[100],riwayat,status[100],acc[10],paket[10];
	int saldo, poin, rank;
}user,temp,logged_in,t[100],log;

struct item{ //data untuk daftar item
	char item[100];
	int harga;
}it;

int i=0,j=0,n,harga,opt,paket1=100000, paket2=50000, paket3=30000;
FILE *f;
char accu[100],login[100];
int main(){
	//Tampilan utama, variable n untuk memilih menu menggunakan switch case
	system("cls");
	printf("SELAMAT DATANG DI D-GAME\nMenu:\n");
	printf("1. Admin\n2. User\n3. Exit\nPilihan : ");scanf("%d",&n);getchar();
	switch(n){
		case 1 :i=0;login_admin(); break;
		case 2 : user_landing(); break;
		case 3 : exit(EXIT_FAILURE); break;
		default : main();break;
	}
}

void login_admin(){	
	//Ini adalah fungsi login admin, login admin menggunakan user : admin, pass : admin, gunakan rekursif
	char user[100], pass[100];
	system("cls");
	if(i<3){
		printf("Username : ");gets(user);
		printf("Password : ");gets(pass);
		if(strcmp(user,"admin")!=0 || strcmp(pass,"admin")!=0){
			printf("Login Gagal!");getch();			
			i++;
			login_admin();
		}
		else{
			printf("Login berhasil");getch();i=0;admin();
		}
	}
	else{
		printf("Anda sudah mencoba lebih dari 3 kali, silahkan coba lain kali...");getch();main();
	}
}

void acc(){//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
	//Ini adalah prosedur untuk meng-ACC akun user oleh admin
	f=fopen("temp.dat","rb");
	printf("--- [ Data User ] ---\n");
	while(fread(&user,sizeof(user),1,f)==1){
		printf("Username		: %s\t\t%s\n",user.user,user.status);
		printf("Password		: %s\n\n",user.pass);
	}
	fclose(f);
	char cari[100];
	printf("Masukkan Username Akun Yang Akan Di ACC	: ");gets(cari);
	f=fopen("temp.dat","rb+");
	while(fread(&user,sizeof(user),1,f)==1){
		if(strcmp(user.user,cari)==0){
			fseek(f,(long)-sizeof(user),SEEK_CUR);
			strcpy(user.status,"");
			fwrite(&user, sizeof(user), 1, f);
			printf("\n\t%s telah di verifikasi",cari);getch();admin();
			// break;  gaperlu break
		}
	}fclose(f);
	system("cls");
	f=fopen("temp.dat","rb+");
	while(fread(&user,sizeof(user),1,f)==1){
		if(strcmp(user.user,cari)!=0){
			printf("\n\t%s Tidak ditemukan",cari);getch();fclose(f);admin();
			break;
		}
	}fclose(f);
}

void input(){//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
	//Digunakan untuk menginput item
	f=fopen("item.dat","ab");
	printf("Nama item\t: ");gets(it.item);
	printf("Harga\t\t: ");scanf("%d",&it.harga);
	fwrite(&it,sizeof(it),1,f);
	getchar();
	getch();
	fclose(f);
	admin();	
}

void update_rank(){
	//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
	int x=0,i=0;
	f=fopen("temp.dat","rb");
	while(fread(&user,sizeof(user),1,f)==1){
		t[i]=user;
		i++;x++;
	}fclose(f);
	for(i=x-1;i>=1;i--)
		for(j=1;j<=i;j++){
			if(t[j-1].poin>t[j].poin){
			temp=t[j-1];
			t[j-1]=t[j];
			t[j]=temp;
		}
	}
	i=0;
	f=fopen("temp1.dat","wb"); // ini maksudnya
	for(i=0;i<x;i++){ //ini salah sih bagian ini, pantesan
		user=t[i];
		user.rank=i+1; //biar keliatan dari ranking 1
	fwrite(&user,sizeof(user),1,f);
	}fclose(f); fclose(f); // misterius harusnya sekali aja, 
	remove("temp.dat");rename("temp1.dat","temp.dat");
//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
}

void update(){
	f = fopen("temp.dat","rb");
	while(fread(&user,sizeof(user),1,f)==1){
		if(strcmp(user.user,logged_in.user)==0){
			logged_in = user;
		}
	}fclose(f);
}

void ranking(){
	//Ini adalah bagian yang menunjukkan ranking pelanggan
	system("cls");
	update_rank();
	printf("Rank\tNama\tPoin\tSaldo\n");
	f =  fopen("temp.dat","rb");
	while(fread(&user,sizeof(user),1,f)==1){
		printf("%d\t%s\t%d\t%d\n",user.rank,user.user,user.poin,user.saldo);
		i=i+1;
		user.rank++;
		}
	fclose(f);getch();
	admin();
}

void admin(){
	//Ini adalah menu operasi admin
	update_rank();
	system("cls");
	printf("SELAMAT DATANG ADMIN\nMenu:\n");
	printf("1. ACC Akun\n2. Input Item\n3. ACC Saldo User\n4. Ranking Pelanggan\n5. Exit\nPilihan : ");scanf("%d",&n);getchar();
	switch (n)
	{
		case 1: acc(); break;
		case 2: input(); break;
		case 3: admin_topup(); break;
		case 4: ranking(); break;
		case 5: main(); break;
		default: printf("Tidak ada pilihan, coba lagi"); getchar(); system("cls"); admin();
	}
}

void user_landing(){
	//fungsi untuk menanyakan pada user ingin registrasi atau login
	system("cls");
	printf("User Landing :\n1. Registrasi\n2. Login\n3. Kembali\nPilihan : ");scanf("%d",&n);getchar();
	switch(n){
		case 1 : regis_user();break;
		case 2 : i=0; login_user();break;
		case 3 : break;
	}
}

void regis_user(){//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
	//Registrasi user, simpan data data user di temp.dat
	system("cls");
	f=fopen("temp.dat","ab");
	printf("Registrasi User\n");
	printf("Username : ");gets(user.user);
	printf("Password : ");gets(user.pass);
	strcpy(user.status, "Belum diverifikasi");
	user.saldo = 0;user.poin=0; //biar dari awal
	printf("\nSilakan tunggu konfirmasi admin");getch();
	fwrite(&user,sizeof(user),1,f);
	fclose(f);
	main();	
}

void login_user(){//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
	//Ini adalah fungsi login user, gunakan rekursif
	system("cls");
	if(i<3){
	printf("Username : ");gets(logged_in.user);
	printf("Password : ");gets(logged_in.pass);
	f = fopen("temp.dat","rb");
	while(fread(&user,sizeof(user),1,f)==1){
		if(strcmp(logged_in.user,user.user)==0){
			if(strcmp(logged_in.user,user.user)==0 && strcmp(logged_in.pass,user.pass)==0 && strcmp(user.status,"")==0 ){
				printf("Login berhasil :) ");getch();;i=0;menu_user();
			}
			else{
				printf("Login Gagal :(");getch();			
				i++;
				login_user();
			}
		}
	}
	fclose(f);
	}
	else{
		printf("Anda sudah mencoba lebih dari 3 kali, silahkan coba lain kali...");getch();fclose(f);main();
	}	
}

void beli_item(){
	//Ini adalah bagian pembelian item (pengecekan saldo dan pengurangan saldo)
	system("cls");
	char itbeli[100];
	f=fopen("temp.dat","rb"); //sebenernya ga perlu sih fopen di sini mah
	printf("%d",logged_in.saldo);
	fclose(f);  //berarti kalo mau dihapus fclose ini hapus juga
	printf("\nLIST ITEM\n");
	f=fopen("item.dat","rb");
	printf("No.\titem\tHarga\t");
	while(fread(&it,sizeof(it),1,f)==1){
		printf("\n%d\t%s\t%d",i+1,it.item,it.harga);
		i=i+1;
		printf("\n");
		}
	printf("\nPilih item yang akan dibeli : "); gets(itbeli);
	while(fread(&it,sizeof(it),1,f)==1){
		if(strcmp(it.item,itbeli)==0){
			printf("\n%s", it.item);
			break; //biar dia lanjut 
		}
		else{ printf("item yang dipilih tidak ada");getchar();getch();menu_user(); //begini
		}
	}
	fclose(f);	
	//bagian ini sudah dihapus dan harus kalian isi lagi sesuai dengan file.exe
	char user_[100];
	strcpy(user_,logged_in.user);
	f=fopen("item.dat","rb");
	f=fopen("temp.dat","rb+");
	while(fread(&user,sizeof(user),1,f)==1){
		if(strcmp(user_,user.user)==0){
			int saldo=user.saldo;
			int harga=it.harga;
			printf("Konfirmasi pembelian(y/n)	: ");scanf("%c",&opt);getchar();
			if(opt=='y'||opt=='Y'){
				if(saldo<harga){
					system("cls");
					printf("Maaf isi saldo anda kurang\n");getch();
					fclose(f);
					user_topup();
				}
				else {
					fseek(f,(int)-sizeof(user), SEEK_CUR);
					if(user.poin%10==0 || user.rank == 1 ){
						printf("Selamat, Diskon 50% :*\n");
						user.saldo = user.saldo-(harga-(harga*0.5));
						system("pause");
					}
					else{
						user.saldo=saldo-harga;	
					}
					user.poin++;
					fwrite(&user,sizeof(user),1,f);
					fclose(f);
					menu_user();
				}
			fclose(f);
			}
			else{
				printf("Pembelian gagal!");getch();
				menu_user();
			}
		}
	}
}

void user_topup(){
	//Ini adalah bagian yang mengatur request topup saldo user
	int saldo;
	f = fopen("temp.dat","rb");
	while(fread(&user,sizeof(user),1,f)==1){		
					if (strcmp(user.user, logged_in.user)==0){	
						saldo = user.saldo;
					}
				}
	fclose(f);
	printf("Saldo Anda : %d\n",saldo);
	printf("-=-[ Menu Paket Saldo ]-=-\n");
	printf("1. Paket 1 : 100000 saldo\n");
	printf("2. Paket 2 : 50000 saldo\n");
	printf("3. Paket 3 : 30000 saldo\n");
	printf("Pilih paket 1/2/3 : "); scanf("%d", &n);
	f = fopen("temp.dat","rb+");
	switch(n){
		case 1 : while(fread(&user,sizeof(user),1,f)==1){		
					if (strcmp(user.user, logged_in.user)==0){	
						fseek(f, (int)-sizeof(user), SEEK_CUR);
						strcpy(user.paket, "A");
						fwrite(&user, sizeof(user), 1, f); break;
					}
				} break;
		case 2 : while(fread(&user,sizeof(user),1,f)==1){		
					if (strcmp(user.user, logged_in.user)==0){	
						fseek(f, (int)-sizeof(user), SEEK_CUR);
						strcpy(user.paket, "B");
						fwrite(&user, sizeof(user), 1, f); break;
					}
				} break;
		case 3 : while(fread(&user,sizeof(user),1,f)==1){		
					if (strcmp(user.user, logged_in.user)==0){	
						fseek(f, (int)-sizeof(user), SEEK_CUR);
						strcpy(user.paket, "C");
						fwrite(&user, sizeof(user), 1, f); break;
					}
				} break;
		default : printf("-=-[ Menu Tidak ada ]-=-");
			   	  getchar();
			      system("cls");
				  menu_user(); break;
	}
	fclose(f);	
	system("cls");
	printf("\n--Silahkan tunggu saldo anda terkirim--");
	getch();
	system("cls");	
	menu_user();
}

void admin_topup(){
	//Ini adalah bagian yang mengatur pengisian item user oleh admin
	int s, jml;
	char isaldo[100], ipaket[100];
	f = fopen("temp.dat","rb");
	while(fread(&user,sizeof(user),1,f)==1){
		printf("User  : %s\n", user.user);
		printf("Paket : %s\n", user.paket);
		printf("\n");
		}
		fclose(f);
		f = fopen("temp.dat","rb+");
		printf("User yang ingin di isi Saldo : "); gets(isaldo);
		printf("Paket yang ingin diisi : "); gets(ipaket);
		while(fread(&user,sizeof(user),1,f)==1){		
		if (strcmp(user.user, isaldo)==0){	
			fseek(f,(int) -sizeof(user), SEEK_CUR);
			if(strcmp(ipaket, "A")==0){
				user.saldo = user.saldo + paket1;
				strcpy(user.paket, " ");
				fwrite(&user, sizeof(user), 1, f);  
				fclose(f);
				system("cls");
				printf("\n-=-[ Saldo dikirim ke %s ]-=-", user.user);
				getchar();
				system("cls");
				admin();break;
			}
			else if(strcmp(ipaket, "B")==0){
				user.saldo = user.saldo + paket2;
				strcpy(user.paket, " ");
				fwrite(&user, sizeof(user), 1, f);  
				fclose(f);
				system("cls");
				printf("\n-=-[ Saldo dikirim ke %s ]-=-", user.user);
				getchar();
				system("cls");
				admin();break;
			}
			else if(strcmp(ipaket, "C")==0){
				user.saldo = user.saldo + paket3;
				strcpy(user.paket, " ");
				fwrite(&user, sizeof(user), 1, f);  
				fclose(f);
				system("cls");
				printf("\n-=-[ Saldo dikirim ke %s ]-=-", user.user);
				getchar();
				system("cls");
				admin();break;
			}	
			else {
				getchar();
				system("cls");
				admin();
			}
		}
	}
		fclose(f);
		system("cls");
		printf("\n-=-[ User tidak ada dalam list ]-=-", user.user);
		system("cls");
		admin();
}

void menu_user(){
	//Ini adalah bagian menu operasi user
update_rank();update();
system("cls");
printf(".::|S e l a m a t   d a t a n g   '%s'|::.\n", logged_in.user);
printf("\n======================\n");
printf("-=-[ MENU USER ]-=-");
printf("\n======================\n");
printf("\n\nMENU\t:\n");
printf("1.Beli Item\n");
printf("2.Top Up Saldo\n");
printf("3.Exit\nPilihan: ");scanf("%d",&n);getchar();
switch(n){
	case 1: beli_item();break;
	case 2: user_topup();break;
	case 3: main(); break;
}
system("cls");
}
