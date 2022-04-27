#ifndef _SFMLSLOTSVIEW_H_
#define _SFMLSLOTSVIEW_H_

#include <SFML/Graphics.hpp>
#include <src/Slots/SlotRow.hpp>
#include <vector>

class SFMLSlotsView
{
public:
    SFMLSlotsView(const sf::FloatRect& boundingRect);

    void Draw(sf::RenderTarget& target, const std::vector<SlotRow>& slotRows) const;

private:
    sf::RectangleShape m_boundingRect;
};

#endif