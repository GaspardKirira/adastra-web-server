#include "SimpleServer.hpp"

namespace ADASTRA
{
    class TestServer : public SimpleServer
    {
    private:
        char buffer[3000] = {0};
        int new_socket;
        void accepter();
        void handler();
        void responder();

    public:
        TestServer();
        void launch();
    };
}
