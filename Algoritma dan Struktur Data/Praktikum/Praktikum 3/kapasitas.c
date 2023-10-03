#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "listdin.h"
#include <math.h>

int main(){
    ListDin l;
    int tipe,n,i;
    ElType last;
    CreateListDin(&l,0);
    scanf("%d",&n);
    for(i=0 ; i < n ; i ++){
        scanf("%d",&tipe);
        if(tipe==1){
            int x;
            scanf("%d",&x);
            if (NEFF(l)== 0){
                expandList(&l, 1);
            } else if(isFull(l)){
                expandList(&l, CAPACITY(l));
            }
            insertLast(&l,x);
        }else if(tipe==2){
            deleteLast(&l, &last);
            if (NEFF(l) <= round(CAPACITY(l)/2)){
                shrinkList(&l, round(CAPACITY(l)/2));
            }
        }else{
            printf("%d ", CAPACITY(l));
            printList(l);
            printf("\n");
        }
    }
    
}