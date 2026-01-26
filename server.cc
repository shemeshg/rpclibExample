#include <rpc/server.h>
#include <libSMngr.h>

int main() {
    rpc::server srv(8080);

    
    srv.bind("add", [](double a, double b) { return add(a,b); });
    
    srv.run();

    return 0;
}