#include <stdio.h>
#include "datetime.h"
#include "time.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
int GetMaxDay(int M, int Y){
    /* Mengirimkan jumlah hari maksimum pada bulan M dan tahun Y */
    /* Prekondisi: 1 <= M <= 12*/
    /* Hint: Perhatikan Leap Year. Leap Year adalah tahun dengan 29 hari pada bulan Februari */
    /* Aturan Leap Year: */
    /* 1. Jika angka tahun itu habis dibagi 400, maka tahun itu sudah pasti tahun kabisat. 8*/
    /* 2. Jika angka tahun itu tidak habis dibagi 400 tetapi habis dibagi 100, maka tahun itu sudah pasti bukan merupakan tahun kabisat. */
    /* 3. Jika angka tahun itu tidak habis dibagi 400, tidak habis dibagi 100 akan tetapi habis dibagi 4, maka tahun itu merupakan tahun kabisat. */
    /* 4. Jika angka tahun tidak habis dibagi 400, tidak habis dibagi 100, dan tidak habis dibagi 4, maka tahun tersebut bukan merupakan tahun kabisat. */
    int hari_max;
    boolean kabisat;
    kabisat = false;
    if ((Y%400 == 0)){
        kabisat = true;
    } else if ((Y%100 != 0) && (Y%4 == 0)){
        kabisat = true;
    }
    if (kabisat && M == 2) {
        hari_max = 29;
    } else if (M == 2) {
        hari_max = 28;
    } else if (M <= 7 && M % 2 != 0) {
        hari_max = 31;
    } else if (M <= 7) {
        hari_max = 30;
    } else if (M > 7 && M % 2 == 0) {
        hari_max = 31;
    } else {
        hari_max = 30;
    }
    return hari_max;
}

boolean IsDATETIMEValid(int D, int M, int Y, int h, int m, int s){
    /* Mengirim true jika D,M,Y,h,m,s dapat membentuk D yang valid */
    /* dipakai untuk mentest SEBELUM membentuk sebuah DATETIME */
    return(IsTIMEValid(h,m,s) && (D>=1) && (D<=(GetMaxDay(M,Y))) && (M>=1) && (M<=12) && (Y>=1900) && (Y<=2030));
}

/* *** Konstruktor: Membentuk sebuah DATETIME dari komponen-komponennya *** */
void CreateDATETIME(DATETIME *D, int DD, int MM, int YYYY, int hh, int mm, int ss){
    /* Membentuk sebuah DATETIME dari komponen-komponennya yang valid */
    /* Prekondisi : DD, MM, YYYY, h, m, s valid untuk membentuk DATETIME */
    TIME T;
    Day(*D) = DD;
    Month(*D) = MM;
    Year(*D) = YYYY;
    CreateTime(&T,hh,mm,ss);
    Time(*D) = T;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaDATETIME(DATETIME *D){
    /* I.S. : D tidak terdefinisi */
    /* F.S. : D terdefinisi dan merupakan DATETIME yang valid */
    /* Proses : mengulangi membaca komponen DD, MM, YY, h, m, s sehingga membentuk D */
    /* yang valid. Tidak mungkin menghasilkan D yang tidak valid. */
    /* Pembacaan dilakukan dengan mengetikkan komponen DD, MM, YY, h, m, s
    dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
    /* Jika DATETIME tidak valid maka diberikan pesan: "DATETIME tidak valid", dan pembacaan
        diulangi hingga didapatkan DATETIME yang valid. */
    /* Contoh:
        32 13 2023 12 34 56
        DATETIME tidak valid
        31 12 2023 12 34 56
        --> akan terbentuk DATETIME <31,12,2023,12,34,56> */
    int DD, MM, YY, h, m, s;
    for(;;){
        scanf("%d %d %d %d %d %d %d", &DD, &MM, &YY, &h, &m, &s);
        if (IsDATETIMEValid(DD, MM, YY, h, m, s) == true){
            break;
        } else{
            printf("DATETIME tidak valid");
        }
    }
    CreateDATETIME(D, DD, MM, YY, h, m, s);
}

void TulisDATETIME(DATETIME D){
    /* I.S. : D sembarang */
    /* F.S. : Nilai D ditulis dg format DD/MM/YYYY HH:MM:SS */
    /* Proses : menulis nilai setiap komponen D ke layar dalam format DD/MM/YYYY HH:MM:SS
    tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
    printf("%d/%d/%d ", Day(D), Month(D), Year(D));
    TulisTIME(Time(D));
}

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok operasi relasional terhadap DATETIME *** */
boolean DEQ(DATETIME D1, DATETIME D2){
    /* Mengirimkan true jika D1=D2, false jika tidak */
    return((Hour(Time(D1)) == (Hour(Time(D2)))) && (Minute(Time(D1)) == Minute(Time(D2))) && (Second(Time(D1)) == Second(Time(D2))) && (Day(D1) == Day(D2)) && (Month(D1) == Month(D2)) && (Year(D1) == Year(D2)));
    // return((TEQ(Time(D1),Time(D2))) && (Day(D1) == Day(D2)) && (Month(D1) == Month(D2)) && (Year(D1) == Year(D2)));
}

boolean DNEQ(DATETIME D1, DATETIME D2){
    /* Mengirimkan true jika D1 tidak sama dengan D2 */
    return(TNEQ(Time(D1),Time(D2)) || (Day(D1) != Day(D2)) || (Month(D1) != Month(D2)) || (Year(D1) != Year(D2)));
}

boolean DLT(DATETIME D1, DATETIME D2){
    /* Mengirimkan true jika D1<D2, false jika tidak */
    if (Year(D1) < Year(D2)) {
        return true;
    } else if ((Year(D1) == Year(D2)) && (Month(D1) < Month(D2))) {
        return true;
    } else if ((Year(D1) == Year(D2)) && (Month(D1) == Month(D2)) && Day(D1) < Day(D2)) {
        return true;
    } else if ((Year(D1) == Year(D2)) && (Month(D1) == Month(D2)) && (Day(D1) == Day(D2))) {
        return (TLT(Time(D1), Time(D2)));
    } else {
        return false;
    }
}

boolean DGT(DATETIME D1, DATETIME D2){
    /* Mengirimkan true jika D1>D2, false jika tidak */
    if (Year(D1) < Year(D2)) {
        return true;
    } else if ((Year(D1) == Year(D2)) && (Month(D1) > Month(D2))) {
        return true;
    } else if ((Year(D1) == Year(D2)) && (Month(D1) == Month(D2)) && Day(D1) > Day(D2)) {
        return true;
    } else if ((Year(D1) == Year(D2)) && (Month(D1) == Month(D2)) && (Day(D1) == Day(D2))) {
        return (TGT(Time(D1), Time(D2)));
    } else {
        return false;
    }
}

DATETIME DATETIMENextNDetik(DATETIME D, int N){
    /* Mengirim salinan D dengan detik ditambah N */
    int i;
    DATETIME DX;
    long int detikTahun, detikBulan, detikHari, detikTime, totalDetik, hari_bulan, detikSetelah;
    detikTahun = Year(D)*31536000;
    for (i = 0; i < Month(D); i++){
        hari_bulan += GetMaxDay(Month(D),Year(D));
    }
    detikBulan = hari_bulan*3600;
    detikHari = Day(D)*3600;
    detikTime = TIMEToDetik(Time(D));
    totalDetik = detikTahun + detikBulan + detikHari + detikTime;
    totalDetik += N;
    Year(DX) = totalDetik/31536000;
    for(;;){

    }
    for (i = 0; i < Month(D); i++){
        hari_bulan += GetMaxDay(Month(D),Year(D));
    }
    Month(DX) = (totalDetik%31536000);
    return DX;
}

DATETIME DATETIMEPrevNDetik(DATETIME D, int N){
    /* Mengirim salinan D dengan detik dikurang N */
    DATETIME DX;
    DX = D;
    Time(DX) = PrevNDetik(Time(D),N);
    return DX;
}

/* *** Kelompok Operator Aritmetika terhadap DATETIME *** */
long int DATETIMEDurasi(DATETIME DAw, DATETIME DAkh){
    /* Mengirim DAkh-DAw dlm Detik, dengan kalkulasi */
    /* Prekondisi: DAkh > DAw */
    // long int DetikDAw, DetikDAkh;
    // isKabisatDAw == false;
    // isKabisatDAkh == false;
    // year_jumlahDAw = 365;
    // year_jumlahDAkh = 365;
    // if (Year(DAw)%400 == 0){
    //     isKabisatDAw = true;
    // } else if ((Year(DAw) != 0) && (Year(DAw)%4 == 0)){
    //     isKabisatDAw = true;
    // }
    // if (isKabisatDAw == true){
    //     year_jumlahDAw = 366;
    // }
    // if (Year(DAkh)%400 == 0){
    //     isKabisatDAkh = true;
    // } else if ((Year(DAkh) != 0) && (Year(DAkh)%4 == 0)){
    //     isKabisatDAkh = true;
    // }
    // if (isKabisatDAkh == true){
    //     year_jumlahDAkh = 366;
    // }
    // DetikDAw = year_jumlahDAw*
    printf("p");
}
