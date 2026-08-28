#pragma once
#include "net.hpp"

#include "listener.hpp"
#include "http_session.hpp"

void listener::run(){
    acceptor_.async_accept(
        socket_,
        [self = shared_from_this()](error_code ec){
            self->on_accept(ec);
        });
}

void listener::on_accept(error_code ec){
    if(ec)
    fail(ec, "accept");
    else
    std::make_shared<http_session>(std::move(socket_),
    state_)->run();

    acceptor_.async_accept(socket_,
    [self = shared_from_this()](error_code ec){
        self->on_accept(ec);
    });
}

void listener::fail(error_code ec, char const* what){

}

