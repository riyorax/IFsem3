#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "listlinier.h"

boolean isInList(List l, int x){
    Address p = FIRST(l);
    boolean found = false;
    int i = 0;
    while(p != NULL && !found){
        if(INFO(p) == x){
            found = true;
        }
        else{
            p = NEXT(p);
        }
    }
    return found;
}

int main(){
    int capacity;
    int count = 0;
    int miss = 0;
    int hit = 0;
    int temp;
    List l;
    CreateList(&l);
    scanf("%d", &capacity);
    int n;
    scanf("%d", &n);
    int i;
    for(i = 0; i < n; i++){
        int x;
        scanf("%d", &x);
        if (count<capacity){
            if(!isInList(l,x)){
                insertFirst(&l,x);
                printf("miss ");
                displayList(l);
                printf("\n");
                miss +=1;
                count +=1;
            }else{
                int idx = indexOf(l,x);
                deleteAt(&l, idx, &temp);
                insertFirst(&l,x);
                printf("hit ");
                displayList(l);
                printf("\n");
                hit +=1;
            }
        }else{
            if(!isInList(l,x)){
                deleteLast(&l,&temp);
                insertFirst(&l,x);
                printf("miss ");
                displayList(l);
                printf("\n");
                miss +=1;
            }else{
                if(!isEmpty(l)){
                    int idx = indexOf(l,x);
                    deleteAt(&l, idx, &temp);
                    printf("hit ");
                    displayList(l);
                    printf("\n");
                    hit +=1;
                }else{
                    int idx = indexOf(l,x);
                    printf("miss ");
                    displayList(l);
                    printf("\n");
                    hit +=1;
                }
                
            }
        }
    }
    if(hit+miss == 0){
        printf("hit ratio: 0.00\n");
    }else{
        float ratio = (float) hit/(hit+miss);
        printf("hit ratio: %0.2f\n", ratio);
    }
}