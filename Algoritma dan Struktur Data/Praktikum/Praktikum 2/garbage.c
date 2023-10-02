#include <stdio.h>
#include "liststatik.h"

int lastHouse(ListStatik l, int tipe){
    int idxHouse = 0;
    int i;
    for(i=0; i <= getLastIdx(l); i++){
        if (ELMT(l,i) == tipe){
            idxHouse = i;
        }
    }
    return idxHouse;
}

int totalTravelTime(ListStatik l, int idxLast){
    idxLast -=1;
    int i;
    int time = 0;
    for(i= 0; i <= idxLast; i++){
        time += ELMT(l,i);
    }
    time = time*2;
    return time;
}

int main(){
    ListStatik Lrumah,Lperjalanan;
    int i,besi = 0,kertas = 0,gelas = 0;
    readList(&Lrumah);
    readList(&Lperjalanan);
    if(indexOf(Lrumah,1) != IDX_UNDEF){
        for(i = 0; i <= lastHouse(Lrumah,1); i++){
            if(ELMT(Lrumah,i) == 1){
                besi +=1;
            }
        }
        besi += totalTravelTime(Lperjalanan,lastHouse(Lrumah,1));
    }
    if(indexOf(Lrumah,2) != IDX_UNDEF){
        for(i = 0; i <= lastHouse(Lrumah,2); i++){
            if(ELMT(Lrumah,i) == 2){
                kertas +=1;
            }
        }
        kertas += totalTravelTime(Lperjalanan,lastHouse(Lrumah,2));
    }
    if(indexOf(Lrumah,3) != IDX_UNDEF){
        for(i = 0; i <= lastHouse(Lrumah,3); i++){
            if(ELMT(Lrumah,i) == 3){
                gelas +=1;
            }
        }
        gelas += totalTravelTime(Lperjalanan,lastHouse(Lrumah,3));
    }
    int totalTime = besi+kertas+gelas;
    printf("%d\n", totalTime);
    return 0;
}