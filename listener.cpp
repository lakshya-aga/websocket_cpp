#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;
namespace http = boost::beast::http;

namespace net = boost::asio;
using tcp = net::ip::tcp;


listener::run(){
    acceptor_.async_accept(
        socket_,
        [self](error_code ec){
            self->on_accept(ec);
        })
}

void listener::on_accpet(error_code ec){
    if(ec)
    fail(ec, "accept");
    else
    std::make_shared<http_session>(std::move(socket_),
    state)->run();

    acceptor_.async_accept(socket_,
    [self](error_code ec){
        self->on_accept(ec);
    })
}

void listener::fail(error_code ec, char const* what){

}