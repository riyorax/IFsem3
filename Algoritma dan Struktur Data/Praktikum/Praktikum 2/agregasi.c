#include <stdio.h>
#include "liststatik.h"

int main(){
    ListStatik L;
    int i,x,idx,max,min, idx_median,idx_median2;
    float avg;
    int sum = 0;
    float median;
    readList(&L);
    sortList(&L,true);
    scanf("%d\n", &x);
    for(i= 0 ; i<listLength(L) ; i++){
        sum = sum + ELMT(L,i);
    }
    avg = sum/(float)listLength(L);
    idx = indexOf(L,x);
    extremeValues(L,&max,&min);
    printList(L);
    printf("\n");
    // printf("panjang: %d sum: %d\n", listLength(L), sum);
    printf("Average: %.2f\n", avg);
    if (listLength(L)%2 != 0){
        idx_median = (listLength(L)/2);
        median = ELMT(L,idx_median);
    } else{
        idx_median = (listLength(L)/2)-1;
        median = ELMT(L,idx_median);
    }
    if(idx != IDX_UNDEF){
        printf("%d\n",idx);
        if(x == max){
            printf("X maksimum\n");
        }
        if(x == min){
            printf("X minimum\n");
        }
        if(x == median){
            printf("X median\n");
        }
    } else{
        printf("%d tidak ada\n", x);
    }
    return 0;
}