#pragma once
#include "net.hpp"

class shared_state;
class websocket_session : public std::enable_shared_from_this<websocket_session>{
    beast::flat_buffer buffer_;
    websocket::stream<tcp::socket> ws_;
    std::shared_ptr<shared_state> state_;
    std::vector<std::shared_ptr<std::string const>> queue_;
    void fail(error_code ec, char const* ch);
    void on_accept(error_code ec);
    void on_write(error_code ec, size_t sz);
    void on_read(error_code ec, size_t sz);
    
    public:
    
    template <class Body, class Allocator>
    void run(http::request<Body, http::basic_fields<Allocator>> req){
        ws_.async_accept(req,
        [self = shared_from_this()](error_code ec){
            self->on_accept(ec);
        }
    );
    }
    ~websocket_session();
    websocket_session(std::shared_ptr<shared_state> const& state, tcp::socket socket);

    template<class Body, class Allocator>
    void handle_request(std::string const& doc_root,
        http::request<Body, http::basic_fields<Allocator>>&& req,
        std::function<void(http::response<http::string_body>)> send)
    {
        (void)doc_root;

        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, "websocket_cpp");
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = "hello from websocket_cpp";
        res.prepare_payload();
        send(std::move(res));
    }

    void send(std::shared_ptr<std::string const> const& ss);
};