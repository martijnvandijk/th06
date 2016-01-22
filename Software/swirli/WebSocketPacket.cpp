//
// Created by martijn on 1/20/16.
//

#include "WebSocketPacket.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

WebSocketPacket::WebSocketPacket(const char *json, WebSocket *ws) :
        ws{ws} {
//    Document document;
    std::cout << "WebSocketPacket: " << json << std::endl;
    doc.Parse(json);
    if (doc["request"].IsString()) {
        if (
                !(
                        doc["request"] == "FetchUserSettings" ||
                        doc["request"] == "FetchUpdate" ||
                        doc["request"] == "UpdateUser" ||
                        doc["request"] == "FetchWashingProgram" ||
                        doc["request"] == "StartWashingProgram" ||
                        doc["request"] == "StopWashingProgram" ||
                        doc["request"] == "FetchWashingState" ||
                        doc["request"] == "FetchWashingTime"
                )
                ) {
            throw invalid_argument("Invalid JSON request!");
        }
    } else {
        throw invalid_argument("Invalid JSON request!");
    }
}

rapidjson::Document &WebSocketPacket::getDoc() {
    return doc;
}

WebSocket *WebSocketPacket::getWebsocket() {
    return ws;
}
