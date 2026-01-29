#pragma once
#include <rpc/client.h>
namespace ClntRpc
{
    class CounterExample
    {
    public:
        CounterExample(const CounterExample &) = delete;
        CounterExample &operator=(const CounterExample &) = delete;

        explicit CounterExample(rpc::client *c, int initialValue) : c{c}, uuid{c->call("getUuid").as<std::string>()}
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
            c->call("sessionStateErase", uuid);
        }

    private:
        rpc::client *c;
        std::string uuid;
    };
}