#include "WebInterfaceHandler.h"

void WebInterfaceHandler::main() {
    while (true) {
        timer.set(20 MS);
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
            if (request == "FetchWashingProgram") {
                writer.String("programs");
                writer.StartObject();

                DIR *d{opendir("WashingPrograms")};
                if (d) {
                    struct dirent *nextFile;
                    while ((nextFile = readdir(d)) != NULL) {
                        std::string name{nextFile->d_name};
                        if (name != "." && name != "..") {
                            unsigned long lastindex = name.find_last_of(".");
                            if (lastindex != std::string::npos) {
                                std::string extension = name.substr(lastindex, name.size() - lastindex);
                                if (extension == ".json") {
                                    std::string rawname = name.substr(0, lastindex);

                                    std::cout << "sending info for program " << rawname << std::endl;

                                    WashingProgram washingProgram{rawname, 0, washingMachine, temperatureRegulator, waterLevelRegulator};
                                    washingProgram.writeJSONInfo(writer);
                                }
                            }
                        }
                    }

                    closedir(d);
                } else {
                    // TODO maybe throw something
                }

                writer.EndObject();
            }
            if (request == "FetchUserSettings"){
                std::cout << "procesing fetch user settings" << std::endl;
                rapidjson::Document document{};
                FILE * file{fopen("UserData/UserSettings.json", "r")};
                char *readBuffer{new char[65536]};
                rapidjson::FileReadStream fileReadStream{file, readBuffer, 65536};
                document.ParseStream(fileReadStream);
                writer.Key("settings");

                document.Accept(writer);
                fclose(file);
                delete[] readBuffer;
            }
            if (request == "UpdateUser"){
                std::cout << "procesing store user settings" << std::endl;

                FILE * file{fopen("UserData/UserSettings.json", "w")};
                char *readBuffer{new char[65536]};
                rapidjson::FileWriteStream fileWriteStream{file, readBuffer, 65536};
                rapidjson::Writer<rapidjson::FileWriteStream> settingsWriter{fileWriteStream};

                settingsWriter.StartObject();
                settingsWriter.Key("pin");
                settingsWriter.String(doc["Parameters"]["Pin"].GetString());
                settingsWriter.Key("recovery");
                settingsWriter.String(doc["Parameters"]["RecoveryMethod"].GetString());
                settingsWriter.EndObject();

                ftruncate(fileno(file), ftell(file));
                fclose(file);
                delete[] readBuffer;
            }
            if (request == "StartWashingProgram") {
                std::cout << "starting program " << doc["parameters"]["program"].GetString() << " with temperature " << doc["parameters"]["temperature"].GetInt();
                washingController.start(doc["parameters"]["program"].GetString(), doc["parameters"]["temperature"].GetInt(), doc["parameters"]["delay"].GetInt());
            }
            if (request == "StopWashingProgram") {
                std::cout << "stopping program" << std::endl;
                washingController.stop();
            }
            if (request == "Status") {
                writer.Key("temp");
                writer.Int(washingController.getTemperature());
                writer.Key("time");
                writer.Int(washingController.isStopped() ? 0 : (int)(time(nullptr) - washingController.timeStarted()));
            }
            writer.Key("response");
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
        TemperatureRegulator &temperatureRegulator,
        WaterLevelRegulator &waterLevelRegulator,
        WashingController &washingController,
        SwirliListener &swirliListener
) :
        washingMachine(washingMachine),
        temperatureRegulator(temperatureRegulator),
        waterLevelRegulator(waterLevelRegulator),
        washingController(washingController),
        UARTUser{97, "WebInterface"},
        listener(swirliListener),
        timer{this, "webInterfaceHandler timer"}{ }
