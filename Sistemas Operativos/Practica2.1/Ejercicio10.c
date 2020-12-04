// includes necesarios para el uso de getuid y geteuid
#include <unistd.h>
#include <sys/types.h>
// include necesario para el printf
#include <stdio.h> 

#include <pwd.h>

int main(int argc, char const *argv[])
{
    uid_t euid, uid;
    struct passwd *user;

    // UID real
    uid = getuid();
    printf("UID real: %i\n", uid);

    // UID efectivo
    euid = geteuid();
    printf("UID efectivo: %i\n", euid);

    // Firma de la llamada:
    // struct passwd *getpwuid(uid_t uid);

    user = getpwuid(uid);
    printf("Nombre de usuario: %s\nDirectorio home: %s\nDescripción del usuario: %s\n",
        user->pw_name,
        user->pw_dir,
        user->pw_gecos
    );

    return 0;
}
