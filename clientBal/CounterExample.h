#pragma once
#include "ClientSession.h"
namespace ClntRpc
{


    class CounterExample: public ClientSession
    {
    public:
        // no copy contr
        CounterExample(const CounterExample &) = delete;
        CounterExample &operator=(const CounterExample &) = delete;

        explicit CounterExample(rpc::client *c, int initialValue) : ClientSession{c}
        {
            c->call(rpcConsts::CounterExample::initUniq, uuid, initialValue);
        }
        void add(int i)
        {
            c->call(rpcConsts::CounterExample::addUniq, uuid, i);
        }

        void setExpiredAt(int i)
        {
            c->call(rpcConsts::CounterExample::setExpiredAtUniq, uuid, i);
        }

        int get()
        {
            return c->call(rpcConsts::CounterExample::getUniq, uuid).as<int>();
        }

        virtual ~CounterExample()
        {            
        }
    };
}