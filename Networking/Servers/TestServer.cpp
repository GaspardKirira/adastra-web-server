#include "TestServer.hpp"
#include <cstring>

ADASTRA::TestServer::TestServer()
    : SimpleServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
    launch();
}

void ADASTRA::TestServer::accepter()
{
    struct sockaddr_in address = get_socket()->get_address();
    socklen_t addrlen = sizeof(address);
    new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, &addrlen);

    if (new_socket < 0)
    {
        perror("Accept failed");
        return;
    }

    ssize_t bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0)
    {
        perror("Read failed");
        close(new_socket);
        return;
    }

    buffer[bytes_read] = '\0'; // Ajoute un terminateur de chaîne
}

void ADASTRA::TestServer::handler()
{
    std::cout << "Received: " << buffer << std::endl; // Affiche le contenu du buffer
}

void ADASTRA::TestServer::responder()
{
    const char *response_header = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
    const char *response_body = "Bonsoir c'est Gaspard kirira!";

    // Envoie l'en-tête de la réponse
    write(new_socket, response_header, strlen(response_header));
    // Envoie le corps de la réponse
    write(new_socket, response_body, strlen(response_body));

    close(new_socket);
}

void ADASTRA::TestServer::launch()
{
    while (true)
    {
        std::cout << "************* WAITING ***************" << std::endl;
        accepter();
        handler();
        responder();
        std::cout << "===== DONE ======" << std::endl;
    }
}
