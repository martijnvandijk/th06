#ifndef SWIRLI_WEBSOCKETHANDLER_H
#define SWIRLI_WEBSOCKETHANDLER_H

#include "networking/websocket.h"
#include "WebInterfaceHandler.h"
#include "SwirliListener.h"
#include <iostream>

/**
 * @brief Handles the websocket protocol.
 * @details Passes messages on to a listener.
 * 
 */
class WebSocketHandler {
public:
	/**
	 * @brief Constructor
	 * 
	 * @param port The TCP port used to listen for websocket data. 
	 * @param listener The listener to pass the websockets to.
	 */
    WebSocketHandler(int port, SwirliListener &listener);

    /**
     * @brief Spawn a std::thread to handle the server in a separate thread.
     * @return The thread containing the websocket server.
     */
    std::thread spawnWebSocketHandler();
    
private:
    int port;
    void runServer();
    SwirliListener &listener;
};

#endif