#ifndef _STATE_CHANGED_EVENT_H_
#define _STATE_CHANGED_EVENT_H_

#include <Source/Events/IEvent.hpp>
#include <Source/States/EStateName.hpp>
#include <cstdint>

class StateChangedEvent : public IEvent
{
public:
    StateChangedEvent() = default;
    StateChangedEvent(EStateName oldState, EStateName newState) : m_old(oldState), m_new(newState) {};
    virtual ~StateChangedEvent() {}

    virtual inline EEventType GetEventType() const { return EEventType::StateChanged; }

    inline EStateName GetOldState() const { return m_old; }
    inline EStateName GetNewState() const { return m_new; }
private:
    EStateName m_old;
    EStateName m_new;
};

#endif