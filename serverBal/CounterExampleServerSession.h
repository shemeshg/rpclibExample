#pragma once

#include <rpc/server.h>
#include <rpc/this_handler.h>
#include "CounterExampleServer.h"

class CounterExampleServerSession
{
public:
    explicit CounterExampleServerSession(rpc::server *srv, std::mutex *sessionMutex,
                                         sessionItemMapType
                                             *sessionState)
    {
        rpcServerBind(srv, sessionMutex, sessionState);
    }

    ~CounterExampleServerSession() {}

private:
    void rpcServerBind(rpc::server *srv, std::mutex *sessionMutex,
                       sessionItemMapType
                           *sessionState)
    {
        srv->bind("CounterExampleServerinit", [sessionMutex, sessionState](std::string uuid, int initialValue)
                  { 
                    std::lock_guard<std::mutex> lock(*sessionMutex);
                    sessionState->emplace(uuid, std::make_unique<CounterExampleServer>(initialValue)); });
        srv->bind("CounterExampleServerExpiredAt",
                  [this, sessionState](const std::string &uuid, int val)
                  {
                      try
                      {
                          if (auto *ptr = dynamic_cast<CounterExampleServer *>(getSessionObj(sessionState, uuid)))
                          {
                              ptr->setExpiredAt(val);
                          }
                      }
                      catch (const std::exception &e)
                      {
                          rpc::this_handler().respond_error(
                              std::make_tuple(11, e.what()));
                      }
                  });
        srv->bind("CounterExampleServerAdd",
                  [this, sessionState](const std::string &uuid, int val)
                  {
                      try
                      {
                          auto *ptr = dynamic_cast<CounterExampleServer *>(getSessionObj(sessionState, uuid));
                          if (ptr)
                          {
                              ptr->add(val);
                          }
                      }
                      catch (const std::exception &e)
                      {
                          rpc::this_handler().respond_error(
                              std::make_tuple(11, e.what()));
                      }
                  });
        srv->bind("CounterExampleServerGet",
                  [this, sessionState](const std::string &uuid)
                  {
                      CounterExampleServer *ptr = nullptr;
                      try
                      {
                          ptr = dynamic_cast<CounterExampleServer *>(getSessionObj(sessionState, uuid));
                      }
                      catch (const std::exception &e)
                      {
                          rpc::this_handler().respond_error(
                              std::make_tuple(11, e.what()));
                      }
                      return ptr->get();
                  });
    }

private:
    SessionStateItem *getSessionObj(
        sessionItemMapType *sessionState,
        const std::string &uuid)
    {
        auto it = sessionState->find(uuid);
        if (it == sessionState->end())
        {
            throw std::runtime_error("Unexpected: session '" + uuid + "' not found");
        }

        return it->second.get(); // extract raw pointer from unique_ptr
    }
};