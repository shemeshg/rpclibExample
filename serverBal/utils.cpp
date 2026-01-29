#include "utils.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <chrono>
namespace SvrRpc
{
    std::string getUuid()
    {
        boost::uuids::uuid id = boost::uuids::random_generator()();
        return to_string(id);
    }

    long long currentUtcTime()
    {
        return duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }
}