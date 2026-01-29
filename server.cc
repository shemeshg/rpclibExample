#include <serverBal.h>

int main() {
    SvrRpc::ServerBal srv{8080};
    
    srv.start();

    return 0;
}