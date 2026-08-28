
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;
namespace http = boost::beast::http;

namespace net = boost::asio;
using tcp = net::ip::tcp;

#include "shared_state.hpp"
#include "websocket_session.hpp"

explicit shared_state::shared_state(std::string doc_root): doc_root_(doc_root){
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
