// include necesario para el uso de gettimeofday
#include <sys/time.h>
// include necesario para el uso de errno
#include <errno.h>
// include necesario para el uso de strerror
#include <string.h>
// include necesario para el uso de printf
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int rc;

    struct timeval start_time, end_time;

    // Firma de la llamada:
    // int gettimeofday(struct timeval *tv, struct timezone *tz);
    rc = gettimeofday(&start_time, NULL);

    if (rc == -1){
        printf("Error in gettimeofday: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    // Bucle
    for (int i = 0; i < 1000000; i++)
    {
    }

    rc = gettimeofday(&end_time, NULL);

    if (rc == -1){
        printf("Error in gettimeofday: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    long diff_time = ((end_time.tv_sec * 1000000 + end_time.tv_usec) - (start_time.tv_sec * 1000000 + start_time.tv_usec));
    printf("Duración del bucle en microsegundos: %ld\n",
        diff_time
    );

    return 0;
}
