// includes necesarios para el uso de open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// include necesario para el uso de la entrada y salida
#include <stdio.h>

int main() {
    int rc;
    
    // Firma de la llamada
    // int creat(const char *pathname, mode_t mode)

    mode_t mode = 0645;

    rc = creat("testfile",mode);

    if (rc == -1)
        perror("Error in creat");

    return 0;
}