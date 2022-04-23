#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>


int main() {
    printf("Parent program started\n\n");

    printf("This process (our parent) ID of this program is %d\n", getpid());
    printf("Parent process ID of this program is %d\n", getppid());
    pid_t pid;
    int exitcode;

    if ((pid = fork()) == 0) {
        char pwd[150];
        getcwd(pwd, 100);
        strcat(pwd, "/lab_04_1");

        if (execl(pwd, "HELLO,", "DEAR", "CHILD!", nullptr) == -1) {
            perror("execl");
        }
    } else if (pid > 0) {
        printf("Child process ID of this program is %d\n", pid);
        while (waitpid(pid, &exitcode, WNOHANG) == 0) {
            printf("Wait\n");
            usleep(500000);
        }
        printf("Child exitcode: %i\n", WEXITSTATUS(exitcode));
    } else {
        perror("fork");
    }

    printf("Parent program finished\n");
    return 0;
}
