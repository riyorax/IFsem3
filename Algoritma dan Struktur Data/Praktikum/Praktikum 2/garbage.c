#include <stdio.h>
#include "liststatik.h"

int main(){
    ListStatik Lrumah,Lperjalanan;
    int i,besi,kertas,gelas;
    readList(&Lrumah);
    readList(&Lperjalanan);
    if(indexOf(Lrumah,1) != IDX_UNDEF){
        for(i = 0; i < listLength(Lrumah); i++){
            if(ELMT(Lrumah,i) == 1){
                besi +=1;
            }
            if(i != 0){
                besi += ELMT(Lperjalanan,i-1);
            }
        }
    }
    if(indexOf(Lrumah,2) != IDX_UNDEF){

    }
    if(indexOf(Lrumah,3) != IDX_UNDEF){

    }
    return 0;
}