#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Common.h>
class GameScene;
using Point = sf::Vector2f;
using Vector = sf::Vector2f;

class GameSprite;
DEFINE_STD(GameSprite);

class GameObject
{
    public:
        GameObject() = default;
        virtual ~GameObject() {}

        virtual void tick(GameScene&) {}
        virtual void draw(GameScene&) {}
        virtual bool isEnded() const {return false;}

        virtual int getZOrder() const {return 0;}

        virtual bool needLeftButtonDown() const {return false;}
        virtual bool onLeftButtonDown(int, int, GameScene&) {return false;}
};
DEFINE_STD(GameObject);

#endif // GAMEOBJECT_H
