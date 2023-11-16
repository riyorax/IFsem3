#include <stdio.h>
#define true 1
#define false 0

void Black_Rose(char *input){
    int a[6];
    read_six_numbers(input, a);
    if (a[0] != 1){
        illegal_move();
    }
    int valid = true;
    int i = 0;
    while(valid && i <6){
        if(a[i] != function(i+1)){
            valid = false;
        }
        i++;
    }
    if (!valid){
        illegal_move();
    }else{
        printf("Looks like it's too easy huh? The second area is still merely warm-up.");
    }
}

int function(int n){
    if (n == 1){
        return 1;
    }
    else if (n == 2){
        return 2;
    }
    else{
        if (n%2 == 0){
            return (n-1)+function(n-1);
        }
        else{
            return (n-1)*function(n-1);
        }
    }
}