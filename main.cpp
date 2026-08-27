#include <bits/stdc++.h>
namespace net = boost::asio;
using tcp = net::ip::tcp;
using error_code = boost::system::error_code;
// Beast
namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace websocket = boost::beast::websocket;
#include <bits/stdc++.h>

// using namespace std;
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

#include "websocket_session.hpp"
#include "listener.hpp"
#include "shared_state.hpp"
#include "http_state.hpp"



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