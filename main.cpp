#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 8080
#define BUFFER_SIZE 1024

class P2PServer
{
public:
    P2PServer()
    {
        SSL_load_error_strings();
        OpenSSL_add_ssl_algorithms();
        ctx = SSL_CTX_new(TLS_server_method());
        if (!ctx)
        {
            perror("Unable to create SSL context");
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }
        SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM);
        SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM);
    }

    ~P2PServer()
    {
        SSL_CTX_free(ctx);
        EVP_cleanup();
    }

    void start()
    {
        int server_fd, client_fd;
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        char buffer[BUFFER_SIZE];

        // Créer un socket TCP
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd < 0)
        {
            perror("Socket creation error");
            exit(EXIT_FAILURE);
        }

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(PORT);

        // Lier le socket
        if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("Bind error");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Écouter les connexions entrantes
        if (listen(server_fd, 1) < 0)
        {
            perror("Listen error");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        std::cout << "Serveur en attente de connexions sur le port " << PORT << "...\n";

        // Accepter une connexion
        client_fd = accept(server_fd, (struct sockaddr *)&addr, &len);
        if (client_fd < 0)
        {
            perror("Accept error");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Créer un nouvel objet SSL
        SSL *ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client_fd);

        // Effectuer la handshake SSL
        if (SSL_accept(ssl) <= 0)
        {
            ERR_print_errors_fp(stderr);
        }
        else
        {
            // Recevoir un message
            int bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1);
            if (bytes > 0)
            {
                buffer[bytes] = 0; // Ajout d'un terminateur null
                std::cout << "Message reçu: " << buffer << std::endl;
            }

            // Répondre au client
            const char *reply = "Message reçu avec succès!";
            SSL_write(ssl, reply, strlen(reply));
        }

        // Nettoyage
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client_fd);
        close(server_fd);
    }

private:
    SSL_CTX *ctx;
};

template <typename T>
void print(std::vector<T> &v) {
};

int main()
{
    P2PServer server;
    server.start();
    return 0;
}
