#include <pthread.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <mqueue.h>

bool flag = false;
mqd_t m_qid;

static void* proc(void*) {
    printf("Thread 2 started\n");
    char buf[8192];

    while (!flag) {
        memset(buf, 0, 8192);

        if (mq_receive(m_qid, buf, sizeof(buf), nullptr) == -1) {
            perror("mq_receive");
            sleep(1);
            continue;
        }
        else {
            printf("Data was received\n");
            printf("%s\n", buf);
        }

        sleep(1);
    }
    pthread_exit(reinterpret_cast<void*>(0));
}

int main() {
    printf("Program started\n");

    pthread_t id;
    void* exitcode;

    m_qid = mq_open("/my_queue", O_CREAT | O_RDONLY | O_NONBLOCK, 0644, nullptr);
    if (m_qid == -1) {
        perror("mq_open");
    }
    printf("Message queue was opened\n");

    struct mq_attr getattr {};

    if (mq_getattr(m_qid, &getattr) == -1) {
        perror("mq_getattr");
    }
    printf("\nNew maximum of messages on queue: %ld\n", getattr.mq_maxmsg);
    printf("New maximum message size: %ld\n\n", getattr.mq_msgsize);

    pthread_create(&id, nullptr, proc, nullptr);
    printf("Program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    flag = true;
    pthread_join(id, &exitcode);
    printf("Thread 2 finished with exit code: %p\n", exitcode);

    mq_close(m_qid);
    mq_unlink("my_queue");
    printf("Message queue was closed\n");

    printf("Program finished\n");
    return 0;
}