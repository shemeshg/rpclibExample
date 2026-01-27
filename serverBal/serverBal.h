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
    }

    void start()
    {
        srv.run();
    }

    void startAsync(){
        std::size_t thread_count = std::thread::hardware_concurrency();
        srv.async_run(thread_count);
    }

private:
    rpc::server srv;
};