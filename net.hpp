#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

#include <bits/stdc++.h>

namespace beast     = boost::beast;
namespace http      = boost::beast::http;
namespace websocket = boost::beast::websocket;
namespace net       = boost::asio;

using tcp        = net::ip::tcp;
using error_code = boost::system::error_code;