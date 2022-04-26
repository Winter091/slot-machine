#include "SFMLWindow.hpp"

SFMLWindow::SFMLWindow(uint32_t width, uint32_t height, const char* title)
    : m_width(width)
    , m_height(height)
{
    sf::VideoMode mode(width, height);
    m_sfmlWindow = std::make_unique<sf::RenderWindow>(mode, title);
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
    return false;
}

bool SFMLWindow::IsStopButtonPressed()
{
    return false;
}

void SFMLWindow::Render(const SlotMachine& slotMachine)
{
    (void)slotMachine;

    const auto clearColor = sf::Color::Black;
    m_sfmlWindow->clear(clearColor);
    m_sfmlWindow->display();
}