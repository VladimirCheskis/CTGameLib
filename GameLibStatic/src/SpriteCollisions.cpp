#include "GameSprite.h"
#include "SpriteCollisions.h"

SpriteCollisionPtr SpriteCollisionCalculator::collision(const GameSpritePtr& a,
                                                        const GameSpritePtr& b)
{
    for (auto& w : m_collisions)
    {
        if (auto c = w.lock())
        {
           auto ca = c->a.lock();
           auto cb = c->b.lock();
           if ((ca == a && cb == b) || (cb == a && ca == b))
            return c;
        }
    }
    auto result = std::make_shared<SpriteCollision>(a, b);
    result->collisionDetected = a->hasCollision(*b);
    m_collisions.push_back(result);
    return result;
}

void SpriteCollisionCalculator::tick()
{
    if (m_collisions.empty())
        return;
    for (int i = int(m_collisions.size()) - 1; i >=0; --i)
    {
        if (auto c = m_collisions[i].lock())
        {
            auto a = c->a.lock();
            auto b = c->b.lock();
            if (a && b)
            {
                c->collisionDetected = a->hasCollision(*b);
                continue;
            }
        }
        m_collisions.erase(m_collisions.begin() + i);
    }
}

//-----------------------------------------------------------------------------
bool spriteColor(const sf::Sprite& sprite, const sf::Image& image, int screenX, int screenY, sf::Color& color)
{
   if (!sprite.getGlobalBounds().contains(screenX, screenY))
    return false;

   auto imageSize = image.getSize();
   auto& rect     = sprite.getTextureRect();

   auto& inverse = sprite.getInverseTransform();
   auto p0 = inverse.transformPoint(float(screenX), float(screenY));

   int x = round(p0.x);
   int y = round(p0.y);

   x += rect.left;
   y += rect.top;

   if (x < 0 || x > int(imageSize.x))
    return false;
   if (y < 0 || y > int(imageSize.y))
    return false;

   color = image.getPixel(x, y);
   return color.a > 0;
}

bool hasColor(const sf::Transform& inverse, const sf::Image& image, const sf::Vector2u &imageSize,
              const sf::IntRect& rect,  int screenX, int screenY)
{
   auto p0 = inverse.transformPoint(float(screenX), float(screenY));

   int x = round(p0.x);
   int y = round(p0.y);

   x += rect.left;
   y += rect.top;

   if (x < 0 || x > int(imageSize.x))
    return false;
   if (y < 0 || y > int(imageSize.y))
    return false;

   sf::Color color = image.getPixel(x, y);
   return color.a > 0;
}

bool GameSprite::hasCollision(const GameSprite& sprite) const
{
    if (!m_image.texture || !sprite.m_image.texture)
        return false;
    auto  agb = getGlobalBounds();
    auto  bgb = sprite.getGlobalBounds();
    sf::FloatRect intersection;
    if (!agb.intersects(bgb, intersection))
        return false;

   auto& aRect     = m_sprite.getTextureRect();
   auto& bRect     = sprite.m_sprite.getTextureRect();

   auto& aInverse = m_sprite.getInverseTransform();
   auto& bInverse = sprite.m_sprite.getInverseTransform();

   auto& aImage = m_image.texture->getImage();
   auto& bImage = sprite.m_image.texture->getImage();
   auto aImageSize = aImage.getSize();
   auto bImageSize = bImage.getSize();


   sf::IntRect ir;
   ir.left = std::floor(intersection.left);
   ir.top  = std::floor(intersection.top);
   ir.width = std::ceil(intersection.width);
   ir.height = std::ceil(intersection.height);

   for (auto x = ir.left; x < ir.left + ir.width; ++x)
   for (auto y = ir.top;  y < ir.top + ir.height; ++y)
   {
       if (hasColor(aInverse, aImage, aImageSize, aRect, x, y)
        && hasColor(bInverse, bImage, bImageSize, bRect, x, y))
       {
            return true;
       }
   }
   return false;
}
