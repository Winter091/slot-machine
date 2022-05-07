#ifndef _EVENT_QUEUE_H_
#define _EVENT_QUEUE_H_

#include <queue>
#include <memory>

#include <Source/Events/IEvent.hpp>

class EventQueue
{
public:
    EventQueue(const EventQueue&) = delete;
    EventQueue& operator=(const EventQueue&) = delete;

    static void AddEvent(std::unique_ptr<IEvent> event);
    static std::unique_ptr<IEvent> GetNextEvent();

private:
    std::queue<std::unique_ptr<IEvent>> m_events;

    EventQueue() = default;
    static EventQueue& GetInstance();
};

#endif