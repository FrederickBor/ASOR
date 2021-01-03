// include necesario para el uso de execvp
#include <unistd.h>
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
    rc = execvp(argv[1], &arguments);

    if (rc == -1)
        perror("Error in execvp");

    printf("El comando terminó de ejecutarse\n");

    return 0;
}
