#include "message_queue.h"

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

void MESSAGE_QUEUE::registerMac()
{
    return;
}

void MESSAGE_QUEUE::run()
{
    return;
}

