#include <bits/stdc++.h>

// using namespace std;
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

#include 'websocket_session.hpp'


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