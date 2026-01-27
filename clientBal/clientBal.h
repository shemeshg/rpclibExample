#pragma once
#include <rpc/client.h>

class ClientBal {
    public:
    ClientBal(std::string hostName, uint16_t hostPort):c{hostName, hostPort}{        
    }

    double add(double a, double b){
        return c.call("add", 2, 3).as<double>();
    }
    
    private:
        rpc::client c;
};