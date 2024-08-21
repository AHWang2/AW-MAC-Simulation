#pragma once

#include "../global/global.h"

using namespace std;

extern vector<vector<bool>> topoTable;
extern unsigned short topoType;

#define FULL_LINK \
topoTable.resize(nodeAmount);       \
for ( int i = 0; i < nodeAmount - 1; i++)   \
{ \
    topoTable[i].resize(nodeAmount, 0);    \
    for(int j = i + 1; j < nodeAmount; j++)  \
    {   \
        topoTable[i][j] = 1;    \
    }   \
}

#define CHAIN_LINK \
topoTable.resize(nodeAmount);       \
for ( int i = 0; i < nodeAmount - 1; i++)   \
{ \
    topoTable[i].resize(nodeAmount, 0);    \
    for(int j = i + 1; j < nodeAmount; j++)  \
    {   \
        topoTable[i][j] = 1;    \
    }   \
}

#define LOOP_LINK \
topoTable.resize(nodeAmount);       \
for ( int i = 0; i < nodeAmount - 1; i++)   \
{ \
    topoTable[i].resize(nodeAmount, 0);    \
    for(int j = i + 1; j < nodeAmount; j++)  \
    {   \
        topoTable[i][j] = 1;    \
    }   \
}

#define NO_LINK \
topoTable.resize(nodeAmount);       \
for ( int i = 0; i < nodeAmount - 1; i++)   \
{ \
    topoTable[i].resize(nodeAmount, 0);    \
    for(int j = i + 1; j < nodeAmount; j++)  \
    {   \
        topoTable[i][j] = 1;    \
    }   \
}

void topoInit();

