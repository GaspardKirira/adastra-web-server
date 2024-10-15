#ifndef SIMPLESOCKET_HPP
#define SIMPLESOCKET_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

namespace ADASTRA
{
    class SimpleSocket
    {
    private:
        struct sockaddr_in address;
        int sock;
        int connection;

    public:
        // Constructor
        SimpleSocket(int domain, int service, int protocole, int port, u_long interface);
        // Virtual function to connect to a network
        virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
        // Function to test socket and connections
        void test_connection(int);
        // Getter functions
        int get_sock();
        struct sockaddr_in get_address();
        int get_connection();
        void set_connection(int con);
    };
}

#endif
