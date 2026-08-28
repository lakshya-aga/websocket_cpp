#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <unordered_set>
namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;
namespace http = boost::beast::http;

namespace net = boost::asio;
using tcp = net::ip::tcp;

#include "websocket_session.hpp"

class listener: public std::enable_shared_from_this<listener>
{
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    std::shared_ptr<shared_state> shared_state_;


    void fail(error_code ec, char const* what);
    void on_accept(error_code ec);

    public:
    void run();
    listener(tcp::acceptor acceptor_, 
    tcp::socket socket_,
    std::shared_ptr<shared_state> shared_state
    );
};