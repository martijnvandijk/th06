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
        std::cout << "Pushed websocketpacket, queuesize: " << packetQueue.size() << std::endl;
        std::cout << "PacketsAvailable output: " << packetsAvailable() << std::endl;
\    }
    catch (invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
}

void SwirliListener::onClose(WebSocket *ws) {
    delete ws;
}

bool SwirliListener::packetsAvailable() {
    bool available;

    std::cout << "PacketQueue size: " << packetQueue.size() << std::endl;
    if (packetQueue.size() > 0) {
        available = true;
    } else {
        available = false;
    }
    return available;
}

std::shared_ptr<WebSocketPacket> SwirliListener::getPacket() {
    std::shared_ptr<WebSocketPacket> webSocketPacket;

    webSocketPacket = packetQueue.front();
    std::cout << "popped packet!" << std::endl;
    packetQueue.pop();


    return webSocketPacket;
}


