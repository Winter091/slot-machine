#include "SFMLSlotsView.hpp"

SFMLSlotsView::SFMLSlotsView(const sf::FloatRect& boundingRect)
{
    m_boundingRect.setSize(sf::Vector2f(boundingRect.width, boundingRect.height));
    m_boundingRect.setPosition(sf::Vector2f(boundingRect.left, boundingRect.top));

    auto transparentColor = sf::Color(255, 0, 0, 0);
    m_boundingRect.setFillColor(transparentColor);
    m_boundingRect.setOutlineColor(sf::Color::Black);
    m_boundingRect.setOutlineThickness(2.0f);
}

void SFMLSlotsView::Draw(sf::RenderTarget& target, const std::vector<SlotRow>& slotRows) const
{
    (void)slotRows;
    target.draw(m_boundingRect);
}
