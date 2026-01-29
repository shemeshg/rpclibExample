#pragma once
#include <rpc/server.h>
#include <rpc/this_handler.h>
#include "CounterExampleServerSession.h"

class ServerBalSession
{
public:
    explicit ServerBalSession(rpc::server *srv);
    virtual ~ServerBalSession() {}

private:
    CounterExampleServerSession counterExampleServerSession;

    void rpcServerBind(rpc::server *srv);

    void sessionStateCleanup();

    sessionItemMapType sessionState;

    std::mutex sessionMutex;
};
