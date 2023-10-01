#include <stdio.h>
#include "liststatik.h"

int main(){
    ListStatik l;
    CreateListStatik(&l);
    readList(&l);
    sortList(&l,true);
    printList(l);
}