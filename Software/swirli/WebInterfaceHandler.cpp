#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "WebInterfaceHandler.h"

void WebInterfaceHandler::handleRequest(std::shared_ptr<WebSocketPacket> &webSocketPacket) {
    InputQueue.write(webSocketPacket);
}

void WebInterfaceHandler::main() {
    while (true) {
        auto webSocketPacket = InputQueue.read();
        rapidjson::Document &doc = webSocketPacket->getDoc();
        std::string request = doc["request"].GetString();

        rapidjson::StringBuffer sbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(sbuf);
        writer.StartObject();


        if (request == "fetchTemperature") {
            washingMachine.getTemperatureSensor().poll(this);
            writer.String("temperature");
            writer.Int(replyPool.read());
        }
        if (request == "fetchWashingPrograms") {

        }

        WebSocket *ws = webSocketPacket->getWebsocket();
        try {
            ws->sendTextMessage(sbuf.GetString());
        }
        catch (WebSocketException &e) {
            std::cerr << "WebSockeException" << e.what() << std::endl;
        }
        catch (SocketException &e) {
            std::cerr << "SocketException" << e.what() << std::endl;
        }

    }
}

WebInterfaceHandler::WebInterfaceHandler(
        WashingMachine::WashingMachine &washingMachine
) :
        washingMachine{washingMachine},
        InputQueue(this, "WebInterfaceInputQueue"),
        WashingMachine::UARTUser::UARTUser(97) { }
