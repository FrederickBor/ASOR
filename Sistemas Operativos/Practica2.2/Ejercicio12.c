// include necesario para el uso de la entrada y salida
#include <stdio.h>
// includes necesarios para el uso de open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// include necesario para el uso de dup2
#include <unistd.h>
// include necesario para el uso de strcpy
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd, fd2;
    char path[100];
    struct stat buff;
    
    if (argc < 2) {
        printf("ERROR: Must specify file.\n");
        return -1;
	}

    strcpy(path, argv[1]);

    fd = open(path, O_CREAT | O_RDWR, 00777);
    if (fd == -1)
        perror("Error in open");

    fd2 = dup2(fd, 1);
    printf("Redirecting exit to %s\n", argv[1]);

    dup2(fd2, fd);

    return 0;
}
