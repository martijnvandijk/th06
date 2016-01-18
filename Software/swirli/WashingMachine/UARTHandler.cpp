//
// Created by martijn on 1/14/16.
//

#include "UARTHandler.h"
#include "pRTOS.h"
#include "Protocol.h"
namespace WashingMachine {
    UARTHandler::UARTHandler(LibSerial &serial) :
            serialConnection(serial),
            InputBuffer(this),
            OutputBuffer(),
            inputQueueCounter{0},
            timer(this)
            {}

    void UARTHandler::sendMessage(UARTMessage m) {
        InputBuffer.write(m);
        inputQueueCounter++;
        m.sender->suspend();
    }

    void UARTHandler::main(){
        while(true){
            timer.set(10 MS);
            RTOS::event event = wait(InputBuffer + timer);

            if(event == InputBuffer){
                UARTMessage message = InputBuffer.read();
                serialConnection.writeChar(message.requestByte);
                serialConnection.writeChar(message.commandByte);
                OutputBuffer.push_back(message);
            }
            else{
                if(serialConnection.peek() >= 2 ){
                    uint8_t readBuf[2];
                    serialConnection.read(&readBuf, 2);
                    if((OutputBuffer.front().requestByte | REPLY_BIT) == readBuf[0]){
                        OutputBuffer.front().sender->receiveReply(readBuf[1]);
                        OutputBuffer.front().sender->resume();
                        OutputBuffer.pop_front();
                    }
                }
            }
        }
    }
}