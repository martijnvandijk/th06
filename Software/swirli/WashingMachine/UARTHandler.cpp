//
// Created by martijn on 1/14/16.
//

#include "UARTHandler.h"
#include "Protocol.h"
namespace WashingMachine {
    UARTHandler::UARTHandler(LibSerial &serial) :
		    RTOS::task{1000, "UARTHandler"},
            serialConnection(serial),
            InputBuffer{this, "UARTHandler InputBuffer"},
            OutputBuffer{},
            timer{this, "UARTHandler timer"}
    {}

    void UARTHandler::sendMessage(UARTMessage m) {
        InputBuffer.write(m);
        m.sender->suspend();
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    void UARTHandler::main(){
        while(true){
            timer.set(10 MS);
            RTOS::event event = wait(InputBuffer + timer);

            if(event == InputBuffer){
                UARTMessage message = InputBuffer.read();
//                std::cout << "sent " << std::hex << (int(message.requestByte)) << ", " << (int(message.commandByte)) << std::dec << std::endl;
                serialConnection.writeChar(message.requestByte);
                serialConnection.writeChar(message.commandByte);
//                serialConnection.flush();
                OutputBuffer.push(message);
            }
            else{
                if(serialConnection.peek() >= 2 ){
                    uint8_t readBuf[2];
                    serialConnection.read(&readBuf, 2);
//                    std::cout << "received " << std::hex << (int(readBuf[0])) << ", " << (int(readBuf[1])) << std::dec << std::endl;
                    if((OutputBuffer.front().requestByte | REPLY_BIT) == readBuf[0]){
                        OutputBuffer.front().sender->receiveReply(readBuf[1]);
                        OutputBuffer.front().sender->resume();
                        OutputBuffer.pop();
                    }
                }
            }
        }
    }
#pragma clang diagnostic pop
}