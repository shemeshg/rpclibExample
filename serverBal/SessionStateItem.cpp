#include "SessionStateItem.h"
#include "utils.h"

void SessionStateItem::setExpiredAt(int msFromNow){
    if (msFromNow == -1) {
        _expiredAt = -1;
    }else {
        _expiredAt =  currentUtcTime() + msFromNow;
    }

}

SessionStateItem *getSessionStateItemObj(sessionItemMapType *sessionState, const std::string &uuid)
{
    auto it = sessionState->find(uuid);
    if (it == sessionState->end())
    {
        throw std::runtime_error("Unexpected: session '" + uuid + "' not found");
    }

    return it->second.get(); // extract raw pointer from unique_ptr
}