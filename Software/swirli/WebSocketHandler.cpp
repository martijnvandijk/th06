#include <networking/PracticalSocket.h>
#include <networking/websocket.h>
#include "WebSocketHandler.h"
#include "WebSocketPacket.h"


WebSocketHandler::WebSocketHandler(int port, WebInterfaceHandler &web, SwirliListener &listener) :
        port{port},
        listener(listener) { }

void WebSocketHandler::runServer() {
    try {
        // Make a socket to listen for client connections.
        TCPServerSocket servSock(port);
        std::cout << "server running: " << servSock.getLocalAddress().getAddress() << std::endl;
        for (; ;) {
            TCPSocket *sock = servSock.accept();
            WebSocket *ws = new WebSocket(sock);
            ws->setListener(&listener);
        }
    } catch (SocketException &e) {
        std::cerr << e.what() << std::endl;           // Report errors to the console
    }
}

std::thread WebSocketHandler::spawnWebSocketHandler() {
    return std::thread([this] { this->runServer(); });
}
