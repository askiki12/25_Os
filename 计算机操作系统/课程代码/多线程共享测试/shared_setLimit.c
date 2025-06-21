#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <sys/resource.h>

#define N 1000000000
#define NUMBER_OF_THREADS 2

long sum = 0;

void *T_1(void* nothing) {
    struct rlimit rl;

    getrlimit(RLIMIT_DATA, &rl);
    printf("Current heap space limit: %llu bytes\n", (unsigned long long)rl.rlim_cur);

    rl.rlim_cur = 1024 * 1024 *50; // 设置堆空间大小为50MB
    setrlimit(RLIMIT_DATA, &rl);

    getrlimit(RLIMIT_DATA, &rl);
    printf("New heap space limit: %llu bytes\n", (unsigned long long)rl.rlim_cur);

    char *ptr = malloc(1024 * 1024 *  1024);

    if (ptr == NULL) {
        printf("Thread 1 Failed to allocate memory!\n");
    }
}

void *T_2(void* nothing) {
   for (int i = 0; i < N; i++)
      sum ++;

    char *ptr = malloc(1024 * 1024 *  1024);

    if (ptr == NULL) {
        printf("Thread 2 Failed to allocate memory!\n");
    }
}



int main() {
    pthread_t threads[NUMBER_OF_THREADS];
    pthread_create(&threads[0], NULL, T_1,  NULL);
    pthread_create(&threads[1], NULL, T_2,  NULL);
    for (int i=0; i < NUMBER_OF_THREADS; i++){ pthread_join(threads[i], NULL);}

    printf("main stop\n");
}
