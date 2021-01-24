// include necesario para el uso de printf
#include <stdio.h>
// includes necesarios para el uso de getaddrinfo
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
// includes necesarios para el uso de inet_ntop
#include <arpa/inet.h>

#define MAX_MESSAGE 2
#define MAX_SIZE_MSG 255

int main(int argc, char const *argv[])
{

    if (argc < 4)
    {
        printf("USAGE: %s [host] [port] [command]", argv[0]);
        return -1;
    }

    struct addrinfo *result;
    struct addrinfo hints;

    hints.ai_family = AF_UNSPEC;
    hints.ai_protocol = 0;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    int rc;
    rc = getaddrinfo(argv[1], argv[2], &hints, &result);

    if (rc == -1){
        perror("Error in getaddrinfo");
        return -1;
    }

    int sd;
    sd = socket(result->ai_family, result->ai_socktype, 0);

    char buf[MAX_MESSAGE];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    sendto(sd, argv[3], MAX_MESSAGE, 0, result->ai_addr, result->ai_addrlen);
    
    if (*argv[3] == 't' || *argv[3] == 'd')
    {
        ssize_t c;
        char buf[MAX_SIZE_MSG];
        c = recvfrom(sd, buf, MAX_SIZE_MSG, 0, (struct sockaddr *)&addr, &addrlen);
        buf[c] = '\0';
        printf("%s\n", buf);
    }

    freeaddrinfo(result);
    
    return 0;
}
