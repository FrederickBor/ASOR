// includes necesarios para el uso de getuid y geteuid
#include <unistd.h>
#include <sys/types.h>
// include necesario para el printf
#include <stdio.h> 

int main(int argc, char const *argv[])
{
    uid_t euid, uid;

    // UID real
    uid = getuid();
    printf("UID real: %i\n", uid);

    // UID efectivo
    euid = geteuid();
    printf("UID efectivo: %i\n", euid);

    return 0;
}
