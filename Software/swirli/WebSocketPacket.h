//
// Created by martijn on 1/20/16.
//

#ifndef SWIRLI_WEBSOCKETPACKET_H
#define SWIRLI_WEBSOCKETPACKET_H


#include <networking/websocket.h>
#include <rapidjson/document.h>

/**
 * @brief Used to pass data from websocket messages around.
 * 
 */
class WebSocketPacket {
public:
	/**
	 * @brief Constructor. 
	 * @details You know what to do.
	 * 
	 * @param json The JSON data
	 * @param ws The websocket where the data originated from.
	 */
    WebSocketPacket(const char *json, WebSocket *ws);

    /**
     * @brief Get the JSON document containing the packet data.
     * @details 
     * @return The rapidjson::Document instance.
     */
    rapidjson::Document &getDoc();

    /**
     * @brief Get the websocket that generated this packet
     * @details 
     * @return The websocket
     */
    WebSocket * getWebsocket();

private:
    rapidjson::Document doc;
    WebSocket *ws;
};


#endif //SWIRLI_WEBSOCKETPACKET_H
