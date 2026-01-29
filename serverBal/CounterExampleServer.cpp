#include "CounterExampleServer.h"

namespace SvrRpc
{
    void CounterExampleServer::add(int i)
    {
        this->val += i;
    }

    int CounterExampleServer::get()
    {
        return this->val;
    }
}