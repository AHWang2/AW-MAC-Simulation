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
    int fdSocketFromNet;
    int fdSocketToNet;

    int portFromNet;
    int portToNet;

    string ipFromNet;
    string ipToNet;

    unsigned char* receiveBuffer[MAX_MESSAGE_LENGTH];
    unsigned char* sendBuffer[MAX_MESSAGE_LENGTH];

    INF_NET_MAC* pBufferToMac;
    INF_NET_MAC* pBufferFromMac;

private:
    void initSocketFromNet();
    void initSocketToNet();

public:
    void run();

};
