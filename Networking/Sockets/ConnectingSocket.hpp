
#ifndef CONNECTINGSOCKET_HPP
#define CONNECTINGSOCKET_HPP

#include <stdio.h>
#include "SimpleSockets.hpp"

namespace ADASTRA
{
    class ConnectingSocket : public SimpleSocket
    {
    public:
        // Constructor
        ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);
        // Virtual function from parent
        int connect_to_network(int sock, struct sockaddr_in address);
    };

}

#endif