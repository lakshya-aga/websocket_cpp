
#include <bits/stdc++.h>

// using namespace std;
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>


namespace net = boost::asio;
using tcp = net::ip::tcp;
using error_code = boost::system::error_code;
// Beast
namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace websocket = boost::beast::websocket;

#ifndef CHAT_SERVER_HPP
#define CHAT_SERVER_HPP
#include "chat_server.hpp"
#include "websocket_session.hpp"

void shared_state::join(websocket_session::websocket_session& session){
    sessions_.insert(session);
}

void shared_state::leave(websocket_session::websocket_session& session){
    session_.erase(session);
}

void shared_state::send(std::string message){
    auto ss = shared_ptr<std::string>(std::move(message));
    for(auto session: sessions_)
    session->send(ss);    
}

explicit shared_state::shared_state(std::string doc_root): doc_root_(doc_root){
    
}



#endif