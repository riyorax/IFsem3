#include <stdio.h>
#include "charmachine.h"
#include "wordmachine.h"

int printWord(Word word) {
   int i;
   for (i = 0; i < word.Length; i++) {
      printf("%c", word.TabWord[i]);
   }
}

int stringLength(char *s) {
   int result =  0;
   int i = 0;
   while (s[i] != '\0') {
      ++result;
      ++i;
   }
   return result;
}

boolean isWordEq(Word currWord, char* kata){
    int i = 0;
    boolean valid = true;
    while (i < currentWord.Length && valid){
        if (currentWord.TabWord[i] != kata[i]){
            valid = false;
        }else{
            i +=1;
        }
    }
    return valid;
}

int main(){
    Word n;
    STARTWORD();
    n = currentWord;
    ADVWORD();
    if(isWordEq(currentWord, "MOVEUP")){
        printf("Moving ");
        printWord(n);
        printf(" square upwards\n");
    }else if (isWordEq(currentWord, "MOVEDOWN")){
        printf("Moving ");
        printWord(n);
        printf(" square downwards\n");
    }else if (isWordEq(currentWord, "MOVELEFT")){
        printf("Moving ");
        printWord(n);
        printf(" square leftwards\n");
    }else{
        printf("Moving ");
        printWord(n);
        printf(" square rightwards\n");
    }
    // STARTWORD();
    // if(isWordEq(currentWord,"asep")){
    //     printf("asep is ril cuy");
    // }
    
}