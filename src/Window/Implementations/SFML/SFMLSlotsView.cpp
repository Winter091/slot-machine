#include "SFMLSlotsView.hpp"

#include "SFMLSlot.hpp"
#include <cmath>
#include "SFMLButton.hpp"
#include <src/Utils.hpp>

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
    const auto& rectSize = m_boundingRect.getSize();
    const auto& rectPos = m_boundingRect.getPosition();

    float slotDrawWidth = rectSize.x / slotRows.size();

    for (std::size_t i = 0; i < slotRows.size(); i++) {
        const auto& slotRow = slotRows[i];
        const auto& slots = slotRow.GetSlots();
        
        float currPosX = rectPos.x + i * slotDrawWidth;
        float slotSize = 1.0f / slots.size();

        float toTopLen = slotDrawWidth * (slotRow.DistanceToSlotTop(slotRow.GetPosition()) / slotSize);
        float centerPosY = rectPos.y + rectSize.y / 2.0f - toTopLen;
        float currPosY = centerPosY;

        int centerIndex = slotRow.IndexFromPosition(slotRow.GetPosition());
        int currIndex = centerIndex;
        
        // Find top tile y pos and index
        while (currPosY > rectPos.y) {
            currPosY -= slotDrawWidth;
            currIndex = WrapInt(currIndex + 1, 0, slots.size() - 1);
        }

        float topPosY = currPosY;

        for (int j = 0; currPosY < rectPos.y + rectSize.y; j++) {
            SFMLSlot slot(sf::Vector2f(slotDrawWidth, slotDrawWidth));
            sf::Vector2f pos(currPosX, currPosY);
            sf::Color color = GetColor(slots[currIndex].GetType());
            slot.Draw(target, pos, color);

            currPosY = topPosY + (j + 1) * slotDrawWidth;
            currIndex = WrapInt(currIndex - 1, 0, slots.size() - 1);
        }
    }

    target.draw(m_boundingRect);
}
