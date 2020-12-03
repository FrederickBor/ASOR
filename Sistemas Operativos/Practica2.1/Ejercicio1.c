// include necesario para el uso de setuid
#include <unistd.h>
// include necesario para el uso de la entrada y salida
#include <stdio.h>

int main() {
    int rc;
    rc = setuid(0);

    if (rc == -1)
        perror("Error in setuid");
    
    return 1;
}