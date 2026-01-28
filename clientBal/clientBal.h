#pragma once
#include <rpc/client.h>
#include <rpc/rpc_error.h>

#include "AsyncData.h"
#include "CounterExample.h"


class ClientBal
{
public:
    ClientBal(const ClientBal&) = delete;
    ClientBal& operator=(const ClientBal&) = delete;
    ClientBal(std::string hostName, uint16_t hostPort) : c{hostName, hostPort}
    {
        setClientTimeout(60000);
    }

    void setClientTimeout(int i){
        c.set_timeout(i);
    }

    template <typename T>
    AsyncData<T> add(T a, T b)
    {
        validateConnection();
        std::future<RPCLIB_MSGPACK::object_handle> a_future = c.async_call("add", a, b);
        AsyncData<T> ad(std::move(a_future));
        return ad;
    }

    void serverStop()
    {
        validateConnection();
        c.call("stop");
    }

    void sessionStateCleanup(){
        validateConnection();
        c.call("sessionStateCleanup");        
    }

    std::unique_ptr<CounterExample> getCounterExample(int initialValue){
        validateConnection();
        return std::make_unique<CounterExample>(&c, initialValue);
    }

private:
    rpc::client c;

    const int initialTimeToConnect = 500;
    void validateConnection()
    {
        if (c.get_connection_state() == rpc::client::connection_state::connected)
        {
            return;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(std::chrono::milliseconds(initialTimeToConnect));
        if (c.get_connection_state() != rpc::client::connection_state::connected)
        {
            throw rpc::system_error(std::make_error_code(std::errc::connection_aborted),
                                    "Client disconnected");
        }
    }
};