#include <iostream>
#include <pthread.h>
#include <unistd.h>

bool flag1 = 0;
bool flag2 = 0;

static void* proc1(void *arg) {
    printf("Thread 1 started\n");
    while (!flag1) {
        printf("1\n");
	fflush(stdout);
	sleep(1);
    }
    pthread_exit((void*)3);
}

static void* proc2(void *arg) {
    printf("Thread 2 started\n");
    while (!flag2) {
        printf("2\n");
	fflush(stdout);
	sleep(1);
    }
    pthread_exit((void*)4);
}

int main() {
    printf("Program started\n");

    pthread_t id1;
    pthread_t id2;
    int* exitcode1;
    int* exitcode2;

    pthread_create(&id1, NULL, proc1, NULL);
    pthread_create(&id2, NULL, proc2, NULL);

    printf("Program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    flag1 = 1;
    flag2 = 1;

    pthread_join(id1, (void**)&exitcode1);
    printf("Thread 1 finished with exit code: %p\n", exitcode1);
    pthread_join(id2, (void**)&exitcode2);
    printf("Thread 2 finished with exit code: %p\n", exitcode2);

    printf("Program finished\n");
    return 0;
}
