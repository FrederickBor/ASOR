// include necesario para el uso de localtime
#include <time.h>
// include necesario para el uso de printf
#include <stdio.h>

int main(int argc, char const *argv[])
{
    // Firma de la llamada:
    // size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);

    struct tm *date;
    time_t t = time(NULL);
    date = localtime( &t );

    char buffer[100];

    strftime(buffer,80,"%A, %d de %B de %Y, %H:%M", date);

    printf("%s\n",
        buffer
    );

    return 0;
}
