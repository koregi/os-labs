#include <pthread.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <mqueue.h>

bool flag = false;
mqd_t m_qid;

static void* proc(void*) {
    printf("Thread 1 started\n");
    char buf[256];

    while (!flag) {
        memset(buf, 0, 256);
        long size = sysconf(_SC_NGROUPS_MAX);
        unsigned u_size = 0;
        if (errno == -1) {
            perror("Sysconf");
        }
        else {
            u_size = static_cast<unsigned>(size);
        }
        auto* list = new gid_t[u_size];
        int count = getgroups(static_cast<int>(u_size), list);
        char idx_buf[10];
        for (int idx = 0; idx < count; ++idx) {
            std::sprintf(idx_buf, "%i", list[idx]);
            strcat(buf, idx_buf);
            if (idx < count - 1) {
                strcat(buf, " ");
            }
        }

        if (mq_send(m_qid, (const char*)&buf, sizeof(buf), 0) == -1) {
            perror("mq_send");
        }
        else {
            printf("Data was sent\n");
            printf("%s\n", buf);
        }


        delete[] list;
        sleep(1);
    }
    pthread_exit(reinterpret_cast<void*>(0));
}

void try_change_attrs(mq_attr &attr) {
    if (mq_getattr(m_qid, &attr) == -1) {
        perror("mq_getattr");
    }

    printf("\nMaximum of messages on queue: %ld\n", attr.mq_maxmsg);
    printf("Maximum message size: %ld\n", attr.mq_msgsize);
    printf("Count of messages currently in queue: %ld\n", attr.mq_curmsgs);

    attr.mq_maxmsg = 5;
    printf("Maximum of messages on queue: %ld\n\n", attr.mq_maxmsg);

}

int main() {
    printf("Program started\n");

    pthread_t id;
    void* exitcode;

    struct mq_attr attr {};
    attr.mq_flags = 0;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = 4096;
    attr.mq_curmsgs = 0;
    //try_change_attrs(attr);

    m_qid = mq_open("/my_queue", O_CREAT | O_WRONLY | O_NONBLOCK, 0644, &attr);
    if (m_qid == -1) {
        perror("mq_open");
    }
    printf("Message queue was opened\n");

    pthread_create(&id, nullptr, proc, nullptr);
    printf("Program is waiting for a keystroke\n");
    getchar();
    printf("Key pressed\n");
    flag = true;
    pthread_join(id, &exitcode);
    printf("Thread 1 finished with exit code: %p\n", exitcode);

    mq_close(m_qid);
    mq_unlink("my_queue");
    printf("Message queue was closed\n");

    printf("Program finished\n");
    return 0;
}