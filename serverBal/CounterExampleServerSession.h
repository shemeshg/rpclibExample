#pragma once

#include <rpc/server.h>
#include <rpc/this_handler.h>
#include "CounterExampleServer.h"

class CounterExampleServerSession {
    public:
        explicit CounterExampleServerSession(rpc::server *srv, std::mutex *sessionMutex, 
            std::unordered_map<
        std::string,
        std::variant<CounterExampleServer>>
        *sessionState){
            rpcServerBind(srv, sessionMutex, sessionState);
        }

        ~CounterExampleServerSession(){}
    private:

      void rpcServerBind(rpc::server *srv, std::mutex *sessionMutex, 
            std::unordered_map<
        std::string,
        std::variant<CounterExampleServer>>
        *sessionState){
        srv->bind("CounterExampleServerinit", [sessionMutex, sessionState](std::string uuid, int initialValue)
                  { 
                    std::lock_guard<std::mutex> lock(*sessionMutex);
                    sessionState->emplace(uuid, CounterExampleServer(initialValue)); });
        srv->bind("CounterExampleServerExpiredAt",
                  [this, sessionState](const std::string &uuid, int val)
                  {
                      CounterExampleServer *ptr = nullptr;
                      try
                      {
                          ptr = getSessionObj<CounterExampleServer>(sessionState, uuid);
                          ptr->setExpiredAt(val);
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
                      CounterExampleServer *ptr = nullptr;
                      try
                      {
                          ptr = getSessionObj<CounterExampleServer>(sessionState, uuid);
                          ptr->add(val);
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
                          ptr = getSessionObj<CounterExampleServer>(sessionState, uuid);
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
    template <typename T>
    T *getSessionObj(std::unordered_map<
        std::string,
        std::variant<CounterExampleServer>>
        *sessionState, std::string uuid)
    {
        auto it = sessionState->find(uuid);
        if (it == sessionState->end())
        {
            throw std::runtime_error("Unexpected: session '" + uuid + "' not found");
        }
        auto &var = it->second;

        auto ptr = std::get_if<T>(&var);
        if (!ptr)
        {
            throw std::runtime_error("Unexpected: session '" + uuid +
                                     "' does not contain CounterExampleServer");
        }
        return ptr;
    }

};