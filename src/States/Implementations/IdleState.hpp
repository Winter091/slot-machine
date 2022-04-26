#ifndef _IDLESTATE_H_
#define _IDLESTATE_H_

#include <src/States/IState.hpp>

class IdleState : public IState
{
public:
    virtual void Update(SlotMachine& slotMachine) override;

    virtual ~IdleState() override;
};

#endif