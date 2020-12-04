// include necesario para el uso de time
#include <time.h>
// include necesario para el uso de errno
#include <errno.h>
// include necesario para el uso de strerror
#include <string.h>
// include necesario para el uso de printf
#include <stdio.h>

int main(int argc, char const *argv[])
{

    // Firma de la llamada:
    // time_t time(time_t *tloc);

    int rc;
    time_t epoch_time;

    rc = time(&epoch_time);

    if (rc == -1){
        printf("Error in time: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    printf("Hora, en segundos desde el Epoch: %ld\n", epoch_time);

    return 0;
}
