//
// Created by martijn on 1/21/16.
//

#ifndef SWIRLI_SWIRLILISTENER_H
#define SWIRLI_SWIRLILISTENER_H

#include <mutex>
#include <queue>
#include <networking/websocket.h>
#include "WebSocketPacket.h"

class SwirliListener : public WebSocketListener {
public:
    void onTextMessage(const string &s, WebSocket *ws);

    void onClose(WebSocket *ws);

    bool packetsAvailable();

    std::shared_ptr<WebSocketPacket> getPacket();

private:
    std::queue<std::shared_ptr<WebSocketPacket>> packetQueue;
    std::mutex pQMutex;
};




#endif //SWIRLI_SWIRLILISTENER_H
