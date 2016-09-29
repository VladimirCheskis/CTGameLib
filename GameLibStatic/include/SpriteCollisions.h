#pragma once


struct SpriteCollision
{
    SpriteCollision() = default;
    SpriteCollision(const GameSpritePtr& _a, const GameSpritePtr& _b) : a(_a), b(_b){}

    GameSpriteWeakPtr a, b;
    bool collisionDetected = false;
};
DEFINE_STD(SpriteCollision);


class SpriteCollisionCalculator
{
public:
    SpriteCollisionCalculator() = default;
    SpriteCollisionPtr collision(const GameSpritePtr& a, const GameSpritePtr& b);
    void tick();
private:
    using Collisions = std::vector<SpriteCollisionWeakPtr>;
    Collisions m_collisions;
};

bool spriteColor(const sf::Sprite& sprite, const sf::Image& image, int screenX, int screenY, sf::Color& color);
