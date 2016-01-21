#include <networking/PracticalSocket.h>
#include <networking/websocket.h>
#include "WebSocketHandler.h"
#include "WebSocketPacket.h"


WebSocketHandler::WebSocketHandler(int port, WebInterfaceHandler &web) :
        port{port},
        listener(web) {

}

void WebSocketHandler::runServer() {
    try {
        // Make a socket to listen for client connections.
        TCPServerSocket servSock(8081);
        cout << "server running: " << servSock.getLocalAddress().getAddress() << endl;
        for (; ;) {
            TCPSocket *sock = servSock.accept();
            WebSocket *ws = new WebSocket(sock);
            ws->setListener(&listener);
        }
    } catch (SocketException &e) {
        cerr << e.what() << endl;           // Report errors to the console
    }
}
