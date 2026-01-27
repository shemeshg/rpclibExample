#pragma once
#include <rpc/client.h>

template <typename T>
class AsyncData { 
    public:
    explicit AsyncData(std::future<RPCLIB_MSGPACK::object_handle>&& fut) : 
    a_future(std::move(fut)) 
    {}

    T get(){
       return a_future.get().template as<T>();
    }

    private:
    std::future<RPCLIB_MSGPACK::object_handle> a_future;
};

class ClientBal {
    public:
    ClientBal(std::string hostName, uint16_t hostPort):c{hostName, hostPort}{        
    }

    template <typename T>
    AsyncData<T> add(T a, T b){        
        std::future<RPCLIB_MSGPACK::object_handle> a_future = c.async_call("add", a, b);
        AsyncData<T> ad(std::move(a_future));
        return ad;
    }
    
    void serverStop() {
        c.call("stop");
    }

    private:
        rpc::client c;
}; 