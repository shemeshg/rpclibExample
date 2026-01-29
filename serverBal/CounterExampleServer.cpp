#include "CounterExampleServer.h"


void CounterExampleServer::add(int i){
    this->val += i;
}

int CounterExampleServer::get(){
    return this->val;
}
