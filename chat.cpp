// #include <bits/stdc++.h>

// // using namespace std;
// #include <boost/beast/core.hpp>
// #include <boost/beast/http.hpp>
// #include <boost/beast/version.hpp>
// #include <boost/asio.hpp>


// namespace net = boost::asio;
// using tcp = net::ip::tcp;
// using error_code = boost::system::error_code;
// // Beast
// namespace beast = boost::beast;
// namespace http = boost::beast::http;
// namespace websocket = boost::beast::websocket;




// class listener:
// public std::enable_shared_from_this<listener>
// {
//     tcp::acceptor acceptor_;
//     tcp::socket socket_;
//     std::shared_ptr<shared_state> state;

//     void fail(error_code ed, char const * what);
//     void on_accpet(error_code ec);

//     public:
//     listener(net::io_context& ioc,
//         tcp::endpoint endpoint,
//         shared_ptr<shared_state> state);

//     void run();

//     void run(){
//         acceptor_.async_accept(
//             socket,
//             [self = shared_from_this()](error_code ec){
//                 self->on_accpet(ec);
//             }
//         )
//     }
// };