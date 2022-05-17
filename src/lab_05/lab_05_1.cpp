#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include <cstdio>
#include <fstream>

sem_t* g_sem;
std::ofstream g_out;

static void* proc(void* arg) {
    printf("Thread 1 started\n");
    bool* flag = (bool*)arg;

    while (!(*flag)) {
        sem_wait(g_sem);
        printf("Semaphore captured by prog 1\n");

        for (int j = 0; j < 10; ++j) {
            if (g_out.is_open()) {
                g_out << "1" << std::flush;
                printf("1\n");
                fflush(stdout);
            }
            else {
                printf("out is closed");
            }
            sleep(1);
        }
        sem_post(g_sem);
        sleep(1);
        printf("\nSemaphore free\n");
    }
    pthread_exit((void*)3);
}


int main() {
    printf("Program 1 started\n");

    bool flag = false;
    pthread_t id;
    int* exitcode;

    g_sem = sem_open("/important", O_CREAT, 0644, 1);

    if (g_sem == nullptr) {
        perror("sem_open");
        return 0;
    }
    printf("Semaphore created\n");

    g_out.open("im_file.txt", std::ios::out | std::ios::app);

    pthread_create(&id, nullptr, proc, &flag);
    printf("Program 1 is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    flag = true;
    pthread_join(id, (void**)&exitcode);
    printf("Thread 1 finished with exit code: %p\n", (void*)exitcode);

    sem_close(g_sem);
    printf("Semaphore closed\n");
    sem_unlink("/important");
    printf("Semaphore deleted\n");

    printf("Program 1 finished\n");
    return 0;
}
