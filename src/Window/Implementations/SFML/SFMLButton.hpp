#ifndef _SFMLBUTTON_H_
#define _SFMLBUTTON_H_

#include <SFML/Graphics.hpp>

class SFMLButton : public sf::Drawable
{
public:
    SFMLButton(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::String& text);
    virtual ~SFMLButton() override {}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool TestHit(sf::Vector2i point) const;

private:
    sf::RectangleShape m_rect;
    sf::Font m_textFont;
    sf::Text m_text;
};

#endif