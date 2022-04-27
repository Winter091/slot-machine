#ifndef _SFMLWINDOW_H_
#define _SFMLWINDOW_H_

#include <src/Window/IWindow.hpp>
#include "SFMLButton.hpp"
#include "SFMLSlotsView.hpp"
#include <SFML/Graphics.hpp>

#include <cstddef>
#include <memory>

class SFMLWindow final : public IWindow
{
public:
    SFMLWindow(uint32_t width, uint32_t height, const char* title);
    virtual ~SFMLWindow() override;

    virtual void DispatchEvents() override;

    virtual bool IsClosed() override;
    virtual bool IsButtonPressed(EButtonType buttonType) override;

    virtual void Render(const SlotMachine& slotMachine) override;

private:
    uint32_t m_width;
    uint32_t m_height;
    std::unique_ptr<sf::RenderWindow> m_sfmlWindow;

    std::unique_ptr<SFMLButton> m_startButton;
    std::unique_ptr<SFMLButton> m_endButton;
    std::unique_ptr<SFMLSlotsView> m_slotsView;
};

#endif
