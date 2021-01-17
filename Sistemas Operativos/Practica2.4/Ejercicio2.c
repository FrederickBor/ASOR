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
    int fd_p_h[2];
    int fd_h_p[2];
    
    // firma de la llamada 
    // int pipe(int fd[2]);
    int rc = pipe(fd_p_h);

    if (rc == -1)
        perror("Error in pipe p_h");

    rc = pipe(fd_h_p);

    if (rc == -1)
        perror("Error in pipe p_h");

    pid_t fork_pid;
    fork_pid = fork();

    switch (fork_pid)
    {
        case -1:
            perror("Error in fork");
            break;
        case 0: // HIJO
            close(fd_p_h[PIPE_W]);
            close(fd_h_p[PIPE_R]);

            char mensaje[255];

            for (int i = 0; i < 10; i++)
            {   
                ssize_t bytes = read(fd_p_h[PIPE_R], mensaje, 255);

                if (bytes == -1)
                    perror("Error in read");

                mensaje[bytes] = '\0';
                printf("Mensaje recibido en proceso Hijo: %s\n", mensaje);
                sleep(1);

                char respuesta = 'l';

                if (i == 9) respuesta = 'q';
                
                write(fd_h_p[PIPE_W], &respuesta, 1);
            }

            break;
        default: // PADRE
            close(fd_h_p[PIPE_W]);
            close(fd_p_h[PIPE_R]);

            char respuesta = 'l';

            while (respuesta != 'q'){
                printf("%s\n", "Mensaje a enviar en proceso Padre: ");
                ssize_t bytes = read(0, mensaje, 255);
                mensaje[bytes] = '\0';
                write(fd_p_h[PIPE_W], mensaje, 255);
                read(fd_h_p[PIPE_R], &respuesta, 1);
            }

            printf("Mensajes enviados correctamente.\n");
            break;
    }

    return 0;
}
