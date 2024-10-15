#include "SimpleServer.hpp"

ADASTRA::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklg)
{
    socket = new ListeningSocket(domain, service, protocol, port, interface, bklg);
}

ADASTRA::ListeningSocket *ADASTRA::SimpleServer::get_socket()
{
    return socket;
}