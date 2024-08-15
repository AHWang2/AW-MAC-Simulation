#include "net_socket.h"

NET_SOCKET::NET_SOCKET()
{
    return;
}

NET_SOCKET::NET_SOCKET(int nodeId, INF_NET_MAC* bufferFromMac, INF_NET_MAC* bufferToMac)
{
    portFromNet = nodeId + 7000;
    portToNet = nodeId + 8000;
    ipFromNet = "127.0.0.1";
    ipToNet = "127.0.0.1";

    pBufferFromMac = bufferFromMac;
    pBufferToMac = bufferToMac;

    initSocketFromNet();
    initSocketToNet();

    cout << "initNET_SOCKET" << endl;

    return;
}


NET_SOCKET::~NET_SOCKET()
{
    return;
}

void NET_SOCKET::initSocketFromNet()
{
    int flags;
    struct sockaddr_in server_addr;

    fdSocketFromNet = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portFromNet);
    server_addr.sin_addr.s_addr = inet_addr(ipFromNet.c_str()); // Bind to all available interfaces

    flags = fcntl(fdSocketFromNet, F_GETFL, 0);
    
    fcntl(fdSocketFromNet, F_SETFL, flags | O_NONBLOCK);

    bind(fdSocketFromNet, (struct sockaddr*)&server_addr, sizeof(server_addr));

    cout << "initSocketFromNet" << endl;
    return;
}

void NET_SOCKET::initSocketToNet()
{
    cout << "initSocketToNet" << endl;
}

void NET_SOCKET::run()
{
    return;
}
