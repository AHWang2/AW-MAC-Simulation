#pragma once

#include "../mac/mac_node.h"
#include "../global/global.h"

struct messageUnit
{
    unsigned char sourceNodeID;
    unsigned char smallSlotNumber;
    unsigned short largeFrameNumber;
    unsigned short messageLength;
    unsigned char* pbuffer[MAX_MESSAGE_LENGTH];
};
#pragma once

class MESSAGE_QUEUE
{
public:
    MESSAGE_QUEUE();
    ~MESSAGE_QUEUE();

private:
    queue<messageUnit> messageQueue;
    unordered_set<MAC_NODE*> macNodeSet;
    vector<MAC_NODE*> macNodeVector;
    int queueLength;

private:
    void queueInit();

    messageUnit* getQueueFront()
    {
        if(messageQueue.empty()) 
            return nullptr;
        return &messageQueue.front();
    }
    
    void popQueueFront()
    {
        if(messageQueue.empty())
            return;

        messageQueue.pop();
        queueLength--;

        return;
    }

    messageUnit* getQueueTail()
    {
        if(messageQueue.empty())
            return nullptr;
        return &messageQueue.back();
    }

    unsigned int getQueueLength()
    {
        return queueLength;
    }

    bool isQueueEmpty()
    {
        return queueLength ? true : false;
    }

    void pushQueue(messageUnit messageUnit)
    {
        queueLength++;
        messageQueue.push(messageUnit);

        return;
    }

    bool messageTakeOut();
    bool messagePushIn();
    
// senior interface
public:
    void registerMac(MAC_NODE* node);
    
    void run();
};