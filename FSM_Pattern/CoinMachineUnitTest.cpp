#include <iostream>
#include "CoinMachineState.h"

using namespace std;
using namespace coinMachine;

int main()
{
    //TESTING THE FUNCTIONALITY
    CCoinMachine *coinMachine = new CCoinMachine;
    uint8_t count = 0;
    while (count <= 25)
    {
        coinMachine->placeCoin();
        count++;
    }
    return 0;

}
