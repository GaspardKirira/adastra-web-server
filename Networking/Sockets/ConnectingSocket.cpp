
#include "ConnectingSocket.hpp"

ADASTRA::ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, u_long interface) : SimpleSocket(domain, service, protocol, port, interface)
{
    set_connection(connect_to_network(get_sock(), get_address()));
    test_connection(get_connection());
}

// Definition of the connect_to_network virtual function
int ADASTRA::ConnectingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
    return connect(sock, (struct sockaddr *)&address, sizeof(address));
}