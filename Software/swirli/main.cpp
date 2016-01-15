#include <iostream>

#include "WashingMachine/Motor.h"

#include "libserial.h"
#include "Protocol.h"
#include "WashingMachine/UARTHandler.h"
#include "WashingMachine/UARTUser.h"
using namespace std;

class UARTTest : public WashingMachine::UARTUser{
public:
    UARTTest(WashingMachine::Motor &motor):
        motor(motor),
        WashingMachine::UARTUser{98}{

    }
    void main(){
        std::cout<<"starting motor"<<std::endl;
        motor.setRPM(100,this);
        sleep(1000);
        std::cout<<"stopping motor"<<std::endl;
        motor.setRPM(0,this);
    }
    void receiveReply(uint8_t replyByte){

    }

private:
    WashingMachine::Motor &motor;
};

class TaskTest: RTOS::task{
public:
    void main(){
        while(true){
            std::cout << "test" << std::endl;
            sleep(50);
        }

    }
};

int main() {
//    cout << "Hello, World!" << endl;
    LibSerial serial = LibSerial();
    serial.open("/dev/ttyAMA0", 9600);
    uint8_t commandOn[2];
    uint8_t commandOff[2];
    uint8_t commandStart[2];
    uint8_t commandTurn[2];

    commandOn[0]=SIGNAL_LED_REQ;
    commandOn[1]= ON_CMD;

    commandOff[0]=SIGNAL_LED_REQ;
    commandOff[1]=OFF_CMD;

    commandStart[0]=MACHINE_REQ;
    commandStart[1]=START_CMD;

    commandTurn[0]=SET_RPM_REQ;
    commandTurn[1]=0x00;

    serial.write(commandStart,2);
//    WashingMachine::UARTHandler handler(serial);
//    WashingMachine::Motor motor(handler);
//    UARTTest test(motor);
//    test.resume();
//    TaskTest test();


    class my_task_class : public RTOS::task {
    public:
        my_task_class( const char * name ):
                task(
                        10,    // task priority
                        name,  // name of the task
                        16384  // task stack size
                ){}
    private:
        void main( void ){
            while(true){
                std::cout << "test" << std::endl;
            }
            // put the code of your task here
        }
    };
    my_task_class my_task( "my first task" );
//    my_task_class my_task2( "my second task" );



    while(true){}
    return 0;
}

