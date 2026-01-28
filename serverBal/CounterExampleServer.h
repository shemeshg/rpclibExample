#pragma once
#include "SessionStateItem.h"
class CounterExampleServer: public SessionStateItem {
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