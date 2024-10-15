#include "BindingSocket.hpp"

// Constructor
ADASTRA::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface)
    : SimpleSocket(domain, service, protocol, port, interface)
{
    if (connect_to_network(get_sock(), get_address()) < 0)
    {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }
    test_connection(get_sock());
}

// Definition of connect_to_network virtual function
int ADASTRA::BindingSocket::connect_to_network(int sock, struct sockaddr_in address)
{
    int bind_result = bind(sock, (struct sockaddr *)&address, sizeof(address));
    return bind_result;
}

int ADASTRA::BindingSocket::get_binding()
{
    return binding;
}
