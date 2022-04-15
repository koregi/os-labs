#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>

#include <cstdio>

struct args_t {
    bool flag = false;
    int fd[2];
};

static void* proc1(void* arg) {
    printf("Thread 1 started\n");
    args_t *args = (args_t*)arg;
    int buf;
    while (!(args->flag)) {
        long size = sysconf(_SC_NGROUPS_MAX);
        gid_t *list = new gid_t[size*sizeof(gid_t)];
        buf = getgroups(size, list);

        write(args->fd[1], &buf, sizeof(buf));
        printf("Data write\n");
        delete [] list;
        sleep(1);
    }
    pthread_exit((void*)3);
}

static void* proc2(void* arg) {
    printf("Thread 2 started\n");
    args_t *args = (args_t*)arg;
    int buf = 0;
    while (!(args->flag)) {
        read(args->fd[0], &buf, sizeof(buf));
        printf("Data read: %i\n", buf);
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

    pipe(args.fd);
    fcntl(args.fd[0], F_SETFL, O_NONBLOCK);
    fcntl(args.fd[1], F_SETFL, O_NONBLOCK);
    printf("Pipe created\n");

    pthread_create(&id1, nullptr, proc1, &args);
    pthread_create(&id2, nullptr, proc2, &args);

    printf("Program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    args.flag = true;

    pthread_join(id1, (void**)&exitcode1);
    printf("Thread 1 finished with exit code: %p\n", (void*)exitcode1);
    pthread_join(id2, (void**)&exitcode2);
    printf("Thread 2 finished with exit code: %p\n", (void*)exitcode2);


    close(args.fd[0]);
    close(args.fd[1]);
    printf("Pipe closed\n");
    printf("Program finished\n");
    return 0;
}
