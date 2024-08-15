#pragma once
#include "../global/global.h"

namespace INF_PHY_MAC_STATE
{
    enum
    {
        INF_PHY_MAC_STATE_IDLE,
        INF_PHY_MAC_STATE_READY,
        INF_PHY_MAC_STATE_ERROR,
    };
};


struct INF_PHY_MAC
{
    unsigned char buffer[MAX_MESSAGE_LENGTH];
    unsigned short messageLength;
    unsigned char bufferState;
};

namespace INF_NET_MAC_STATE
{
    enum
    {
        INF_NET_MAC_STATE_IDLE,
        INF_NET_MAC_STATE_READY,
        INF_NET_MAC_STATE_ERROR,
    };
};


struct INF_NET_MAC
{
    unsigned char buffer[MAX_MESSAGE_LENGTH];
    unsigned short messageLength;
    unsigned char bufferState;
};