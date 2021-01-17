// include necesario para el uso de perror
#include <errno.h>
// include necesario para el uso de printf
#include <stdio.h>
// includes necesarios para el uso de mkfifo
#include <sys/types.h>
#include <sys/stat.h>
// include necesario para el uso de open
#include <fcntl.h>
// include necesario para close
#include <unistd.h>
// include necesaario para el uso de strlen
#include <string.h>

#define MAX_BUFFER_SIZE 255

int main(int argc, char const *argv[])
{
    char *pipe1_name = "pipe1";
    char *pipe2_name = "pipe2";

    // firma de la llamada
    // int mkfifo(const char *filename, mode_t mode);

    int rc = mkfifo(pipe1_name, 0644);

    if (rc == -1) 
        perror("Error in mkfifo");

    rc = mkfifo(pipe2_name, 0644);

    if (rc == -1) 
        perror("Error in mkfifo");

    char buffer[MAX_BUFFER_SIZE];

    int pipe1 = open(pipe1_name, O_RDONLY | O_NONBLOCK);

    if (pipe1 == -1){
        perror("Error in pipe");
        return -1;
    }

    int pipe2 = open(pipe2_name, O_RDONLY | O_NONBLOCK);

    if (pipe2 == -1){
        close(pipe1);
        perror("Error in pipe");
        return -1;
    }

    int cambios, pipe_actual, num_pipe;
    
    while (cambios != -1){
        fd_set conjunto;
        FD_ZERO(&conjunto);
        FD_SET(pipe1, &conjunto);
        FD_SET(pipe1, &conjunto);

        int nfds = (pipe1 > pipe2) ? pipe1 : pipe2;
        nfds++;

        cambios = select(nfds, &conjunto, NULL, NULL, NULL);

        if (cambios <= 0) break;

        if (FD_ISSET(pipe1, &conjunto)){
            pipe_actual = pipe1;
            num_pipe = 1;
        }
        else if (FD_ISSET(pipe2, &conjunto)){
            pipe_actual = pipe2;
            num_pipe = 2;
        }
        
        ssize_t buffer_size = MAX_BUFFER_SIZE - 1;
        while (buffer_size == (MAX_BUFFER_SIZE-1))
        {
            buffer_size = read(pipe_actual, buffer, MAX_BUFFER_SIZE-1);
            buffer[buffer_size] = '\0';
            printf("PIPE %i: %s", num_pipe, buffer);
        }

        if (num_pipe == 1)
        {
            close(pipe1);
            pipe1 = open(pipe1_name, O_RDONLY | O_NONBLOCK);

            if (pipe1 == -1){
                close(pipe2);
                perror("Error in pipe");
                return -1;
            }

        }
        else // num_pipe == 2
        {
            close(pipe2);
            pipe2 = open(pipe2_name, O_RDONLY | O_NONBLOCK);

            if (pipe2 == -1){
                close(pipe1);
                perror("Error in pipe");
                return -1;
            }
        }

    }

    close(pipe1);   
    close(pipe2);
    return 0;
}
