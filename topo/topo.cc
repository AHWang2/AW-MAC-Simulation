#include "topo.h"

using namespace std;

vector<vector<bool>> topoTable;
unsigned short topoType;

void topoInit()
{
    switch(topoType)
    {
        case 0:
            FULL_LINK;
            break;
        case 1:
            CHAIN_LINK;
            break;
        case 2:
            NO_LINK;
            break;
        case 3:
            LOOP_LINK;
            break;
        default:
            FULL_LINK;
            break;
    }

    return;
}

