#include "SFMLSlot.hpp"

SFMLSlot::SFMLSlot(const sf::Vector2f& size, const sf::Texture& texture)
{
    m_sprite.setTexture(texture);
    m_sprite.setScale(sf::Vector2f(
        size.x / texture.getSize().x,
        size.y / texture.getSize().y
    ));
}

void SFMLSlot::Draw(sf::RenderTarget& target, const sf::Vector2f& pos)
{
    m_sprite.setPosition(pos);
    target.draw(m_sprite);
}
