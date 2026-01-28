#pragma once
#include <thread>
#include <rpc/server.h>
#include "rpc/this_handler.h"
#include <libSMngr.h>
#include "rpc/this_server.h"
#include "SessionStateItem.h"
#include "ServerBalSession.h"

class ServerBal
{
public:
    ServerBal(uint16_t hostPort) : srv{hostPort}
    {
        rpcServerBind();
        
        serverBalSession.rpcServerBind(&srv);
        serverBalSession.rpcServerBindCounterExampleServer(&srv);
    }

    void rpcServerBind()
    {
        srv.bind("add", [](double a, double b)
                 { return add(a, b); });
        srv.bind("stop", []()
                 { rpc::this_server().stop(); });
        srv.bind("getUuid", []()
                 { return getUuid(); });
    }

    void start()
    {
        srv.run();
    }

    void startAsync()
    {
        std::size_t thread_count = std::thread::hardware_concurrency();
        srv.async_run(thread_count);
    }

private:
    rpc::server srv;
    ServerBalSession serverBalSession;
    
};