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

int main(int argc, char const *argv[])
{
    int rc;
    char path[255];
    struct stat buff;
    long minor_value, major_value;
    char type[25];
    
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

    minor_value = minor(buff.st_dev);
    major_value = major(buff.st_dev);

    if (S_ISLNK(buff.st_mode))
        strcpy(type, "Symbolic Link");
    else if (S_ISREG(buff.st_mode))
        strcpy(type, "File");
    else if (S_ISDIR(buff.st_mode))
        strcpy(type, "Directory");
    
    struct tm *tm_mtime = localtime(&buff.st_mtime);
    struct tm *tm_ctime = localtime(&buff.st_ctime);

    printf("Information about %s: \n \
            \t Major number: %li \n \
            \t Minor number: %li \n \
            \t I-Node number: %li\n \
            \t Mode: %i - %s\n \
            \t Last access (m_time): %d:%d\n \
            \t Last access (c_time): %d:%d\n",
            path,
            major_value,
            minor_value,
            (long) buff.st_ino,
            buff.st_mode,
            type,
            tm_mtime->tm_hour,
            tm_mtime->tm_min,
            tm_ctime->tm_hour,
            tm_ctime->tm_min);

    return 0;
}