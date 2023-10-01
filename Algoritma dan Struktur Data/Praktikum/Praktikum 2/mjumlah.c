#include <stdio.h>
#include "liststatik.h"

int main(){
    ListStatik L1,L2,L3;
    int i, j, element, temp;
    readList(&L1);
    readList(&L2);
    CreateListStatik(&L3);
    if (listLength(L1)>= listLength(L2)){
        j = 0;
        temp = 0;
        for(i=getLastIdx(L2); i >= getFirstIdx(L2) ; i--){
            element = ELMT(L1,getLastIdx(L1)-j)+ ELMT(L2,i) +temp;
            if(element >= 10){
                temp = element/10;
                element = element%10;
            }
            insertFirst(&L3, element);
            j +=1;
        }
        for (i = getLastIdx(L1)-j; i >=getFirstIdx(L1) ; i--){
            insertFirst(&L3, ELMT(L1,i));
            temp = 0;
        }
        if(temp>0){
            insertFirst(&L3, temp);
        }
    } else{
        j = 0;
        temp = 0;
        for(i=getLastIdx(L1); i >= getFirstIdx(L1) ; i--){
            element = ELMT(L2,getLastIdx(L2)-j)+ ELMT(L1,i) +temp;
            if(element >= 10){
                temp = element/10;
                element = element%10;
            }
            insertFirst(&L3, element);
            j +=1;
        }
        for (i = getLastIdx(L2)-j; i >=getFirstIdx(L2) ; i--){
            insertFirst(&L3, ELMT(L2,i));
            temp = 0;
            j -=1;
        }
        if(temp>0){
            insertFirst(&L3, temp);
        }
    }
    printList(L3);
    printf("\n");
    return 0;
}