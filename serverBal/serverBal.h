#pragma once
#include <rpc/server.h>
#include "ServerBalSession.h"
namespace SvrRpc
{
    class ServerBal
    {
    public:
        ServerBal(uint16_t hostPort);

        void rpcServerBind();

        void start();

        void startAsync();

    private:
        rpc::server srv;
        ServerBalSession serverBalSession;
    };
}