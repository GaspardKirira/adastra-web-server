#include "SimpleSockets.hpp"

// Default constructor
ADASTRA::SimpleSocket::SimpleSocket(int domain, int service, int protocole, int port, u_long interface)
{
    // Define address structure
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);
    // Establish connection
    sock = socket(domain, service, protocole);
    test_connection(sock);
}

// Test connection virtual function
void ADASTRA::SimpleSocket::test_connection(int item_to_test)
{
    // Confirmst that sockt or connection has been properly
    if (item_to_test < 0)
    {
        perror("Failed to connect...");
        exit(EXIT_FAILURE);
    }
}

// Getter function
struct sockaddr_in ADASTRA::SimpleSocket::get_address()
{
    return address;
}

int ADASTRA::SimpleSocket::get_sock()
{
    return sock;
}

void ADASTRA::SimpleSocket::set_connection(int con)
{
    connection = con;
}

int ADASTRA::SimpleSocket::get_connection()
{
    return connection;
}
