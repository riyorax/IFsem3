#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "listlinier.h"

Address newNode(ElType val){
    Address p = (Address) malloc(sizeof(Node));
    if(p != NULL){
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l){
    /* I.S. sembarang             */
    /* F.S. Terbentuk list kosong */
    FIRST(*l) = NULL;
}


/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l){
    /* Mengirim true jika list kosong */
    return FIRST(l) == NULL;
}

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx){
    /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. Mengembalikan nilai elemen l pada indeks idx */
    int i = 0;
    List p = FIRST(l);
    while (i<idx){
        p = NEXT(p);
        i +=1;
    }
    return(INFO(p));
}

void setElmt(List *l, int idx, ElType val){
    /* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
    int i = 0;
    List p = FIRST(*l);
    while (i<idx){
        p = NEXT(p);
        i+=1;
    }
    INFO(p) = val;
}

int indexOf(List l, ElType val){
    /* I.S. l, val terdefinisi */
    /* F.S. Mencari apakah ada elemen list l yang bernilai val */
    /* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
    /* Mengembalikan IDX_UNDEF jika tidak ditemukan */
    int idx = 0;
    boolean found = false;
    List p = FIRST(l);
    while(p != NULL && !found){
        if(INFO(p) == val){
            found = true;
        }else{
            idx +=1;
            p = NEXT(p);
        }
    }
    if (found){
        return idx;
    }else{
        return IDX_UNDEF;
    }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val){
    /* I.S. l mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
    /* Jika alokasi gagal: I.S.= F.S. */
    List p = newNode(val);
    if (p != NULL){
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
}

void insertLast(List *l, ElType val){
    /* I.S. l mungkin kosong */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menambahkan elemen list di akhir: elemen terakhir yang baru */
    /* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    List last;
    if (isEmpty(*l)){
        insertFirst(l,val);
    }else{
        List p = newNode(val);
        if(p != NULL){
            last = FIRST(*l);
            while (NEXT(last) != NULL){
                last = NEXT(last);
            }
            NEXT(last) = p;
        }
    }
}

void insertAt(List *l, ElType val, int idx){
    /* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. Melakukan alokasi sebuah elemen dan */
    /* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
    /* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    if (idx == 0){
        insertFirst(l,val);
    }else{
        Address p = newNode(val);
        if (p != NULL){
            int counter = 0;
            Address loc = FIRST(*l);
            while (counter < idx -1){
                counter +=1;
                loc = NEXT(loc);
            }
            NEXT(p) = NEXT(loc);
            NEXT(loc) = p;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val){
    /* I.S. List l tidak kosong  */
    /* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
    /*      dan alamat elemen pertama di-dealokasi */
    Address loc = FIRST(*l);
    *val = INFO(loc);
    FIRST(*l) = NEXT(loc);
    free(loc);
}

void deleteLast(List *l, ElType *val){
    /* I.S. list tidak kosong */
    /* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
    /*      dan alamat elemen terakhir di-dealokasi */
    if (NEXT(*l) == NULL){
        deleteFirst(l,val);
    }else{
        Address p = *l;
        Address loc = NULL;
        while(NEXT(p) != NULL){
            loc = p;
            p = NEXT(p);
        }
        if(loc == NULL){
            FIRST(*l) = NULL;
        }else{
            NEXT(loc) = NULL;
        }
        *val = INFO(p);
        free(p);
    }
}

void deleteAt(List *l, int idx, ElType *val){
    /* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
    /* F.S. val diset dengan elemen l pada indeks ke-idx. */
    /*      Elemen l pada indeks ke-idx dihapus dari l */
    if (idx == 0){
        deleteFirst(l,val);
    }else{
        int counter = 0;
        Address loc = FIRST(*l);
        while (counter < idx-1){
            counter +=1;
            loc = NEXT(loc);
        }
        Address p = NEXT(loc);
        *val = INFO(p);
        NEXT(loc) = NEXT(p);
        free(p);
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l){
    // void printInfo(List l);
    /* I.S. List mungkin kosong */
    /* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika list kosong : menulis [] */
    /* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    Address p;
    printf("[");
    if(!isEmpty(l)){
        p = FIRST(l);
        printf("%d", INFO(p));
        p = NEXT(p);
        while (p != NULL){
            printf(",%d", INFO(p));
            p = NEXT(p);
        }
    }
    printf("]");
}

int length(List l){
    /* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    Address p;
    int counter;
    if (isEmpty(l)){
        return 0;
    }else{
        p = FIRST(l);
        counter = 0;
        while (NEXT(p) != NULL){
            counter +=1;
            p = NEXT(p);
        }
        return counter;
    }
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2) {
    /* I.S. l1 dan l2 sembarang */
    /* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
    /* Konkatenasi dua buah list : l1 dan l2    */
    /* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
    /* Tidak ada alokasi/dealokasi pada prosedur ini */
    List l3;
    Address p;
    CreateList(&l3);
    p = FIRST(l1);
    while (p != NULL){
        insertLast(&l3,INFO(p));
        p = NEXT(p);
    }
    p = FIRST(l2);
    while (p != NULL){
        insertLast(&l3,INFO(p));
        p = NEXT(p);
    }
    return l3;
}