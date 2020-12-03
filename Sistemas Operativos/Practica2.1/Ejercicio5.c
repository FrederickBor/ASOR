// include para el uso de uname
#include <sys/utsname.h>
// include necesario para el uso de errno
#include <errno.h>
// include necesario para el uso de strerror
#include <string.h>
// include necesario para el printf
#include <stdio.h> 


int main(int argc, char const *argv[])
{

    int rc;

    // Firma de la llamada:
    // int uname(struct utsname *buf);

    struct utsname buf;
    rc = uname(&buf);

    if (rc == -1){
        printf("Error in uname: \n\t Error code: %i \n\t Error message: %s\n",
            errno,
            strerror(errno)
        );
        return -1;
    }

    printf("SYSNAME: %s\nNODENAME: %s\nRELEASE: %s\nVERSION: %s\nMACHINE: %s\n",
        buf.sysname,
        buf.nodename,
        buf.release,
        buf.version,
        buf.machine
    );

    return 0;
}
