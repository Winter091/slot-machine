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

    m_slotsView = std::make_unique<SFMLSlotsView>(sf::FloatRect(50, 50, 450, 450));
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

bool SFMLWindow::IsStartButtonPressed()
{
    /*
    static bool alreadyPressed = false;
    
    bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
    bool res = !alreadyPressed && pressed;
    alreadyPressed = pressed;
    return res;
    */

    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_sfmlWindow);
    bool hit = m_startButton->TestHit(mousePos);

    return hit && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool SFMLWindow::IsStopButtonPressed()
{
    /*
    static bool alreadyPressed = false;
    
    bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::G);
    bool res = !alreadyPressed && pressed;
    alreadyPressed = pressed;
    return res;
    */
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_sfmlWindow);
    bool hit = m_endButton->TestHit(mousePos);

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