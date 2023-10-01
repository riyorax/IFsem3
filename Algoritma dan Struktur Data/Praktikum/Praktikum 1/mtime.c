#include <stdio.h>
#include "time.h"

int main(){
    int banyakPengulangan, i;
    long durasi;
    TIME T1, T2, Tmax, Tmin;
    CreateTime(&Tmax, 0, 0, 0);
    CreateTime(&Tmin, 23, 59, 59);
    scanf("%d", &banyakPengulangan);
    for (i = 0; i < banyakPengulangan; i++){
        printf("[%d]\n", i+1);
        BacaTIME(&T1);
        BacaTIME(&T2);
        // if (i == 0){
        //     if (TLT(T1,T2)){
        //         Tmin = T1;
        //         Tmax = T2;
        //     } else{
        //         Tmin = T2;
        //         Tmax = T1;
        //     }
        // }
        if(TLT(T1,T2)){
            durasi = Durasi(T1,T2);
            if(TLT(T1,Tmin)){
                Tmin = T1;
            }
            if(TGT(T2,Tmax)){
                Tmax = T2;
            }
        }else{
            durasi = Durasi(T2,T1);
            if(TLT(T2,Tmin)){
                Tmin = T2;
            }
            if(TGT(T1,Tmax)){
                Tmax = T1;
            }
        }
        printf("%ld\n", durasi);
    }
    printf("%d:%d:%d\n", Hour(Tmin), Minute(Tmin), Second(Tmin));
    printf("%d:%d:%d\n", Hour(Tmax), Minute(Tmax), Second(Tmax));
    return 0;
}