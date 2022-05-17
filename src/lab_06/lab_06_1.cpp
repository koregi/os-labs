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

sem_t* write_sem;
sem_t* read_sem;
int shmid;
char* addr;
const char* shm_name = "/shmem";

static void* proc(void* arg) {
    printf("Thread 1 started\n");
    auto* flag = reinterpret_cast<bool*>(arg);
    char buf[256];
    int sem_status;
    int failure = 0;

    while (!(*flag)) {
        sem_getvalue(write_sem, &sem_status);
        if (sem_status == 0) {
            failure = 0;
            sem_wait(read_sem);

            memset(buf, 0, 256);
            long size = sysconf(_SC_NGROUPS_MAX);
            unsigned usize = 0;
            if (errno == -1) {
                perror("Sysconf");
            } else {
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

            sem_post(read_sem);
            sem_post(write_sem);
        } else {
            sleep(1);
            failure++;
            if (failure == 10) {
                printf("\nTime to write is over\n");
                break;
            }
        }
        sleep(1);
    }
    pthread_exit(reinterpret_cast<void*>(0));
}

void sig_handler(int s) {
    munmap(addr, 256);
    sem_unlink("/write_sem");
    sem_unlink("/read_sem");
    close(shmid);
    shm_unlink(shm_name);

    if (s == SIGINT) {
        exit(1);
    }
}

int main() {
    printf("Program started\n");

    bool flag = false;
    pthread_t id;
    void* exitcode;

    write_sem = sem_open("/write_sem", O_CREAT, 0644, 0);
    read_sem = sem_open("/read_sem", O_CREAT, 0644, 1);
    shmid = shm_open(shm_name, O_CREAT | O_RDWR, 0644);
    ftruncate(shmid, 256);
    addr = (char*)mmap(nullptr, 256, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);

    signal(SIGINT, sig_handler);

    pthread_create(&id, nullptr, proc, &flag);
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