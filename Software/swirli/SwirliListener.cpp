//
// Created by martijn on 1/21/16.
//

#include "SwirliListener.h"

void SwirliListener::onTextMessage(const string &s, WebSocket *ws) {
    try {
        std::shared_ptr<WebSocketPacket> webSocketPacket(
                new WebSocketPacket(s.c_str(), ws)
        );
        packetQueue.push(webSocketPacket);
    }
    catch (invalid_argument &e) {
        std::cerr << e.what() << std::endl;
    }
}

void SwirliListener::onClose(WebSocket *ws) {
    delete ws;
}

bool SwirliListener::packetsAvailable() {
    bool available;
    pQMutex.lock();
    available = !(packetQueue.empty());
    pQMutex.unlock();
    return available;
}

std::shared_ptr<WebSocketPacket> SwirliListener::getPacket() {
    std::shared_ptr<WebSocketPacket> webSocketPacket;
    pQMutex.lock();
    webSocketPacket = packetQueue.front();
    packetQueue.pop();
    pQMutex.unlock();


    return webSocketPacket;
}
