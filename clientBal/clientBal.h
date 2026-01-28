#pragma once
#include <rpc/client.h>
#include <rpc/rpc_error.h>
template <typename T>
class AsyncData
{
public:
    explicit AsyncData(std::future<RPCLIB_MSGPACK::object_handle> &&fut) : a_future(std::move(fut))
    {
    }

    T get()
    {
        return a_future.get().template as<T>();
    }

private:
    std::future<RPCLIB_MSGPACK::object_handle> a_future;
};

class CounterExample {
    public:
    CounterExample(const CounterExample&) = delete;
    CounterExample& operator=(const CounterExample&) = delete;

    explicit CounterExample(rpc::client *c, int initialValue):
    c{c}, uuid{c->call("getUuid").as<std::string>()}
    {
        c->call("CounterExampleServerinit",uuid, initialValue);
    }
    void add(int i){
        c->call("CounterExampleServerAdd",uuid, i);
    }

    void setExpiredAt(int i){
        c->call("CounterExampleServerExpiredAt",uuid, i);
    }

    int get(){
        return c->call("CounterExampleServerGet", uuid).as<int>();
    }

    virtual ~CounterExample(){
        c->call("sessionStateErase",uuid);
    }

    private:
    rpc::client *c;
    std::string uuid;
};

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
        clientTimeout = i;
        c.set_timeout(clientTimeout);
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
    int clientTimeout = 1000;
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