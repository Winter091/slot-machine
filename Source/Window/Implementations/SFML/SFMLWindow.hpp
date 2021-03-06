#ifndef _SFML_WINDOW_H_
#define _SFML_WINDOW_H_

#include <Source/Window/IWindow.hpp>
#include "SFMLButton.hpp"
#include "SFMLSlotsView.hpp"
#include <SFML/Graphics.hpp>
#include <Source/Events/Implementations/ButtonEvent.hpp>

#include <cstddef>
#include <memory>

class SFMLWindow final : public IWindow
{
public:
    SFMLWindow(uint32_t width, uint32_t height, const char* title);
    SFMLWindow(SFMLWindow&) = delete;
    SFMLWindow& operator=(SFMLWindow&) = delete;
    virtual ~SFMLWindow() override {}

    virtual bool IsOpen() override;
    virtual void Update() override;
    virtual void OnEvent(const IEvent& event) override;
    virtual void Render(const SlotMachine& slotMachine) override;

private:
    uint32_t m_width;
    uint32_t m_height;
    std::unique_ptr<sf::RenderWindow> m_sfmlWindow;

    std::unique_ptr<SFMLButton> m_startButton;
    std::unique_ptr<SFMLButton> m_stopButton;
    std::unique_ptr<SFMLButton> m_winMessageButton;
    std::unique_ptr<SFMLSlotsView> m_slotsView;

    static sf::String s_winMessage;
    static sf::String s_loseMessage;

    EButtonType m_currentActiveButton;

    void SetWinLoseMessage(const SlotMachine& slotMachine);
    void DispatchButtonPressEvent(const sf::Event& event);
    bool IsButtonPressed(EButtonType buttonType);
};

#endif
