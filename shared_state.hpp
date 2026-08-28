#pragma once

#include "net.hpp"

class websocket_session;
class shared_state;
#include "websocket_session.hpp"
class shared_state{
    std::string doc_root_;
    std::unordered_set<websocket_session*> sessions_;
    public:
        explicit shared_state(std::string doc_root);
        std::string const& doc_root() const noexcept;
        void join(websocket_session& session);
        void leave(websocket_session& session);
        void send(std::string message);
};