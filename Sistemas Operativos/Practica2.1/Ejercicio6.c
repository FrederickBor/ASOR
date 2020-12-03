// include necesario para el uso de sysconf
#include <unistd.h>
// include necesario para el uso de errno
#include <errno.h>
// include necesario para el uso de strerror
#include <string.h>
// include necesario para el printf
#include <stdio.h> 

int main(int argc, char const *argv[])
{
    long rc;

    // Firma de la llamada:
    // long sysconf(int name);

    // Longitud máxima de los argumentos
    rc = sysconf(_SC_ARG_MAX);

    if (rc == -1){
        printf("Error in sysconf: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    printf("Longitud máxima de los argumentos: %li\n", rc);
    

    // Número máximo de hijos
    rc = sysconf(_SC_CHILD_MAX);

    if (rc == -1){
        printf("Error in sysconf: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    printf("Número máximo de hijos: %li\n", rc);

    // Número máximo de ficheros
    rc = sysconf(_SC_OPEN_MAX);

    if (rc == -1){
        printf("Error in sysconf: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    printf("Número máximo de ficheros: %li\n", rc);

    return 0;
}
