#ifndef _SFMLWINDOW_H_
#define _SFMLWINDOW_H_

#include <src/Window/IWindow.hpp>

class SFMLWindow final : public IWindow
{
    virtual void DispatchEvents() override;

    virtual bool IsClosed() override;
    virtual bool IsStartButtonPressed() override;
    virtual bool IsStopButtonPressed() override;

    virtual void Render(const SlotRows& slotRows) override;
};

#endif
