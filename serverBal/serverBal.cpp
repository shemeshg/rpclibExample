#include "serverBal.h"

#include <thread>
#include "utils.h"
#include "rpc/this_server.h"
#include "sharedConst.h"

namespace SvrRpc
{
    ServerBal::ServerBal(uint16_t hostPort) : srv{hostPort}, serverBalSession{&srv}
    {
        rpcServerBind();
    }

    void ServerBal::rpcServerBind()
    {
        srv.bind(rpcConsts::asyncAdd, [](double a, double b)
                 { return (double)(a + b); });
        srv.bind(rpcConsts::serverStop, []()
                 { rpc::this_server().stop(); });
        srv.bind(rpcConsts::getUuid, []()
                 { return getUuid(); });
    }

    void ServerBal::start()
    {
        srv.run();
    }

    void ServerBal::startAsync()
    {
        std::size_t thread_count = std::thread::hardware_concurrency();
        srv.async_run(thread_count);
    }

}