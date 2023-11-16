#include <stdio.h>

void Metropolis(int input){
    if(input < 1 || input > 9){
        illegal_move();
    }
    int input2,compare;
    scanf("%d", &input);
    switch (input){
        case 2:
            compare = 696;
            break;
        case 3:
            compare = 678;
            break;
        case 4:
            compare = 1150;
            break;
        case 5:
            compare = 530;
            break;
        case 6:
            compare = 620;
            break;
        case 7:
            compare = 395;
            break;
        case 8:
            compare = 560;
            break;
        case 9:
            compare = 395;
            break;
    }
    if(compare != input2){
        illegal_move();
    }else{
        printf("Kurohime's metropolis has been conquered. The street above the sky awaits.");
    }
    return;
}