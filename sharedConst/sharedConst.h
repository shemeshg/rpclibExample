#pragma once

namespace rpcConsts {
    constexpr auto asyncAdd="add";
    constexpr auto serverStop = "serverStop";
    constexpr auto setClientTimeout ="setClientTimeout";
    constexpr auto getUuid = "getUuid";
    constexpr auto sessionStateCleanup = "sessionStateCleanup";
    constexpr auto sessionStateErase = "sessionStateErase";
    constexpr auto getCounterExample ="getCounterExample";
    
    namespace CounterExample {
        constexpr auto setExpiredAt = "setExpiredAt";
        constexpr auto setExpiredAtUniq ="CounterExampleServerExpiredAt";

        constexpr auto add = "add";
        constexpr auto addUniq = "CounterExampleServerAdd";

        constexpr auto get = "get";
        constexpr auto getUniq = "CounterExampleServerGet";

        constexpr auto initUniq = "CounterExampleServerinit";


    }
}