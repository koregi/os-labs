#include <iostream>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    bool flag;
    int exitcode;
} targs;

static void* proc1(void *arg) {
    printf("Thread 1 started\n");
    fflush(stdout);
    targs *args = (targs*) arg;
    while (!args->flag) {
        printf("1\n");
	fflush(stdout);
	sleep(1);
    }
    pthread_exit((void*)&(args->exitcode));
}

static void* proc2(void *arg) {
    printf("Thread 2 started\n");
    fflush(stdout);
    targs *args = (targs*) arg;
    while (!args->flag) {
        printf("2\n");
	fflush(stdout);
	sleep(1);
    }
    pthread_exit((void*)&(args->exitcode));
}

int main() {
    printf("Program started\n");

    pthread_t id1;
    pthread_t id2;
    targs arg1;
    targs arg2;
    int* exitcode1;
    int* exitcode2;

    arg1.flag = 0;
    arg1.exitcode = 3;
    arg2.flag = 0;
    arg2.exitcode = 4;

    pthread_create(&id1, NULL, proc1, &arg1);
    pthread_create(&id2, NULL, proc2, &arg2);

    printf("Program is waiting for a keystroke\n");
    fflush(stdout);
    getchar();
    printf("Key pressed\n");
    fflush(stdout);
    arg1.flag = 1;
    arg2.flag = 1;

    pthread_join(id1, (void**)&exitcode1);
    printf("Thread 1 finished with exit code: %u\n", *exitcode1);
    fflush(stdout);
    pthread_join(id2, (void**)&exitcode2);
    printf("Thread 2 finished with exit code: %u\n", *exitcode2);
    fflush(stdout);

    printf("Program finished\n");
    fflush(stdout);
    return 0;
}
