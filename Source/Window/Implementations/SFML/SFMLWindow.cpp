#include "SFMLWindow.hpp"

#include <Source/Config.hpp>
#include <Source/Events/EventQueue.hpp>
#include <Source/Events/Implementations/StateChangedEvent.hpp>

#include <iostream>


sf::String SFMLWindow::s_winMessage = cfg::WIN_MESSAGE;
sf::String SFMLWindow::s_loseMessage = cfg::LOSE_MESSAGE;


SFMLWindow::SFMLWindow(uint32_t width, uint32_t height, const char* title)
    : m_width(width)
    , m_height(height)
    , m_currentActiveButton(EButtonType::Start)
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

void SFMLWindow::Update()
{
    sf::Event event;
    while (m_sfmlWindow->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_sfmlWindow->close();
                break;
            case sf::Event::MouseButtonPressed:
                DispatchButtonPressEvent(event);
                break;
            default:
                break;
        }
    }
}

void SFMLWindow::OnEvent(const IEvent& event)
{
    if (event.GetEventType() != EEventType::StateChanged) {
        return;
    }

    const auto& stateEvent = dynamic_cast<const StateChangedEvent&>(event);
    
    if (stateEvent.GetNewState() == EStateName::ShowResults) {
        m_startButton->SetIsActive(false);
        m_stopButton->SetIsActive(false);
        m_winMessageButton->SetIsActive(true);
    } else {
        m_startButton->SetIsActive(true);
        m_stopButton->SetIsActive(true);
        m_winMessageButton->SetIsActive(false);
    }
}

bool SFMLWindow::IsOpen()
{
    return m_sfmlWindow->isOpen();
}

void SFMLWindow::Render(const SlotMachine& slotMachine)
{
    m_sfmlWindow->clear(sf::Color::White);

    SetWinLoseMessage(slotMachine);
    if (slotMachine.GetCurrentState() == EStateName::ShowResults) {
        m_sfmlWindow->draw(*m_winMessageButton);
        m_sfmlWindow->display();
        return;
    }

    const auto& pressColor = sf::Color(178, 13, 192);
    const auto& usualColor = sf::Color(36, 130, 234);

    const auto isActive = [this](EButtonType button, EButtonType activeButton) {
        return (button == activeButton && IsButtonPressed(button));
    };

    m_startButton->SetFillColor(isActive(EButtonType::Start, m_currentActiveButton) ? pressColor : usualColor);
    m_stopButton->SetFillColor(isActive(EButtonType::Stop, m_currentActiveButton) ? pressColor : usualColor);

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

void SFMLWindow::DispatchButtonPressEvent(const sf::Event& event)
{
    if (event.mouseButton.button != sf::Mouse::Button::Left) {
        return;
    }

    for (EButtonType buttonType : { EButtonType::Start, EButtonType::Stop, EButtonType::WinMessage }) {
        if (IsButtonPressed(buttonType)) {
            m_currentActiveButton = buttonType;
            EventQueue::AddEvent(std::unique_ptr<IEvent>(new ButtonEvent(buttonType, EButtonAction::Press)));
            return;
        }
    }
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
        case EButtonType::WinMessage:
            hit = m_winMessageButton->TestHit(mousePos);
            break;
        default:
            throw std::out_of_range("Can't handle provided buttonType");
    }

    return hit && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}