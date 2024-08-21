#include "message_queue.h"
#include "../topo/topo.h"

MESSAGE_QUEUE::MESSAGE_QUEUE()
{
    queueInit();
}

MESSAGE_QUEUE::~MESSAGE_QUEUE()
{
    return;
}

void MESSAGE_QUEUE::queueInit()
{
    while(!messageQueue.empty())
    {
        messageQueue.pop();
    }
    queueLength = 0;

    macNodeSet.clear();

    cout << "MessageQueue Init" << endl;
    
    return;
}

bool MESSAGE_QUEUE::messageTakeOut()
{
    return false;
}

bool MESSAGE_QUEUE::messagePushIn()
{
    return false;
}

void MESSAGE_QUEUE::registerMac(MAC_NODE* pNode)
{
    macNodeSet.insert(pNode);
    macNodeVector.push_back(pNode);
    return;
}

void MESSAGE_QUEUE::run()
{
    while(1)
    {
        // inspect every mac_node's buffer to phy first
        for(auto& nodeInstance : macNodeVector)
        {
            if(nodeInstance->getBufferToPhysical()->bufferState == INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_READY)
            {
                messageUnit temp;
                memcpy(nodeInstance->getBufferToPhysical()->buffer, temp.pbuffer, nodeInstance->getBufferToPhysical()->messageLength);
                temp.sourceNodeID = nodeInstance->getNodeID();
                temp.messageLength = nodeInstance->getBufferToPhysical()->messageLength;
                // i need to push time stamp here later
                // temp.smallSlotNumber = 
                // temp.largeFrameNumber = 

                messageQueue.push(temp);
            }
        }

        if(!messageQueue.empty())
        {
            messageUnit* temp = &messageQueue.front();
            for(int i = 0; i < nodeAmount; i++)
            {
                int srcNode = temp->sourceNodeID;
                if(i == srcNode) continue;

                if(topoTable[i][srcNode] == 1)
                {
                    if(macNodeVector[i]->getBufferFromPhysical()->bufferState = INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_IDLE)
                    {
                        memcpy(macNodeVector[i]->getBufferFromPhysical()->buffer, temp->pbuffer, temp->messageLength);
                        macNodeVector[i]->getBufferFromPhysical()->bufferState = INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_READY;
                        macNodeVector[i]->getBufferToPhysical()->messageLength = temp->messageLength;
                    }
                    else
                    {
                        macNodeVector[i]->getBufferToPhysical()->bufferState = INF_PHY_MAC_STATE::INF_PHY_MAC_STATE_ERROR;
                    }
                }
            }
            messageQueue.pop();
        }
    }
    return;
}

