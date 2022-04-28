#ifndef _SFMLSLOT_H_
#define _SFMLSLOT_H_

#include <SFML/Graphics.hpp>
#include <Source/Slots/Slot.hpp>

class SFMLSlot
{
public:
    SFMLSlot(const sf::Vector2f& size, const sf::Texture& texture);
    SFMLSlot(const SFMLSlot&) = delete;
    SFMLSlot& operator=(const SFMLSlot&) = delete;

    void Draw(sf::RenderTarget& target, const sf::Vector2f& pos);

private:
    sf::Sprite m_sprite;
};

#endif
