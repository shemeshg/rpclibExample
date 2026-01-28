#pragma once
#include <libSMngr.h>
#include "CounterExampleServer.h"
#include <rpc/server.h>
#include <rpc/this_handler.h>
#include "CounterExampleServerSession.h"
class ServerBalSession
{
public:
    explicit ServerBalSession(rpc::server *srv){
        rpcServerBind(srv);
        counterExampleServerSession.rpcServerBind(srv, &sessionMutex , &sessionState);
    }
    virtual ~ServerBalSession(){}
    
    
    
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
            bool erase = false;

            std::visit([&](auto &item)
                       {
        SessionStateItem* base = dynamic_cast<SessionStateItem*>(&item);
        if (!base) {
            throw std::runtime_error(
                "Unexpected: session '" + it->first +
                "' does not contain SessionStateItem"
            );
        }

        if (base->expiredAt() < currentUtcTime() && base->expiredAt() != -1) {
            erase = true;
        } }, it->second);

            if (erase)
                it = sessionState.erase(it);
            else
                ++it;
        }
    }

    std::unordered_map<
        std::string,
        std::variant<CounterExampleServer>>
        sessionState;


    std::mutex sessionMutex;
};