#include "SessionStateItem.h"
#include "utils.h"

void SessionStateItem::setExpiredAt(int msFromNow){
    if (msFromNow == -1) {
        _expiredAt = -1;
    }else {
        _expiredAt =  currentUtcTime() + msFromNow;
    }

}
