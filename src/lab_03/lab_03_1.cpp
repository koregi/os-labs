#include <pthread.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

#include <cstdio>

struct args_t {
    bool flag = false;
    int fd[2];
    unsigned nbytes = 0;
};

static void* proc1(void* arg) {
    printf("Thread 1 started\n");
    auto *args = (args_t*)arg;
    ssize_t nw;
    char buf[256];

    while (!(args->flag)) {
        memset(buf, 0, 256);

        long size = sysconf(_SC_NGROUPS_MAX);
        unsigned usize = 0;
        if (errno == -1) {
            perror("Sysconf");
        } else {
            usize = static_cast<unsigned> (size);
        }
        auto *list = new gid_t[usize];
        int count = getgroups(int(usize), list);

        char buff[10];
        for (int idx = 0; idx < count; ++idx) {
            std::sprintf(buff, "%i", list[idx]);
            strcat(buf, buff);
            if (idx < count-1) {
                strcat(buf, " ");
            }
        }

        args->nbytes = sizeof(buf);
        nw = write(args->fd[1], &buf, args->nbytes);
        if (nw != -1) {
            printf("Data write\n");
        } else {
            perror("write");
        }

        delete [] list;
        sleep(1);
    }
    pthread_exit((void*)3);
}

static void* proc2(void* arg) {
    printf("Thread 2 started\n");
    auto *args = (args_t*)arg;
    ssize_t nr;
    char buf[256];

    while (!(args->flag)) {
        nr = read(args->fd[0], &buf, args->nbytes);
        if (nr > 0) {
            printf("Data read: %s\n", buf);
        } else {
            perror("read");
        }
        sleep(1);
    }
    pthread_exit((void*)4);
}


int main() {
    printf("Program started\n");

    pthread_t id1;
    pthread_t id2;
    void* exitcode1;
    void* exitcode2;
    args_t args;

    int rv = pipe(args.fd);
    if (rv == 0) {
        printf("Pipe created\n");
    } else {
        perror("pipe");
        printf("Program finished\n");
        return 0;
    }

    pthread_create(&id1, nullptr, proc1, &args);
    pthread_create(&id2, nullptr, proc2, &args);

    printf("Program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    args.flag = true;

    pthread_join(id1, &exitcode1);
    printf("Thread 1 finished with exit code: %p\n", exitcode1);
    pthread_join(id2, &exitcode2);
    printf("Thread 2 finished with exit code: %p\n", exitcode2);


    close(args.fd[0]);
    close(args.fd[1]);
    printf("Pipe closed\n");
    printf("Program finished\n");
    return 0;
}
