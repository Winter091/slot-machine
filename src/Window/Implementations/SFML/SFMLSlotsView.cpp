#include "SFMLSlotsView.hpp"

#include "SFMLSlot.hpp"
#include <cmath>
#include "SFMLButton.hpp"
#include <src/Utils.hpp>

void SFMLSlotsView::LoadTextures()
{
    sf::Texture texture;
    texture.setSmooth(true);

    texture.loadFromFile("Resources/SlotTextures/apple.png");
    m_slotTextures[ESlotType::APPLE] = texture;

    texture.loadFromFile("Resources/SlotTextures/glemon.png");
    m_slotTextures[ESlotType::GLEMON] = texture;

    texture.loadFromFile("Resources/SlotTextures/heart.png");
    m_slotTextures[ESlotType::HEART] = texture;

    texture.loadFromFile("Resources/SlotTextures/redberry.png");
    m_slotTextures[ESlotType::RED_BERRY] = texture;

    texture.loadFromFile("Resources/SlotTextures/bar.png");
    m_slotTextures[ESlotType::BAR] = texture;

    texture.loadFromFile("Resources/SlotTextures/bell.png");
    m_slotTextures[ESlotType::BELL] = texture;

    texture.loadFromFile("Resources/SlotTextures/seven.png");
    m_slotTextures[ESlotType::SEVEN] = texture;

    texture.loadFromFile("Resources/SlotTextures/vinegar.png");
    m_slotTextures[ESlotType::VINEGAR] = texture;

    texture.loadFromFile("Resources/SlotTextures/watermelon.png");
    m_slotTextures[ESlotType::WATERMELON] = texture;
}

SFMLSlotsView::SFMLSlotsView(const sf::FloatRect& boundingRect)
{
    m_boundingRect.setSize(sf::Vector2f(boundingRect.width, boundingRect.height));
    m_boundingRect.setPosition(sf::Vector2f(boundingRect.left, boundingRect.top));

    auto transparentColor = sf::Color(255, 0, 0, 0);
    m_boundingRect.setFillColor(transparentColor);
    m_boundingRect.setOutlineColor(sf::Color::Black);
    m_boundingRect.setOutlineThickness(2.0f);

    m_centerRowRect.setFillColor(transparentColor);
    m_centerRowRect.setOutlineColor(sf::Color::Black);
    m_centerRowRect.setOutlineThickness(-5.0f);

    m_texture.create(boundingRect.width, boundingRect.height);

    m_sprite.setPosition(boundingRect.left, boundingRect.top);
    m_sprite.setTexture(m_texture.getTexture());

    LoadTextures();
}

void SFMLSlotsView::Draw(sf::RenderTarget& target, const std::vector<SlotRow>& slotRows)
{
    const auto& rectSize = m_boundingRect.getSize();
    const auto& rectPos = m_boundingRect.getPosition();

    float slotDrawWidth = rectSize.x / slotRows.size();

    // Render to texture in order not to draw slots out of bounds
    m_texture.setActive(true);
    m_texture.clear();

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
            sf::Texture& texture = m_slotTextures.at(slots[currIndex].GetType());
            SFMLSlot slot(sf::Vector2f(slotDrawWidth, slotDrawWidth), texture);
            sf::Vector2f pos(currPosX - rectPos.x, currPosY - rectPos.y);
            slot.Draw(m_texture, pos);

            currPosY = topPosY + (j + 1) * slotDrawWidth;
            currIndex = WrapInt(currIndex - 1, 0, slots.size() - 1);
        }
    }

    m_texture.display();
    target.draw(m_sprite);

    m_centerRowRect.setSize({rectSize.x, slotDrawWidth});
    m_centerRowRect.setOrigin({rectSize.x / 2.0f, slotDrawWidth / 2.0f});
    m_centerRowRect.setPosition({
        rectPos.x + rectSize.x / 2.0f, 
        rectPos.y + rectSize.y / 2.0f});
    target.draw(m_centerRowRect);
    
    target.draw(m_boundingRect);
}
