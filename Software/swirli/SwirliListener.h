//
// Created by martijn on 1/21/16.
//

#ifndef SWIRLI_SWIRLILISTENER_H
#define SWIRLI_SWIRLILISTENER_H

#include "WebInterfaceHandler.h"

class SwirliListener : public WebSocketListener {
public:
    SwirliListener(WebInterfaceHandler &webInterfaceHandler);

    void onTextMessage(const string &s, WebSocket *ws);

    void onClose(WebSocket *ws);

private:
    WebInterfaceHandler &webInterfaceHandler;
};




#endif //SWIRLI_SWIRLILISTENER_H
