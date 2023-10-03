#include <stdio.h>
#include <stdlib.h>
#include "listdin.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity){
    /* I.S. l sembarang, capacity > 0 */
    /* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
    CAPACITY(*l) = capacity;
    BUFFER(*l) = (ElType *)malloc(capacity * sizeof(ElType));
    NEFF(*l) = 0;

}


void dealocateList(ListDin *l){
    /* I.S. l terdefinisi; */
    /* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
    NEFF(*l) = 0;
    CAPACITY(*l) = 0;
    free(BUFFER(*l));
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLength(ListDin l){
    /* Mengirimkan banyaknya elemen efektif list */
    /* Mengirimkan nol jika list l kosong */
    /* *** Daya tampung container *** */
    return NEFF(l);
}


/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListDin l){
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l pertama */
    return IDX_MIN;
}

IdxType getLastIdx(ListDin l){
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l terakhir */
    return(IdxType)(listLength(l)-1);
}


/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, IdxType i){
    /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
    /* yaitu antara indeks yang terdefinisi utk container*/
    return (i>=getFirstIdx(l)) && (i< CAPACITY(l));
}

boolean isIdxEff(ListDin l, IdxType i){
    /* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
    /* yaitu antara 0..NEFF(l) */
    return (i>=getFirstIdx(l)) && (i<=NEFF(l));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListDin l){
    /* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
    /* *** Test list penuh *** */
    return(listLength(l) == 0);
}

boolean isFull(ListDin l){
    /* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
    return(listLength(l) == CAPACITY(l));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l){
    /* I.S. l sembarang dan sudah dialokasikan sebelumnya */
    /* F.S. List l terdefinisi */
    /* Proses : membaca banyaknya elemen l dan mengisi nilainya */
    /* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
    /*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
    /*    Jika N tidak valid, tidak diberikan pesan kesalahan */
    /* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
        0 satu per satu diakhiri enter */
    /*    Jika N = 0; hanya terbentuk l kosong */
    int N,i;
    ElType elm;
    boolean valid;
    valid = false;
    while (!valid){
        scanf("%d\n", &N);
        if ((N>=0) && (N<=CAPACITY(*l))){
            valid = true;
        }
    }
    NEFF(*l) = N;
    for(i = 0; i<NEFF(*l); i++){
        scanf("%d\n", &elm);
        ELMT(*l, i) = elm;
    }
}

void printList(ListDin l){
    /* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
    antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
    di tengah, atau di belakang, termasuk spasi dan enter */
    /* I.S. l boleh kosong */
    /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika list kosong : menulis [] */
    int i;
    if(listLength(l) == 0){
        printf("[]");
    } else{
        printf("[");
        for (i = 0; i < NEFF(l); i++){
            printf("%d", ELMT(l, i));
            if (i != NEFF(l)-1){
                printf(",");
            }
        }
        printf("]");
    }
}


/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus){
    /* Prekondisi : l1 dan l2 memiliki Neff sama dan tidak kosong */
    /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
    /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */
    int i;
    ListDin lhasil;
    CreateListDin(&lhasil, NEFF(l1));
    if (plus){
        for (i = 0; i < NEFF(l1); i++){
            ELMT(lhasil,i) = ELMT(l1,i) + ELMT(l2,i);
        }
    }
    else{
        for (i = 0; i < NEFF(l1); i++){
            ELMT(lhasil,i) = ELMT(l1,i) - ELMT(l2,i);
        }
    }
    NEFF(lhasil) = NEFF(l1);
    return lhasil;
}


/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListEqual(ListDin l1, ListDin l2){
    /* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */
    int i;
    boolean valid;
    valid = true;
    if (NEFF(l1) == NEFF(l2)){
        for (i = 0; i < NEFF(l1); i++){
             if (ELMT(l1,i) != ELMT(l2,i)){
                valid = false;
             }
        }
        return valid;
    } else{
        return false;
    }
}


/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, ElType val){
    /* Search apakah ada elemen List l yang bernilai val */
    /* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
    /* Jika tidak ada, mengirimkan IDX_UNDEF */
    /* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
    /* Skema Searching yang digunakan bebas */
    IdxType i = 0;
    boolean ketemu = false;
    while(i<NEFF(l) && ketemu == false){
         if(ELMT(l,i) == val){
            ketemu = true;
        }
        else{
            i++;
        } 
    }
    if(ketemu){
        return i;
    } else{
        return IDX_UNDEF;
    }
}


/* ********** NILAI EKSTREM ********** */
void extremeValues(ListDin l, ElType *max, ElType *min){
    /* I.S. List l tidak kosong */
    /* F.S. max berisi nilai maksimum l;
            min berisi nilai minimum l */
    int i = IDX_MIN;
    *max = ELMT(l,i);
    *min = ELMT(l,i);
    for(i = IDX_MIN; i < NEFF(l); i++){
        if(ELMT(l,i)>*max){
            *max = ELMT(l,i);
        }
        if(ELMT(l,i)<*min){
            *min = ELMT(l,i);
        }
    }    
}


/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut){
    /* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
    /* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
    /* Proses : Menyalin isi lIn ke lOut */
    int i;
    CreateListDin(lOut, CAPACITY(lIn));
    NEFF(*lOut) = NEFF(lIn);
    for(i = 0; i < NEFF(lIn); i++){
       ELMT(*lOut,i) = ELMT(lIn,i);
    }   
}

ElType sumList(ListDin l){
    /* Menghasilkan hasil penjumlahan semua elemen l */
    /* Jika l kosong menghasilkan 0 */
    ElType sum = 0;
    int i;
    for(i = 0; i < NEFF(l); i++){
        sum += ELMT(l,i);
    }
    return sum;
}

int countVal(ListDin l, ElType val){
    /* Menghasilkan berapa banyak kemunculan val di l */
    /* Jika l kosong menghasilkan 0 */
    int count = 0;
    int i;
    for(i = 0; i < NEFF(l); i++){
        if (ELMT(l,i) == val){
            count += 1;
        }
    }
    return count;
}


/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc){
    /* I.S. l boleh kosong */
    /* F.S. Jika asc = true, l terurut membesar */
    /*      Jika asc = false, l terurut mengecil */
    /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
    algoritma bebas */
    int i, j;
    int n = listLength(*l);
    boolean swapped;
    if(asc == true){
        for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (ELMT(*l,j) > ELMT(*l,(j+1))) {
                int temp = ELMT(*l,j);
                ELMT(*l,j) = ELMT(*l,(j+1));
                ELMT(*l,(j+1)) = temp;
                swapped = true;
            }
        }
        if (swapped == false){
            break;
        }
        }
    } else{
        for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (ELMT(*l,j) < ELMT(*l,(j+1))) {
                int temp = ELMT(*l,j);
                ELMT(*l,j) = ELMT(*l,(j+1));
                ELMT(*l,(j+1)) = temp;
                swapped = true;
            }
        }
        if (swapped == false){
            break;
        }
        }
    }
}


/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, ElType val){
    /* Proses: Menambahkan val sebagai elemen terakhir list */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen terakhir l yang baru */
    ELMT(*l,NEFF(*l)) = val;
    NEFF(*l) += 1;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, ElType *val){
    /* Proses : Menghapus elemen terakhir list */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
    /*      Banyaknya elemen list berkurang satu */
    /*      List l mungkin menjadi kosong */
    *val = ELMT(*l,NEFF(*l)-1);
    NEFF(*l) -= 1;
}


/* ********* MENGUBAH UKURAN ARRAY ********* */
void expandList(ListDin *l, int num){
    /* Proses : Menambahkan capacity l sebanyak num */
    /* I.S. List sudah terdefinisi */
    /* F.S. Ukuran list bertambah sebanyak num */
    ListDin ltemp;
    int i;
    CreateListDin(&ltemp, CAPACITY(*l) + num);
    for(i = 0; i < NEFF(*l); i++){
       ELMT(ltemp,i) = ELMT(*l,i);
    }
    NEFF(ltemp) = NEFF(*l);
    dealocateList(l);
    copyList(ltemp,l);
}


void shrinkList(ListDin *l, int num){
    /* Proses : Mengurangi capacity sebanyak num */
    /* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
    /* F.S. Ukuran list berkurang sebanyak num. */
    ListDin ltemp;
    int i;
    CreateListDin(&ltemp, CAPACITY(*l) - num);
    for(i = 0; i < NEFF(*l); i++){
       ELMT(ltemp,i) = ELMT(*l,i);
    }
    NEFF(ltemp) = NEFF(*l);
    dealocateList(l);
    copyList(ltemp,l);
}

void compressList(ListDin *l){
    /* Proses : Mengubah capacity sehingga capacity = nEff */
    /* I.S. List tidak kosong */
    /* F.S. Ukuran capacity = nEff */
    ListDin ltemp;
    int i;
    CreateListDin(&ltemp, NEFF(*l));
    for(i = 0; i < NEFF(*l); i++){
       ELMT(ltemp,i) = ELMT(*l,i);
    }
    NEFF(ltemp) = NEFF(*l);
    dealocateList(l);
    copyList(ltemp,l);
}