#ifndef LISTSIRKULER_H
#define LISTSIRKULER_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

//Konstanta
#define Nil NULL
 
typedef int infotype;
typedef char label;
typedef struct TElmtList *address;

typedef struct TElmtList {
	infotype 	info;
	label 		data;
	address 	next;
} ElmtList;

typedef struct {
	address		first;
	address 	last;
} List;
 
#define First(L) (L).first
#define Last(L) (L).last
#define Next(P) (P)->next
#define Info(P) (P)->info
#define Data(P) (P)->data
 
boolean IsListEmpty (List L);
/* Mengirim true jika list kosong */

void CreateList (List *L);
/*	I.S. sembarang
	F.S. Terbentuk list kosong 
*/

address Alokasi (infotype X, label C);
/*	Mengirimkan address hasil alokasi sebuah elemen
	Jika alokasi berhasil, maka address tidak Nil, dan misalnya menghasilkan P, maka
	Info(P) = X, Data(P)=C, Next(P) = Nil
	Jika alokasi gagal, mengirimkan Nil
*/

void Dealokasi (address *P);
/*	I.S. P terdefinisi
	F.S. P dikembalikan ke sistem
	Melakukan dealokasi/pengembalian address P
*/

// PENCARIAN SEBUAH ELEMEN LIST
address Search (List L, infotype X);
/*	Mencari apakah ada elemen list dengan Info(P) = X
	Jika ada, mengirimkan address elemen tersebut
	Jika tidak ada, mengirimkan Nil
*/

address SearchBefore (List L, address P);
/*	Mengirimkan address sebelum address P
	Jika ada, mengirimkan address Before, dengan Next(Before) = P
	Jika tidak ada, mengirimkan Nil
	Jika P adalah elemen pertama, maka mengirimkan Nil
	Search dengan spesifikasi seperti ini menghindari traversal ulang jika setelah search akan dilakukan operasi lain
*/

//PRIMITIF BERDASARKAN ALAMAT
//PENAMBAHAN ELEMEN BERDASARKAN ALAMAT
void InsertFirst (List *L, address P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. Menambahkan elemen ber-address P sebagai elemen pertama
*/

void InsertLast (List *L, address P);
/*	I.S. Sembarang, P sudah dialokasi
	F.S. P ditambahkan sebagai elemen terakhir yang baru
*/

//PENGHAPUSAN SEBUAH ELEMEN
void DeleteFirst (List *L, infotype *X, label *C);
/*	I.S. List tidak kosong
	F.S. X adalah nilai Quanta, C adalah Data label dari Quanta
	Elemen list berkurang satu (mungkin menjadi kosong)
	First element yang baru adalah suksesor elemen pertama yang lama
*/

void DeleteP (List *L, infotype X,label *C);
/*	I.S. Sembarang
	F.S. Jika ada elemen list ber-address P, dengan Info(P) = X
	Maka P dihapus dari list dan di-dealokasi
	Jika tidak ada elemen list dengan Info(P) = X, maka list tetap
	List mungkin menjadi kosong karena penghapusan
*/

void DeleteLast (List *L, infotype *X,label *C);
/*	I.S. List tidak kosong
	F.S. P adalah alamat elemen terakhir list sebelum penghapusan
	Elemen list berkurang satu (mungkin menjadi kosong)
	Last element baru adalah predesesor elemen terakhir yang lama, jika ada
*/

void DeleteAfter (List *L, address *P, address Before);
/*	I.S. List tidak kosong. Prec adalah anggota list L. Prec bukan elemen terakhir.
	F.S. Menghapus Next(Prec) : Pdel adalah alamat elemen list yang dihapus
*/

//PROSES SEMUA ELEMEN LIST
void PrintInfo (List L);
/*	I.S. List mungkin kosong
	F.S. Jika list tidak kosong,
	Semua info yg disimpan pada elemen list diprint dengan format [elemen-1, elemen-2, elemen-3, ...]
	Jika list kosong, hanya menuliskan "[]"
*/
void PrintPreview(List L)
/* 	I.S. List mungkin kosong
	F.S. Jika List Tidak kosong
	semua info akan diprint dengan format dua kolom [data dan Quanta]
	Jika list kosong hanya menulis kepala tabel aja
*/

void PrintElmt(List L, address P)
{
/* 	I.S. Tidak mungkin kosong
	F.S. Print elmt yang beralamat P kedalam format tabel  4 kolom [Data, Quantum , Quanta dan status]
	jika Quanta <1 maka status Dispose jika tidak maka status In Proses
*/
}
void Switch()
{
/*	F.S. Print Quantum=1 ketika berlanjut ke proses berikutnya
*/	
}

#endif
