#include <iostream>
#include <pthread.h>
#include <unistd.h>

bool flag1 = 0;
bool flag2 = 0;

static void * proc1(void *arg) {
    while (!flag1) {
        std::cout << '1' << std::endl;
	sleep(1);
    }
    return 0;
}

static void * proc2(void *arg) {
    while (!flag2) {
        std::cout << '2' << std::endl;
	sleep(1);
    }
    return 0;
}

int main() {
    pthread_t id1;
    pthread_t id2;

    pthread_create(&id1, NULL, proc1, NULL);
    std::cout << "Thread 1 started" << std::endl;
    pthread_create(&id2, NULL, proc2, NULL);
    std::cout << "Thread 2 started" << std::endl;

    std::cout << "The program is waiting for a keystroke" << std::endl;
    getchar();
    std:: cout << "Key pressed" << std::endl;

    flag1 = 1;
    flag2 = 1;
    pthread_join(id1, NULL);
    std:: cout << "Thread 1 finished" << std::endl;
    pthread_join(id2, NULL);
    std:: cout << "Thread 2 finished" << std::endl;

    std::cout << "The program finished" << std::endl;
    return 0;
}
