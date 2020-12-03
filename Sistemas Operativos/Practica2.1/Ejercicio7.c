// include necesario para el uso de pathconf
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
    // long pathconf(const char *path, int name);

    // Número máximo de enlaces
    rc = pathconf(".",_PC_LINK_MAX);

    if (rc == -1){
        printf("Error in pathconf: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    printf("Número máximo de enlaces: %li\n", rc);

    // Tamaño máximo de una ruta
    rc = pathconf(".",_PC_PATH_MAX);

    if (rc == -1){
        printf("Error in pathconf: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    printf("Tamaño máximo de una ruta: %li\n", rc);

    // Tamaño maximo de un nombre de fichero
    rc = pathconf(".",_PC_NAME_MAX);

    if (rc == -1){
        printf("Error in pathconf: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    printf("Tamaño maximo de un nombre de fichero: %li\n", rc);

    return 0;
}
