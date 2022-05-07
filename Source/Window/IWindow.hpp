#ifndef _IWINDOW_H_
#define _IWINDOW_H_

#include <Source/Slots/SlotMachine.hpp>
#include <Source/Events/Implementations/ButtonEvent.hpp>

class IWindow
{
public:
    virtual void HandleEvents() = 0;

    virtual bool IsClosed() = 0;
    virtual bool IsButtonPressed(EButtonType buttonType) = 0;

    virtual void Render(const SlotMachine& SlotMachine) = 0;

    virtual ~IWindow() {};

private:
};

#endif