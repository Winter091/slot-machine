#include "SFMLSlot.hpp"

SFMLSlot::SFMLSlot(const sf::Vector2f& size)
{
    m_rect.setSize(size);
    m_rect.setOutlineThickness(5.0f);
    m_rect.setOutlineColor(sf::Color::Yellow);
}

sf::Color GetColor(ESlotType type)
{
    switch (type)
    {
        case ESlotType::ONE:
            return sf::Color::Red;
        case ESlotType::TWO:
            return sf::Color::Green;
        case ESlotType::THREE:
            return sf::Color::Blue;
        default:
            return sf::Color::Magenta;
    }
}

void SFMLSlot::Draw(sf::RenderTarget& target, const sf::Vector2f& pos, const sf::Color& color)
{
    m_rect.setPosition(pos);
    m_rect.setFillColor(color);
    target.draw(m_rect);
}
