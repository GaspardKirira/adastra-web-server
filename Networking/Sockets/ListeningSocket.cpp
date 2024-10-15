#include "ListeningSocket.hpp"

ADASTRA::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg)
    : BindingSocket(domain, service, protocol, port, interface)
{
    backlog = bklg;
    start_listening();
    test_connection(get_sock());
}

void ADASTRA::ListeningSocket::start_listening()
{
    int listen_result = listen(get_sock(), backlog);
    if (listen_result < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
}

int ADASTRA::ListeningSocket::get_listening()
{
    return listening;
}

int ADASTRA::ListeningSocket::get_backlog()
{
    return backlog;
}
