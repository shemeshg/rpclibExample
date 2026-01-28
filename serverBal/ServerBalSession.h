#pragma once
#include <libSMngr.h>
#include "CounterExampleServer.h"
#include <rpc/server.h>
#include <rpc/this_handler.h>

class ServerBalSession
{
public:
    explicit ServerBalSession(rpc::server *srv){
        rpcServerBind(srv);
        rpcServerBindCounterExampleServer(srv);
    }
    virtual ~ServerBalSession(){}
    private:

    

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

    void rpcServerBindCounterExampleServer(rpc::server *srv)
    {
        srv->bind("CounterExampleServerinit", [this](std::string uuid, int initialValue)
                  { 
                    std::lock_guard<std::mutex> lock(sessionMutex);
                    sessionState.emplace(uuid, CounterExampleServer(initialValue)); });
        srv->bind("CounterExampleServerExpiredAt",
                  [this](const std::string &uuid, int val)
                  {
                      CounterExampleServer *ptr = nullptr;
                      try
                      {
                          ptr = getSessionObj<CounterExampleServer>(uuid);
                          ptr->setExpiredAt(val);
                      }
                      catch (const std::exception &e)
                      {
                          rpc::this_handler().respond_error(
                              std::make_tuple(11, e.what()));
                      }
                  });
        srv->bind("CounterExampleServerAdd",
                  [this](const std::string &uuid, int val)
                  {
                      CounterExampleServer *ptr = nullptr;
                      try
                      {
                          ptr = getSessionObj<CounterExampleServer>(uuid);
                          ptr->add(val);
                      }
                      catch (const std::exception &e)
                      {
                          rpc::this_handler().respond_error(
                              std::make_tuple(11, e.what()));
                      }
                  });
        srv->bind("CounterExampleServerGet",
                  [this](const std::string &uuid)
                  {
                      CounterExampleServer *ptr = nullptr;
                      try
                      {
                          ptr = getSessionObj<CounterExampleServer>(uuid);
                      }
                      catch (const std::exception &e)
                      {
                          rpc::this_handler().respond_error(
                              std::make_tuple(11, e.what()));
                      }
                      return ptr->get();
                  });
    }

    template <typename T>
    T *getSessionObj(std::string uuid)
    {
        auto it = this->sessionState.find(uuid);
        if (it == sessionState.end())
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