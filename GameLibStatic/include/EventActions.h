#pragma once

#include "GameSprite.h"
#include "SpriteCollisions.h"

class IOnEventAction : public GameAction
{
public:

    void addAction(const GameActionPtr& action);

    virtual bool isEnded() const override;
    virtual bool isBackground() const override;

    virtual void tick(GameScene& scene) override;

    void setIsRepeatable(bool is) {m_isRepeatable = is;}
    bool getIsRepeatable() const { return m_isRepeatable;}

protected:
    virtual bool isTrigger(GameScene& scene) = 0;
    void copyTo(IOnEventAction* dst) const;
private:
    GameActionList m_actions;
    GameActionList m_patterns;
    bool           m_wereActionsStarted = false;
    bool           m_isRepeatable = false;
    size_t         m_runCount = 0;
};
DEFINE_STD(IOnEventAction);


class WaitAction : public IOnEventAction
{
public:
    WaitAction(float waitTime);
    virtual bool isTrigger(GameScene& scene) override;
    virtual GameActionPtr createCopy() const override;
private:
    GameActionList m_actions;
    float          m_waitTime = 0;
    float          m_waitingEndTime = 0;
    bool           m_wasWaitingStarted = false;
};
DEFINE_STD(WaitAction);

class OnSpriteMouseClickAction : public IOnEventAction
{
public:
    OnSpriteMouseClickAction(const GameSpritePtr& sprite);
    virtual bool isTrigger(GameScene& scene) override;
    virtual GameActionPtr createCopy() const override;
    virtual void tick(GameScene& scene) override;

    virtual bool needLeftButtonDown() const override;
    virtual void onLeftButtonDown(const sf::Color&) override;
private:
    GameSpriteWeakPtr m_sprite;
    bool              m_mouseCliked = false;
};
DEFINE_STD(OnSpriteMouseClickAction);

class OnSpriteCollsionAction : public IOnEventAction
{
public:
    OnSpriteCollsionAction(const GameSpritePtr& sprite, const GameSpritePtr& other);
    virtual bool isTrigger(GameScene& scene) override;
    virtual GameActionPtr createCopy() const override;
private:
    GameSpriteWeakPtr m_sprite;
    GameSpriteWeakPtr m_other;
    SpriteCollisionPtr m_collision;
};
DEFINE_STD(OnSpriteCollsionAction);

class OnKeyPressedAction : public IOnEventAction
{
public:

    using Key = sf::Keyboard::Key;

    OnKeyPressedAction(Key key);
    virtual bool isTrigger(GameScene& scene) override;
    virtual GameActionPtr createCopy() const override;
private:
    bool m_wasPressedOnPrevTick = false;
    Key m_key;
};
DEFINE_STD(OnKeyPressedAction);
