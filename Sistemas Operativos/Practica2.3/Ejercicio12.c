// include necesario para el uso de printf
#include <stdio.h>

#include <signal.h>
#include <stdlib.h>

volatile int _sigint_count = 0;
volatile int _sigtstp_count = 0;

void handler(int signal){
    switch (signal)
    {
    case SIGINT:
        _sigint_count++;
        break;
    case SIGTSTP:
        _sigtstp_count++;
        break;
    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    struct sigaction action;

    sigaction(SIGINT, NULL, &action);
    action.sa_handler = handler;
    sigaction(SIGINT, &action, NULL);

    sigaction(SIGTSTP, NULL, &action);
    action.sa_handler = handler;
    sigaction(SIGTSTP, &action, NULL);

    sigset_t blk_set;

    sigemptyset(&blk_set);

    while (_sigint_count + _sigtstp_count < 10)
    {
        sigsuspend(&blk_set);
    }
    
    printf("\nThe signal SIGINT was captured %i times.\nThe signal SIGTSTP was captured %i times.\n",
        _sigint_count,
        _sigtstp_count
    );

    return 0;
}
