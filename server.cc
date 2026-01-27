#include <serverBal.h>

int main() {
    ServerBal srv{8080};
    
    srv.run();

    return 0;
}