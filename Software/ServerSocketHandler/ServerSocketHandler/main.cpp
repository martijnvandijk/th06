#include <iostream>
#include "PracticalSocket.h"
#include "websocket.h"
#include "broadcaster.h"
#include <thread>
using namespace std;

Broadcaster mc;

class MyListener:public WebSocketListener {
public:
	void onTextMessage(const string& s, WebSocket* ws) {
		mc.broadcast(s);
	}
	
	void onClose(WebSocket* ws) {
		mc.remove(ws);
		delete ws;
	}
};

MyListener ml;

void runserver() {
	try {
		// Make a socket to listen for client connections.
		TCPServerSocket servSock(2222);
		cout << "server running: " << servSock.getLocalAddress().getAddress() << endl;
		for (;;) {                         
			TCPSocket *sock = servSock.accept();
			WebSocket *ws = new WebSocket(sock);
			ws->setListener(&	ml);
			mc.add(ws);
		}
	} catch (SocketException &e) {
		cerr << e.what() << endl;           // Report errors to the console
	}
}

int main(int argc, char **argv) {
	thread serverthread(runserver);
	serverthread.join();
}
