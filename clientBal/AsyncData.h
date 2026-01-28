#pragma once
#include <rpc/rpc_error.h>
#include <future>

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