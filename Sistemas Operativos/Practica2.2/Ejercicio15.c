// includes necesarios para el uso de open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// include necesario para el uso de la entrada y salida
#include <stdio.h>
//
#include <string.h>
// include necesario para el uso de localtime
#include <time.h>
// includes necesarios para getpid
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int rc, fd;
    char path[100];
    struct flock lock;
    
    if (argc < 2) {
        printf("ERROR: Must specify file.\n");
        return -1;
	}

    strcpy(path, argv[1]);

    fd = open(path, O_CREAT | O_RDWR, 00777);
    if (fd == -1)
        perror("Error in open");


    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    rc = fcntl(fd, F_GETLK, &lock);
    if (rc == -1)
        perror("Error in fnctl");

    if (lock.l_type == F_UNLCK){
        printf("Lock status: UNLOCKED\n");
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        lock.l_pid = getpid();

        rc = fcntl(fd, F_GETLK, &lock);
        if (rc == -1){
            close(fd);
            perror("Error in fnctl");
        }

        time_t actual_time = time(NULL);
        struct tm *tm = localtime(&actual_time);

        char buffer[255];

        sprintf(buffer, "Time: %d:%d", tm->tm_hour, tm->tm_min);

        write(fd, &buffer, strlen(buffer));

        sleep(3);

        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;
        lock.l_pid = getpid();

        rc = fcntl(fd, F_GETLK, &lock);
        if (rc == -1){
            close(fd);
            perror("Error in fnctl");
        }
    }
    else{
        printf("Lock status: LOCKED\n");
        close(fd);
        return -1;
    }

    close(fd);

    return 0;
}
