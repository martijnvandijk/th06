#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "WebInterfaceHandler.h"

void WebInterfaceHandler::main() {
    while (true) {
        if (listener.packetsAvailable()) {
            auto webSocketPacket = listener.getPacket();

            rapidjson::Document &doc = webSocketPacket->getDoc();
            std::string request = doc["request"].GetString();
            std::cout << "WebInterfaceHandler: request is " << request << std::endl;

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
}

/*
WebInterfaceHandler::WebInterfaceHandler(
        WashingMachine::WashingMachine &washingMachine,
        SwirliListener &swirliListener
) :
        washingMachine{washingMachine},
        WashingMachine::UARTUser::UARTUser(97),
        listener{swirliListener}
*/
WebInterfaceHandler::WebInterfaceHandler(
        WashingMachine::WashingMachine &washingMachine,
        SwirliListener &swirliListener
) :
        washingMachine{washingMachine},
        WashingMachine::UARTUser::UARTUser(97),
        listener{swirliListener} { }
