#include <pthread.h>
#include <unistd.h>

#include <cstdio>

static void* proc1(void* arg) {
    printf("Thread 1 started\n");
    bool* flag = (bool*)arg;
    while (!(*flag)) {
        printf("1\n");
        fflush(stdout);
        sleep(1);
    }
    pthread_exit((void*)3);
}

static void* proc2(void* arg) {
    printf("Thread 2 started\n");
    bool* flag = (bool*)arg;
    while (!(*flag)) {
        printf("2\n");
        fflush(stdout);
        sleep(1);
    }
    pthread_exit((void*)4);
}

int main() {
    printf("Program started\n");

    bool flag1 = false;
    bool flag2 = false;
    pthread_t id1;
    pthread_t id2;
    int* exitcode1;
    int* exitcode2;

    pthread_create(&id1, nullptr, proc1, &flag1);
    pthread_create(&id2, nullptr, proc2, &flag2);

    printf("Program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    flag1 = true;
    flag2 = true;

    pthread_join(id1, (void**)&exitcode1);
    printf("Thread 1 finished with exit code: %p\n", (void*)exitcode1);
    pthread_join(id2, (void**)&exitcode2);
    printf("Thread 2 finished with exit code: %p\n", (void*)exitcode2);

    printf("Program finished\n");
    return 0;
}
