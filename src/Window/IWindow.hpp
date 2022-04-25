#ifndef _IWINDOW_H_
#define _IWINDOW_H_

#include <src/Slots/SlotRows.hpp>

class IWindow
{
public:
    virtual void DispatchEvents() = 0;

    virtual bool IsClosed() = 0;
    virtual bool IsStartButtonPressed() = 0;
    virtual bool IsStopButtonPressed() = 0;

    virtual void Render(const SlotRows& slotRows) = 0;
};

#endif