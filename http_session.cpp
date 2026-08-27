http_session::http_session(
 tcp::socket socket,
 std::shared_ptr<shared_state> const& state)
 : socket_(std::move(socket))
 , state_(state)
{
}

void http_session::run()
{
 // Read a request
 http::async_read(socket_, buffer_, req_,
 [self = shared_from_this()]
 (error_code ec, std::size_t bytes)
 {
 self->on_read(ec, bytes);
 });
}

void http_session::on_read(error_code ec, std::size_t)
{
    if(ec == http::error::end_of_stream){
        socket_.shutdown(tcp::socket::shutdown_send, ec);
        return;
    }
    if(ec)
    return fail(ec, "read");

    if(websocket::is_upgrade(req_)){
        std::make_shared<websocket_session>(
        std::move(socket_), state_)->run(std::move(req_));
        return;
    }
    handle_request(state_->doc_root(), std::move(req_),
    [this](auto&& response)
    {
        using response_type = typename std::decay<decltype(response)>::type;
        auto sp = std::make_shared<response_type>(std::move(response));
        http::async_write(this->socket_, *sp,
        [self = shared_from_this(), sp](error_code ec, std::size_t bytes)
        {
        self->on_write(ec, bytes, sp->need_eof());
        });
    });
}

void http_session::on_write(error_code ec, std::size_t, bool close)
{
    if(ec)
    return fail(ec, "write");
    if(close){
        socket_.shutdown(tcp::socket::shutdown_send, ec);
        return;
    }
    req_ = {};

    http::async_read(socket_, buffer_, req_,
    [self = shared_from_this()]
    (error_code ec, std::size_t bytes)
    {
        self->on_read(ec, bytes);
    });
}