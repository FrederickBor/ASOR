// include necesario para el uso de printf
#include <stdio.h>
// include necesario para el uso de las seniales
#include <signal.h>
#include <stdlib.h>
// include necesario para el uso de sleep
#include <unistd.h>

volatile int _stop = 0; 

void handler(int signal){
    switch (signal)
    {
    case SIGUSR1:
        _stop = 1;
        break;
    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("ERROR: Must specify seconds.\n");
        return -1;
	}

    int seconds = atoi(argv[1]);

    sigset_t blk_set;

    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

    // Cambiamos la accion realiza con la senial SIGUSR1

    struct sigaction action;

    sigaction(SIGUSR1, NULL, &action);
    action.sa_handler = handler;
    sigaction(SIGUSR1, &action, NULL);

    // esperamos la cantidad de segundos indicados
    int i = 0;

    while (i < seconds && _stop == 0){
        sleep(1);
        i++;
    }

    // Borramos (o no) el ejecutable

    if (_stop == 0){
        printf("Deleting executable %s\n", argv[0]);
        unlink(argv[0]);
    }
    else{
        printf("Deletion stopped.\n");
    }

    return 0;
}
