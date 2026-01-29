#pragma once

#include <rpc/server.h>
#include <rpc/this_handler.h>
#include "SessionStateItem.h"
namespace SvrRpc
{
    class CounterExampleServerSession
    {
    public:
        explicit CounterExampleServerSession(rpc::server *srv, std::mutex *sessionMutex,
                                             sessionItemMapType
                                                 *sessionState);

        ~CounterExampleServerSession() {}

    private:
        void rpcServerBind(rpc::server *srv, std::mutex *sessionMutex,
                           sessionItemMapType
                               *sessionState);
    };
}