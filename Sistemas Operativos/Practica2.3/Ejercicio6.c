// include necesario para uso de getpid y fork
#include <unistd.h>
// include necesario para el uso de printf
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int rc;
    pid_t fork_pid = fork();

    switch (fork_pid){
        case -1:
            perror("Error in fork");
            break;
        case 0:
            rc = chdir("/tmp");

            pid_t pid,
                ppid,
                pgid,
                sid;

            pid = getpid();
            ppid = getppid();
            pgid = getpgid(pid);
            sid = getsid(pid);

            printf("CURRENT PROCESS INFORMATION:\n \
                \tPID: %i\n \
                \tParent PID: %i\n \
                \tProcess Group ID: %i\n \
                \tSession ID: %i\n",
                pid,
                ppid,
                pgid,
                sid
            );

            break;
        default:
            sleep(3);
            break;
    }
    
    return 0;
}
