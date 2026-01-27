#include <iostream>
#include <clientBal.h>

int main() {
    ClientBal cb("localhost",8080);


    std::cout << "add(2, 3) = ";
    double five = cb.add(2,3);
    std::cout << five << std::endl;


    return 0;
}