#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <bits/stdc++.h>
#include <shared_state.h>
namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace beast = boost::beast;
namespace websocket = boost::beast::websocket;
namespace http = boost::beast::http;




    websocket_session::websocket_session(std::shared_ptr<shared_state> const& state, tcp::socket socket):state_(state), socket_(socket){}


    template <class Body, class Allocator>
    void websocket_session::run(http::request<Body, http::basic_fields<Allocator>> req){
        ws_.async_accept(req,
        [self = shared_from_this()](error_code ec){
            self->on_accept(ec);
        }
    );
    }

    void websocket_session::on_accept(error_code ec){
        if(ec)
        return fail(ec, "accept");

        state_->join(*this);

        ws_.async_read(
        buffer_,
        [sp = shared_from_this()](
        error_code ec, std::size_t bytes)
        {
        sp->on_read(ec, bytes);
        });
    }

    void websocket_session::on_read(error_code ec, std::size_t){
        if(ec)
        return fail(ec, "read");
        
        state_->send(beast::buffers_to_string(buffer_.data()));
        
        buffer_.consume(buffer_.size());
        ws_.async_read(buffer_, [sp = shared_from_this()](
        error_code ec, std::size_t bytes)
        {
        sp->on_read(ec, bytes);
        });
    }

    void send(std::shared_ptr<std::string const> const& ss){
        queue_.push_back(ss);
        if(queue_.size()>1){
            return;
        }
        ws_.async_write(net::buffer(*queue_.front()),
        [self = shared_from_this()](error_code ec, size_t bytes){
            self->on_write(ec, bytes);
        });
    
    }

    void on_write(error_code ec, size_t sz){
        if(ec)
        return fail(ec, "write");

        queue_.erase(queue_.begin());

        if(!queue_.empty()){
            ws_.async_write(
                net::buffer(*queue_.front()),
                [self = shared_from_this()](error_code ec, size_t sz){
                    self->on_write(ec, sz);
                }
            );
        }
    }

    void websocket_session::on_write(error_code ec, std::size_t){
        if(ec){
            return fail(ec, "write");
        }
        queue_.erase(queue_.begin());
        if(!queue_.empty())
        ws_.async_write(
            net::buffer(*queue_.front()),
            [sp = shared_from_this()](
            error_code ec, std::size_t bytes)
                {
                sp->on_write(ec, bytes);
                });
    }

    void websocket_session::fail(error_code ec, char const* what){
        // Don't report these
        if(ec == net::error::operation_aborted || ec == websocket::error::closed)
        return;
        std::cerr << what << ": " <<
        ec.message() << "\n";
    }

    websocket_session::~websocket_session(){
        state_->leave(*this);
    }