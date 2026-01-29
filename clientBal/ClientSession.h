#pragma once
#include <rpc/client.h>
#include "sharedConst.h"

namespace ClntRpc
{
    class ClientSession
    {
    public:
        explicit ClientSession(rpc::client *c) : c{c}, uuid{c->call(rpcConsts::getUuid).as<std::string>()}
        {
        }

        virtual ~ClientSession()
        {
            c->call(rpcConsts::sessionStateErase, uuid);
        }

    protected:
        rpc::client *c;
        std::string uuid;
    };
}