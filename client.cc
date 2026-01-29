#include <iostream>
#include <clientBal.h>

int main() {
    ClntRpc::ClientBal cb("localhost",8080);


    std::cout << "add(2, 3) = ";
    auto five = cb.add<double>(2,3);
    std::cout << five.get() << std::endl;


    return 0;
}