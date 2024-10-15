#ifndef LISTEINGSOCKET_HPP
#define LISTEINGSOCKET_HPP

#include <stdio.h>
#include "BindingSocket.hpp"

namespace ADASTRA
{
    class ListeningSocket : public BindingSocket
    {
    private:
        int backlog;
        int listening;

    public:
        ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg);
        void start_listening();
        int get_listening();
        int get_backlog();
    };
}

#endif