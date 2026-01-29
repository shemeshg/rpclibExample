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
            c->call("CounterExampleServerinit", uuid, initialValue);
        }
        void add(int i)
        {
            c->call("CounterExampleServerAdd", uuid, i);
        }

        void setExpiredAt(int i)
        {
            c->call("CounterExampleServerExpiredAt", uuid, i);
        }

        int get()
        {
            return c->call("CounterExampleServerGet", uuid).as<int>();
        }

        virtual ~CounterExample()
        {            
        }
    };
}