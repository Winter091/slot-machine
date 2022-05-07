#ifndef _IEVENT_H_
#define _IEVENT_H_

#include "EEventType.hpp"

class IEvent
{
public:
    virtual EEventType GetEventType() const = 0;

    virtual ~IEvent() {}
};

#endif 