#pragma once

#include <iostream>
#include <cstring>
#include <sys/types.h> // For socket functions
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  
#include <string>
#include <fcntl.h> // 包含fcntl函数

#include "../global/global.h"
#include "../interface/interface.h"

using namespace std;

class NET_SOCKET
{
public:
    NET_SOCKET();
    NET_SOCKET(int nodeId, INF_NET_MAC* bufferFromMac, INF_NET_MAC* bufferToMac);
    ~NET_SOCKET();

private:
    unsigned char nodeID;

    int fdSocketFromApp;
    int fdSocketToApp;

    int portFromApp;
    int portToApp;

    string ipFromApp;
    string ipToApp;

    unsigned char* receiveBuffer[MAX_MESSAGE_LENGTH];
    unsigned char* sendBuffer[MAX_MESSAGE_LENGTH];

    int receiveLength;
    unsigned short sendLength;

    INF_NET_MAC* pBufferToMac;
    INF_NET_MAC* pBufferFromMac;

private:
    void initSocketFromApp();
    void initSocketToApp();
    void sendToMac();
    void sendToApp();

public:
    void run();

};
