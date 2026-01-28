#pragma once
#include <string>
#include <iostream>

long long  currentUtcTime();

class SessionStateItem {
    public:
    explicit SessionStateItem(){}

    void setExpiredAt(int msFromNow){
        if (msFromNow == -1) {
            _expiredAt = -1;
        }else {
            _expiredAt =  currentUtcTime() + msFromNow;
        }
        
    }

    const long long  expiredAt(){
        return _expiredAt;
    }


    virtual ~SessionStateItem(){}

    private:
        long long _expiredAt =  -1;
    
};

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

int add(int a, int b);

std::string getUuid();