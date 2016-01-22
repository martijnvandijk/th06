#ifndef SWIRLI_WEBSOCKETHANDLER_H
#define SWIRLI_WEBSOCKETHANDLER_H

#include "networking/websocket.h"
#include "WebInterfaceHandler.h"
#include "SwirliListener.h"


class WebSocketHandler {
public:
    WebSocketHandler(int port, WebInterfaceHandler &web);

    void runServer();

    std::thread spawnWebSocketHandler();

    void sendMessage();

private:
    int port;
//    std::list<WebSocket *> clients;
    SwirliListener listener;
};

#endif