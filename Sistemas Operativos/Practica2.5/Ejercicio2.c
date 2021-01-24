// include necesario para el uso de printf
#include <stdio.h>
// includes necesarios para el uso de getaddrinfo
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
// includes necesarios para el uso de sockets
#include <sys/types.h>
#include <sys/socket.h>
// include necesario para time y localtime
#include <time.h>
// include necesario para close
#include <unistd.h>

#define MAX_MESSAGE 2
#define MAX_SIZE_MSG 255

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("USAGE: %s [host] [port]", argv[0]);
        return -1;
    }

    struct addrinfo hints; 
    struct addrinfo *result; 

    hints.ai_flags = AI_PASSIVE; // Devolver 0.0.0.0 o ::
    hints.ai_family = AF_UNSPEC; // IPv4 o IPv6
    hints.ai_socktype = SOCK_DGRAM;
    
    int rc;
    rc = getaddrinfo(argv[1], argv[2], &hints, &result);

    if (rc == -1){
        perror("Error in getaddrinfo");
        return -1;
    }

    int sd;
    sd = socket(result->ai_family, result->ai_socktype, 0);
    
    bind(sd, (struct sockaddr *)result->ai_addr, result->ai_addrlen);

    freeaddrinfo(result);

    ssize_t c;
    char buf[MAX_MESSAGE];
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);

    while (1)
    {
        // Recibimos la conexion
        c = recvfrom(sd, buf, 80, 0, (struct sockaddr *)&addr, &addrlen);
        buf[c] = '\0';
        getnameinfo((struct sockaddr *)&addr, addrlen, host, NI_MAXHOST,
                    serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        printf("%zi bytes de %s:%s\n", c, host, serv);

        time_t t = time(NULL);
        struct tm *tm = localtime(&t);        
        char msg[MAX_SIZE_MSG];
        size_t msg_bytes;

        // Tratamos el mensaje
        switch (buf[0])
        {
        case 't':
            msg_bytes = strftime(msg, MAX_SIZE_MSG, "%H:%M:%S", tm);
            msg[msg_bytes] = '\0';
            sendto(sd, msg, msg_bytes, 0, (struct sockaddr *)&addr, addrlen);
            break;
        case 'd':
            msg_bytes = strftime(msg, MAX_SIZE_MSG, "%d-%m-%Y", tm);
            msg[msg_bytes] = '\0';
            sendto(sd, msg, msg_bytes, 0, (struct sockaddr *)&addr, addrlen);
            break;
        case 'q':
            printf("Saliendo...\n");
            return 0;
            break;
        default:
            printf("Comando no soportado %c\n", buf[0]);
            break;
        }
    }

    close(sd);

    return 0;
}
