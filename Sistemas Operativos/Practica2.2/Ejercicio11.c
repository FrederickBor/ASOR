// Includes necesarios para el uso de stat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
// include necesario para el uso de localtime
#include <time.h>
// include necesario para el uso de strcopy
#include <string.h>
// include necesario para el uso de la entrada y salida
#include <stdio.h>
// include necesario para el uso de malloc
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int rc;
    char path[100];
    struct stat buff;
    
    if (argc < 2) {
        printf("ERROR: Must specify [file / directory].\n");
        return -1;
	}

    strcpy(path, argv[1]);
    
    // Firma de la llamada
    // int stat(const char *path, struct stat *buf);
    rc = stat(path, &buff);

    if (rc == -1)
        perror("Error in stat");

    char* hard = malloc(sizeof(char)*(5 + strlen(path)));
	char* sym = malloc(sizeof(char)*(5 + strlen(path)));
	strcpy(hard, path);
	strcpy(sym, path);
    
    hard = strcat(hard, ".hard");
	sym = strcat(sym, ".sym");

    if (S_ISREG(buff.st_mode)){
        rc = link(argv[1],hard);
        if (rc == -1)
            perror("Error in link");
        
        rc = symlink(argv[1],sym);
        if (rc == -1)
            perror("Error in symlink");
    }

    return 0;
}
