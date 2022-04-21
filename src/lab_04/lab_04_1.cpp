#include <unistd.h>

#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[]) {
    printf("Child program started\n\n");

    printf("This process (our child) ID of this program is %d\n", getpid());
    printf("Parent process ID of this program is %d\n", getppid());

    printf("Args are:\n");
    for (int idx = 0; idx < argc; ++idx) {
        printf("%s\n", argv[idx]);
        sleep(1);
    }

    printf("Child program finished\n");
    exit(3);
}