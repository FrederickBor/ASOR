// includes necesarios para el uso de creat
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// include necesario para el uso de la entrada y salida
#include <stdio.h>

int main() {
    int rc;
    
    // Firma de la llamada
    // int open(const char *pathname, int flags);
    // int creat(const char *pathname, mode_t mode)
    // mode_t umask(mode_t mask);

    mode_t newmask = 027;
    mode_t currentmask = umask(newmask);

    rc = open("testfile", O_CREAT);

    if (rc == -1)
        perror("Error in open");

    umask(currentmask);

    return 0;
}