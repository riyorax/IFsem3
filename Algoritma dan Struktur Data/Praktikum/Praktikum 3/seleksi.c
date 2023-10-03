#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "listdin.h"
#include <math.h>

int main(){
    ListDin l;
    int kapasitas, n, i, query;
    scanf("%d", &kapasitas);
    CreateListDin(&l, kapasitas);
    scanf("%d", &n);
    for(i = 0 ; i <n ; i++){
        scanf("%d", &query);
        if (query == 1){
            int x,i,j;
            scanf("%d",&x);
            for(i = 0; i < NEFF(l) ; i++){
                if (ELMT(l,i) < x){
                    for(j = i ; j < NEFF(l); j++){
                        ELMT(l,j) = ELMT(l,j+1);
                    }
                    NEFF(l) -= 1;
                }
                if (ELMT(l,getLastIdx(l)) < x){
                    NEFF(l) -= 1;
                }
            }
            insertLast(&l,x);
        }else {
            printf("%d\n", NEFF(l));
            printList(l);
            printf("\n");
        }
    }
    return 0;
}