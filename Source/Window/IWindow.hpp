#ifndef _IWINDOW_H_
#define _IWINDOW_H_

#include <Source/Slots/SlotMachine.hpp>
#include <Source/Events/IEvent.hpp>

class IWindow
{
public:
    virtual bool IsOpen() = 0;
    virtual void Update() = 0;
    virtual void OnEvent(const IEvent& event) = 0;
    virtual void Render(const SlotMachine& SlotMachine) = 0;

    virtual ~IWindow() {};

private:
};

#endif