//
// Created by martijn on 1/20/16.
//

#ifndef SWIRLI_WEBSOCKETPACKET_H
#define SWIRLI_WEBSOCKETPACKET_H


#include <networking/websocket.h>
#include <rapidjson/document.h>

class WebSocketPacket {
public:
    WebSocketPacket(const char *json, WebSocket *ws);
    rapidjson::Document &getDoc();

    WebSocket * getWebsocket();

private:
    rapidjson::Document doc;
    WebSocket *ws;
};


#endif //SWIRLI_WEBSOCKETPACKET_H
