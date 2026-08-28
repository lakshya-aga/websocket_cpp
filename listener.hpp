#pragma once
#include "net.hpp"
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
    acceptor_.open(ep.protocol(), ec);                                if(ec) { fail(ec, "open"); return;}
    acceptor_.set_option(net::socket_base::reuse_address(true), ec);  if(ec) { fail(ec, "set_option"); return;}
    acceptor_.bind(ep, ec);                                           if(ec) { fail(ec, "bind"); return;}
    acceptor_.listen(net::socket_base::max_listen_connections, ec);   if(ec) { fail(ec, "listen"); return;}
}
};