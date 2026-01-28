#pragma once
#include "libSMngr.h"

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