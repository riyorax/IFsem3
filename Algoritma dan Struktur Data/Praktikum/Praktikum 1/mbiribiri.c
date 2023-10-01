#include <stdio.h>
#include "point.h"
#include "garis.h"

int main(){
    GARIS Wolf;
    POINT Sheep;
    int harus_diselamatkan, b, n, i;
    harus_diselamatkan = 0;
    scanf("%d", &b);
    BacaGARIS(&Wolf);
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        BacaPOINT(&Sheep);
        if (JarakGARIS(Wolf,Sheep) <= b){
            harus_diselamatkan += 1;
        }
    }
    printf("%d\n", harus_diselamatkan);
    return 0;
}