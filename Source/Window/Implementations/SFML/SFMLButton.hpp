#ifndef _SFML_BUTTON_H_
#define _SFML_BUTTON_H_

#include <SFML/Graphics.hpp>

class SFMLButton : public sf::Drawable
{
public:
    SFMLButton(const sf::FloatRect& rect, const sf::String& text);
    SFMLButton(const SFMLButton&) = delete;
    SFMLButton& operator=(const SFMLButton&) = delete;
    virtual ~SFMLButton() override {}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setFillColor(const sf::Color& color);
    void setTextColor(const sf::Color& color);

    bool TestHit(sf::Vector2i point) const;

private:
    sf::RectangleShape m_rect;
    sf::Font m_textFont;
    sf::Text m_text;
};

#endif