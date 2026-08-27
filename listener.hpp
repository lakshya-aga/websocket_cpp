#include <bits/stdc++.h>

// using namespace std;
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

#include "websocket_session.hpp"

class listener: public make_shared_from_this<listener>
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