#pragma once

#include "../global/global.h"
#include "../interface/interface.h"
#include "../net/net_socket.h"



class MAC_NODE
{
public:
    MAC_NODE() {}
    MAC_NODE(int nodeid);
    ~MAC_NODE() {}
private:
    bool registerNet();
private:
    unsigned char nodeID;
    NET_SOCKET* netSocketDevice;
    INF_PHY_MAC bufferFromPhysical;
    INF_PHY_MAC bufferToPhysical;
    INF_NET_MAC bufferFromNet;
    INF_NET_MAC bufferToNet;

// junior interface
public:
    INF_PHY_MAC* getBufferFromPhysical();
    INF_PHY_MAC* getBufferToPhysical();
    INF_NET_MAC* getBufferFromNet();
    INF_NET_MAC* getBufferToNet();

// senior interface
public:
    void sendMessageToPhysical();
    void receiveMessageFromPhysical();
    void sendMessageToNet();
    void receiveMessageToNet();

// global run
public:
    void run();

};




