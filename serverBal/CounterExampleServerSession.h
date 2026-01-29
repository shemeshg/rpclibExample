#pragma once

#include <rpc/server.h>
#include <rpc/this_handler.h>
#include "SessionStateItem.h"

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

private:
    SessionStateItem *getSessionObj(
        sessionItemMapType *sessionState,
        const std::string &uuid);
};
