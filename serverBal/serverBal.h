#pragma once
#include <rpc/server.h>
#include <libSMngr.h>

class ServerBal {
    public:
    ServerBal(uint16_t hostPort):srv{hostPort}{     
        srv.bind("add", [](double a, double b) { return add(a,b); });   
    }

    void run(){
        srv.run();
    }
    
    private:
        rpc::server srv;
};