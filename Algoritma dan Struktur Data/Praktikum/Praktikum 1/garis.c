#include <stdio.h>
#include "garis.h"
#include <math.h>
#include "boolean.h"
#include "point.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */ 
/* ***************************************************************** */
/* *** Konstruktor membentuk GARIS *** */
void CreateGaris (GARIS * L, POINT P1, POINT P2){
    /* I.S. P1 dan P2 terdefinisi */
    /* F.S. L terdefinisi dengan L.PAw = P1 dan L.PAkh = P2 */
    /* Membentuk sebuah L dari komponen-komponennya */
    PAwal(*L) = P1;
    PAkhir(*L) = P2;
}

/* ***************************************************************** */
/* KELOMPOK INTERAKSI DENGAN I/O DEVICE, BACA/TULIS                  */
/* ***************************************************************** */
void BacaGARIS (GARIS * L){
    /* I.S. sembarang */
    /* F.S. L terdefinisi sebagai GARIS yang valid */
    /* Proses : mengulangi membaca dua buah nilai P1 dan P2 sehingga dapat 
    membentuk GARIS yang valid 
    GARIS disebut valid jika titik awal tidak sama dengan titik akhirnya. */
    /* Jika pembacaan garis tidak valid, diberikan pesan kesalahan: 
    "Garis tidak valid" */
    /* Contoh:
    2 3
    2 3
    Garis tidak valid
    2 3
    3 3 
    --> terbentuk garis L dengan L.PAw = <2,3> dan L.PAkh = <3,3> */
    POINT P1,P2;
    float x1,x2,y1,y2;
    for(;;){
        scanf("%f %f", &x1, &y1);
        scanf("%f %f", &x2, &y2);
        CreatePoint(&P1, x1, y1);
        CreatePoint(&P2, x2, y2);
        if (NEQ(P1,P2)){
            CreateGaris(L,P1,P2);
            break;
        } else{
            printf("Garis tidak valid\n");
        }
    }
    // POINT P1,P2;
    // for(;;){
    //     BacaPOINT(&P1);
    //     BacaPOINT(&P2);
    //     if (NEQ(P1,P2) == true){
    //         break;
    //     }else{
    //         printf("Garis tidak valid\n");
    //     }
    // }
    // CreateGaris(L,P1,P2);
}


void TulisGARIS (GARIS L){
    /* I.S. L terdefinisi */
    /* F.S. L tertulis di layar dengan format "((x1,y1),(x2,y2))" 
    tanpa tambahan karakter apa pun di depan, di tengah, atau di belakang,
    termasuk spasi dan enter */
    // POINT P1,P2;
    // P1 = PAwal(L);
    // P2 = PAkhir(L);
    printf("((%.2f,%.2f),(%.2f,%.2f))", Absis(PAwal(L)), Ordinat(PAwal(L)), Absis(PAkhir(L)), Ordinat(PAkhir(L)));
}

/* *** Kelompok operasi garis *** */
float PanjangGARIS (GARIS L){
    /* Menghitung panjang garis L : berikan rumusnya */
    POINT P1,P2;
    float panjang;
    P1 = PAwal(L);
    P2 = PAkhir(L);
    panjang = Panjang(P1,P2);
    return panjang;
}

float Gradien (GARIS L){
    /* Mengembalikan Gradien (m) dari L */
    /* Gradien garis yang melalui (x1,y1) dan (x2,y2) adalah: (y2-y1)/(x2-x1) */
    /* Prekondisi : x1 != x2 */
    return (Ordinat(PAkhir(L))-Ordinat(PAwal(L)))/(Absis(PAkhir(L))-Absis(PAwal(L)));;
}

void GeserGARIS (GARIS * L, float deltaX, float deltaY){
    /* I.S. L terdefinisi */
    /* F.S. L digeser sebesar deltaX ke arah sumbu X dan sebesar deltaY ke arah sumbu Y */
    /* Proses : PAw dan PAkh digeser. */
    POINT P1,P2;
    P1 = PAwal(*L);
    P2 = PAkhir(*L);
    Geser(&P1,deltaX,deltaY);
    Geser(&P2,deltaX,deltaY);
    PAwal(*L) = P1;
    PAkhir(*L) = P2;
}


/* *** Kelompok predikat *** */
boolean IsTegakLurus (GARIS L1, GARIS L2){
    /* Menghasilkan true jika L1 tegak lurus terhadap L2 */
    /* Dua garis saling tegak lurus jika hasil perkalian kedua gradiennya = -1 */
    float m1,m2;
    m1 = Gradien(L1);
    m2 = Gradien(L2);
    return (m1*m2 == (-1));
}

boolean IsSejajar (GARIS L1, GARIS L2){
    /* Menghasilkan true jika L "sejajar" terhadap L1 */
    /* Dua garis saling sejajar jika memiliki gradien yang sama */
    float m1,m2;
    m1 = Gradien(L1);
    m2 = Gradien(L2);
    return (m1==m2);
}

/* *** Kelompok operasi garis dan point *** */
float JarakGARIS (GARIS L, POINT P){
    /* Menghasilkan jarak terdekat antara titik P dan garis L */
    /* Bentuklah persamaan dari garis L menjadi ax + by + c = 0 */
    /* Jarak terdekat dari titik P ke garis L dapat didefinisikan sebagai d = |a * x + b * y + c| / akar kuadrat dari a * a + b * b */
    POINT P1;
    float a,b,c,x,y,atas,bawah,d;
    P1 = PAwal(L);
    b = 1;
    a = (-1)*Gradien(L);
    c = Ordinat(P1)-(Gradien(L)*Absis(P1));
    x = Absis(P);
    y = Ordinat(P);
    atas = a*x+b*y+c;
    bawah = sqrt(a*a+b*b);
    if (atas < 0){
        d = (float)((atas)*(-1))/bawah;
    }else{
        d = (float)(atas)/bawah;
    }
    return d;
}

boolean IsPointMemenuhiGaris (GARIS L, POINT P){
    /* Menghasilkan true jika  titik P terletak di garis L */
    /* Bentuklah persamaan dari garis L menjadi ax + by + c = 0 */
    /* Titik P terletak di garis L jika dan hanya jika P memenuhi persamaan garis L, yaitu ax + by + c = 0 */
    POINT P1;
    float a,b,c,x,y,atas,d;
    P1 = PAwal(L);
    b = 1;
    a = (-1)*Gradien(L);
    c = Ordinat(P1)-(Gradien(L)*Absis(P1));
    x = Absis(P);
    y = Ordinat(P);
    return (a*x+b*y+c == 0);
}