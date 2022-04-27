#ifndef _SFMLSLOTSVIEW_H_
#define _SFMLSLOTSVIEW_H_

#include <SFML/Graphics.hpp>
#include <src/Slots/SlotRow.hpp>
#include <vector>
#include <cstddef>

class SFMLSlotsView
{
public:
    SFMLSlotsView(const sf::FloatRect& boundingRect);

    void Draw(sf::RenderTarget& target, const std::vector<SlotRow>& slotRows);

private:
    sf::RectangleShape m_boundingRect;
    sf::RenderTexture m_texture;
    sf::Sprite m_sprite;
};

#endif