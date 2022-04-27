#include "SFMLSlotsView.hpp"

#include "SFMLSlot.hpp"
#include <cmath>
#include "SFMLButton.hpp"

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
    // int slotsInRowToRender = static_cast<int>(rectSize.y / slotDrawWidth + 1);

    for (std::size_t i = 0; i < slotRows.size(); i++) {
        const auto& slotRow = slotRows[i];
        const auto& slots = slotRow.GetSlots();
        
        float slotSize = 1.0f / slots.size();

        float currPosX = rectPos.x + i * slotDrawWidth;

        float toTopLen = slotDrawWidth * (slotRow.DistanceToSlotTop(slotRow.GetPosition()) / slotSize);
        int centerIndex = slotRow.IndexFromPosition(slotRow.GetPosition());

        float centerY = rectPos.y + rectSize.y / 2.0f - toTopLen;
        float currY = centerY;
        int currIndex = centerIndex;
        while (currY > rectPos.y) {
            currY -= slotDrawWidth;
            currIndex = (currIndex + 1) % slots.size();
        }

        float topY = currY;

        for (int j = 0; currY < rectPos.y + rectSize.y; j++) {
            SFMLSlot slot(
                sf::Vector2f(slotDrawWidth, slotDrawWidth)
            );

            sf::Vector2f pos(currPosX, currY);
            sf::Color color = GetColor(slots[currIndex].GetType());

            SFMLButton button(
                sf::FloatRect(pos, sf::Vector2f(slotDrawWidth, slotDrawWidth)),
                std::to_string(currIndex)
            );
            target.draw(button);

            // slot.Draw(target, pos, color);

            currY = topY + (j + 1) * slotDrawWidth;

            currIndex--;
            if (currIndex < 0) {
                currIndex += slots.size();
            }
            currIndex %= slots.size();
        }
    }

    target.draw(m_boundingRect);
}
