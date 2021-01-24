// include necesario para el uso de printf
#include <stdio.h>
// includes necesarios para el uso de getaddrinfo
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
// includes necesarios para el uso de inet_ntop
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{

    if (argc < 2){
        printf("USAGE: %s [host]", argv[0]);
        return -1;
    }

    struct addrinfo *res;
    struct addrinfo hints;

    hints.ai_family = AF_UNSPEC;
    hints.ai_protocol = 0;
    hints.ai_socktype = 0;
    hints.ai_flags = NI_NUMERICHOST;

    int rc;
    rc = getaddrinfo(argv[1], NULL, &hints, &res);

    if (rc == -1){
        perror("Error in getaddrinfo");
        return -1;
    }

    struct in_addr inaddr;
    struct in6_addr in6addr;
    char buffer[INET_ADDRSTRLEN];
    char buffer6[INET6_ADDRSTRLEN];

    while (res != NULL){
        switch (res->ai_family)
        {
        case AF_INET: // IPv4
            // firma de la llamada
            // const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
            if (inet_ntop(AF_INET, &inaddr, buffer, INET_ADDRSTRLEN) == NULL)
            {
                perror("Error in inet_ntop (IPv4)");
                return -1;
            }
            
            printf("IPv4: %s \n\t PROTOCOL FAMILY: %i \n\t SOCKET TYPE: %i \n",buffer, res->ai_protocol, res->ai_socktype);

            break;
        case AF_INET6: // IPv6
            // firma de la llamada
            // const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
            if (inet_ntop(AF_INET6, &in6addr, buffer6, INET6_ADDRSTRLEN) == NULL)
            {
                perror("Error in inet_ntop (IPv6)");
                return -1;
            }
            
            printf("IPv6: %s \n\t PROTOCOL FAMILY: %i \n\t SOCKET TYPE: %i \n",buffer6, res->ai_protocol, res->ai_socktype);

            break;
        default:
            printf("ERROR: Not valid ai_family (%i)", res->ai_family);
            break;
        }

        // Pasamos al siguiente
        res = res->ai_next;
    }

    freeaddrinfo(res);
    
    return 0;
}
