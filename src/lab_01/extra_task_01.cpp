#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstdint>
#include <errno.h>
#include <cerrno>

#include <string.h>
#include <stdlib.h>

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

static void pclock(clockid_t cid) {
    struct timespec ts;
    clock_gettime(cid, &ts);
    printf("Clocktime value: ");
    printf("%4jd.%03ld\n", (intmax_t)ts.tv_sec, ts.tv_nsec / 10000);
}


int main() {
    printf("Program started\n");

    bool flag1 = false;
    bool flag2 = false;
    pthread_t id1;
    pthread_t id2;
    clockid_t cid1;
    clockid_t cid2;
    int* exitcode1;
    int* exitcode2;

    pthread_create(&id1, nullptr, proc1, &flag1);
    pthread_create(&id2, nullptr, proc2, &flag2);

    printf("Main thread consuming some CPU time...\n");
    for (int j = 0; j < 2000000; j++)
         getppid();
    pclock(CLOCK_PROCESS_CPUTIME_ID);

    pthread_getcpuclockid(id1, &cid1);
    pthread_getcpuclockid(id2, &cid2);

    printf("Program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    flag1 = true;
    flag2 = true;


    pclock(cid1);
    pthread_join(id1, (void**)&exitcode1);
    printf("Thread 1 finished with exit code: %p\n", (void*)exitcode1);
    pclock(cid2);
    pthread_join(id2, (void**)&exitcode2);
    printf("Thread 2 finished with exit code: %p\n", (void*)exitcode2);

    printf("Program finished\n");
    return 0;
}
