#include <stdio.h>
#include "stack.h"

void SortirKeranjang (Stack * S1, Stack * S2){
    /* Menyortir keranjang S1 menggunakan bantuan S2 */
    /* I.S. S1 tidak terurut dan S2 kosong */
    /* F.S. S1 kosong dan S2 terurut */
    /* Contoh: */
    /* TOP */
    /* I.S. S1 = [23, 92, 98, 31, 3, 34]; S2 = [] */
    /* TOP */
    /* I.S. S1 = []; S2 = [3, 23, 31, 34, 92, 98] */
    int max;
    int i;
    while(!IsEmpty(*S1)){
        infotype temp1;
        Pop(S1,&temp1);
        while (temp1>InfoTop(*S2) && !IsEmpty(*S2)){
            infotype temp2;
            Pop(S2,&temp2);
            Push(S1,temp2);
        }
        Push(S2,temp1);
        
    }
    // do{
    //     int count = 0;
    //     Pop(S1,&temp);
    //     if (temp>InfoTop(*S2)){
    //         while((temp>InfoTop(*S2)) && (!IsEmpty(*S2))){
    //             Pop(S2,&temp2);
    //             Push(S1,temp2);
    //             count +=1;
    //         }
    //         Push(S2,temp);
    //         for(i = 0; i <= count; i++){
    //             Pop(S1,&temp2);
    //             Push(S2,temp2);
    //         }
    //     }else{
    //         Push(S2,temp);
    //     }
    // }while (!IsEmpty(*S1));
}

int main() {
    // Initialize S1 and S2 and perform sorting
    Stack S1, S2;
    CreateEmpty(&S1);
    Push(&S1, 23);
    Push(&S1, 92);
    Push(&S1, 98);
    Push(&S1, 31);
    Push(&S1, 3);
    Push(&S1, 34);

    SortirKeranjang(&S1, &S2);

    // Print the sorted elements from S2
    while (!IsEmpty(S2)) {
        infotype temp;
        Pop(&S2, &temp);
        printf("%d ", temp);
    }

    return 0;
}

// int main(){
//     Stack s1,s2;
//     CreateEmpty(&s1);
//     CreateEmpty(&s2);
//     Push(&s1,1);
//     Push(&s1,1);
//     Push(&s1,1);
//     SortirKeranjang(&s1,&s2);
//     return 0;
// }