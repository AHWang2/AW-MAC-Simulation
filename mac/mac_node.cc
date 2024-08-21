#include "mac_node.h"

MAC_NODE::MAC_NODE(int nodeid) : nodeID(nodeid)
{
    registerNet();

    bufferFromNet.bufferState = INF_NET_MAC_STATE::INF_NET_MAC_STATE_IDLE;
    bufferToNet.bufferState = INF_NET_MAC_STATE::INF_NET_MAC_STATE_IDLE;
    bufferFromPhysical.bufferState = INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_IDLE;
    bufferToPhysical.bufferState = INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_IDLE;
    
}

bool MAC_NODE::registerNet()
{
    netSocketDevice = new NET_SOCKET(nodeID, this->getBufferFromNet(), this->getBufferToNet());
    return true;
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
        auto tempBufferFromNet = getBufferFromNet();
        if(tempBufferFromNet->bufferState == INF_NET_MAC_STATE::INF_NET_MAC_STATE_READY)
        {
            if(getBufferToPhysical()->bufferState == INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_IDLE)
            {
                getBufferToPhysical()->bufferState = INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_READY;
                getBufferToPhysical()->messageLength = tempBufferFromNet->messageLength;
                memcpy(getBufferToPhysical()->buffer, tempBufferFromNet->buffer, tempBufferFromNet->messageLength);
            }
        }


        if(bufferFromNet.bufferState == INF_NET_MAC_STATE::INF_NET_MAC_STATE_ERROR)
            bufferFromNet.bufferState = INF_NET_MAC_STATE::INF_NET_MAC_STATE_IDLE;
        if(bufferToNet.bufferState == INF_NET_MAC_STATE::INF_NET_MAC_STATE_ERROR)
            bufferToNet.bufferState = INF_NET_MAC_STATE::INF_NET_MAC_STATE_IDLE;
        if(bufferFromPhysical.bufferState == INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_ERROR)
            bufferFromPhysical.bufferState = INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_IDLE;
        if(bufferToPhysical.bufferState == INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_ERROR)
            bufferToPhysical.bufferState = INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_IDLE;
        // std::this_thread::sleep_for(std::chrono::miliseconds(200));
    }
    return;
}
