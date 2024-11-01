#ifndef SIMPLESERVER_HPP
#define SIMPLESERVER_HPP

#include <stdio.h>
#include <unistd.h>
#include "../hdelibc-networking.hpp"
#include "../Sockets/ListeningSocket.hpp"

namespace ADASTRA
{
    class SimpleServer
    {
    private:
        ListeningSocket *socket;
        virtual void accepter() = 0;
        virtual void handler() = 0;
        virtual void responder() = 0;

    public:
        SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklg);
        virtual void launch() = 0;
        ListeningSocket *get_socket();
    };
}

#endif