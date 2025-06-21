#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h> 


bool done = false;
void *T_loop(void* nothing) {
    while (!done);
}
void *T_setbool(void* nothing) {
    done = true;
}
int main() {
    pthread_t threads[2];
    pthread_create(&threads[0], NULL, T_loop,  NULL);
    pthread_create(&threads[1], NULL, T_setbool,  NULL);
    for (int i=0; i < 2; i++){ pthread_join(threads[i], NULL);}
    printf("main stop");
}
