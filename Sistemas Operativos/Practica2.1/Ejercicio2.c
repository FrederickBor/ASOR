// include necesario para el uso de setuid
#include <unistd.h>
// include necesario para el uso de errno
#include <errno.h>
// include necesario para el uso de strerror
#include <string.h>
// include necesario para el uso de la entrada y salida
#include <stdio.h>

int main() {
    int rc;
    rc = setuid(0);

    if (rc == -1)
        printf("Error in setuid: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
    
    return 1;
}