# syntax=docker/dockerfile:1

# ---------- build stage ----------
FROM debian:trixie-slim AS build

# libboost-dev is headers only -- Beast, Asio and Boost.System are all
# header-only, so no compiled Boost libraries are needed.
RUN apt-get update \
 && apt-get install -y --no-install-recommends g++ libboost-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /src

# Headers first so edits to a .cpp don't invalidate the apt layer above.
COPY net.hpp http_session.hpp listener.hpp shared_state.hpp websocket_session.hpp ./
COPY main.cpp http_session.cpp listener.cpp shared_state.cpp websocket_session.cpp ./

# -pthread is the only link requirement; Asio needs it on Linux.
RUN g++ -std=c++17 -O2 -Wall -Wextra -pthread \
      main.cpp http_session.cpp listener.cpp shared_state.cpp websocket_session.cpp \
      -o /chat_server

# ---------- runtime stage ----------
FROM debian:trixie-slim

RUN useradd --system --uid 10001 --no-create-home app

COPY --from=build /chat_server /app/chat_server
COPY index.html /app/www/index.html

USER app
EXPOSE 8080

# argv: <address> <port> <doc_root>
ENTRYPOINT ["/app/chat_server", "0.0.0.0", "8080", "/app/www"]
