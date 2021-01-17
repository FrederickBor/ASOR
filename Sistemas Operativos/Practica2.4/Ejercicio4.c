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

int main(int argc, char const *argv[])
{
    if (argc < 2){
        printf("ERROR: correct use %s [command]", argv[0]);
        return -1;
    }
    
    char *pipe = "pipe";

    // firma de la llamada
    // int mkfifo(const char *filename, mode_t mode);

    int rc = mkfifo(pipe, 0777);

    if (rc == -1) 
        perror("Error in mkfifo");

    int fd = open(pipe, O_WRONLY);
    write(fd, argv[1], strlen(argv[1]));
    close(fd);

    return 0;
}
