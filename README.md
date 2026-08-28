# Websocket Implementation in cpp

Networking is one of the areas where C++ lacks native support. Making it much harder to build a server. Websocket even more so.

I use boost beast (not part of standard as of 26/08/26). I referenced the code from a CppCon18 talk for this to start with a chat server to evolve it into a paddle pong multiplayer game later and maybe just maybe my attempt at index arbitraging.

It contains 

http_session

shared_state

websocket_session

listener

main


for core functionalities and for driving the server.

We additionally add an html page for the user interface.

## Demo

In progress: lakshya-aga.github.io/cpp_chat