#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <fstream>
#include "WebInterfaceHandler.h"

void WebInterfaceHandler::main() {
    while (true) {
        timer.set(1 S);
        wait();
//        std::cout << "WebInterfaceHandler run" << std::endl;
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
                rapidjson::Document document{};
                FILE * file{fopen("UserData/UserSettings.json", "r")};
                char *readBuffer = new char[65536];
                rapidjson::FileReadStream fileReadStream{file, readBuffer, 65536};
                document.ParseStream(fileReadStream);
                writer.String("settings");

                document.Accept(writer);
                fclose(file);
                delete[] readBuffer;
            }
            writer.String("response");
            writer.String(request.c_str());
            writer.EndObject();


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
