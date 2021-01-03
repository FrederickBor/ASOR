// include necesario para el uso del printf
#include <stdio.h>
// include necesario para el uso de sleep
#include <unistd.h>

#include <stdlib.h>
#include <signal.h>

int main() {
    sigset_t blk_set;

    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGINT);
    sigaddset(&blk_set, SIGTSTP);

    sigprocmask(SIG_BLOCK, &blk_set, NULL);

    // Firma de la llamada
    // char *getenv(const char *name );
    int segundos = (int) getenv("SLEEP_SECS");
    sleep(segundos);

    sigset_t pending;
    int rc;
    rc = sigpending(&pending);

    if (rc == -1)
        perror("Error in sigpending");

    if (sigismember(&pending, SIGINT)){
        printf("Signal SIGINT received");
    }

    if (sigismember(&pending, SIGTSTP)){
        printf("Signal SIGTSTP received");

        sigprocmask(SIG_UNBLOCK, &pending, NULL);
    }

    sigprocmask(SIG_UNBLOCK, &blk_set, NULL);
}
