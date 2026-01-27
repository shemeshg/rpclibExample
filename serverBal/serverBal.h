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
        srv.bind("CounterExampleServerinit", [this](std::string uuid, int initialValue)
                 { sessionState.emplace(uuid, CounterExampleServer(initialValue)); });
        srv.bind("CounterExampleServerAdd",
                 [this](const std::string &uuid, int val) -> void
                 {
                     auto ptr = getSessionObj<CounterExampleServer>(uuid);
                     ptr->add(val);
                 });
        srv.bind("CounterExampleServerGet",
                 [this](const std::string &uuid, int val) -> int
                 {
                     auto ptr = getSessionObj<CounterExampleServer>(uuid);
                     return ptr->get();
                 });
        srv.bind("eraseSessionState",
                 [this](const std::string &uuid)
                 {
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