#include "CounterExampleServerSession.h"
#include "CounterExampleServer.h"

CounterExampleServerSession::CounterExampleServerSession(rpc::server *srv, std::mutex *sessionMutex, sessionItemMapType *sessionState)
{
    rpcServerBind(srv, sessionMutex, sessionState);
}

void CounterExampleServerSession::rpcServerBind(rpc::server *srv, std::mutex *sessionMutex, sessionItemMapType *sessionState)
{
    srv->bind("CounterExampleServerinit", [sessionMutex, sessionState](std::string uuid, int initialValue)
              {
                  std::lock_guard<std::mutex> lock(*sessionMutex);
                  sessionState->emplace(uuid, std::make_unique<CounterExampleServer>(initialValue)); });
    srv->bind("CounterExampleServerExpiredAt",
              [this, sessionState](const std::string &uuid, int val)
              {
                  try
                  {
                      if (auto *ptr = dynamic_cast<CounterExampleServer *>(getSessionStateItemObj(sessionState, uuid)))
                      {
                          ptr->setExpiredAt(val);
                      }
                  }
                  catch (const std::exception &e)
                  {
                      rpc::this_handler().respond_error(
                          std::make_tuple(11, e.what()));
                  }
              });
    srv->bind("CounterExampleServerAdd",
              [this, sessionState](const std::string &uuid, int val)
              {
                  try
                  {
                      auto *ptr = dynamic_cast<CounterExampleServer *>(getSessionStateItemObj(sessionState, uuid));
                      if (ptr)
                      {
                          ptr->add(val);
                      }
                  }
                  catch (const std::exception &e)
                  {
                      rpc::this_handler().respond_error(
                          std::make_tuple(11, e.what()));
                  }
              });
    srv->bind("CounterExampleServerGet",
              [this, sessionState](const std::string &uuid)
              {
                  CounterExampleServer *ptr = nullptr;
                  try
                  {
                      ptr = dynamic_cast<CounterExampleServer *>(getSessionStateItemObj(sessionState, uuid));
                  }
                  catch (const std::exception &e)
                  {
                      rpc::this_handler().respond_error(
                          std::make_tuple(11, e.what()));
                  }
                  return ptr->get();
              });
}


