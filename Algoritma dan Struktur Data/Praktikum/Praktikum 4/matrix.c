#include <stdio.h>
#include "boolean.h"
#include "matrix.h"
#include <math.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m){
    /* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
    /* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
    /* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
}


/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixIdxValid(int i, int j){
    /* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */
    return (i >= 0) && (i < ROW_CAP) && (j >= 0) && (j < COL_CAP);
}


/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRow(Matrix m){
    /* Mengirimkan Index baris terbesar m */
    return (ROW_EFF(m)-1);
}

IdxType getLastIdxCol(Matrix m){
    /* Mengirimkan Index kolom terbesar m */
    return (COL_EFF(m)-1);
}

boolean isIdxEff(Matrix m, IdxType i, IdxType j){
    /* Mengirimkan true jika i, j adalah Index efektif bagi m */
    return (i >= 0) && (i < ROW_EFF(m)) && (j >= 0) && (j < COL_EFF(m));
}

ElType getElmtDiagonal(Matrix m, IdxType i){
    /* Mengirimkan elemen m(i,i) */
    return ELMT(m,i,i);
}


/* ********** Assignment  Matrix ********** */
void copyMatrix(Matrix mIn, Matrix *mOut){
    /* Melakukan assignment mOut <- mIn */
    ROW_EFF(*mOut) = ROW_EFF(mIn);
    COL_EFF(*mOut) = COL_EFF(mIn);
    *mOut = mIn;
}


/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrix(Matrix *m, int nRow, int nCol){
    /* I.S. isIdxValid(nRow,nCol) */
    /* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
    /* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
    /* Selanjutnya membaca nilai elemen per baris dan kolom */
    /* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
    1 2 3
    4 5 6
    8 9 10 
    */
    int i,j;
    ElType elmt;
    createMatrix(nRow,nCol,m);
    for(i = 0; i < nRow; i++){
        for(j = 0; j < nCol; j++){
            scanf("%d", &elmt);
            ELMT(*m, i, j) = elmt;
        }
   }
}

void displayMatrix(Matrix m){
    /* I.S. m terdefinisi */
    /* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
    dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
    /* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
    /* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
    1 2 3
    4 5 6
    8 9 10
    */
    int i,j;
    for(i = 0; i < ROW_EFF(m); i++){
        for(j = 0; j < COL_EFF(m); j++){
            printf("%d", ELMT(m,i,j));
            if (j != COL_EFF(m)-1){
                printf(" ");
        }
    }
    if (i != ROW_EFF(m)-1){
        printf("\n");
    }
   }
   printf("\n");
}


/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
Matrix addMatrix(Matrix m1, Matrix m2){
    /* Prekondisi : m1 berukuran sama dengan m2 */
    /* Mengirim hasil penjumlahan matriks: m1 + m2 */
    Matrix mhasil;
    int i,j;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &mhasil);
    for(i = 0; i < ROW_EFF(m1); i++){
        for(j = 0; j < COL_EFF(m1); j++){
            ELMT(mhasil, i, j) = ELMT(m1, i, j) + ELMT(m2, i, j);
        }
   }
   return mhasil;
}

Matrix subtractMatrix(Matrix m1, Matrix m2){
    /* Prekondisi : m1 berukuran sama dengan m2 */
    /* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
    Matrix mhasil;
    int i,j;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &mhasil);
    for(i = 0; i < ROW_EFF(m1); i++){
        for(j = 0; j < COL_EFF(m1); j++){
            ELMT(mhasil, i, j) = ELMT(m1, i, j) - ELMT(m2, i, j);
        }
   }
   return mhasil;
}

Matrix multiplyMatrix(Matrix m1, Matrix m2){
    /* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
    /* Mengirim hasil perkalian matriks: salinan m1 * m2 */
    Matrix mhasil;
    int i,j,k;
    createMatrix(ROW_EFF(m1),COL_EFF(m2),&mhasil);
    for(i = 0; i < ROW_EFF(m2) ; i++){
        for(j = 0; j < COL_EFF(m1); j++){
            ELMT(mhasil,i,j) = 0;
            for(k=0 ; k < ROW_EFF(mhasil); k++){
                ELMT(mhasil,i,j) += ELMT(m1,i,k)*ELMT(m2,k,j);
            }
        }
    }
    return mhasil;
}

Matrix multiplyMatrixWithMod(Matrix m1,Matrix m2,int mod){
/* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
/* Mengirim hasil perkalian matriks: salinan (m1 * m2)%mod, artinya setiap elemen matrix hasil perkalian m1 * m2 dilakukan modulo terhadap mod */
    Matrix mhasil;
    mhasil = multiplyMatrix(m1,m2);
    int i,j;
    for(i = 0; i < ROW_EFF(mhasil) ; i++){
        for(j = 0; j < COL_EFF(mhasil); j++){
            ELMT(mhasil,i,j) = ELMT(mhasil,i,j)%mod;
        }
    }
    return mhasil;
}

Matrix multiplyByConst(Matrix m, ElType x){
    /* Mengirim hasil perkalian setiap elemen m dengan x */
    Matrix mhasil;
    int i,j;
    copyMatrix(m,&mhasil);
    for(i = 0; i < ROW_EFF(m) ; i++){
        for(j = 0; j < COL_EFF(m); j++){
            ELMT(mhasil,i,j) = ELMT(mhasil,i,j)*x;
        }
    }
    return mhasil;
}

void pMultiplyByConst(Matrix *m, ElType k){
    /* I.S. m terdefinisi, k terdefinisi */
    /* F.S. Mengalikan setiap elemen m dengan k */
    int i,j;
    for(i = 0; i < ROW_EFF(*m) ; i++){
        for(j = 0; j < COL_EFF(*m); j++){
            ELMT(*m,i,j) = ELMT(*m,i,j)*k;
        }
    }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */
boolean isMatrixEqual(Matrix m1, Matrix m2){
    /* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
    /* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
    /* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
    int i = 0,j = 0;
    boolean valid = true;
    if(countElmt(m1) != countElmt(m2)){
        valid = false;
    }
    while((valid)&&(i<ROW_EFF(m1))){
        while((valid)&&(j<COL_EFF(m1))){
            if (ELMT(m1, i, j) != ELMT(m2, i, j))
            {
                valid = false;
            }
            j +=1;
        }
        i += 1;
    }
    return valid;
}

boolean isMatrixNotEqual(Matrix m1, Matrix m2){
    /* Mengirimkan true jika m1 tidak sama dengan m2 */
    if (!isMatrixEqual(m1,m2)){
        return true;
    }
    else{
        return false;
    }
}

boolean isMatrixSizeEqual(Matrix m1, Matrix m2){
    /* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
    /* yaitu RowEff(m1) = RowEff (m2) dan ColEff (m1) = ColEff (m2) */
    return ((ROW_EFF(m1) == ROW_EFF(m2)) && (COL_EFF(m1) == COL_EFF(m2)));
}


/* ********** Operasi lain ********** */
int countElmt(Matrix m){
    /* Mengirimkan banyaknya elemen m */
    return ROW_EFF(m)*COL_EFF(m);
}


/* ********** KELOMPOK TEST TERHADAP Matrix ********** */
boolean isSquare(Matrix m){
    /* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
    return ROW_EFF(m) == COL_EFF(m);
}

boolean isSymmetric(Matrix m){
    /* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
    dan untuk setiap elemen m, m(i,j)=m(j,i) */
    int i, j;
    boolean valid = true;
    if (isSquare(m)){
        for(i = 0 ; i <ROW_EFF(m); i++){
            for(j = 0; j < COL_EFF(m); j++){
                if (ELMT(m,i,j) != ELMT(m,j,i)){
                    valid = false;
                }
            }
        }
    }
    else{
        valid = false;
    }
    return valid;
}

boolean isIdentity(Matrix m){
    /* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
    setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
    int i, j;
    boolean valid = true;
    if (isSquare(m)){
        for(i = 0 ; i <ROW_EFF(m); i++){
            for(j = 0; j < COL_EFF(m); j++){
                if (i == j){
                    if (ELMT(m,i,j) != 1){
                        valid = false;
                    }
                else{
                    if (ELMT(m,i,j) != 0){
                        valid = false;
                    }
                }     
                }
            }
        }
    }
    else{
        valid = false;
    }
    return valid;
}

boolean isSparse(Matrix m){
    /* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
    hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
    int i,j;
    int sum = 0;
    for(i = 0; i < ROW_EFF(m) ; i++){
        for(j = 0; j < COL_EFF(m); j++){
            if(ELMT(m,i,j) != 0){
                sum += 1;
            }
        }
    }
    if((sum) <= (0.05*countElmt(m))){
        return true;
    }
    else{
        return false;
    }
}

Matrix negation(Matrix m){
    /* Menghasilkan salinan m dengan setiap elemen dinegasikan (dikalikan -1) */
    Matrix mhasil;
    copyMatrix(m,&mhasil);
    multiplyByConst(mhasil,-1);
    return mhasil;
}

void pNegation(Matrix *m){
    /* I.S. m terdefinisi */
    /* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
    pMultiplyByConst(m,-1);
}
Matrix minorMatriks(Matrix m, int row, int col){
    Matrix mhasil;
    int i,j,idx_row,idx_col;
    createMatrix(ROW_EFF(m)-1, COL_EFF(m)-1, &mhasil);
    idx_row = 0;
    for(i = 0; i<COL_EFF(m); i++){
        if(i!= row){
            idx_col = 0;
            for(j = 0; j<ROW_EFF(m); j++){
                if(j!=col){
                    ELMT(mhasil, idx_row, idx_col) = ELMT(m, i, j);
                    idx_col +=1;
                }
            }
            idx_row +=1;
        }
    }
    return mhasil;
}
float determinant(Matrix m){
    /* Prekondisi: isSquare(m) */
    /* Menghitung nilai determinan m */
    int i;
    float det;
    int sign = 1;
    if(ROW_EFF(m) == 1){
        return ELMT(m,0,0);
    }
    det = 0;
    for(i=0; i<COL_EFF(m); i++){
        det += sign*ELMT(m,0,i)*determinant(minorMatriks(m,0,i));
        sign = sign*(-1);
    }
    return det;
}

// float determinant(Matrix m){
//     /* Prekondisi: isSquare(m) */
//     /* Menghitung nilai determinan m */
//     Matrix mhasil;
//     int a,i,j,k,l;
//     int currCol = 0;
//     int banyak_tukeran = 0;
//     int currRow,temp;
//     createMatrix(ROW_EFF(m), COL_EFF(m), &mhasil);
//     copyMatrix(m,&mhasil);
//     float dikurang;    
//     for(i = 0; i < ROW_EFF(mhasil); i++){
//         currRow = 0;
//         boolean tuker = true;
//         while(tuker){
//             if(ELMT(mhasil,i,currCol) != 0){
//                 tuker = false;
//             }
//             else{
//                 if(ELMT(mhasil,currRow,currCol) != 0){
//                     for(j = 0; j<COL_EFF(mhasil); j++){
//                         temp = ELMT(mhasil,currRow,j);
//                         ELMT(mhasil,currRow,j) = ELMT(mhasil,i,j);
//                         ELMT(mhasil,i,j) = temp;
//                     banyak_tukeran += 1;
//                     tuker = false;
//                     }
//                 }
//             }
//             currRow += 1;
//         }
//         for(k = i+1; k<ROW_EFF(mhasil); k++){
//             if (ELMT(mhasil,k,currCol) != 0){
//                 dikurang = ELMT(mhasil,k,currCol)/ELMT(mhasil,i,currCol);
//                 for(l = 0; l < COL_EFF(mhasil); l++){
//                     ELMT(mhasil,k,l) = ELMT(mhasil,k,l) - dikurang*ELMT(mhasil,i,l);
//                     printf("baris ke :%d\n", k+1);
//                     printf("step ke :%d\n", l+1);
//                     displayMatrix(mhasil);
//                     printf("\n");
//                     printf("\n");
//                 }
//             }
            
//         }
//         currCol += 1;
//     }
    
//     float product = 1;
//     for(a = 0; a < ROW_EFF(m); a ++){
//         product = product*(getElmtDiagonal(mhasil,a));
//     }
//     float det = pow(-1,banyak_tukeran)*(product);
//     return det;
// }

Matrix transpose(Matrix m){
    /* I.S. m terdefinisi dan IsSquare(m) */
    /* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
    Matrix mhasil;
    int i,j;
    createMatrix(COL_EFF(m), ROW_EFF(m), &mhasil);
    for(i = 0; i < ROW_EFF(m) ; i++){
        for(j = 0; j < COL_EFF(m); j++){
            ELMT(mhasil,j,i) = ELMT(m,i,j);
        }
    }
    return mhasil;
}

void pTranspose(Matrix *m){
    /* I.S. m terdefinisi dan IsSquare(m) */
    /* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
    Matrix mhasil;
    createMatrix(ROW_EFF(*m), COL_EFF(*m), &mhasil);
    copyMatrix(*m,&mhasil);
    mhasil = transpose(mhasil);
    copyMatrix(mhasil,m);
}
