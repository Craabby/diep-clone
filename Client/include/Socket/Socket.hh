#pragma once

#include <functional>
#include <string>

#ifndef __EMSCRIPTEN__
#include <IXWebSocket.h>
#else
#include <emscripten/socket.h>
#endif

namespace client
{
    // header only file for simplicity

#ifndef __EMSCRIPTEN__
    class Socket
    {
        ix::WebSocket socket;

    public:
        Socket(const std::string &url, std::function<void(const std::vector<uint8_t> &)> onData, std::function<void()> onOpen)
        {
            socket.setUrl(url);
            socket.disableAutomaticReconnection();
            socket.setOnMessageCallback([onData, onOpen](const ix::WebSocketMessagePtr &message)
                                        {
                if (message->type == ix::WebSocketMessageType::Open)
                {
                    onOpen();
                }
                else if (message->type == ix::WebSocketMessageType::Message)
                {
                    std::vector<uint8_t> data;
                    data.reserve(message->str.size());
                    for (size_t i = 0; i < message->str.size(); i++)
                        data.push_back((uint8_t)message->str.at(i));


                    onData(data);
                } });

            socket.start();
        }
    };
#endif
}
