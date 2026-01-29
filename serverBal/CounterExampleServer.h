#pragma once
#include "SessionStateItem.h"

namespace SvrRpc
{
    class CounterExampleServer : public SessionStateItem
    {
    public:
        explicit CounterExampleServer(int initialValue) : val{initialValue}
        {
        }
        void add(int i);

        int get();

    private:
        int val;
    };
}
