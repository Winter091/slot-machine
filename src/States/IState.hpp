#ifndef _ISTATE_H_
#define _ISTATE_H_

#include <src/Slots/SlotMachine.hpp>

class IState
{
public:
    virtual void Update(SlotMachine& slotMachine) = 0;

    virtual ~IState() {};
};

#endif