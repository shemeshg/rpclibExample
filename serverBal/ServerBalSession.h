#pragma once
#include <libSMngr.h>
#include "CounterExampleServer.h"
#include <rpc/server.h>
#include <rpc/this_handler.h>
#include "CounterExampleServerSession.h"
class ServerBalSession
{
public:
    explicit ServerBalSession(rpc::server *srv) : counterExampleServerSession{srv, &sessionMutex, &sessionState}
    {
        rpcServerBind(srv);
    }
    virtual ~ServerBalSession() {}

private:
    CounterExampleServerSession counterExampleServerSession;

    void rpcServerBind(rpc::server *srv)
    {
        srv->bind("sessionStateErase",
                  [this](const std::string &uuid)
                  {
                      std::lock_guard<std::mutex> lock(sessionMutex);
                      auto it = sessionState.find(uuid);
                      if (it != sessionState.end())
                      {
                          sessionState.erase(it);
                      }
                      // We dont throw exceptionif not found because it might have been destroid because of timeout
                  });
        srv->bind("sessionStateCleanup", [this]()
                  { 
                    std::lock_guard<std::mutex> lock(sessionMutex);
                    sessionStateCleanup(); });
    }

    void sessionStateCleanup()
    {
        for (auto it = sessionState.begin(); it != sessionState.end();)
        {
            SessionStateItem *base = it->second.get(); // stored pointer

            if (!base)
            {
                throw std::runtime_error(
                    "Unexpected: session '" + it->first +
                    "' contains a null SessionStateItem pointer");
            }

            const auto exp = base->expiredAt();
            if (exp != -1 && exp < currentUtcTime())
            {
                it = sessionState.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    sessionItemMapType sessionState;

    std::mutex sessionMutex;
};