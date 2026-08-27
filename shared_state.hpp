#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;
namespace http = boost::beast::http;

namespace net = boost::asio;
using tcp = net::ip::tcp;

class shared_state{
    std::string doc_root_;
    std::unordered_set<Websocket_session*> sessions_;
    public:
        explicit shared_state(std::string doc_root);
        std::string const& doc_root() const noexcept;
        void join(Websocket_session session);
        void leave(Websocket_session session);
        void send(std::string message);
};