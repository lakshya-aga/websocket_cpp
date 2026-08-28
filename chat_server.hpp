// #include <bits/stdc++.h>

// // using namespace std;
// #include <boost/beast/core.hpp>
// #include <boost/beast/http.hpp>
// #include <boost/beast/version.hpp>
// #include <boost/asio.hpp>

// #include 'websocket_session.hpp'


// namespace net = boost::asio;
// using tcp = net::ip::tcp;
// using error_code = boost::system::error_code;
// // Beast
// namespace beast = boost::beast;
// namespace http = boost::beast::http;
// namespace websocket = boost::beast::websocket;

// class shared_state
// {
// std::string doc_root_;
// std::unordered_set<websocket_session*> sessions_;
// public:
//         explicit shared_state(std::string doc_root);
//         std::string const& doc_root() const noexcept {
//             return doc_root_;
//         }
//         void join (websocket_session& session);
//         void leave (websocket_session& session);
//         void send (std::string message);
// };