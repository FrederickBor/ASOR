// includes necesarios para el uso de open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// include necesario para el uso de la entrada y salida
#include <stdio.h>
// include necesario para el uso de strcpy, strlen
#include <string.h>
// include necesario para el uso de DIR y dirent
#include <sys/types.h>
#include <dirent.h>
// include necesario para el uso de malloc
#include <stdlib.h>
// include necesario para el uso de readlink
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int rc;
    char path[100];
    struct dirent *current;
    struct stat info;
    unsigned long int total_size = 0;
    
    if (argc < 2) {
        printf("ERROR: Must specify file.\n");
        return -1;
	}

    strcpy(path, argv[1]);

    size_t path_size = strlen(path);
    DIR *directory = opendir(path);

    if (directory == NULL) 
        perror("Error in opendir");

    current = readdir(directory);

    while (current != NULL){
        char *new_path = malloc(sizeof(char)*(path_size + strlen(current->d_name) + 3));
        strcpy(new_path, path);
        strcat(new_path, "/");
        strcat(new_path, current->d_name);

        rc = stat(new_path, &info);
        if (rc == -1){
            perror("Error in stat");
        }
    
        if (S_ISREG(info.st_mode)){
            if (info.st_mode & S_IXUSR)
                printf("%s *\n", current->d_name);
            else
                printf("%s\n", current->d_name);
            
            total_size += info.st_size;
        }
        else if (S_ISDIR(info.st_mode)){
            printf("%s /\n", current->d_name);
        }
        else if (S_ISLNK(info.st_mode)){
            char *link_name = malloc(info.st_size + 1);
            rc = readlink(new_path, link_name, info.st_size + 1);
            if (rc == -1)
                perror("Error in readlink");

            printf("%s -> %s\n", current->d_name, link_name);
            free(link_name);
        }

        free(new_path);
        current = readdir(directory);
    }

    printf("TOTAL SIZE OF FILES ON %s : %ld Kilobytes\n", path, total_size/1024);

    return 0;
}
