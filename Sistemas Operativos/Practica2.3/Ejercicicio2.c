// includes necesarios para el uso de getpid
#include <sys/types.h>
#include <unistd.h>
// include necesario para el uso de scheduler
#include <sched.h>
// include necesario para el uso de printf
#include <stdio.h>
// include necesario para el uso de strcpy
#include <string.h>
// includes necesarios para el uso de getpriority
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char const *argv[])
{
    int rc, 
        policy,
        priority,
        max_priority,
        min_priority;

    pid_t pid;
    char policy_name[25];

    pid = getpid();

    rc = sched_getscheduler(pid);
    if (rc == -1)
        perror("Error in sched_getscheduler");
    policy = rc;

    rc = sched_get_priority_max(policy);
    if (rc == -1)
        perror("Error in sched_get_priority_max");
    max_priority = rc;

    rc = sched_get_priority_min(policy);
    if (rc == -1)
        perror("Error in sched_get_priority_min");
    min_priority = rc;

    switch (policy)
    {
    case SCHED_FIFO:
        strcpy(policy_name, "FIFO");
        break;
    case SCHED_OTHER:
        strcpy(policy_name, "OTHER");
        break;
    case SCHED_RR:
        strcpy(policy_name, "RR");
        break;
    default:
        strcpy(policy_name, "ERROR");
        break;
    }

    rc = getpriority(PRIO_PROCESS, pid);
    if (rc == -1)
        perror("Error in getpriority");
    priority = rc;

    printf("Process information:\n \
            \t POLICY: %i - %s\n \
            \t PRIORITY: %i\n \
            \t MIX PRIORITY: %i\n \
            \t MAX PRIORITY: %i\n",
            policy,
            policy_name,
            priority,
            min_priority,
            max_priority);

    return 0;
}
