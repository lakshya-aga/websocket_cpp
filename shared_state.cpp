#pragma once
#include "net.hpp" 
#include "shared_state.hpp"
#include "websocket_session.hpp"

shared_state::shared_state(std::string doc_root): doc_root_(doc_root){
}

std::string const& shared_state::doc_root() const noexcept{
    return doc_root_;
}
void shared_state::join(websocket_session& session){
    sessions_.insert(&session);
}
void shared_state::leave(websocket_session& session){
    sessions_.erase(&session);
}

void shared_state::send(std::string message){
    auto ss = make_shared<std::string>(std::move(message));
    for(auto session: shared_state::sessions_)
    session->send(ss);
}
