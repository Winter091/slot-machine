#include "EventQueue.hpp"


void EventQueue::AddEvent(std::unique_ptr<IEvent> event)
{
    EventQueue& instance = GetInstance();
    instance.m_events.push(std::move(event));
}

std::unique_ptr<IEvent> EventQueue::GetNextEvent()
{
    EventQueue& instance = GetInstance();
    
    if (instance.m_events.empty()) {
        return nullptr;
    }

    std::unique_ptr<IEvent> event = std::move(instance.m_events.front());
    instance.m_events.pop();
    return event;
}

EventQueue& EventQueue::GetInstance()
{
    static EventQueue instance;
    return instance;
}
