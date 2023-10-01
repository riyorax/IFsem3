#include <stdio.h>
#include "time.h"
#include "boolean.h"

/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsTIMEValid (int H, int M, int S){
    /* Mengirim true jika H,M,S dapat membentuk T yang valid */
    /* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
    return (((H>=0) && (H<=23)) && ((M>=0) && (M<=59)) && ((S>=0) && (S<=59)));
}

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */
void CreateTime (TIME * T, int HH, int MM, int SS){
    /* Membentuk sebuah TIME dari komponen-komponennya yang valid */
    /* Prekondisi : HH, MM, SS valid untuk membentuk TIME */
    if (IsTIMEValid(HH,MM,SS)){
        Hour(*T) = HH;
        Minute(*T) = MM;
        Second(*T) = SS;
    }
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaTIME (TIME * T){
    /* I.S. : T tidak terdefinisi */
    /* F.S. : T terdefinisi dan merupakan jam yang valid */
    /* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk T */
    /* yang valid. Tidak mungkin menghasilkan T yang tidak valid. */
    /* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
    dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
    /* Jika TIME tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
    diulangi hingga didapatkan jam yang valid. */
    /* Contoh: 
    60 3 4
    Jam tidak valid
    1 3 4
    --> akan terbentuk TIME <1,3,4> */
    int h,m,s;
    for(;;){
        scanf("%d %d %d\n", &h,&m,&s);
        if (IsTIMEValid(h,m,s) == true){
            break;
        }else{
            printf("Jam tidak valid\n");
        }
    }
    CreateTime(T,h,m,s);
}

   
void TulisTIME (TIME T){
    /* I.S. : T sembarang */
    /* F.S. : Nilai T ditulis dg format HH:MM:SS */
    /* Proses : menulis nilai setiap komponen T ke layar dalam format HH:MM:SS
    tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
    printf("%02d:%02d:%02d", Hour(T), Minute(T), Second(T));
}


/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long TIMEToDetik (TIME T){
    /* Diberikan sebuah TIME, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
    /* Rumus : detik = 3600*HH + 60*MM + SS */
    /* Nilai maksimum = 3600*23+59*60+59 */
    long detik;
    detik = 3600*Hour(T) + 60*Minute(T) + Second(T);
    return detik;
}


TIME DetikToTIME (long N){
    /* Mengirim  konversi detik ke TIME */
    /* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
    mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
    N1 = N mod 86400, baru N1 dikonversi menjadi TIME */
    TIME TX;
    long N1,h,m,s,sisa;
    N = (N + 86400) % 86400;
    h = N / 3600;
    sisa = N % 3600;
    m = sisa / 60;
    s = sisa % 60;
    CreateTime(&TX,h,m,s);
    return TX;
}


/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean TEQ (TIME T1, TIME T2){
    /* Mengirimkan true jika T1=T2, false jika tidak */
    return((TIMEToDetik(T1)) == (TIMEToDetik(T2)));
}

boolean TNEQ (TIME T1, TIME T2){
    /* Mengirimkan true jika T1 tidak sama dengan T2 */
    return((TIMEToDetik(T1)) != (TIMEToDetik(T2)));
}

boolean TLT (TIME T1, TIME T2){
    /* Mengirimkan true jika T1<T2, false jika tidak */
    return((TIMEToDetik(T1)) < (TIMEToDetik(T2)));
}

boolean TGT (TIME T1, TIME T2){
    /* Mengirimkan true jika T1>T2, false jika tidak */
    return((TIMEToDetik(T1)) > (TIMEToDetik(T2)));
}

/* *** Operator aritmatika TIME *** */
TIME NextDetik (TIME T){
    /* Mengirim 1 detik setelah T dalam bentuk TIME */
    TIME TX;
    long N;
    N = TIMEToDetik(T);
    N += 1;
    TX = DetikToTIME(N);
    return TX;
}

TIME NextNDetik (TIME T, int N){
    /* Mengirim N detik setelah T dalam bentuk TIME */
    TIME TX;
    long temp;
    temp = TIMEToDetik(T);
    temp += N;
    TX = DetikToTIME(temp);
    return TX;
}

TIME PrevDetik (TIME T){
    /* Mengirim 1 detik sebelum T dalam bentuk TIME */
    TIME TX;
    long N;
    N = TIMEToDetik(T);
    if (N < 0){
        N += 86400;
    }
    N -= 1;
    TX = DetikToTIME(N);
    return TX;
}

TIME PrevNDetik (TIME T, int N){
    /* Mengirim N detik sebelum T dalam bentuk TIME */
    TIME TX;
    long temp;
    temp = TIMEToDetik(T);
    if (temp < 0){
        temp += 86400;
    }
    temp -= N;
    TX = DetikToTIME(temp);
    return TX;
}

/* *** Kelompok Operator Aritmetika *** */
long Durasi (TIME TAw, TIME TAkh){
    /* Mengirim TAkh-TAw dlm Detik, dengan kalkulasi */
    /* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */
    long durasi;
    if (TGT(TAkh,TAw)){
        durasi = (TIMEToDetik(TAkh)) - (TIMEToDetik(TAw));
    } else{
        durasi = (TIMEToDetik(TAkh)) + 86400 - (TIMEToDetik(TAw));
    }
    return durasi%86400;
}