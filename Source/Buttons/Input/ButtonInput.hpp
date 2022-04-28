#ifndef _BUTTONINPUT_H_
#define _BUTTONINPUT_H_

#include <queue>

#include <Source/Buttons/Events/ButtonEvent.hpp>
#include <Source/Window/IWindow.hpp>

class ButtonInput
{
public:
    static void HandleWindowEvents(IWindow* window);
    static bool GetNextEvent(ButtonEvent& outEvent);

private:
    ButtonInput() = default;
    ButtonInput(const ButtonInput&) = delete;
    ButtonInput& operator=(const ButtonInput&) = delete;
    
    static ButtonInput& GetInstance();

    std::queue<ButtonEvent> m_buttonEvents;
};

#endif