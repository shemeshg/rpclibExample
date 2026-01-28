#include "libSMngr.h"
#include <iostream>
#include <fstream>
#include <vector>

#include <chrono>
#include <iostream>

int main(int ac, char *av[])
{

    std::cout << getUuid() << "\n";

    //Date.now()
    using namespace std::chrono;

    auto jsTime = duration_cast<milliseconds>(
                           system_clock::now().time_since_epoch())
                           .count();

    std::cout << jsTime << std::endl;

    return 0;
}
