// include necesario para el uso de system
#include <stdlib.h>
// include necesario para el printf
#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("ERROR: Must specify file.\n");
        return -1;
	}

    // Firma de la llamada
    // execvp(const char *file, char *const argv[]);

    int rc;
    char *arguments;
    rc = system(argv[1]);

    if (rc == -1)
        perror("Error in System");

    printf("El comando terminó de ejecutarse\n");

    return 0;
}
