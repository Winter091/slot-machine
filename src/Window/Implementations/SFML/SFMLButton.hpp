#ifndef _SFMLBUTTON_H_
#define _SFMLBUTTON_H_

#include <SFML/Graphics.hpp>

class SFMLButton : public sf::Drawable
{
public:
    SFMLButton(sf::Vector2f pos, sf::Vector2f size, const char* text);
    virtual ~SFMLButton() override {}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool TestHit(sf::Vector2i point) const;

private:
    sf::RectangleShape m_rect;
    sf::Font m_textFont;
    sf::Text m_text;
};

#endif