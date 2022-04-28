#include "SFMLWindow.hpp"

#include <iostream>

SFMLWindow::SFMLWindow(uint32_t width, uint32_t height, const char* title)
    : m_width(width)
    , m_height(height)
{
    sf::VideoMode mode(width, height);
    m_sfmlWindow = std::make_unique<sf::RenderWindow>(mode, title, sf::Style::Close);
    m_sfmlWindow->setVerticalSyncEnabled(true);

    m_startButton = std::make_unique<SFMLButton>(
        sf::FloatRect(m_width - 250, 50, 200, 50), "Start");

    m_endButton = std::make_unique<SFMLButton>(
        sf::FloatRect(m_width - 250, 150, 200, 50), "End");

    m_slotsView = std::make_unique<SFMLSlotsView>(
        sf::FloatRect(50, 50, m_height - 100, m_height - 100));
}

SFMLWindow::~SFMLWindow()
{
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
            hit = m_endButton->TestHit(mousePos);
            break;
        default:
            throw std::out_of_range("Can't handle provided buttonType");
    }

    return hit && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void SFMLWindow::Render(const SlotMachine& slotMachine)
{
    m_sfmlWindow->clear(sf::Color::White);

    m_sfmlWindow->draw(*m_startButton);
    m_sfmlWindow->draw(*m_endButton);
    m_slotsView->Draw(*m_sfmlWindow, slotMachine.GetRows());

    m_sfmlWindow->display();
}