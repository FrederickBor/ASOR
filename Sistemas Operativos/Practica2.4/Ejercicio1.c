// includes necesarios para el uso de fork
#include <sys/types.h>
#include <unistd.h>
// include necesario para el uso de perror
#include <errno.h>
// include necesario para el uso de printf
#include <stdio.h>

#define PIPE_W 1
#define PIPE_R 0

int main(int argc, char const *argv[])
{
    if (argc < 5){
        printf("ERROR: correct use %s [command1] [argument1] [command2] [argument2]", argv[0]);
        return -1;
    }

    int fd[2];
    
    // firma de la llamada 
    // int pipe(int fd[2]);
    int rc = pipe(fd);

    if (rc == -1)
        perror("Error in pipe");

    pid_t fork_pid;
    fork_pid = fork();

    switch (fork_pid)
    {
        case -1:
            perror("Error in fork");
            break;
        case 0: // HIJO
            dup2(fd[PIPE_R],0);
            close(fd[PIPE_W]);
            close(fd[PIPE_R]);
            execlp(argv[3], argv[3], argv[4]);
            break;
        default: // Padre
            dup2(fd[PIPE_W],1);
            close(fd[PIPE_W]);
            close(fd[PIPE_R]);
            execlp(argv[1], argv[1], argv[2]);
            break;
    }

    return 0;
}
