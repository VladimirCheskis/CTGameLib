#ifndef MIVEACTIONS_H
#define MIVEACTIONS_H

#include "GameSprite.h"

class SpriteActionMove : public SpriteAction
{
public:
    SpriteActionMove(const GameSpritePtr& sprite, float x, float y, float time);

    bool isEnded() const override {return m_isEnded;}
    bool isBackground() const override {return m_isEnded;}
    void tick(GameScene& scene) override;
    virtual GameActionPtr createCopy() const override;
protected:
    virtual void start(GameScene& scene, float curTime);
    void setEndPosition(const Point& endPosition)
        { m_endPosition = endPosition; }
    float getDuration() const
        { return m_duration; }
private:
    void step(float curTime);
    void moveSprite(const Point& point);

    Point m_endPosition;
    float m_duration;
    Point m_startPosition;
    float m_endTime = 0;
    float m_startTime = 0;
    bool  m_isStarted = false;
    bool  m_isEnded = false;
};
DEFINE_STD(SpriteActionMove);

class SpriteActionMoveToMouse : public SpriteActionMove
{
public:
   SpriteActionMoveToMouse(const GameSpritePtr& sprite, float time);
    virtual GameActionPtr createCopy() const override;
protected:
    virtual void start(GameScene& scene, float curTime) override;
};
DEFINE_STD(SpriteActionMoveToMouse);

class SpriteActionMoveByVector : public SpriteActionMove
{
public:
    SpriteActionMoveByVector(const GameSpritePtr& sprite, float dx, float dy, float time);
    SpriteActionMoveByVector(const GameSpritePtr& sprite, const Vector& delta, float time);
    virtual GameActionPtr createCopy() const override;
protected:
    virtual void start(GameScene& scene, float curTime) override;
private:
    Vector m_delta;
};
DEFINE_STD(SpriteActionMoveToMouse);

class SpriteActionMoveToSprite : public SpriteActionMove
{
public:
    SpriteActionMoveToSprite(const GameSpritePtr& sprite, const GameSpritePtr& targetSprite, float time);
    virtual GameActionPtr createCopy() const override;
protected:
    virtual void start(GameScene& scene, float curTime) override;

    GameSpriteWeakPtr m_targetSprite;
};
DEFINE_STD(SpriteActionMoveToMouse);

#endif // MIVEACTIONS_H
