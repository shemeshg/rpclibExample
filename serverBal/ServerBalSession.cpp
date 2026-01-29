#include "ServerBalSession.h"
#include "utils.h"

ServerBalSession::ServerBalSession(rpc::server *srv) : counterExampleServerSession{srv, &sessionMutex, &sessionState}
{
    rpcServerBind(srv);
}

void ServerBalSession::rpcServerBind(rpc::server *srv)
{
    srv->bind("sessionStateErase",
              [this](const std::string &uuid)
              {
                  std::lock_guard<std::mutex> lock(sessionMutex);
                  auto it = sessionState.find(uuid);
                  if (it != sessionState.end())
                  {
                      sessionState.erase(it);
                  }
                  // We dont throw exceptionif not found because it might have been destroid because of timeout
              });
    srv->bind("sessionStateCleanup", [this]()
              {
                  std::lock_guard<std::mutex> lock(sessionMutex);
                  sessionStateCleanup(); });
}

void ServerBalSession::sessionStateCleanup()
{
    for (auto it = sessionState.begin(); it != sessionState.end();)
    {
        SessionStateItem *base = it->second.get(); // stored pointer

        if (!base)
        {
            throw std::runtime_error(
                "Unexpected: session '" + it->first +
                "' contains a null SessionStateItem pointer");
        }

        const auto exp = base->expiredAt();
        if (exp != -1 && exp < currentUtcTime())
        {
            it = sessionState.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
