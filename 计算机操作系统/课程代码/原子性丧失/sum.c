#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>

#define N 100000000
#define NUMBER_OF_THREADS 2

long sum = 0;

void *T_sum(void* nothing) {
    for (int i = 0; i < N; i++) {
        sum++;
        // Won't work even if we force a single-instruction increment.
        // asm volatile(
        //     "incq %0" : "+m"(sum)
        // );
    }
}

int main() {
    pthread_t threads[NUMBER_OF_THREADS];
    pthread_create(&threads[0], NULL, T_sum,  NULL);
    pthread_create(&threads[1], NULL, T_sum,  NULL);
    for (int i=0; i < NUMBER_OF_THREADS; i++){ pthread_join(threads[i], NULL);}

    printf("sum = %ld\n", sum);
    printf("2*n = %ld\n", 2L * N);
}
