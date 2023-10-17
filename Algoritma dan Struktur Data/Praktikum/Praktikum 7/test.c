#include <stdio.h>
#include "queue.h"
#include "boolean.h"

int main(){
    Queue q;
    CreateQueue(&q);
    enqueue(&q,1);
    enqueue(&q,20);
    enqueue(&q,30);
    displayQueue(q);
    return 0;
}