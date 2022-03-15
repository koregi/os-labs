#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include <cstdio>


struct args_t {
    bool flag{false};
    sem_t sem{};
};

static void* proc1(void* arg) {
    printf("Thread 1 started\n");
    args_t* args = (args_t*)arg;
    while (!(args->flag)) {
        sem_wait(&args->sem);
        printf("Semaphore captured by thread 1\n");
        for (size_t idx = 0; idx < 6; ++idx) {
            printf("1\n");
            fflush(stdout);
            sleep(1);
        }
        sem_post(&args->sem);
        printf("Semaphore free\n");
        sleep(1);
    }
    pthread_exit((void*)3);
}

static void* proc2(void* arg) {
    printf("Thread 2 started\n");
    args_t* args = (args_t*)arg;
    while (!(args->flag)) {
        sem_wait(&args->sem);
        printf("Semaphore captured by thread 2\n");
        for (size_t idx = 0; idx < 3; ++idx) {
            printf("2\n");
            fflush(stdout);
            sleep(1);
        }
        sem_post(&args->sem);
        printf("Semaphore free\n");
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
    args_t args;

    sem_init(&args.sem, 0, 1);
    printf("Semaphore created\n");

    pthread_create(&id1, nullptr, proc1, &args);
    pthread_create(&id2, nullptr, proc2, &args);

    getchar();
    printf("Key pressed\n");
    args.flag = true;

    pthread_join(id1, (void**)&exitcode1);
    printf("Thread 1 finished with exit code: %p\n", (void*)exitcode1);
    pthread_join(id2, (void**)&exitcode2);
    printf("Thread 2 finished with exit code: %p\n", (void*)exitcode2);

    sem_destroy(&args.sem);
    printf("Semaphore removed\n");

    printf("Program finished\n");
    return 0;
}
