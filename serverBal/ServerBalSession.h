#pragma once
#include <libSMngr.h>
#include "CounterExampleServer.h"
#include <rpc/server.h>

class ServerBalSession
{
public:
    void rpcServerBind(rpc::server *srv, std::mutex *sessionMutex){
        srv->bind("sessionStateErase",
                 [this, sessionMutex](const std::string &uuid)
                 {
                     std::lock_guard<std::mutex> lock(*sessionMutex);
                     auto it = sessionState.find(uuid);
                     if (it != sessionState.end())
                     {
                         sessionState.erase(it);
                     }
                     // We dont throw exceptionif not found because it might have been destroid because of timeout
                 });
        srv->bind("sessionStateCleanup", [this, sessionMutex]()
                 { 
                    std::lock_guard<std::mutex> lock(*sessionMutex);
                    sessionStateCleanup(); });                 
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

private:
};