#include <stdio.h>
#define true 1
#define false 0

void Beginning(char *input)
{
    int bool = strings_not_equal(input, "Tubes yang lain jangan dilupakan yak wahai para praktikan kesayanganku, mwah");
    if (bool != false){
        illegal_move();
    }else{
        printf("Congratulations, you passed the first are. Feeling satisfied?");
    }
    return;
}