#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include <cstdio>

sem_t* msem;

static void* proc(void* arg) {
    printf("Thread 2 started\n");
    bool* flag = (bool*)arg;

    FILE* fp = fopen("im_file.txt", "a+");
    while (!(*flag)) {
        sem_wait(msem);
        printf("Semaphore captured by prog 2\n");

        for (int j = 0; j < 3; ++j) {
            fputc('2', fp);
            printf("2");
            fflush(stdout);
            sleep(1);
        }
        sem_post(msem);
        sleep(1);
        printf("\nSemaphore free\n");
    }
    fclose(fp);
    pthread_exit((void*)4);
}


int main() {
    printf("Program 2 started\n");

    bool flag = false;
    pthread_t id;
    int* exitcode;

    msem = sem_open("/important", O_CREAT, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);

    if (msem == nullptr) {
        perror("sem_open");
        return 0;
    }
    printf("Semaphore created\n");

    pthread_create(&id, nullptr, proc, &flag);
    printf("Program 2 is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    flag = true;
    pthread_join(id, (void**)&exitcode);
    printf("Thread 2 finished with exit code: %p\n", (void*)exitcode);

    sem_close(msem);
    sem_unlink("/important");

    printf("Program 2 finished\n");
    return 0;
}