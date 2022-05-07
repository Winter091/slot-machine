#ifndef _BUTTON_EVENT_H_
#define _BUTTON_EVENT_H_

#include <Source/Events/IEvent.hpp>
#include <cstdint>

enum class EButtonType : uint32_t
{
    Start = 0,
    Stop,
    WinMessage,
};

enum class EButtonAction : uint32_t
{
    Press = 0,
};

class ButtonEvent : public IEvent
{
public:
    ButtonEvent() = default;
    ButtonEvent(EButtonType type, EButtonAction action) : m_type(type), m_action(action) {};
    virtual ~ButtonEvent() {}

    virtual inline EEventType GetEventType() const { return EEventType::Button; }

    inline EButtonType GetButtonType() const { return m_type; }
    inline EButtonAction GetButtonAction() const { return m_action; }
private:
    EButtonType m_type;
    EButtonAction m_action;
};

#endif