//
// Created by martijn on 1/21/16.
//

#include "SwirliListener.h"

void SwirliListener::onTextMessage(const string &s, WebSocket *ws) {
    try {
        std::shared_ptr<WebSocketPacket> webSocketPacket(
                new WebSocketPacket(s.c_str(), ws)
        );
        webInterfaceHandler.handleRequest(webSocketPacket);
    }
    catch (invalid_argument &e) {
        std::cerr << e.what() << std::endl;
    }
}

void SwirliListener::onClose(WebSocket *ws) {
    delete ws;
}

SwirliListener::SwirliListener(WebInterfaceHandler &webInterfaceHandler) :
        webInterfaceHandler{webInterfaceHandler} { }
