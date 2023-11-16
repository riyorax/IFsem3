#include <stdio.h>

int fibonacci(int n){
    if(n == 0){
        return 0;
    }else if(n == 1){
        return 1;
    }else{
        return fibonacci(n-1) + fibonacci(n-2);
    }
}

void Sky_Street(){
    int a,b;
    scanf("%d %d", &a,&b);
    int check = fibonacci(a);
    if(b != check){
        illegal_move();
    }else{
        printf("Upon traversing the sky street you started to realize something and that the key lies on the ##@64#$#");
    }
}