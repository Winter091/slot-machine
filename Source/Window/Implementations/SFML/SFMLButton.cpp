#include "SFMLButton.hpp"

#include <iostream>
#include <cstdlib>

SFMLButton::SFMLButton(const sf::FloatRect& rect, const sf::String& text)
{
    m_rect = sf::RectangleShape(sf::Vector2f(rect.width, rect.height));
    m_rect.setPosition(sf::Vector2f(rect.left, rect.top));
    m_rect.setFillColor(sf::Color::Black);
    m_rect.setOutlineThickness(0.0f);

    const char* path = "Resources/Fonts/arial.ttf";
    if (!m_textFont.loadFromFile(path)) {
        std::cerr << "Font is not found! (path: " << path << ")\n";
        std::exit(1);
    }

    m_text.setFont(m_textFont);
    m_text.setString(text);
    m_text.setCharacterSize(44);
    m_text.setFillColor(sf::Color::White);

    const auto& global = m_text.getGlobalBounds();
    m_text.setOrigin(sf::Vector2f(global.width / 2.0f, global.height / 1.3f));
    m_text.setPosition(m_rect.getPosition() + m_rect.getSize() / 2.0f);
}

void SFMLButton::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const
{
    target.draw(m_rect);
    target.draw(m_text);
}

void SFMLButton::setFillColor(const sf::Color& color)
{
    m_rect.setFillColor(color);
}

void SFMLButton::setTextColor(const sf::Color& color)
{
    m_text.setFillColor(color);
}

bool SFMLButton::TestHit(sf::Vector2i point) const
{
    const auto& rect = m_rect.getPosition();
    const auto& size = m_rect.getSize();

    const bool goodX = (point.x >= rect.x) && (point.x <= (rect.x + size.x));
    const bool goodY = (point.y >= rect.y) && (point.y <= (rect.y + size.y));

    return goodX && goodY;
}
