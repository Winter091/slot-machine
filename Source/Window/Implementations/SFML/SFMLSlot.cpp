#include "SFMLSlot.hpp"

SFMLSlot::SFMLSlot(const sf::Vector2f& size, const sf::Texture& texture)
{
    m_sprite.setTexture(texture);

    // Make texture fill exactly 'size' space
    const auto& texSize = texture.getSize();
    m_sprite.setScale(sf::Vector2f(size.x / texSize.x, size.y / texSize.y));
}

void SFMLSlot::Draw(sf::RenderTarget& target, const sf::Vector2f& pos)
{
    m_sprite.setPosition(pos);
    target.draw(m_sprite);
}
