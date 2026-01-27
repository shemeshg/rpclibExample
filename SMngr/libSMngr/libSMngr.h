#pragma once
#include <string>

class CounterExampleServer {
    public:
    explicit CounterExampleServer(int initialValue):val{initialValue}{

    }
    void add(int i){
        this->val += i;
    }

    int get(){
        return this->val;
    }

    private:
    int val;
};

int add(int a, int b);

std::string getUuid();