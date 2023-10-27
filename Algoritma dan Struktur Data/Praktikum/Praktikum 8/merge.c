#include <stdio.h>
#include "listlinier.h"
#include "boolean.h"
#include "merge.h"

void splitList(List source, List* front, List* back){
    /* Fungsi untuk memecah sebuah list dengan head source menjadi dua buah 
    list baru, yaitu front dan back. Apabila panjang list ganjil, maka
    list front akan lebih panjang dibandingkan list back.
    Sebagai contoh untuk list dengan panjang 5, maka list front memiliki
    3 elemen dan list back memiliki 2 elemen.
    */
    CreateList(front);
    CreateList(back);
    int temp;
    while(source != NULL){
        deleteFirst(source,&temp);
        insertLast(front, temp);
        if(source != NULL){
            deleteLast(source, &temp);
            insertFirst(back,temp);
        }

    }
}


List merge(List a, List b){
    /* Fungsi untuk melakukan merge sort list a dan b secara rekursif.
    Sort dilakukan secara ascending berdasarkan nilai elemen.
    Apabila List a = NULL, maka kembalikan List b
    Apabila List b = NULL, maka kembalikan List a
    Selain itu, lakukan perbandingan antara INFO(a) dengan 
    INFO(b) untuk mendapatkan urutannya
    */
    if(a == NULL){
        return b;
    }else{
        if (b == NULL){
            return a;
        }else{
            // splitList()
            if(INFO(a)< INFO(b)){
                return merge(a,b);
            }else{
                return merge(b,a);
            }
        }
    }
}


void mergeSort(List* list){
    /* Fungsi untuk melakukan inisialisasi merge sort secara rekursif.
    Setiap kali fungsi dipanggil, maka tampilkan list yang sekarang
    sedang diproses.
    Apabila head atau NEXT(head) kosong, maka lakukan return
    Fungsi akan membagi list menjadi dua terlebih dahulu, kemudian 
    secara rekursif melakukan merge untuk mengurutkan
    */
    List front, back;
    CreateList(&front);
    CreateList(&back);
    splitList(*list, &front, &back);

   
}
