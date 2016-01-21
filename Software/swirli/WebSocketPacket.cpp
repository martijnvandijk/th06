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
    Document document;
    document.Parse(json);
    if (document["request"].IsString()) {
        if (
                !(
                        document["request"] == "FetchUserSettings" ||
                        document["request"] == "FetchUpdate" ||
                        document["request"] == "UpdateUser" ||
                        document["reuqest"] == "FetchWashingProgram" ||
                        document["reuqest"] == "StartWashingProgram" ||
                        document["reuqest"] == "StopWashingProgram" ||
                        document["reuqest"] == "FetchWashingState" ||
                        document["request"] == "FetchWashingTime"
                )
                ) {
            throw invalid_argument("Invalid JSON request!");
        }
    }
}

rapidjson::Document &WebSocketPacket::getDoc() {
    return doc;
}

WebSocket * WebSocketPacket::getWebsocket() {
    return ws;
}
