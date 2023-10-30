#include <stdio.h>
#include "charmachine.h"
#include "wordmachine.h"

int printWord(Word word) {
   int i;
   for (i = 0; i < word.Length; i++) {
      printf("%c", word.TabWord[i]);
   }
}

int main(){
    START();
    IgnoreBlanks();
    int i =0;
    while(currentChar != MARK){
        currentWord.TabWord[i] = currentChar;
        i +=1;
        ADV();
    }
    currentWord.Length = i;
    printWord(currentWord);
    printf("\n");
    printf("%d\n", currentWord.Length);
}