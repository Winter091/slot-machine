#ifndef _SFMLSLOT_H_
#define _SFMLSLOT_H_

#include <SFML/Graphics.hpp>
#include <src/Slots/Slot.hpp>

class SFMLSlot
{
public:
    SFMLSlot(const sf::Vector2f& size);

    void Draw(sf::RenderTarget& target, const sf::Vector2f& pos, const sf::Color& color);

private:
    sf::RectangleShape m_rect;
};

sf::Color GetColor(ESlotType type);

#endif
