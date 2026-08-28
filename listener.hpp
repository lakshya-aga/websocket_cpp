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
    std::shared_ptr<shared_state> state_;


    void fail(error_code ec, char const* what);
    void on_accept(error_code ec);

    public:
    void run();
    listener::listener(net::io_context& ioc, tcp::endpoint ep, std::shared_ptr<shared_state> state)
    : acceptor_(ioc)          // executor supplied here
    , socket_(ioc)
    , state_(std::move(state))
    {
        error_code ec;
        acceptor_.open(ep.protocol(), ec);                                if(ec) return fail(ec, "open");
        acceptor_.set_option(net::socket_base::reuse_address(true), ec);  if(ec) return fail(ec, "set_option");
        acceptor_.bind(ep, ec);                                           if(ec) return fail(ec, "bind");
        acceptor_.listen(net::socket_base::max_listen_connections, ec);   if(ec) return fail(ec, "listen");
    }   
};