#include "net_socket.h"

NET_SOCKET::NET_SOCKET()
{
    return;
}

NET_SOCKET::NET_SOCKET(int nodeId, INF_NET_MAC* bufferFromMac, INF_NET_MAC* bufferToMac) : nodeID(nodeId)
{
    portFromApp = nodeID + 7000;
    portToApp = nodeID + 8000;
    ipFromApp = "127.0.0.1";
    ipToApp = "127.0.0.1";

    pBufferFromMac = bufferFromMac;
    pBufferToMac = bufferToMac;

    initSocketFromApp();
    initSocketToApp();

    cout << "initNET_SOCKET" << endl;

    return;
}

NET_SOCKET::~NET_SOCKET()
{
    return;
}

void NET_SOCKET::initSocketFromApp()
{
    int flags;
    struct sockaddr_in server_addr;

    fdSocketFromApp = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portFromApp);
    server_addr.sin_addr.s_addr = inet_addr(ipFromApp.c_str()); // Bind to all available interfaces

    flags = fcntl(fdSocketFromApp, F_GETFL, 0);
    
    fcntl(fdSocketFromApp, F_SETFL, flags | O_NONBLOCK);

    bind(fdSocketFromApp, (struct sockaddr*)&server_addr, sizeof(server_addr));

    cout << "initSocketFromNet" << endl;
    return;
}

void NET_SOCKET::initSocketToApp()
{
    cout << "initSocketToNet" << endl;
}

void NET_SOCKET::sendToMac()
{
    memcpy(pBufferToMac->buffer, receiveBuffer, receiveLength);
    pBufferToMac->messageLength = receiveLength;
    pBufferToMac->bufferState = INF_NET_MAC_STATE::INF_NET_MAC_STATE_IDLE;
    return;
}

void NET_SOCKET::sendToApp()
{
    struct sockaddr_in destSocket;
    destSocket.sin_family = AF_INET;
    destSocket.sin_port = htons(8000 + nodeID);
    destSocket.sin_addr.s_addr = inet_addr("127.0.0.1");

    memcpy(sendBuffer, pBufferFromMac->buffer, pBufferFromMac->messageLength);
    sendto(fdSocketToApp, sendBuffer, pBufferFromMac->messageLength, 0, (sockaddr*)&destSocket, sizeof destSocket);

    pBufferFromMac->bufferState == INF_NET_MAC_STATE::INF_NET_MAC_STATE_IDLE;
    return;
}

void NET_SOCKET::run()
{
    while(1)
    {
        receiveLength = 0;
        receiveLength = recvfrom(fdSocketFromApp, receiveBuffer, MAX_MESSAGE_LENGTH, MSG_DONTWAIT, NULL, NULL);
        if(receiveLength == -1)
            continue;

        while(pBufferToMac->bufferState == INF_NET_MAC_STATE::INF_NET_MAC_STATE_IDLE)
        {
            sendToMac();
        }

        if(pBufferFromMac->bufferState == INF_NET_MAC_STATE::INF_NET_MAC_STATE_READY)
        {
            sendToApp();
        }
    }
    return;
}
