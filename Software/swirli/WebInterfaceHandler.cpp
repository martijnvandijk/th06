#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "WebInterfaceHandler.h"

void WebInterfaceHandler::main() {
    while (true) {
        timer.set(1 S);
        wait();
        std::cout << "WebInterfaceHandler run" << std::endl;
        if (listener.packetsAvailable()) {
            std::cout << "Got packet!" << std::endl;
            auto webSocketPacket = listener.getPacket();

            rapidjson::Document &doc = webSocketPacket->getDoc();
            std::string request = doc["request"].GetString();
            std::cout << "WebInterfaceHandler: request is " << request << std::endl;

            rapidjson::StringBuffer sbuf;
            rapidjson::Writer<rapidjson::StringBuffer> writer(sbuf);
            writer.StartObject();


            if (request == "FetchTemperature") {
                writer.String("temperature");
                writer.Int(washingMachine.getTemperatureSensor().poll(this));
            }
            if (request == "FetchWashingPrograms") {

            }
            if (request == "FetchUserSettings"){
                std::cout << "procesing fetch user settings" << std::endl;
                writer.String("pin");
                writer.String("1234");
                writer.String("recovery");
                writer.String("01189998819991197253");
            }
            std::cout << "reply is: " << sbuf.GetString() << std::endl;
            WebSocket *ws = webSocketPacket->getWebsocket();
            try {
                ws->sendTextMessage(sbuf.GetString());
                std::cout << "Sent reply: " << sbuf.GetString();
            }
            catch (WebSocketException &e) {
                std::cout << "WebSockeException" << e.what() << std::endl;
            }
            catch (SocketException &e) {
                std::cout << "SocketException" << e.what() << std::endl;
            }

            writer.String("response");
            writer.String(request.c_str());
            writer.EndObject();
        }
    }
}

WebInterfaceHandler::WebInterfaceHandler(
        WashingMachine::WashingMachine &washingMachine,
        SwirliListener &swirliListener
) :
        washingMachine(washingMachine),
        WashingMachine::UARTUser::UARTUser{97},
        listener(swirliListener),
        timer{this, "webInterfaceHandler timer"}{ }
