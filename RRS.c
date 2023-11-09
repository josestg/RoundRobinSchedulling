#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

#define Nil NULL
#define timeSwitch 1

typedef int infotype;
typedef char label;
typedef struct TElmtList *address;
typedef struct TElmtList
{
	infotype info;
	label data;
	address next;
}ElmtList;

typedef struct
{
	address First;
	address Last;
}List;

/* Selektor */
#define Info(P) (P)->info
#define Data(P) (P)->data
#define Next(P) (P)->next
#define First(L) ((L).First)
#define Last(L) ((L).Last)

address Alokasi(infotype X,label C)
{
	address P;
	P=(address)malloc(sizeof(ElmtList));
	if(P==Nil)
		return Nil;
	
	Data(P)=C;
	Info(P)=X;
	Next(P)=Nil;
	return P;
	
	
}

void Dealokasi(address *P)
{
	free(*P);
}


void CreateListEmpty(List *L)
{
	Last(*L)=Nil;
	First(*L)=Nil;
}

boolean IsListEmpty(List L)
{
	return(First(L)==Nil && Last(L)==Nil);
}

/**/
//PENCARIAN ALAMAT
void SearchBefore(List L,address *Before,address P)
{
	*Before=First(L);
	while(Next(*Before)!=P)
	{
		*Before=Next(*Before);
	}
}

/**/
//PENAMBAHAN ELEMEN BERDASARKAN ALAMAT
void InsertFirst(List *L,address P)
{
	if(IsListEmpty(*L))
	{
		First(*L)=P;
		Last(*L)=P;
		Next(P)=First(*L);
	}
	else
	{
		Next(P)=First(*L);
		First(*L)=P;
		Next(Last(*L))=First(*L);
	}
}

void InsertLast(List *L,address P)
{
	if(IsListEmpty(*L))
	{
		First(*L)=P;
		Last(*L)=P;
		Next(P)=First(*L);
	}
	else
	{
		Next(Last(*L))=P;
		Last(*L)=P;
		Next(P)=First(*L);
	}
}

/**/
//PENGHAPUSAN ELEMEN
void DeleteFirst(List *L,infotype *X,label *C)
{
	address P;
	P=First(*L);
	*X=Info(P);
	*C=Data(P);

	if(Last(*L)==First(*L))
	{
		CreateListEmpty(L);
	}
	else
	{
		First(*L)=Next(P);
		Next(Last(*L))=First(*L);
		Next(P)=Nil;

		Dealokasi(&P);
	}
}

void DeleteLast(List *L,infotype *X,label *C)
{
	address P,Before;
	P=Last(*L);
	*X=Info(P);
	*C=Data(P);
	if(Last(*L)==First(*L))
	{
		CreateListEmpty(L);
	}
	else
	{
		/*Mencari Alamat Sebelum P*/
		SearchBefore(*L,&Before,P);
		
		Next(Before)=Next(P);
		Next(P)=Nil;
		Last(*L)=Before;
		Dealokasi(&P);
	}
}

/**/
//MENCETAK
void PrintPreview(List L)
{
	address P;
	P=First(L);
	printf("+--------------------------+\n");
	printf ("| %7s   %3s   %-8s |\n", "Data", "| ", "Quanta");
	printf("+--------------------------+\n");
	if(P!=Nil)
	{
		do{
			printf ("| %5c     %3s   %-7d  |\n", Data(P), "| ", Info(P));
			printf("+--------------------------+\n");
			P=Next(P);
		}while(P!=First(L));		
	}
	else
	{//jika Data Kosong
		printf ("| %5s     %3s   %-7s  |\n","Empty", "| ", "Empty");
		printf("+--------------------------+\n");	
	}
}

void PrintLine()
{
	printf("+-------------------------------------------------------------+\n");
}

void Switch()
{
	printf ("| %5s    %3s    %-7d  %3s   %-7s  %3s   %-10s   |\n", "Switch", "| ",timeSwitch, "| ", " ", "| "," ");
	PrintLine();
}


void PrintElmt(List L,address P,int timeQuantum)
{
	if(Info(P)<1)
	{
		printf ("| %5c     %3s    %-7d  %3s   %-7d  %3s   %-10s   |\n", Data(P), "| ",timeQuantum, "| ", Info(P), "| ","DISPOSE");	
	}
	else
	{
		printf ("| %5c     %3s    %-7d  %3s   %-7d  %3s   %-10s   |\n", Data(P), "| ",timeQuantum, "| ", Info(P), "| ","In Proses");
	}

	PrintLine();
	
	if(Last(L)!=First(L))
	{//Tidak Satu Element
		Switch();

	}
	else
	{//Satu Elment
		if(Info(P)>=1)
		{//jika lebih besar dari satu masih butuh switch
			Switch();
		}
	}

}

//MENGHAPUS ELEMEN JIKA QUANTA < 1
void Dispose(List *L,infotype *X,label *C,int *nTransversal,int timeQuantum)
{
	address P,Q,Before;
	boolean DisF;
	/*
		DisF : Sudah Di dispose tetapi P masih tetap di First
		Kondisinya ketika Dispose di First.
		ketika DisF = true maka mengijingkan untuk melanjutkan
		penelurusan ke node berikutnya
	*/
	P=First(*L);

	/*	
		Menelusuri Quanta < 1 
		Jika Quanta<1 Maka Dispose
	*/

	do
	{
		DisF=false;

		/*	Waktu Quanta - Waktu Quantum
			Waktu Quantum = Waktu yang dibutuhkan melakukan pekerjaan
		*/	
		Info(P)-=timeQuantum; 
		
		if(Info(P)<1)
		{
			if(P==First(*L))
			{	
				if(P!=Last(*L))
				{//Next(P) = First(*L) tetapi bukan 1 elemen
					DisF=true;
				}

				PrintElmt(*L,P,timeQuantum);
				DeleteFirst(L,X,C);
				
				P=First(*L);
			}
			else if(P==Last(*L))
			{//Dispose Di Last Element
				
				PrintElmt(*L,P,timeQuantum);
				P=Next(P);
				DeleteLast(L,X,C);
			}
			else
			{//Dispose bukan di Last atau di First Element 
				
				PrintElmt(*L,P,timeQuantum);
				Q=P;
				*X=Info(Q);
				*C=Data(Q);
				P=Next(P);

				//Mencari Alamat Sebelum data yang akan di dispose
				SearchBefore(*L,&Before,Q);
				Next(Before)=Next(Q);
				Next(Q)=Nil;

				Dealokasi(&Q);
			}
		}
		else
		{//Quanta>=1
			PrintElmt(*L,P,timeQuantum);
			P=Next(P);
		}

		/*Menghitung n kali data yang dikunjungi*/
		*nTransversal+=1;

	}while(P!=First(*L)||DisF==true);
}

int main()
{
	/* KAMUS */
	List L;
	infotype Quanta;
	address P;
	label C;
	int i,nTransversal,total,timeQuantum,n;

	/*Membuat List Kosong*/
	CreateListEmpty(&L);
	
	/*Initial Value*/
	i=0; //masukan data
	nTransversal=0;
	
	/*Input Data & Quantum*/
	printf("Jumlah Data\t\t : ");
	scanf("%d",&n);
	printf("Quantum Per Proses\t : ");
	scanf("%d",&timeQuantum);
	printf("\n\n");

	while(i<n)
	{
		printf("Simpul\t #%d\n",i+1);
		printf("Quanta\t #%d ",i+1);
		scanf("%d",&Quanta);
		printf("Data\t #%d ",i+1);
		scanf("%*c%c",&C);
		printf("\n");
		InsertFirst(&L,Alokasi(Quanta,C));
		i++;
	}

	/*Cetak data awal*/
	PrintPreview(L);
	printf("\n\n");
	PrintLine();

	/*PROSES ROUND ROBIN SCHEDULING*/	
	
	/*Mencetak Header*/
	printf ("| %7s   %3s   %-8s  %3s   %-8s %3s   %-12s |\n", "Data", "| ","Quantum","| ","Quanta","| ","Status");
	PrintLine();

	/*Proses Dispose*/
	while(!IsListEmpty(L))
	{
		Dispose(&L,&Quanta,&C,&nTransversal,timeQuantum);
	}
	if(IsListEmpty(L))
	{//List Kosong
		if(n<1)
		{
			total=0;
			printf ("| %5s     %3s    %-7d  %3s   %-7s  %3s   %-10s   |\n", "Total", "| ",total, "| ", " ", "| ","Empty");	
		}
		else
		{
			//Menghitung waktu total
			total=nTransversal*(timeQuantum+timeSwitch)-timeSwitch;
			
			printf ("| %5s     %3s    %-7d  %3s   %-7s  %3s   %-10s   |\n", "Total", "| ",total, "| ", " ", "| ","FINISHED!");	
		}
		PrintLine();
	}
	return 0;
}
