#include "SFMLButton.hpp"

#include <iostream>
#include <cstdlib>

SFMLButton::SFMLButton(sf::Vector2f pos, sf::Vector2f size, const char* text)
{
    m_rect = sf::RectangleShape(size);
    m_rect.setPosition(pos);
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
    m_text.setOrigin(-m_rect.getPosition());
}

void SFMLButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    (void)states;
    
    target.draw(m_rect);
    target.draw(m_text);
}

bool SFMLButton::TestHit(sf::Vector2i point) const
{
    const auto& rect = m_rect.getPosition();
    const auto& size = m_rect.getSize();

    const bool goodX = (point.x >= rect.x) && (point.x <= (rect.x + size.x));
    const bool goodY = (point.y >= rect.y) && (point.y <= (rect.y + size.y));

    return goodX && goodY;
}
