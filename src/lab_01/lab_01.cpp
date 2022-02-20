#include <iostream>
#include <pthread.h>
#include <unistd.h>

bool flag1 = 0;
bool flag2 = 0;

static void * proc1(void *arg) {
    std::cout << "Thread 1 started" << std::endl;
    while (!flag1) {
        std::cout << '1' << std::endl;
	sleep(1);
    }
    pthread_exit((void*)3);
    return 0;
}

static void * proc2(void *arg) {
    std::cout << "Thread 2 started" << std::endl;
    while (!flag2) {
        std::cout << '2' << std::endl;
	sleep(1);
    }
    pthread_exit((void*)4);
    return 0;
}

int main() {
    pthread_t id1;
    pthread_t id2;
    int *exitcode1;
    int *exitcode2;

    pthread_create(&id1, NULL, proc1, NULL);
    pthread_create(&id2, NULL, proc2, NULL);

    std::cout << "Program is waiting for a keystroke" << std::endl;
    getchar();
    std:: cout << "Key pressed" << std::endl;
    flag1 = 1;
    flag2 = 1;

    pthread_join(id1, (void**)&exitcode1);
    std::cout << "Thread 1 finished with exit code: " << *exitcode1 << std::endl;
    pthread_join(id2, (void**)&exitcode2);
    std::cout << "Thread 2 finished with exit code: " << *exitcode2 << std::endl;

    std::cout << "Program finished" << std::endl;
    return 0;
}
