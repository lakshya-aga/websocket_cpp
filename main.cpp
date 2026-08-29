#include "net.hpp"
#include "websocket_session.hpp"
#include "listener.hpp"
#include "shared_state.hpp"
#include "http_session.hpp"
int main(int argc, char** argv) {
    auto address = net::ip::make_address(argv[1]);
    auto port = (unsigned short)std::atoi(argv[2]);
    auto doc_root = std::string(argv[3]);
    net::io_context ioc;

    std::make_shared<listener>(
        ioc,
        tcp::endpoint{address, port},
        std::make_shared<shared_state>(doc_root))->run();

    ioc.run();

    return EXIT_SUCCESS;
    
}