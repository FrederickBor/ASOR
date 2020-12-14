// include necesario para el uso de la entrada y salida
#include <stdio.h>
// includes necesarios para el uso de mkdir
#include <sys/stat.h>
#include <sys/types.h>
// include necesario para el uso del chdir
#include <unistd.h>

int main() {
    int rc;
    
    // Firma de la llamada
    // int mkdir(const char *pathname, mode_t mode);

    mode_t mode = 0000;

    rc = mkdir("mytestdirectory", mode);

    if (rc == -1)
        perror("Error in mkdir");

    // Firma de la función
    // int chdir(const char *path);

    rc = chdir("mytestdirectory");

    if (rc == -1)
        perror("Error in chdir");
    
    return 0;
}