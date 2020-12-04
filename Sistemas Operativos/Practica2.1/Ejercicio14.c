// include necesario para el uso de localtime
#include <time.h>
// include necesario para el uso de printf
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // Firma de la llamada:
    // struct tm *localtime(const time_t *timep);

    struct tm *date;
    time_t t = time(NULL);
    date = localtime( &t );

    printf("El año actual es: %i\n",
        date->tm_year + 1900
    );

    return 0;
}
