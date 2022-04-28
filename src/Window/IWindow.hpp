#ifndef _IWINDOW_H_
#define _IWINDOW_H_

#include <src/Slots/SlotMachine.hpp>
#include <src/Buttons/Events/EButtonType.hpp>

class IWindow
{
public:
    virtual void DispatchEvents() = 0;

    virtual bool IsClosed() = 0;
    virtual bool IsButtonPressed(EButtonType buttonType) = 0;

    virtual void Render(const SlotMachine& SlotMachine) = 0;

    virtual ~IWindow() {};

private:
};

#endif