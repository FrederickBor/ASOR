// include necesario para el uso de strerror
#include <string.h>
// include necesario para el uso de la entrada y salida
#include <stdio.h>

const int NUMBER_OF_ERRORS = 255;

int main() {
    int count = 255;

    for (int i = 0; i < NUMBER_OF_ERRORS; i++)
    {
        printf("Error #%i: \n\t Error code: %i \n\t Error message: %s\n", i, i, strerror(i));
    }

    return 0;
}