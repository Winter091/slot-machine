#include "SFMLWindow.hpp"

#include <Source/Config.hpp>

#include <iostream>


sf::String SFMLWindow::s_winMessage = cfg::WIN_MESSAGE;
sf::String SFMLWindow::s_loseMessage = cfg::LOSE_MESSAGE;


SFMLWindow::SFMLWindow(uint32_t width, uint32_t height, const char* title)
    : m_width(width)
    , m_height(height)
{
    sf::VideoMode mode(width, height);
    m_sfmlWindow = std::make_unique<sf::RenderWindow>(mode, title, sf::Style::Close);
    m_sfmlWindow->setVerticalSyncEnabled(true);

    m_startButton = std::make_unique<SFMLButton>(
        sf::FloatRect(
            cfg::START_BUTTON_X, cfg::START_BUTTON_Y, 
            cfg::START_BUTTON_WIDTH, cfg::START_BUTTON_HEIGHT
        ), 
        "Start"
    );

    m_stopButton = std::make_unique<SFMLButton>(
        sf::FloatRect(
            cfg::STOP_BUTTON_X, cfg::STOP_BUTTON_Y, 
            cfg::STOP_BUTTON_WIDTH, cfg::STOP_BUTTON_HEIGHT
        ),
        "Stop"
    );

    m_winMessageButton = std::make_unique<SFMLButton>(
        sf::FloatRect(
            0, 0, cfg::WINDOW_WIDTH, cfg::WINDOW_HEIGHT
        ),
        ""
    );
    m_winMessageButton->SetFillColor(sf::Color(0, 0, 0, 0));
    m_winMessageButton->SetTextColor(sf::Color(0, 0, 0, 255));

    m_slotsView = std::make_unique<SFMLSlotsView>(sf::FloatRect(
        cfg::SLOTSVIEW_X, cfg::SLOTSVIEW_Y, 
        cfg::SLOTSVIEW_WIDTH, cfg::SLOTSVIEW_HEIGHT
    ));
}

void SFMLWindow::DispatchEvents()
{
    sf::Event event;
    while (m_sfmlWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_sfmlWindow->close();
        }
    }
}

bool SFMLWindow::IsClosed()
{
    return !m_sfmlWindow->isOpen();
}

bool SFMLWindow::IsButtonPressed(EButtonType buttonType)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_sfmlWindow);

    bool hit;
    switch (buttonType) {
        case EButtonType::Start:
            hit = m_startButton->TestHit(mousePos);
            break;
        case EButtonType::Stop:
            hit = m_stopButton->TestHit(mousePos);
            break;
        default:
            throw std::out_of_range("Can't handle provided buttonType");
    }

    return hit && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void SFMLWindow::Render(const SlotMachine& slotMachine)
{
    m_sfmlWindow->clear(sf::Color::White);

    if (slotMachine.GetCurrentState() == EStateName::ShowResults) {
        SetWinLoseMessage(slotMachine);
        m_sfmlWindow->draw(*m_winMessageButton);
        m_sfmlWindow->display();
        return;
    }

    const auto& pressColor = sf::Color(178, 13, 192);
    const auto& usualColor = sf::Color(36, 130, 234);
    m_startButton->SetFillColor(IsButtonPressed(EButtonType::Start) ? pressColor : usualColor);
    m_stopButton->SetFillColor(IsButtonPressed(EButtonType::Stop) ? pressColor : usualColor);

    m_sfmlWindow->draw(*m_startButton);
    m_sfmlWindow->draw(*m_stopButton);

    m_slotsView->Draw(*m_sfmlWindow, slotMachine.GetRows());

    m_sfmlWindow->display();
}

void SFMLWindow::SetWinLoseMessage(const SlotMachine& slotMachine)
{
    static EStateName prevState = EStateName::Idle;

    // Change text only once per state transition
    EStateName currState = slotMachine.GetCurrentState();
    if (currState == EStateName::ShowResults && currState != prevState) {
        m_winMessageButton->SetText(slotMachine.GetHasWon() ? s_winMessage : s_loseMessage);
    }

    prevState = currState;
}