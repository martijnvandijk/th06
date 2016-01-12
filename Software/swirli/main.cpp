#include <iostream>
#include "libserial.h"
#include "Protocol.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    LibSerial serial = LibSerial();
    serial.open("/dev/ttyAMA0", 9600);
    char* command = []
    return 0;
}