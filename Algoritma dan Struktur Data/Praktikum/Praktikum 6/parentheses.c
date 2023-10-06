#include <stdio.h>
#include "stack.h"
#include "wordmachine.h"
#include "charmachine.h"

void readWord(Word *input) {
    int i;
    START();
    IgnoreBlanks();

    (*input).Length = 0;
    i = 0;

    while ((currentChar != MARK) && (i < NMax)) {
        (*input).TabWord[i] = currentChar;
        ADV();
        i++;
    }

    (*input).Length = i;

    (*input).TabWord[i] = '\0';
}

int main(){
    Word in;
    Stack s;
    infotype val;
    CreateEmpty(&s);
    readWord(&in);
    int i;
    int count;
    while(in.TabWord[i] != '\0'){
        if(in.TabWord[i] = '('){
            Push(&s,in.TabWord[i]);
        }else{
            Pop(&s,&val);
            count +=1;
        }
        i+=1;
    }
    if(!IsEmpty(s)){
        printf("-1\n");
    }else{
        printf("%d\n", count);
    }
    return 0;
}
