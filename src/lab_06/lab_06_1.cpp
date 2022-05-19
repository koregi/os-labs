#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>

bool flag = false;
sem_t* write_sem;
sem_t* read_sem;
int shmid;
char* addr;

static void* proc(void*) {
    printf("Thread 1 started\n");
    char buf[256];

    while (!flag) {
        memset(buf, 0, 256);
        long size = sysconf(_SC_NGROUPS_MAX);
        unsigned usize = 0;
        if (errno == -1) {
            perror("Sysconf");
        }
        else {
            usize = static_cast<unsigned>(size);
        }
        auto* list = new gid_t[usize];
        int count = getgroups(static_cast<int>(usize), list);
        char idx_buf[10];
        for (int idx = 0; idx < count; ++idx) {
            std::sprintf(idx_buf, "%i", list[idx]);
            strcat(buf, idx_buf);
            if (idx < count - 1) {
                strcat(buf, " ");
            }
        }

        std::sprintf(addr, "%s", buf);
        printf("Data write\n");
        printf("%s\n", addr);

        sem_post(write_sem);
        sem_wait(read_sem);

        sleep(1);
    }
    pthread_exit(reinterpret_cast<void*>(0));
}

void sig_handler(int s) {
    munmap(addr, 256);
    sem_close(write_sem);
    sem_unlink("/write_sem");
    sem_close(read_sem);
    sem_unlink("/read_sem");
    close(shmid);
    shm_unlink("/shmem");

    if (s == SIGINT) {
        exit(1);
    }
}

int main() {
    printf("Program started\n");

    pthread_t id;
    void* exitcode;

    shmid = shm_open("/shmem", O_CREAT | O_RDWR, 0644);
    ftruncate(shmid, 256);
    addr = (char*)mmap(nullptr, 256, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
    write_sem = sem_open("/write_sem", O_CREAT, 0644, 0);
    read_sem = sem_open("/read_sem", O_CREAT, 0644, 1);

    signal(SIGINT, sig_handler);

    pthread_create(&id, nullptr, proc, nullptr);
    printf("Program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    flag = true;
    pthread_join(id, &exitcode);
    printf("Thread 1 finished with exit code: %p\n", exitcode);

    sig_handler(0);

    printf("Program finished\n");
    return 0;
}