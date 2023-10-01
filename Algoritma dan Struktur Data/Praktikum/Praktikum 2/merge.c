#include <stdio.h>
#include "liststatik.h"

int main(){
    ListStatik L1,L2;
    int i;
    readList(&L1);
    readList(&L2);
    for(i = 0; i < listLength(L2); i++){
        insertLast(&L1,ELMT(L2,i));
    }
    sortList(&L1,true);
    printList(L1);
    printf("\n");
    return 0;
}