#include "mac_node.h"

MAC_NODE::MAC_NODE(int nodeid) : nodeID(nodeid)
{
    registerNet();
}

bool MAC_NODE::registerNet()
{
    netSocketDevice = new NET_SOCKET(nodeID, this->getBufferFromNet(), this->getBufferToNet());
    return true;
}

INF_PHY_MAC* MAC_NODE::getBufferFromPhysical()
{
    return &bufferFromPhysical;
}

INF_PHY_MAC* MAC_NODE::getBufferToPhysical()
{
    return &bufferToPhysical;
}

INF_NET_MAC* MAC_NODE::getBufferFromNet()
{
    return &bufferFromNet;
}

INF_NET_MAC* MAC_NODE::getBufferToNet()
{
    return &bufferToNet;
}

void MAC_NODE::run()
{
    // first you need to run "routed"
    thread t(&NET_SOCKET::run, this->netSocketDevice);
    if(t.joinable())
        t.join();
    
    // running the mac protocol
    while(1)
    {
        // receive from physical and send it to net
        auto bufferFromPhy = getBufferFromPhysical();
        if(bufferFromPhy->bufferState == INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_READY)
        {
            if(getBufferToNet()->bufferState == INF_NET_MAC_STATE::INF_NET_MAC_STATE_IDLE)
            {
                getBufferToNet()->bufferState == INF_NET_MAC_STATE::INF_NET_MAC_STATE_READY;
                getBufferToNet()->messageLength = bufferFromPhy->messageLength;
                memcpy(getBufferToNet()->buffer, bufferFromPhy->buffer, bufferFromPhy->messageLength);
            }
        }

        // receive from net and send it to physical
        auto bufferFromNet = getBufferFromNet();
        if(bufferFromNet->bufferState == INF_NET_MAC_STATE::INF_NET_MAC_STATE_READY)
        {
            if(getBufferToPhysical()->bufferState == INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_IDLE)
            {
                getBufferToPhysical()->bufferState = INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_READY;
                getBufferToPhysical()->messageLength = bufferFromNet->messageLength;
                memcpy(getBufferToPhysical()->buffer, bufferFromNet->buffer, bufferFromNet->messageLength);
            }
        }
        
        // std::this_thread::sleep_for(std::chrono::miliseconds(200));
    }
    return;
}
