#pragma once
#include <unordered_map>
namespace SvrRpc
{
    class SessionStateItem
    {
    public:
        explicit SessionStateItem() {}

        void setExpiredAt(int msFromNow);

        const long long expiredAt()
        {
            return _expiredAt;
        }

        virtual ~SessionStateItem() {}

    private:
        long long _expiredAt = -1;
    };

    using sessionItemMapType = std::unordered_map<
        std::string,
        std::unique_ptr<SessionStateItem>>;

    SessionStateItem *getSessionStateItemObj(
        sessionItemMapType *sessionState,
        const std::string &uuid);
}