#pragma once
#include <thread>
#include <rpc/server.h>
#include <libSMngr.h>
#include "rpc/this_server.h"

class ServerBal
{
public:
    ServerBal(uint16_t hostPort) : srv{hostPort}
    {
        srv.bind("add", [](double a, double b)
                 { return add(a, b); });
        srv.bind("stop", []()
                 { rpc::this_server().stop(); });
        srv.bind("getUuid", []()
                 { return getUuid(); });
        srv.bind("CounterExampleServerinit", [this](std::string uuid, int initialValue)
                 { 
                    std::lock_guard<std::mutex> lock(sessionMutex);
                    sessionState.emplace(uuid, CounterExampleServer(initialValue)); 
                });
        srv.bind("CounterExampleServerAdd",
                 [this](const std::string &uuid, int val)
                 {
                     auto ptr = getSessionObj<CounterExampleServer>(uuid);
                     ptr->add(val);
                 });
        srv.bind("CounterExampleServerGet",
                 [this](const std::string &uuid)
                 {
                     auto ptr = getSessionObj<CounterExampleServer>(uuid);
                     return ptr->get();
                 });
        srv.bind("sessionStateErase",
                 [this](const std::string &uuid)
                 {
                    std::lock_guard<std::mutex> lock(sessionMutex);
                     auto it = sessionState.find(uuid);
                     if (it != sessionState.end())
                     {
                         sessionState.erase(it); // destructor of CounterExampleServer runs here
                     }
                     else
                     {
                         throw std::runtime_error("Session '" + uuid + "' not found");
                     }
                 });
        srv.bind("sessionStateCleanup", [this]()
                 { 
                    std::lock_guard<std::mutex> lock(sessionMutex);
                    sessionStateCleanup();
                 });
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

        if (base->expiredAt() < currentUtcTime()) {
            erase = true;
        } }, it->second);

            if (erase)
                it = sessionState.erase(it);
            else
                ++it;
        }
    }

private:
    rpc::server srv;
    std::mutex sessionMutex;
    std::unordered_map<
        std::string,
        std::variant<CounterExampleServer>>
        sessionState;

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
};