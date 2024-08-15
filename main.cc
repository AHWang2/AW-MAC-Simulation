#include "message_queue/message_queue.h"
#include "mac/mac_node.h"
#include "net/net_socket.h"


static unsigned short nodeAmount;
static unsigned short topoType;
static vector<thread> threadLine;

int main()
{
    cout << "input the node amount: ";
    cin >> nodeAmount;
    cout << "input the topo type: ";
    cin >> topoType;
    
    MESSAGE_QUEUE messageQueue;

    for(int i = 0; i < nodeAmount; i++)
    {
        MAC_NODE node = MAC_NODE(i);
        messageQueue.registerMac();
        threadLine.emplace_back(&MAC_NODE::run, &node);
    }
    // thread
    threadLine.emplace_back(&MESSAGE_QUEUE::run, &messageQueue);
    for(auto& t : threadLine)
    {
        if(t.joinable())
            t.join();
    }

    for(;;); sleep(1);
    return 0;
}