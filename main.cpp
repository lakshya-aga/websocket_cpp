#pragma once
#include "net.hpp"
#include "websocket_session.hpp"
#include "listener.hpp"
#include "shared_state.hpp"
#include "http_session.hpp"
#include <bits/stdc++.h>
int main(int argc, char** argv) {
    auto address = argv[1];
    auto port = argv[2];
    auto doc_root = std::atoi(argv[3]);
    net::io_context ioc;

    std::make_shared<listener>(
        ioc,
        tcp::endpoint{address, port},
        std::make_shared<shared_state>(doc_root))->run();

    ioc.run();

    return EXIT_SUCCESS;
    
}