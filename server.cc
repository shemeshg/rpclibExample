#include <serverBal.h>

int main() {
    ServerBal srv{8080};
    
    srv.start();

    return 0;
}